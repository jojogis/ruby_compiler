
const fs = require('fs');
const CONSTS = require('./consts');
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

const FUNCTIONCLASS = 'Main';

let semanticProgramGlobal = {};

const genFunc = function (semanticProgram) {
  if (!fs.existsSync('classes')){
    fs.mkdirSync('classes');
  }
  semanticProgramGlobal = semanticProgram;
  Object.keys(semanticProgram.classesTable).forEach((semanticClassName) => {
    fs.writeFileSync(`classes/${semanticClassName}.class`,'');
    let writeStream = fs.createWriteStream(`classes/${semanticClassName}.class`);
    writeBinary(writeStream, [...CONSTS.magic, 0, CONSTS.minor_version, 0, CONSTS.major_version]);
    /*  таблица констант */
    writeConstants(writeStream, semanticProgram.classesTable[semanticClassName].constantsTable);
    // флаги доступа
    if (semanticClassName != "Main"){
      writeBinary(writeStream, [0, CONSTS.ACC_PUBLIC | CONSTS.ACC_SUPER]);
    } else {
      writeBinary(writeStream, [0, CONSTS.ACC_PUBLIC]);
    }

    // номер константы класса - всегда 3
    writeBinary(writeStream, toU2(3));
    // родительский класс - java/lang/Object
    writeBinary(writeStream, toU2(5));
    // интерфейсы
    writeBinary(writeStream, toU2(0));
    /* таблица полей */
    writeFields(writeStream, semanticProgram.classesTable[semanticClassName].fieldsTable);
    /* таблица методов */
    writeMethods(writeStream, semanticProgram.classesTable[semanticClassName]);
    //количество атрибутов класса
    writeBinary(writeStream, toU2(0));
  })
}

function writeFields (writeStream, fieldsTable) {
  // количество полей - 2 байта
  writeBinary(writeStream, toU2(Object.keys(fieldsTable).length));

  Object.keys(fieldsTable).forEach((field) => {
    writeBinary(writeStream, toU2(CONSTS.ACC_PRIVATE));
    writeBinary(writeStream, toU2(fieldsTable[field].nameConst.id))
    writeBinary(writeStream, toU2(fieldsTable[field].typeConst.id))
    writeBinary(writeStream, toU2(0))
  })


}

function writeMethods (writeStream, semanticClass) {
  let isFuncClass = semanticClass.classConst.const1.utf8Const == FUNCTIONCLASS;
  let methodsTable = semanticClass.methodsTable;
  // количество методов - 2 байта
  writeBinary(writeStream, toU2(Object.keys(methodsTable).length + (isFuncClass ? 0 : 1) - (Object.keys(methodsTable).indexOf('initialize') == -1 ? 0 : 1) ));
  if(!isFuncClass){
    // init
    writeBinary(writeStream, toU2(CONSTS.ACC_PUBLIC));
    writeBinary(writeStream, toU2(semanticClass.initNameConst.id));
    writeBinary(writeStream, toU2(semanticClass.initDescriptorConst.id));
    // количество атрибутов метода(атрибут - Code)
    writeBinary(writeStream, toU2(1));
    let byteCode = [CONSTS.ALOAD_0, CONSTS.INVOKESPECIAL];
    byteCode = byteCode.concat(toU2(semanticClass.objectInit.id));
    if (semanticClass.methodsTable['initialize']){
      byteCode = byteCode.concat(createByteCodeFromStatementList(semanticClass.methodsTable['initialize'].body, semanticClass, semanticClass.methodsTable['initialize']))
    }
    //byteCode.push(CONSTS.POP);//Конструктор возвращает экземпляр убираем лишнее
    byteCode.push(CONSTS._RETURN);
    // индекс константы Code
    writeBinary(writeStream, toU2(1));
    // длина оставшейся части атрибута
    writeBinary(writeStream, toU4(12 + byteCode.length)); // why 12? - Use calc & VM spec, Luke.
    // размер стека
    writeBinary(writeStream, toU2(100));
    //количество локальных переменных метода
    let argsCount = semanticClass.methodsTable['initialize'] && semanticClass.methodsTable['initialize'].arguments ? semanticClass.methodsTable['initialize'].arguments.length : 0
    writeBinary(writeStream, toU2(1 + argsCount));
    // Длина байткода
    writeBinary(writeStream, toU4(byteCode.length));
    //byteArray
    writeBinary(writeStream, byteCode);
    // количество записей в таблице исключений
    writeBinary(writeStream, toU2(0));
    // количество атрибутов
    writeBinary(writeStream, toU2(0));

  }
  Object.keys(methodsTable).forEach((semanticMethodName) => {
    if (semanticMethodName != 'initialize') {
      let semanticMethod = methodsTable[semanticMethodName];
      if (isFuncClass) {
        writeBinary(writeStream, toU2(CONSTS.ACC_STATIC | CONSTS.ACC_PUBLIC));
      } else {
        if (semanticMethod.isStatic) {
          writeBinary(writeStream, toU2(CONSTS.ACC_PUBLIC | CONSTS.ACC_STATIC));
        } else {
          writeBinary(writeStream, toU2(semanticMethod.access == ACC.PUBLIC ? CONSTS.ACC_PUBLIC : CONSTS.ACC_PRIVATE));
        }
      }
      //имя метода
      writeBinary(writeStream, toU2(semanticMethod.methodrefConst.const2.const1.id));
      //дескриптор метода
      writeBinary(writeStream, toU2(semanticMethod.methodrefConst.const2.const2.id));
      // количество атрибутов метода(атрибут - Code)
      writeBinary(writeStream, toU2(1));
      // атрибут Code
      writeCodeAttribute(writeStream, semanticClass, semanticMethod);
    }
  })

}

//запись аттрибутов метода(в т.ч. байткод).
function writeCodeAttribute (writeStream, semanticClass, semanticMethod) {
  let byteCode = createByteCodeFromStatementList(semanticMethod.body, semanticClass, semanticMethod);
  if (semanticClass.name == "Main" && semanticMethod.name == "main") {
    byteCode.push(CONSTS._RETURN);
  } else {
    byteCode.push(CONSTS.ARETURN);
  }
  // индекс константы Code
  writeBinary(writeStream, toU2(1));
  // длина оставшейся части атрибута
  writeBinary(writeStream, toU4(12 + byteCode.length)); // why 12? - Use calc & VM spec, Luke.
  // размер стека
  writeBinary(writeStream, toU2(100));
  //количество локальных переменных метода
  writeBinary(writeStream, toU2(Object.keys(semanticMethod.localVariableTable).length + 1));
  // Длина байткода
  writeBinary(writeStream, toU4(byteCode.length));
  //byteArray
  writeBinary(writeStream, byteCode);
  // количество записей в таблице исключений
  writeBinary(writeStream, toU2(0));
  // количество атрибутов
  writeBinary(writeStream, toU2(0));

}

function writeConstants (writeStream, constantsTable) {
  // количество констант, 2 байта
  writeBinary(writeStream, toU2(constantsTable.length + 1));

  constantsTable.forEach((contant) => {
    writeBinary(writeStream, [contant.type]); // тип константы 1 байт
    if (contant.type == SemanticConstantType.Utf8) {
      writeBinary(writeStream, toU2(contant.utf8Const.length));
      writeBinary(writeStream, contant.utf8Const);
    } else if (contant.type == SemanticConstantType.Integer) {
      const buf = Buffer.allocUnsafe(4);
      buf.writeIntBE(contant.intConst, 0, 4)
      writeStream.write(buf, "binary");
    } else if (contant.type == SemanticConstantType.Float) {
      const buf = Buffer.allocUnsafe(4);
      buf.writeFloatBE(contant.floatConst, 0)
      writeStream.write(buf, "binary");
    } else if (contant.type == SemanticConstantType.Class || contant.type == SemanticConstantType.String) {
      writeBinary(writeStream, toU2(contant.const1.id));
    } else if (contant.type == SemanticConstantType.NameAndType ||
        contant.type == SemanticConstantType.Fieldref || contant.type == SemanticConstantType.Methodref ||
        SemanticConstantType.InterfaceMethodref) {
      writeBinary(writeStream, toU2(contant.const1.id));
      writeBinary(writeStream, toU2(contant.const2.id));
    }
  })
}

function createByteCodeFromStatementList (statementList, semanticClass, semanticMethod) {
  if (statementList == null) return;
  let bytes = [];
  statementList.forEach((statement) => {
    bytes = bytes.concat(createByteCodeFromStatement(statement, semanticClass, semanticMethod));
  })
  return bytes;
}

function createByteCodeFromStatement (statement, semanticClass, semanticMethod) {
  if (statement == null) return [];
  let bytes = [];
  if (statement.While) {
    let statements = statement.While.block.Statement.StatementList.Statement;
    statements = (statements instanceof Array) ? statements : [statements];
    let blockBytes = createByteCodeFromStatementList(statements, semanticClass, semanticMethod);
    for(let i = 0; i < statements.length; i++)blockBytes.push(CONSTS.POP)//TODO костыль, разобраться
    bytes.push(CONSTS.GOTO);
    bytes = bytes.concat(toU2(blockBytes.length+3));
    bytes = bytes.concat(blockBytes);
    let exprBytes = createByteCodeFromExpr(statement.While.condition, semanticClass, semanticMethod);
    bytes = bytes.concat(exprBytes);
    bytes.push(CONSTS.INVOKEVIRTUAL);
    bytes = bytes.concat(toU2(semanticClass.boolVal.id));
    bytes.push(CONSTS.IFNE);
    const buf = Buffer.allocUnsafe(2);
    buf.writeIntBE(-(blockBytes.length +exprBytes.length + 3), 0, 2)
    bytes = bytes.concat([...buf]);
  } else if (statement.If) {
    let blockBytes = [];
    let elseBlockBytes = [];
    let withElse = statement.If.false != null;
    if (statement.If.true.Statement.StatementList) {//многострочный
      let statements = statement.If.true.Statement.StatementList.Statement;
      statements = (statements instanceof Array) ? statements : [statements];
      blockBytes = createByteCodeFromStatementList(statements, semanticClass, semanticMethod);
      for(let i = 0; i < statements.length; i++)blockBytes.push(CONSTS.POP)//TODO костыль, разобраться
    } else { //однострочный
      blockBytes = createByteCodeFromExpr(statement.If.true.Statement.Expr, semanticClass, semanticMethod);
    }
    if (withElse) {
        elseBlockBytes = createByteCodeFromStatement(statement.If.false.Statement, semanticClass, semanticMethod);
    }

    bytes = bytes.concat(createByteCodeFromExpr(statement.If.condition, semanticClass, semanticMethod));
    bytes.push(CONSTS.INVOKEVIRTUAL);
    bytes = bytes.concat(toU2(semanticClass.boolVal.id));
    bytes.push(CONSTS.IFEQ);
    bytes = bytes.concat(toU2(blockBytes.length + (withElse ? 6 : 3) ));
    bytes = bytes.concat(blockBytes);
    if (withElse) {
      bytes.push(CONSTS.GOTO);
      bytes = bytes.concat(toU2(elseBlockBytes.length + 3 ));
      bytes = bytes.concat(elseBlockBytes);
    }
  } else if (statement.Expr) {
    bytes = bytes.concat(createByteCodeFromExpr(statement.Expr, semanticClass, semanticMethod));
  } else if (statement.StatementList) {
    let statements = statement.StatementList.Statement;
    statements = (statements instanceof Array) ? statements : [statements];
    bytes = bytes.concat(createByteCodeFromStatementList(statements, semanticClass, semanticMethod));

  }
  return bytes;
}

function createByteCodeFromExpr (expression, semanticClass, semanticMethod) {
  let bytes = [];
  if (expression.Assign) {

    if (expression.Assign.Identifier.name.startsWith('__dog__')) {
      bytes.push(CONSTS.ALOAD_0);//ref на этот класс
      bytes = bytes.concat(createByteCodeFromExpr(expression.Assign.Value, semanticClass, semanticMethod));
      bytes.push(CONSTS.PUTFIELD);
      let id = semanticClass.fieldsTable[expression.Assign.Identifier.name].fieldRef.id;
      bytes = bytes.concat(toU2(id));
      //возвращаем значение после присваивания
      bytes.push(CONSTS.ALOAD_0);
      bytes.push(CONSTS.GETFIELD);
      bytes = bytes.concat(toU2(id));
    } else {
      bytes = bytes.concat(createByteCodeFromExpr(expression.Assign.Value, semanticClass, semanticMethod));
      bytes.push(CONSTS.DUP);//возвращаем значение после присваивания
      bytes.push(CONSTS.ASTORE);
      bytes = bytes.concat(semanticMethod.localVariableTable[expression.Assign.Identifier.name].id);
    }
  } else if (expression.Bool) {
    bytes.push(CONSTS.NEW);
    bytes = bytes.concat(toU2(semanticClass.boolConst.id));
    bytes.push(CONSTS.DUP);
    if (expression.Bool.value == '1') {
      bytes.push(CONSTS.ICONST_1);
    } else {
      bytes.push(CONSTS.ICONST_0);
    }
    bytes.push(CONSTS.INVOKESPECIAL);
    bytes = bytes.concat(toU2(semanticClass.boolInit.id));
  } else if (expression.Nil) {
    bytes.push(CONSTS.NEW);
    bytes = bytes.concat(toU2(semanticClass.nilConst.id));
    bytes.push(CONSTS.DUP);
    bytes.push(CONSTS.INVOKESPECIAL);
    bytes = bytes.concat(toU2(semanticClass.nilInit.id));
  } else if (expression.String) {
    bytes.push(CONSTS.NEW);
    bytes = bytes.concat(toU2(semanticClass.stringConst.id));
    bytes.push(CONSTS.DUP);
    bytes.push(CONSTS.LDC);
    let strVal = expression.String.value;
    let strConstId = semanticClass.constantsTable.find((cnst) => cnst.type == SemanticConstantType.String && cnst.const1.utf8Const == strVal).id;
    bytes.push(strConstId);
    bytes.push(CONSTS.INVOKESPECIAL);
    bytes = bytes.concat(toU2(semanticClass.stringInit.id));
  } else if (expression.Const) {
    bytes.push(CONSTS.NEW);
    bytes = bytes.concat(toU2(semanticClass.integerConst.id));
    bytes.push(CONSTS.DUP);
    bytes.push(CONSTS.LDC);
    let intVal = parseInt(expression.Const.value);
    let intConstId = semanticClass.constantsTable.find((cnst) => cnst.type == SemanticConstantType.Integer && cnst.intConst == intVal).id;
    bytes.push(intConstId);
    bytes.push(CONSTS.INVOKESPECIAL);
    bytes = bytes.concat(toU2(semanticClass.integerInit.id));
  } else if (expression.ConstF) {
    bytes.push(CONSTS.NEW);
    bytes = bytes.concat(toU2(semanticClass.floatConst.id));
    bytes.push(CONSTS.DUP);
    bytes.push(CONSTS.LDC);
    let floatVal = parseFloat(expression.ConstF.value);
    let floatConstId = semanticClass.constantsTable.find((cnst) => cnst.type == SemanticConstantType.Float && cnst.floatConst == floatVal).id;
    bytes.push(floatConstId);
    bytes.push(CONSTS.INVOKESPECIAL);
    bytes = bytes.concat(toU2(semanticClass.floatInit.id));
  } else if (expression.FuncCall) { //вызов функции со скобками
    let argBytes = [];
    let arguments = (expression.FuncCall.arguments.expr instanceof Array) ? expression.FuncCall.arguments.expr : [expression.FuncCall.arguments.expr];
    arguments.forEach((argument) => {
      argBytes = argBytes.concat(createByteCodeFromExpr(argument, semanticClass, semanticMethod));
    })
    if (expression.FuncCall.func.Identifier) {
      bytes = bytes.concat(argBytes);
      if (expression.FuncCall.func.Identifier.name == "puts") {
        bytes.push(CONSTS.INVOKESTATIC);
        bytes = bytes.concat(toU2(semanticClass.putsRef.id));
      } else if (semanticClass.name == "Main")  {
        bytes.push(CONSTS.INVOKESTATIC);
        bytes = bytes.concat(toU2(semanticClass.methodsTable[expression.FuncCall.func.Identifier.name].methodrefConst.id));
      }
    } else if (expression.FuncCall.func.Dot) {
      //Дублирует expression.Dot
      if (expression.FuncCall.func.Dot.left.ClassIdentifier) {//Если обращаемся к статическому методу класса
        if (expression.FuncCall.func.Dot.right.Identifier && expression.FuncCall.func.Dot.right.Identifier.name == "new") {//Если вызывается конструктор
          bytes.push(CONSTS.NEW);
          let classConst = semanticClass.constantsTable.find((cnst) => cnst.type == SemanticConstantType.Class && cnst.const1.utf8Const == expression.FuncCall.func.Dot.left.ClassIdentifier.name);
          if (classConst == null) throw new Error("Undefined class " + expression.FuncCall.func.Dot.left.ClassIdentifier.name);
          bytes = bytes.concat(toU2(classConst.id));
          bytes.push(CONSTS.DUP);
          bytes = bytes.concat(argBytes);
          bytes.push(CONSTS.INVOKESPECIAL);
          let initConst = semanticClass.constantsTable.find((cnst) => cnst.type == SemanticConstantType.Methodref && cnst.const1 == classConst && cnst.const2.const1.utf8Const == "<init>");
          bytes = bytes.concat(toU2(initConst.id));
        } else {
          let methodRefConst = semanticClass.constantsTable.find((cnst) => cnst.type == SemanticConstantType.Methodref &&
              cnst.const1.const1.utf8Const == expression.FuncCall.func.Dot.left.ClassIdentifier.name && cnst.const2.const1.utf8Const == expression.FuncCall.func.Dot.right.Identifier.name);
          bytes = bytes.concat(argBytes);
          bytes.push(CONSTS.INVOKESTATIC);
          bytes = bytes.concat(toU2(methodRefConst.id));

        }
      } else {
        let callingCall = expression.FuncCall.func.Dot.right.Identifier.name == "call";

        bytes = bytes.concat(createByteCodeFromExpr(expression.FuncCall.func.Dot.left, semanticClass, semanticMethod));
        if (callingCall) {
          //Берем имя функции из первого аргумента
          bytes = bytes.concat(createByteCodeFromExpr(arguments[0], semanticClass, semanticMethod));
          arguments = arguments.splice(1);
        } else {
          bytes.push(CONSTS.NEW);//создаем объект строки с именем метода
          bytes = bytes.concat(toU2(semanticClass.stringConst.id));
          bytes.push(CONSTS.DUP);
          bytes.push(CONSTS.LDC);
          let strVal = expression.FuncCall.func.Dot.right.Identifier.name;
          let strConstId = semanticClass.constantsTable.find((cnst) => cnst.type == SemanticConstantType.String && cnst.const1.utf8Const == strVal).id;
          bytes.push(strConstId);
          bytes.push(CONSTS.INVOKESPECIAL);
          bytes = bytes.concat(toU2(semanticClass.stringInit.id));
        }

        //аргументы
        bytes.push(CONSTS.BIPUSH);
        bytes.push(arguments.length);
        bytes.push(CONSTS.ANEWARRAY);
        bytes = bytes.concat(toU2(semanticClass.objConst.id));

        arguments.forEach((argument, index) => {
          bytes.push(CONSTS.DUP);
          //Индекс элемента массива
          bytes.push(CONSTS.BIPUSH);
          bytes.push(index);
          //значение
          bytes = bytes.concat(createByteCodeFromExpr(argument, semanticClass, semanticMethod));

          bytes.push(CONSTS.AASTORE);
        })

        //Вызываем метод через call
        bytes.push(CONSTS.INVOKEVIRTUAL);
        bytes = bytes.concat(toU2(semanticClass.callR.id));

      }
    }

  } else if (expression.Identifier) {
    let varConst = semanticMethod.localVariableTable[expression.Identifier.name];
    if (varConst) {
      bytes.push(CONSTS.ALOAD);
      bytes = bytes.concat(varConst.id);
    } else if (semanticClass.fieldsTable[expression.Identifier.name]) {
      bytes.push(CONSTS.ALOAD_0);
      bytes.push(CONSTS.GETFIELD);
      bytes = bytes.concat(toU2(semanticClass.fieldsTable[expression.Identifier.name].fieldRef.id));
    } else if (expression.Identifier.name == "gets") {
      bytes.push(CONSTS.INVOKESTATIC);
      bytes = bytes.concat(toU2(semanticClass.getsRef.id));
    } else {
      if (semanticClass.name == "Main")
        bytes.push(CONSTS.INVOKESTATIC);
      if (semanticClass.methodsTable[expression.Identifier.name])
        bytes = bytes.concat(toU2(semanticClass.methodsTable[expression.Identifier.name].methodrefConst.id));
      else
        throw new Error("undefined variable " + expression.Identifier.name)
    }
  } else if (expression.Plus) {
    bytes = bytes.concat(createByteCodeFromExpr(expression.Plus.left, semanticClass, semanticMethod));
    bytes = bytes.concat(createByteCodeFromExpr(expression.Plus.right, semanticClass, semanticMethod));
    bytes.push(CONSTS.INVOKEVIRTUAL);
    bytes = bytes.concat(toU2(semanticClass.plusROP.id));
  } else if (expression.Minus) {
    bytes = bytes.concat(createByteCodeFromExpr(expression.Minus.left, semanticClass, semanticMethod));
    bytes = bytes.concat(createByteCodeFromExpr(expression.Minus.right, semanticClass, semanticMethod));
    bytes.push(CONSTS.INVOKEVIRTUAL);
    bytes = bytes.concat(toU2(semanticClass.minusROP.id));
  } else if (expression.Mul) {
    bytes = bytes.concat(createByteCodeFromExpr(expression.Mul.left, semanticClass, semanticMethod));
    bytes = bytes.concat(createByteCodeFromExpr(expression.Mul.right, semanticClass, semanticMethod));
    bytes.push(CONSTS.INVOKEVIRTUAL);
    bytes = bytes.concat(toU2(semanticClass.multROP.id));
  } else if (expression.Div) {
    bytes = bytes.concat(createByteCodeFromExpr(expression.Div.left, semanticClass, semanticMethod));
    bytes = bytes.concat(createByteCodeFromExpr(expression.Div.right, semanticClass, semanticMethod));
    bytes.push(CONSTS.INVOKEVIRTUAL);
    bytes = bytes.concat(toU2(semanticClass.divROP.id));
  } else if (expression.Push) {
    bytes = bytes.concat(createByteCodeFromExpr(expression.Push.left, semanticClass, semanticMethod));
    bytes = bytes.concat(createByteCodeFromExpr(expression.Push.right, semanticClass, semanticMethod));
    bytes.push(CONSTS.INVOKEVIRTUAL);
    bytes = bytes.concat(toU2(semanticClass.pushROP.id));
  } else if (expression.Lt) {
    bytes = bytes.concat(createByteCodeFromExpr(expression.Lt.left, semanticClass, semanticMethod));
    bytes = bytes.concat(createByteCodeFromExpr(expression.Lt.right, semanticClass, semanticMethod));
    bytes.push(CONSTS.INVOKEINTERFACE);
    bytes = bytes.concat(toU2(semanticClass.LtROP.id));
    bytes.push(2);//нужно для вызова метода интерфейса
    bytes.push(0);
  } else if (expression.Gt) {
    bytes = bytes.concat(createByteCodeFromExpr(expression.Gt.left, semanticClass, semanticMethod));
    bytes = bytes.concat(createByteCodeFromExpr(expression.Gt.right, semanticClass, semanticMethod));
    bytes.push(CONSTS.INVOKEINTERFACE);
    bytes = bytes.concat(toU2(semanticClass.GtROP.id));
    bytes.push(2);
    bytes.push(0);
  } else if (expression.Le) {
    bytes = bytes.concat(createByteCodeFromExpr(expression.Le.left, semanticClass, semanticMethod));
    bytes = bytes.concat(createByteCodeFromExpr(expression.Le.right, semanticClass, semanticMethod));
    bytes.push(CONSTS.INVOKEINTERFACE);
    bytes = bytes.concat(toU2(semanticClass.LeROP.id));
    bytes.push(2);
    bytes.push(0);
  } else if (expression.Ge) {
    bytes = bytes.concat(createByteCodeFromExpr(expression.Ge.left, semanticClass, semanticMethod));
    bytes = bytes.concat(createByteCodeFromExpr(expression.Ge.right, semanticClass, semanticMethod));
    bytes.push(CONSTS.INVOKEINTERFACE);
    bytes = bytes.concat(toU2(semanticClass.GeROP.id));
    bytes.push(2);
    bytes.push(0);
  } else if (expression.Eq) {
    bytes = bytes.concat(createByteCodeFromExpr(expression.Eq.left, semanticClass, semanticMethod));
    bytes = bytes.concat(createByteCodeFromExpr(expression.Eq.right, semanticClass, semanticMethod));
    bytes.push(CONSTS.INVOKEINTERFACE);
    bytes = bytes.concat(toU2(semanticClass.EqROP.id));
    bytes.push(2);
    bytes.push(0);
  } else if (expression.And) {
    bytes = bytes.concat(createByteCodeFromExpr(expression.And.left, semanticClass, semanticMethod));
    let rightBytes = bytes.concat(createByteCodeFromExpr(expression.And.right, semanticClass, semanticMethod));
    bytes.push(CONSTS.DUP);
    bytes.push(CONSTS.DUP);
    bytes.push(CONSTS.INVOKEVIRTUAL);
    bytes = bytes.concat(toU2(semanticClass.boolVal.id));
    bytes.push(CONSTS.IFEQ);
    bytes = bytes.concat(toU2(rightBytes.length + 5));
    bytes.push(CONSTS.POP);
    bytes.push(CONSTS.POP);
    bytes = bytes.concat(rightBytes);
  } else if (expression.Or) {
    bytes = bytes.concat(createByteCodeFromExpr(expression.Or.left, semanticClass, semanticMethod));
    let rightBytes = bytes.concat(createByteCodeFromExpr(expression.Or.right, semanticClass, semanticMethod));
    bytes.push(CONSTS.DUP);
    bytes.push(CONSTS.DUP);
    bytes.push(CONSTS.INVOKEVIRTUAL);
    bytes = bytes.concat(toU2(semanticClass.boolVal.id));
    bytes.push(CONSTS.IFNE);
    bytes = bytes.concat(toU2(rightBytes.length + 5));
    bytes.push(CONSTS.POP);
    bytes.push(CONSTS.POP);
    bytes = bytes.concat(rightBytes);
  } else if (expression.Neg) {
    bytes.push(CONSTS.NEW);
    bytes = bytes.concat(toU2(semanticClass.boolConst.id));
    bytes.push(CONSTS.DUP);
    bytes = bytes.concat(createByteCodeFromExpr(expression.Neg, semanticClass, semanticMethod));
    bytes.push(CONSTS.INVOKEVIRTUAL);
    bytes = bytes.concat(toU2(semanticClass.boolVal.id));
    bytes.push(CONSTS.IFNE);
    bytes = bytes.concat(toU2(7));
      bytes.push(CONSTS.ICONST_1);
    bytes.push(CONSTS.GOTO);
      bytes = bytes.concat(toU2(4));
    bytes.push(CONSTS.ICONST_0);
    bytes.push(CONSTS.INVOKESPECIAL);
    bytes = bytes.concat(toU2(semanticClass.boolInit.id));
  } else if (expression.ArrayItemAccess) {
    bytes = bytes.concat(createByteCodeFromExpr(expression.ArrayItemAccess.array, semanticClass, semanticMethod));
    bytes = bytes.concat(createByteCodeFromExpr(expression.ArrayItemAccess.index, semanticClass, semanticMethod));
    bytes.push(CONSTS.INVOKEVIRTUAL);
    bytes = bytes.concat(toU2(semanticClass.indexROP.id));
  } else if (expression.Array) {
    bytes.push(CONSTS.NEW);
    bytes = bytes.concat(toU2(semanticClass.arrayConst.id));
    bytes.push(CONSTS.DUP);
    bytes.push(CONSTS.INVOKESPECIAL);
    bytes = bytes.concat(toU2(semanticClass.arrayInit.id));
    let elements = (expression.Array.elements.expr instanceof Array) ? expression.Array.elements.expr : [expression.Array.elements.expr];
    elements.forEach((expr) => {
      bytes = bytes.concat(createByteCodeFromExpr(expr, semanticClass, semanticMethod));
      bytes.push(CONSTS.INVOKEVIRTUAL);
      bytes = bytes.concat(toU2(semanticClass.pushROP.id));
    })
  } else if (expression.Dot) {//вызов функции без скобок
    //вызов функции
    if (expression.Dot.left.ClassIdentifier) {//Если обращаемся к статическому методу класса
      if (expression.Dot.right.Identifier && expression.Dot.right.Identifier.name == "new") {//Если вызывается конструктор
        bytes.push(CONSTS.NEW);
        let classConst = semanticClass.constantsTable.find((cnst) => cnst.type == SemanticConstantType.Class && cnst.const1.utf8Const == expression.Dot.left.ClassIdentifier.name);
        if (classConst == null) throw new Error("Undefined class " + expression.Dot.left.ClassIdentifier.name);
        bytes = bytes.concat(toU2(classConst.id));
        bytes.push(CONSTS.DUP);
        bytes.push(CONSTS.INVOKESPECIAL);
        let initConst = semanticClass.constantsTable.find((cnst) => cnst.type == SemanticConstantType.Methodref && cnst.const1 == classConst && cnst.const2.const1.utf8Const == "<init>");
        bytes = bytes.concat(toU2(initConst.id));
      } else {
        let methodRefConst = semanticClass.constantsTable.find((cnst) => cnst.type == SemanticConstantType.Methodref &&
            cnst.const1.const1.utf8Const == expression.Dot.left.ClassIdentifier.name && cnst.const2.const1.utf8Const == expression.Dot.right.Identifier.name);
        bytes.push(CONSTS.INVOKESTATIC);
        bytes = bytes.concat(toU2(methodRefConst.id));

      }
    } else if (expression.Dot.right.Identifier.name == "class") { // Если получаем имя класса
      bytes = bytes.concat(createByteCodeFromExpr(expression.Dot.left, semanticClass, semanticMethod));
      bytes.push(CONSTS.INVOKEVIRTUAL);
      bytes = bytes.concat(toU2(semanticClass.classNameR.id));
    } else if (expression.Dot.right.Identifier.name == "to_s") { // Если получаем имя класса
      bytes = bytes.concat(createByteCodeFromExpr(expression.Dot.left, semanticClass, semanticMethod));
      bytes.push(CONSTS.INVOKEVIRTUAL);
      bytes = bytes.concat(toU2(semanticClass.to_sR.id));
    } else {
      bytes = bytes.concat(createByteCodeFromExpr(expression.Dot.left, semanticClass, semanticMethod));

      bytes.push(CONSTS.NEW);//создаем объект строки с именем метода
      bytes = bytes.concat(toU2(semanticClass.stringConst.id));
      bytes.push(CONSTS.DUP);
      bytes.push(CONSTS.LDC);
      let strVal = expression.Dot.right.Identifier.name;
      let strConstId = semanticClass.constantsTable.find((cnst) => cnst.type == SemanticConstantType.String && cnst.const1.utf8Const == strVal).id;
      bytes.push(strConstId);
      bytes.push(CONSTS.INVOKESPECIAL);
      bytes = bytes.concat(toU2(semanticClass.stringInit.id));

      //Заглушка для аргументов
      bytes.push(CONSTS.ICONST_0);
      bytes.push(CONSTS.ANEWARRAY);
      bytes = bytes.concat(toU2(semanticClass.objConst.id));
      //Вызываем метод через call
      bytes.push(CONSTS.INVOKEVIRTUAL);
      bytes = bytes.concat(toU2(semanticClass.callR.id));
    }

  }
  return bytes;
}

function toU4 (number) {
  const buf = Buffer.allocUnsafe(4);
  buf.writeIntBE(number, 0, 4)
  return buf;
}

function toU2 (number) {
  if (number <= 256) {
    return [0, number];
  } else {
    return [number];
  }
}

function writeBinary (writeStream, data) {
  writeStream.write(Buffer.from(data), "binary");
}

module.exports = genFunc;
