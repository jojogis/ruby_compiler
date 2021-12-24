
const SemanticConstantType = {
    Integer: 3,		// содержит константу - целое число
    Float: 4,		// содержит константу -  не целое число
    String: 8,		// содержит константу - строка  (CONSTANT_Utf8)
    Utf8: 1,			// строка utf8
    NameAndType: 12,	// имя и дескриптор поля или метода (два номера CONSTANT_Utf8)
    Class: 7,			// имя класса (номер CONSTANT_Utf8)
    Fieldref: 9,		// описание поля класса (CONSTANT_Class, CONSTANT_NameAndType)
    Methodref: 10,		// описание метода класса (CONSTANT_Class, CONSTANT_NameAndType)
    InterfaceMethodref: 11 // описание метода интерфейса (CONSTANT_Class, CONSTANT_NameAndType)
};

const ACC = {
  PUBLIC: 0,
  PRIVATE: 1
}

const UNIVERSALCLASS = 'java/lang/Object';
const OBJECTLCLASS = 'ObjectR';
const INTEGERCLASS = 'IntegerR';
const FLOATCLASS = 'FloatR';
const STRINGCLASS = 'StringR';
const BOOLCLASS = 'BooleanR';
const ARRAYCLASS = 'ArrayR';
const NILCLASS = 'NilR';
const COMPARABLEMODULE = 'ComparableR';

const IOCLASS = 'IO';

const fs = require('fs');
const parser = require('xml2json');
const CONSTS = require('./consts');
const genFunc = require('./generate');
const FUNCTIONCLASS = 'Main';
const FUNCTIONTYPE = 'LObjectR;'; //TODO заменить на базовый класс
let MainFunc = {};

fs.readFile( 'tree.xml', function(err, data) {
  var json = parser.toJson(data);
  let root = JSON.parse(json).File;
  //console.log(JSON.stringify(root, null, 1));

  let semanticProgram = {
    classesTable: {},
    functionsTable: {},
    errorsList: []
  }

  doSemantic(root, semanticProgram);
  //console.log(JSON.stringify(semanticProgram, null, 1));
  genFunc(semanticProgram);
});




function doSemantic(root, semanticProgram){
  let funcClass = addFunctionClass(semanticProgram);
  externalDeclarations = (root.ExternalDeclaration instanceof Array) ? root.ExternalDeclaration : [root.ExternalDeclaration];
  if(!(externalDeclarations[0]))return;
  externalDeclarations.forEach((externalDeclaration) => {
    if (externalDeclaration.Definition) {
      semanticFunction(externalDeclaration.Definition, semanticProgram, funcClass);
    } else if (externalDeclaration.Class) {
      semanticClass(externalDeclaration.Class, semanticProgram);
    } else if (externalDeclaration.Statement) {
      MainFunc.body.push(externalDeclaration.Statement);
      semanticStmt(externalDeclaration.Statement, funcClass, MainFunc, semanticProgram);
    }
  })
  //
  addOtherClassesMethodRefs(semanticProgram, funcClass);
  Object.keys(semanticProgram.classesTable).forEach((semanticClassName) => {
    addOtherClassesMethodRefs(semanticProgram, semanticProgram.classesTable[semanticClassName]);
  })
}

function addOtherClassesMethodRefs(semanticProgram, semanticClass) {
  Object.keys(semanticProgram.classesTable).forEach((semanticClassName) => {
    if (semanticClassName != "Main" ) { //&& semanticClass.name != semanticClassName
      //Добавляем конструктор
      addClassToConstants(semanticClass.constantsTable, semanticClassName);
      let type = '(';
      if (semanticProgram.classesTable[semanticClassName].methodsTable['initialize'] && semanticProgram.classesTable[semanticClassName].methodsTable['initialize'].arguments) {
        semanticProgram.classesTable[semanticClassName].methodsTable['initialize'].arguments.forEach((arg) => {
          type += FUNCTIONTYPE;
        })
      }
      type += ')V';
      addMethodrefToConstants(semanticClass.constantsTable, semanticClassName, type, "<init>");
      Object.keys(semanticProgram.classesTable[semanticClassName].methodsTable).forEach((methodName) => {
        if (methodName != 'plusROP' && methodName != 'minusROP' && methodName != 'multROP' && methodName != 'divROP' && methodName != 'initialize' && methodName != 'to_s') {
          addMethodrefToConstants(semanticClass.constantsTable, semanticClassName, semanticProgram.classesTable[semanticClassName].methodsTable[methodName].type, methodName);
        }
      })
    }
  })
}

//семантика функций
function semanticFunction(func, semanticProgram, semanticClass, access, isStatic = false) {
  let arguments = func.Parameters && func.Parameters.Parameter;
  if (arguments && !(arguments instanceof Array)) arguments = [arguments];
  let type = '(';
  if (arguments) {
    arguments.forEach((arg) => {
      type += FUNCTIONTYPE;
    })
  }
  type += ')' + FUNCTIONTYPE;
  let methodrefConst =
    addMethodrefToConstants(semanticClass.constantsTable, semanticClass.name, type, func.name);
  let statements = func.Block.StatementList ? func.Block.StatementList.Statement : [];
  let semanticMethod = {
    name: func.name,
    type: type,
    methodrefConst: methodrefConst,
    arguments: arguments,
    localVariableTable: {},
    access: access,
    isStatic: isStatic,
    body: (statements instanceof Array) ? statements : [statements]
  }
  if (semanticClass.name != FUNCTIONCLASS && !semanticMethod.isStatic) {
    addLocalVariableToTable("self", semanticMethod);
  }
  if (semanticMethod.arguments) {
    semanticMethod.arguments.forEach((arg) => {
      addLocalVariableToTable(arg.name, semanticMethod);
    })
  }
  semanticClass.methodsTable[func.name] = semanticMethod;
  semanticStmtList(semanticMethod.body, semanticClass, semanticMethod, semanticProgram);
  return semanticMethod;
}

//семантика класса
function semanticClass(classObj, semanticProgram) {
  let semanticClass = {
    name: classObj.classname,
    constantsTable: [],
    fieldsTable: {},
    methodsTable: {}
  }
  //добавим в таблицу констант класса "Code"
  addCodeToConstants(semanticClass.constantsTable);
  let classConst = addClassToConstants(semanticClass.constantsTable, classObj.classname);
  semanticClass.classConst = classConst;
  let parentName = classObj.Parent ? classObj.Parent.Identifier.name : OBJECTLCLASS;
  semanticClass.objectInit = addMethodrefToConstants(semanticClass.constantsTable, parentName, "()V", "<init>");//Родитель
  addRTL(semanticClass);
  let statements = classObj.StatementList.Statement;
  statements = (statements instanceof Array) ? statements : [statements];
  let currentAccessFlag = ACC.PUBLIC;

  statements.forEach((stmt) => {
    if (stmt.Definition) {
      semanticFunction(stmt.Definition, semanticProgram, semanticClass, currentAccessFlag);
    } else if (stmt.Private !== undefined) {
      currentAccessFlag = ACC.PRIVATE;
    } else if (stmt.Static) {
      let staticStmts = (stmt.Static.StatementList.Statement instanceof Array) ? stmt.Static.StatementList.Statement : [stmt.Static.StatementList.Statement];
      staticStmts.forEach((staticStmt) => {
        semanticFunction(staticStmt.Definition, semanticProgram, semanticClass, currentAccessFlag, true);
      })
    }
  })

  addClassToConstants(semanticClass.constantsTable, parentName);
  semanticClass.initNameConst = addUtf8ToConstants(semanticClass.constantsTable, "<init>");
  let type = '(';
  if (semanticClass.methodsTable['initialize'] && semanticClass.methodsTable['initialize'].arguments) {
    semanticClass.methodsTable['initialize'].arguments.forEach((arg) => {
      type += FUNCTIONTYPE;
    })
  }
  type += ')V';


  semanticClass.initDescriptorConst = addUtf8ToConstants(semanticClass.constantsTable, type);

  semanticProgram.classesTable[classObj.classname] = semanticClass;
  return semanticClass;
}

function semanticStmtList(stmtList, semanticClass, semanticMethod, semanticProgram) {
  let result = true;
  stmtList.forEach((stmt) => {
    result &= semanticStmt(stmt, semanticClass, semanticMethod, semanticProgram);
  })
  return result;
}

function semanticStmt(statement, semanticClass, semanticMethod, semanticProgram) {
  if (statement == null) return true;
  if (statement.Expr) {
    semanticExpr(statement.Expr, semanticClass, semanticMethod, semanticProgram);
  } else if (statement.While) {
    let statements = statement.While.block.Statement;
    statements = (statements instanceof Array) ? statements : [statements];
    semanticStmtList(statements, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(statement.While.condition, semanticClass, semanticMethod, semanticProgram);
  }else if (statement.If) {
    let statements = statement.If.true.Statement;
    statements = (statements instanceof Array) ? statements : [statements];
    semanticStmtList(statements, semanticClass, semanticMethod, semanticProgram);
    if (statement.If.false) {
      semanticStmt(statement.If.false.Statement, semanticClass, semanticMethod, semanticProgram);
    }
    semanticExpr(statement.If.condition, semanticClass, semanticMethod, semanticProgram);
  } else if (statement.StatementList) {
    let statements = statement.StatementList.Statement;
    statements = (statements instanceof Array) ? statements : [statements];
    semanticStmtList(statements, semanticClass, semanticMethod, semanticProgram);
  }
}

function semanticExpr(expression, semanticClass, semanticMethod, semanticProgram) {
  if (expression == null) return;
  if (expression.Assign) {
    if (expression.Assign.Identifier.name[0] == '@'){
      expression.Assign.Identifier.name = expression.Assign.Identifier.name.replace('@', '__dog__');
      addClassVariableToTable(expression.Assign.Identifier.name, semanticClass);
    } else {
      addLocalVariableToTable(expression.Assign.Identifier.name, semanticMethod);
    }
    semanticExpr(expression.Assign.Value, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.Identifier) {
    expression.Identifier.name = expression.Identifier.name.replace('@', '__dog__');
  } else if (expression.ConstF) {
    addFloatToConstants(semanticClass.constantsTable, parseFloat(expression.ConstF.value));
  } else if (expression.String) {
    addStringToConstants(semanticClass.constantsTable, expression.String.value);
  } else if (expression.Const) {
    addIntegerToConstants(semanticClass.constantsTable, parseInt(expression.Const.value));
  } else if (expression.Plus) {
    semanticExpr(expression.Plus.left, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(expression.Plus.right, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.Minus) {
    semanticExpr(expression.Minus.left, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(expression.Minus.right, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.Mul) {
    semanticExpr(expression.Mul.left, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(expression.Mul.right, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.Div) {
    semanticExpr(expression.Div.left, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(expression.Div.right, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.Lt) {
    semanticExpr(expression.Lt.left, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(expression.Lt.right, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.Gt) {
    semanticExpr(expression.Gt.left, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(expression.Gt.right, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.Le) {
    semanticExpr(expression.Le.left, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(expression.Le.right, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.Ge) {
    semanticExpr(expression.Ge.left, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(expression.Ge.right, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.Eq) {
    semanticExpr(expression.Eq.left, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(expression.Eq.right, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.And) {
    semanticExpr(expression.And.left, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(expression.And.right, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.Or) {
    semanticExpr(expression.Or.left, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(expression.Or.right, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.Dot) {
    semanticExpr(expression.Dot.left, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(expression.Dot.right, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.Neg) {
    semanticExpr(expression.Neg, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.ArrayItemAccess) {
    semanticExpr(expression.ArrayItemAccess.array, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(expression.ArrayItemAccess.index, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.Push) {
    semanticExpr(expression.Push.left, semanticClass, semanticMethod, semanticProgram);
    semanticExpr(expression.Push.right, semanticClass, semanticMethod, semanticProgram);
  } else if (expression.Array && expression.Array.elements) {
    let elements = (expression.Array.elements.expr instanceof Array) ? expression.Array.elements.expr : [expression.Array.elements.expr];
    elements.forEach((expr) => {
      semanticExpr(expr, semanticClass, semanticMethod, semanticProgram);
    })
  } else if (expression.FuncCall && expression.FuncCall.arguments) {
    let arguments = (expression.FuncCall.arguments.expr instanceof Array) ? expression.FuncCall.arguments.expr : [expression.FuncCall.arguments.expr];
    arguments.forEach((expr) => {
      semanticExpr(expr, semanticClass, semanticMethod, semanticProgram);
    })
  }
}

function addClassVariableToTable(name, semanticClass) {
  if (semanticClass.fieldsTable[name] != null)
    return semanticClass.fieldsTable[name];
  let nameConst = addUtf8ToConstants(semanticClass.constantsTable, name);
  let typeConst = addUtf8ToConstants(semanticClass.constantsTable, FUNCTIONTYPE);
  let fieldRef = addFieldrefToConstants(semanticClass.constantsTable, semanticClass.name, FUNCTIONTYPE, name);
  let semanticVariable = {
    id: Object.keys(semanticClass.fieldsTable).length,
    name: name,
    nameConst: nameConst,
    typeConst: typeConst,
    fieldRef: fieldRef,
    access: 0//private
  }
  semanticClass.fieldsTable[name] = semanticVariable;
  return semanticVariable;
}

function addLocalVariableToTable(name, semanticMethod) {
  if (semanticMethod.localVariableTable[name] != null)
    return semanticMethod.localVariableTable[name];
  let semanticLocalVariable = {
    id: Object.keys(semanticMethod.localVariableTable).length,
    name: name
  }
  semanticMethod.localVariableTable[name] = semanticLocalVariable;
  return semanticLocalVariable;
}

function addFieldrefToConstants(constantsTable, classname, type, name) {
  let classConst = addClassToConstants(constantsTable, classname);
  let nameAndTypeConst = addNameAndTypeToConstants(constantsTable, name, type);

  let methodrefConst = constantsTable.find((cnst) =>
    cnst.type == SemanticConstantType.Fieldref && cnst.const1 == classConst && cnst.const2 == nameAndTypeConst);
  if (methodrefConst != null) return methodrefConst;

  methodrefConst = {
    id: constantsTable.length + 1,
    type: SemanticConstantType.Fieldref,
    const1: classConst,
    const2: nameAndTypeConst
  }
  constantsTable.push(methodrefConst);
  return methodrefConst;
}

function addMethodrefToConstants(constantsTable, classname, type, name) {
  let classConst = addClassToConstants(constantsTable, classname);
  let nameAndTypeConst = addNameAndTypeToConstants(constantsTable, name, type);
  let stringConst = addStringToConstants(constantsTable, name);
  let methodrefConst = constantsTable.find((cnst) =>
    cnst.type == SemanticConstantType.Methodref && cnst.const1 == classConst && cnst.const2 == nameAndTypeConst);
  if (methodrefConst != null) return methodrefConst;

  methodrefConst = {
    id: constantsTable.length + 1,
    type: SemanticConstantType.Methodref,
    const1: classConst,
    const2: nameAndTypeConst
  }
  constantsTable.push(methodrefConst);
  return methodrefConst;
}

function addInterfaceMethodrefToConstants(constantsTable, classname, type, name) {
  let classConst = addClassToConstants(constantsTable, classname);
  let nameAndTypeConst = addNameAndTypeToConstants(constantsTable, name, type);

  let methodrefConst = constantsTable.find((cnst) =>
    cnst.type == SemanticConstantType.InterfaceMethodref && cnst.const1 == classConst && cnst.const2 == nameAndTypeConst);
  if (methodrefConst != null) return methodrefConst;

  methodrefConst = {
    id: constantsTable.length + 1,
    type: SemanticConstantType.InterfaceMethodref,
    const1: classConst,
    const2: nameAndTypeConst
  }
  constantsTable.push(methodrefConst);
  return methodrefConst;
}

//добавляет константу CONSTANT_Utf8 в таблицу констант
function addUtf8ToConstants(constantsTable, constant) {
  let utf8Const = constantsTable.find((cnst) =>
    cnst.type == SemanticConstantType.Utf8 && cnst.utf8Const == constant);

  if (utf8Const != null) return utf8Const;

  utf8Const = {
    id: constantsTable.length + 1,
    type: SemanticConstantType.Utf8,
    utf8Const: constant
  }
  constantsTable.push(utf8Const);
  return utf8Const;
}

//добавляет константу CONSTANT_String в таблицу констант
function addStringToConstants(constantsTable, constant) {
  let utf8Const = addUtf8ToConstants(constantsTable, constant);

  let strConst = constantsTable.find((cnst) =>
    cnst.type == SemanticConstantType.String && cnst.const1 == utf8Const);

  if (strConst != null) return strConst;

  strConst = {
    id: constantsTable.length + 1,
    type: SemanticConstantType.String,
    const1: utf8Const,
  }
  constantsTable.push(strConst);
  return strConst;
}

//добавляет константу CONSTANT_Integer в таблицу констант
function addIntegerToConstants(constantsTable, constant) {
  let intConst = constantsTable.find((cnst) =>
    cnst.type == SemanticConstantType.Integer && cnst.intConst == constant);

  if (intConst != null) return intConst;

  intConst = {
    id: constantsTable.length + 1,
    type: SemanticConstantType.Integer,
    intConst: constant
  }
  constantsTable.push(intConst);
  return intConst;
}

//добавляет константу CONSTANT_Float в таблицу констант
function addFloatToConstants(constantsTable, constant) {
  let floatConst = constantsTable.find((cnst) =>
    cnst.type == SemanticConstantType.Float && cnst.floatConst == constant);

  if (floatConst != null) return floatConst;

  floatConst = {
    id: constantsTable.length + 1,
    type: SemanticConstantType.Float,
    floatConst: constant
  }
  constantsTable.push(floatConst);
  return floatConst;
}

function addNameAndTypeToConstants(constantsTable, name, type) {
  let nameUtf8Const = addUtf8ToConstants(constantsTable, name);
  let typeUtf8Const = addUtf8ToConstants(constantsTable, type);
  let nameAndTypeConst = constantsTable.find((cnst) =>
    cnst.type == SemanticConstantType.NameAndType && cnst.const1 == nameUtf8Const && cnst.const2 == typeUtf8Const);
  if (nameAndTypeConst != null) return nameAndTypeConst;
  nameAndTypeConst = {
    id: constantsTable.length + 1,
    type: SemanticConstantType.NameAndType,
    const1: nameUtf8Const,
    const2: typeUtf8Const
  }
  constantsTable.push(nameAndTypeConst);
  return nameAndTypeConst;
}

function addClassToConstants(constantsTable, className) {
  let utf8Const = addUtf8ToConstants(constantsTable, className);
  let classConst = constantsTable.find((cnst) =>
    cnst.type == SemanticConstantType.Class && cnst.const1 == utf8Const);
  if (classConst != null) return classConst;
  classConst = {
    id: constantsTable.length + 1,
    type: SemanticConstantType.Class,
    const1: utf8Const
  }
  constantsTable.push(classConst);
  return classConst;
}

//вставляет "Code" в таблицу констант
function addCodeToConstants(constantsTable){
  let constantUtf8 = {
    id: constantsTable.length + 1,
    type: SemanticConstantType.Utf8,
    utf8Const: "Code"
  }
  constantsTable.push(constantUtf8);
  return constantsTable;
}

//добавляет универсальный класс для функций
function addFunctionClass(semanticProgram){

  let funcClass = {
    name: FUNCTIONCLASS,
    constantsTable: [],
    fieldsTable: {},
    methodsTable: {}
  }

  //добавим в таблицу констант класса "Code"
  addCodeToConstants(funcClass.constantsTable);

  //записать константу класса(его имя)
  let classConst = addClassToConstants(funcClass.constantsTable, FUNCTIONCLASS);
  funcClass.classConst = classConst;

  //Родитель класса - object
  addClassToConstants(funcClass.constantsTable, UNIVERSALCLASS);

  addRTL(funcClass);

  semanticProgram.classesTable[FUNCTIONCLASS] = funcClass;

  addMainFunction(semanticProgram, funcClass);

  return funcClass;
}


//семантика функций
function addMainFunction(semanticProgram, semanticClass) {
  let methodrefConst =
    addMethodrefToConstants(semanticClass.constantsTable, semanticClass.name, '([Ljava/lang/String;)V', 'main');
  let semanticMethod = {
    name: 'main',
    methodrefConst: methodrefConst,
    arguments: [{name: 'args'}],
    localVariableTable: {},
    access: ACC.PUBLIC,
    isStatic: true,
    body: []
  }

  if (semanticMethod.arguments) {
    semanticMethod.arguments.forEach((arg) => {
      addLocalVariableToTable(arg.name, semanticMethod);
    })
  }

  semanticClass.methodsTable['main'] = semanticMethod;
  MainFunc = semanticMethod;
  semanticStmtList(semanticMethod.body, semanticClass, semanticMethod, semanticProgram);
  return semanticMethod;
}

function addRTL (semanticClass) {
  semanticClass.objConst = addClassToConstants(semanticClass.constantsTable, OBJECTLCLASS);
  semanticClass.plusROP = addMethodrefToConstants(semanticClass.constantsTable, OBJECTLCLASS, "(LObjectR;)LObjectR;", "plusROP");
  semanticClass.minusROP = addMethodrefToConstants(semanticClass.constantsTable, OBJECTLCLASS, "(LObjectR;)LObjectR;", "minusROP");
  semanticClass.multROP = addMethodrefToConstants(semanticClass.constantsTable, OBJECTLCLASS, "(LObjectR;)LObjectR;", "multROP");
  semanticClass.divROP = addMethodrefToConstants(semanticClass.constantsTable, OBJECTLCLASS, "(LObjectR;)LObjectR;", "divROP");
  semanticClass.indexROP = addMethodrefToConstants(semanticClass.constantsTable, OBJECTLCLASS, "(LObjectR;)LObjectR;", "indexROP");
  semanticClass.pushROP = addMethodrefToConstants(semanticClass.constantsTable, OBJECTLCLASS, "(LObjectR;)LObjectR;", "pushROP");
  semanticClass.classNameR = addMethodrefToConstants(semanticClass.constantsTable, OBJECTLCLASS, "()LStringR;", "class_name");
  semanticClass.to_sR = addMethodrefToConstants(semanticClass.constantsTable, OBJECTLCLASS, "()LObjectR;", "to_s");
  semanticClass.callR = addMethodrefToConstants(semanticClass.constantsTable, OBJECTLCLASS, "(LObjectR;[LObjectR;)LObjectR;", "call");

  semanticClass.boolVal = addMethodrefToConstants(semanticClass.constantsTable, OBJECTLCLASS, "()I", "to_32int");

  let comparableConst = addClassToConstants(semanticClass.constantsTable, COMPARABLEMODULE);
  semanticClass.LtROP = addInterfaceMethodrefToConstants(semanticClass.constantsTable, COMPARABLEMODULE, "(LObjectR;)LObjectR;", "LtROP");
  semanticClass.GtROP = addInterfaceMethodrefToConstants(semanticClass.constantsTable, COMPARABLEMODULE, "(LObjectR;)LObjectR;", "GtROP");
  semanticClass.LeROP = addInterfaceMethodrefToConstants(semanticClass.constantsTable, COMPARABLEMODULE, "(LObjectR;)LObjectR;", "LeROP");
  semanticClass.GeROP = addInterfaceMethodrefToConstants(semanticClass.constantsTable, COMPARABLEMODULE, "(LObjectR;)LObjectR;", "GeROP");
  semanticClass.EqROP = addInterfaceMethodrefToConstants(semanticClass.constantsTable, COMPARABLEMODULE, "(LObjectR;)LObjectR;", "EqROP");


  semanticClass.integerConst = addClassToConstants(semanticClass.constantsTable, INTEGERCLASS);
  semanticClass.integerInit = addMethodrefToConstants(semanticClass.constantsTable, INTEGERCLASS, "(I)V", "<init>");

  semanticClass.boolConst = addClassToConstants(semanticClass.constantsTable, BOOLCLASS);
  semanticClass.boolInit = addMethodrefToConstants(semanticClass.constantsTable, BOOLCLASS, "(Z)V", "<init>");

  semanticClass.floatConst = addClassToConstants(semanticClass.constantsTable, FLOATCLASS);
  semanticClass.floatInit = addMethodrefToConstants(semanticClass.constantsTable, FLOATCLASS, "(F)V", "<init>");

  semanticClass.nilConst = addClassToConstants(semanticClass.constantsTable, NILCLASS);
  semanticClass.nilInit = addMethodrefToConstants(semanticClass.constantsTable, NILCLASS, "()V", "<init>");

  semanticClass.arrayConst = addClassToConstants(semanticClass.constantsTable, ARRAYCLASS);
  semanticClass.arrayInit = addMethodrefToConstants(semanticClass.constantsTable, ARRAYCLASS, "()V", "<init>");

  semanticClass.IOConst = addClassToConstants(semanticClass.constantsTable, IOCLASS);
  semanticClass.putsRef = addMethodrefToConstants(semanticClass.constantsTable, IOCLASS, "(LObjectR;)LObjectR;", "puts");
  semanticClass.getsRef = addMethodrefToConstants(semanticClass.constantsTable, IOCLASS, "()LObjectR;", "gets");

  semanticClass.stringConst = addClassToConstants(semanticClass.constantsTable, STRINGCLASS);
  semanticClass.stringInit = addMethodrefToConstants(semanticClass.constantsTable, STRINGCLASS, "(Ljava/lang/String;)V", "<init>");


}
