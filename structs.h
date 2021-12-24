#pragma once

#include <stdio.h>
#include <malloc.h>


struct Parameter{
    char *name;             // имя параметра
    struct Expression *def; // значение по умолчанию
    int named;
	struct Parameter *next;
};

struct ParameterList {
	struct Parameter *first;
	struct Parameter *last;
};

//данные класса
struct ClassInfo {
    char * name;                    //имя класса
    struct Expression * parent;     //имя родителя
    struct StatementList *statements;
};

//данные метода
struct Definition {
    char * name;		                //название функции
	struct ParameterList * parameters;	//параметры
    struct StatementList *statements;     //тело
};

enum ExprType {
    ExprTypeAssign = 0,		// = 
    ExprTypeOr,				// ||
    ExprTypeAnd,			// &&
    ExprTypeLt,				// <
    ExprTypeLE,				// <=
    ExprTypeGr,				// >
    ExprTypeGE,				// >=
	ExprTypeEq,				// ==
    ExprTypeNotEq,			// !=
    ExprTypeEqS,			// ===
    ExprTypeAddAssign,		// +=
    ExprTypeSubAssign,		// -=
    ExprTypeMultAssign,		// *=
    ExprTypeDivAssign,		// /=
    ExprTypeModAssign,		// %=
    ExprTypeExpAssign,		// **=
    ExprTypePlus,			// +
    ExprTypeMinus,			// -
    ExprTypeMul,			// *
    ExprTypeDiv,			// /
    ExprTypeMod,			// %
    ExprTypeExp,			// **
	ExprTypeNeg,			// !
    ExprTypeCompare,		// <=>
    ExprTypeRangeOut,		// ...
    ExprTypeRangeIn,		// ..
    ExprTypeSymbol,		    // Символ
    ExprTypeDot,			// точка
    ExprTypeUMinus,			// унарный минус
    ExprTypeUPlus,			// унарный плюс
    ExprTypeObjectFieldAccess, // доступ к полю класса (Class.methods)
    ExprTypeIdentifier,		// обращение к переменной или вызов метода без параметров
    ExprTypeClassIdentifier,	
	ExprTypeFunctionCallArgs,	// вызов функции с параметрами
    ExprTypeString,			// строка
    ExprTypeArrayItemAccess, //Доступ к элементу массива
    ExprTypeConstant,
    ExprTypeConstantF,
    ExprTypeBool,
    ExprTypeSuper,
    ExprTypeNil,
    ExprTypeArray,
    ExprTypePush
};

struct Expression {
    enum ExprType type;					// тип выражения
    int num;							// целое число
    float float_num;					// не целое число
    char *name; 						// id
	char *string;						// строка
    struct Expression *left;			// левый expr
    struct Expression *right;			// правый expr
    struct ExpressionList *arguments;	// аргументы функции или элементы массива
	struct Expression *next;		
};

struct ExpressionList {
    struct Expression *first;
    struct Expression *last;
};

//тип stmt
enum StmtType {
    StmtTypeExpr = 0,	  // из expr'а
    StmtTypeIf,				// if
    StmtTypeIfElse,				// if else
    StmtTypeSwitch,			// switch
    StmtTypeWhile,			// while
    StmtTypeDoWhile,		// do while
    StmtTypeFor,			// for
    StmtTypeBreak,			// break
    StmtTypeReturn,			// return
    StmtDefinition,
    StmtTypeBlock,
    StmtTypePrivate,
    StmtTypeStatic
};

struct Statement {
    enum StmtType type;                 // тип
    struct Expression *expr;            // выражение
	struct Expression *condition;		// условие
	struct Statement *stmt;	            
	struct Statement *elseBlock;	// оператор для else 
    struct Statement *block;       // тело
    struct Definition *definition;
    struct StatementList *stmtList;
    struct LabeledStatementList *labeledList;
	struct Statement *next;    
};

enum LabeledStatementType
{
    LabeledStatementTypeCase = 0,
    LabeledStatementTypeDefault
};

struct LabeledStatement
{
    enum LabeledStatementType type; //тип
    struct Expression * expr;       //выражение в скобках у case
    struct Statementlist *block;     //тело
	struct LabeledStatement *next;
};

struct LabeledStatementList
{
	struct LabeledStatement *first;
	struct LabeledStatement *last;
};

struct StatementList
{
	struct Statement *first;
	struct Statement *last;
};

enum ExternalDeclarationType {
    ExternalDeclarationFunction = 0,
    ExternalDeclarationClassInfo,
    ExternalDeclarationStmt
};

struct ExternalDeclaration {
    enum ExternalDeclarationType type;      
    struct Definition * function;   
    struct ClassInfo * classInfo;          
    struct Statement * stmt;
	struct ExternalDeclaration * next;
};

struct ExternalDeclarationList {
	struct ExternalDeclaration * first;
	struct ExternalDeclaration * last;
};
