#pragma once

#include <stdio.h>
#include <malloc.h>


struct Parameter{
    char *name;             // ��� ���������
    struct Expression *def; // �������� �� ���������
    int named;
	struct Parameter *next;
};

struct ParameterList {
	struct Parameter *first;
	struct Parameter *last;
};

//������ ������
struct ClassInfo {
    char * name;                    //��� ������
    struct Expression * parent;     //��� ��������
    struct StatementList *statements;
};

//������ ������
struct Definition {
    char * name;		                //�������� �������
	struct ParameterList * parameters;	//���������
    struct StatementList *statements;     //����
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
    ExprTypeSymbol,		    // ������
    ExprTypeDot,			// �����
    ExprTypeUMinus,			// ������� �����
    ExprTypeUPlus,			// ������� ����
    ExprTypeObjectFieldAccess, // ������ � ���� ������ (Class.methods)
    ExprTypeIdentifier,		// ��������� � ���������� ��� ����� ������ ��� ����������
    ExprTypeClassIdentifier,	
	ExprTypeFunctionCallArgs,	// ����� ������� � �����������
    ExprTypeString,			// ������
    ExprTypeArrayItemAccess, //������ � �������� �������
    ExprTypeConstant,
    ExprTypeConstantF,
    ExprTypeBool,
    ExprTypeSuper,
    ExprTypeNil,
    ExprTypeArray,
    ExprTypePush
};

struct Expression {
    enum ExprType type;					// ��� ���������
    int num;							// ����� �����
    float float_num;					// �� ����� �����
    char *name; 						// id
	char *string;						// ������
    struct Expression *left;			// ����� expr
    struct Expression *right;			// ������ expr
    struct ExpressionList *arguments;	// ��������� ������� ��� �������� �������
	struct Expression *next;		
};

struct ExpressionList {
    struct Expression *first;
    struct Expression *last;
};

//��� stmt
enum StmtType {
    StmtTypeExpr = 0,	  // �� expr'�
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
    enum StmtType type;                 // ���
    struct Expression *expr;            // ���������
	struct Expression *condition;		// �������
	struct Statement *stmt;	            
	struct Statement *elseBlock;	// �������� ��� else 
    struct Statement *block;       // ����
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
    enum LabeledStatementType type; //���
    struct Expression * expr;       //��������� � ������� � case
    struct Statementlist *block;     //����
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
