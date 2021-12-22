
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
const FUNCTIONCLASS = 'Main';


const genFunc = function (semanticProgram) {
  if (!fs.existsSync('../classes')){
    fs.mkdirSync('../classes');
  }

  Object.keys(semanticProgram.classesTable).forEach((semanticClassName) => {
    fs.writeFileSync(`../classes/${semanticClassName}.class`,'');
    let writeStream = fs.createWriteStream(`../classes/${semanticClassName}.class`);
    writeBinary(writeStream, [...CONSTS.magic, 0, CONSTS.minor_version, 0, CONSTS.major_version]);
    /*  таблица констант */
    writeConstants(writeStream, semanticProgram.classesTable[semanticClassName].constantsTable);
    // флаги доступа
    writeBinary(writeStream, [0, CONSTS.ACC_PUBLIC]);
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
  //writeBinary(writeStream, toU2(Object.keys(fieldsTable).length));
  writeBinary(writeStream, toU2(0));
}

function writeMethods (writeStream, semanticClass) {
  let methodsTable = semanticClass.methodsTable;
  // количество методов - 2 байта
  writeBinary(writeStream, toU2(Object.keys(methodsTable).length));

  Object.keys(methodsTable).forEach((semanticMethodName) => {
    let semanticMethod = methodsTable[semanticMethodName];
    if (semanticClass.classConst.const1.utf8Const == FUNCTIONCLASS) {
      writeBinary(writeStream, toU2(CONSTS.ACC_STATIC | CONSTS.ACC_PUBLIC));
    } else {
      writeBinary(writeStream, toU2(CONSTS.ACC_PUBLIC));
    }
    //имя метода
    writeBinary(writeStream, toU2(semanticMethod.methodrefConst.const2.const1.id));
    //дескриптор метода
    writeBinary(writeStream, toU2(semanticMethod.methodrefConst.const2.const2.id));
    // количество атрибутов метода(атрибут - Code)
    writeBinary(writeStream, toU2(1));
    // атрибут Code
    writeCodeAttribute(writeStream, semanticClass, semanticMethod);
  })

}

//запись аттрибутов метода(в т.ч. байткод).
function writeCodeAttribute (writeStream, semanticClass, semanticMethod) {
  let byteCode = createByteCodeFromStatementList(semanticMethod.body, semanticClass, semanticMethod);
  byteCode.push(CONSTS._RETURN);
  console.log(byteCode);
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
  console.log(expression)
  let bytes = [];
  if (expression.Assign) {
    bytes = bytes.concat(createByteCodeFromExpr(expression.Assign.Value, semanticClass, semanticMethod));
    bytes.push(CONSTS.ASTORE);
    bytes = bytes.concat(semanticMethod.localVariableTable[expression.Assign.Identifier.name].id);

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
  } else if (expression.FuncCall) {
    let arguments = (expression.FuncCall.arguments.expr instanceof Array) ? expression.FuncCall.arguments.expr : [expression.FuncCall.arguments.expr];
    arguments.forEach((argument) => {
      bytes = bytes.concat(createByteCodeFromExpr(argument, semanticClass, semanticMethod));
    })
    if (expression.FuncCall.func.Identifier.name == "puts") {
      bytes.push(CONSTS.INVOKESTATIC);
      bytes = bytes.concat(toU2(semanticClass.putsRef.id));
    }
  } else if (expression.Identifier) {
    bytes.push(CONSTS.ALOAD);
    bytes = bytes.concat(semanticMethod.localVariableTable[expression.Identifier.name].id);
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
