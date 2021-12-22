#include <malloc.h>
#include "declarations.h"
#include "grammar.tab.h"
#include "structs.h"
extern int yylex(void);

//!-- EXPR
// Очищаем структуру Expression
void CleanStructExpression(struct Expression * expr)
{
	expr->num = 0;
	expr->name = NULL;
	expr->string = NULL;
	expr->left = NULL;
	expr->right = NULL;
	expr->arguments = NULL;
	expr->next = NULL;
}

struct Expression * CreateSuperExpr()
{
	struct Expression *result = (struct Expression *)malloc(sizeof(struct Expression));
	CleanStructExpression(result);
	
	result->type = ExprTypeSuper;
	return result;
}

struct Expression * CreateNilExpr()
{
	struct Expression *result = (struct Expression *)malloc(sizeof(struct Expression));
	CleanStructExpression(result);
	
	result->type = ExprTypeNil;
	return result;
}

//создание выражение для id
struct Expression * CreateIdentifierExpr(char * id)
{
	struct Expression *result = (struct Expression *)malloc(sizeof(struct Expression));
	CleanStructExpression(result);
	
	result->type = ExprTypeIdentifier;
	result->name = id;
	return result;
}

//создание выражение для bool
struct Expression * CreateBoolExpr(int num)
{
	struct Expression *result = (struct Expression *)malloc(sizeof(struct Expression));
	CleanStructExpression(result);
	
	result->type = ExprTypeBool;
	 result->num = num;
	return result;
}

// создание выражения string
struct Expression * CreateStringExpr(char * string)
{
	struct Expression *result = (struct Expression *)malloc(sizeof(struct Expression));
	CleanStructExpression(result);
	
	result->type = ExprTypeString;
	result->string = string;
	return result;
}

// создание выражения Const
struct Expression * CreateConstantExpr(int num)
{
    struct Expression *result = (struct Expression *)malloc(sizeof(struct Expression));
    CleanStructExpression(result);

    result->type = ExprTypeConstant;
    result->num = num;
    return result;
}

struct Expression * CreateFloatConstantExpr(float num)
{
    struct Expression *result = (struct Expression *)malloc(sizeof(struct Expression));
    CleanStructExpression(result);

    result->type = ExprTypeConstantF;
    result->float_num = num;
    return result;
}

// бинарные операции
struct Expression * CreateBinaryExpr(enum ExprType type, struct Expression *left_expr, struct Expression *right_expr)
{
	struct Expression *result = (struct Expression *) malloc(sizeof(struct Expression));
	CleanStructExpression(result);
	
	result->type = type;
	result->left = left_expr;
	result->right = right_expr;
	return result;
}

// унарные операции
struct Expression * CreateUnaryExpr(enum ExprType type, struct Expression *expr)
{
	struct Expression *result = (struct Expression *) malloc(sizeof(struct Expression));
	CleanStructExpression(result);
	
	result->type = type;
	result->right = expr;
	return result;
}

// доступ к полю объекта
struct Expression * CreateObjectFieldAccessExpr(struct Expression * object, char * field)
{
	struct Expression *result = (struct Expression *) malloc(sizeof(struct Expression));
	CleanStructExpression(result);
	
	result->type = ExprTypeObjectFieldAccess;
	result->left = object;
	result->name = field;
	return result;
}

// вызов функции
struct Expression * CreateFunctionCallExpr(struct Expression * object, struct ExpressionList * args)
{
	struct Expression *result = (struct Expression *) malloc(sizeof(struct Expression));
	CleanStructExpression(result);
	
	result->type = ExprTypeFunctionCallArgs;
	result->left = object;
	result->arguments = args;
	return result;
}

// Создание массива
struct Expression * CreateArrayExpr(struct ExpressionList * args)
{
	struct Expression *result = (struct Expression *) malloc(sizeof(struct Expression));
	CleanStructExpression(result);
	
	result->type = ExprTypeArray;
	result->arguments = args;
	return result;
}

// создание списка expr
struct ExpressionList * CreateExpressionList(struct Expression * expr)
{
	struct ExpressionList *result=(struct ExpressionList *)malloc(sizeof(struct ExpressionList));
	result->first = NULL;
	result->last = NULL;

	if(expr != NULL)
	{
		result->first = expr;
		result->last = expr;
		return result;
	}
	else
	{
		return NULL;
	}
}

// добавление в список expr
struct ExpressionList * AddToExpressionList(struct ExpressionList * list, struct Expression * expr)
{
	// если в списке уже чтото есть
	if(list != NULL)
	{
		// и есть что добавлять
		if(expr != NULL)
		{
			list->last->next = expr;
			list->last = expr;
			return list;
		}
	}
	else
		return CreateExpressionList(expr);
}

//!-- Statement----------------
void CleanStructStatement(struct Statement * stmt)
{
    stmt->expr = NULL;
	stmt->elseBlock = NULL;
    stmt->block = NULL;
	stmt->next = NULL;
}

// stmt из Definition
struct Statement * CreateDefinitionStatement(struct Definition *definition)
{
	struct Statement *result = (struct Statement *) malloc(sizeof(struct Statement));
	CleanStructStatement(result);
	
	result->type = StmtDefinition;
	result->definition = definition;
	
	return result;
}

// stmt из expr'a
struct Statement * CreateExprStatement(struct Expression *expr)
{
	struct Statement *result = (struct Statement *) malloc(sizeof(struct Statement));
	CleanStructStatement(result);
	
	result->type = StmtTypeExpr;
	result->expr = expr;
	
	return result;
}

struct Statement * CreateCompoundStatement(struct StatementList *stmtList)
{
	struct Statement *result = (struct Statement *) malloc(sizeof(struct Statement));
	CleanStructStatement(result);
	
	result->type = StmtTypeBlock;
	result->block = stmtList;
	
	return result;
}

struct Statement * CreateIfStatement(struct Expression *condition, struct Statement *block)
{
	struct Statement *result = (struct Statement *) malloc(sizeof(struct Statement));
	CleanStructStatement(result);
	
	result->type = StmtTypeIf;
	result->condition = condition;
	result->block = block;
	return result;
}

struct Statement * CreateIfElseStatement(struct Expression *condition, struct Statement *true_stmt, struct Statement *false_stmt)
{
	struct Statement *result = (struct Statement *) malloc(sizeof(struct Statement));
	CleanStructStatement(result);
	
	result->type = StmtTypeIf;
	result->condition = condition;
	result->block = true_stmt;
	result->elseBlock = false_stmt;
	return result;
}

struct Statement * CreateWhileStatement(struct Expression *condition, struct Statement *block)
{
	struct Statement *result = (struct Statement *) malloc(sizeof(struct Statement));
	CleanStructStatement(result);
	
	result->type = StmtTypeWhile;
	result->condition = condition;
	result->block = block;
	return result;
}

struct Statement * CreateForStatement(struct Expression *identifier, struct Expression *expr, struct Statement *block)
{
	struct Statement *result = (struct Statement *) malloc(sizeof(struct Statement));
	CleanStructStatement(result);
	
	result->type = StmtTypeFor;
	result->condition = identifier;
	result->expr = expr;
	result->block = block;
	return result;
}

struct Statement * CreateBreakStatement()
{
	struct Statement *result = (struct Statement *) malloc(sizeof(struct Statement));
	CleanStructStatement(result);
	
	result->type = StmtTypeBreak;
	return result;
}

struct Statement * CreateReturnStatement(struct Expression *expr)
{
	struct Statement *result = (struct Statement *) malloc(sizeof(struct Statement));
	CleanStructStatement(result);
	
	result->type = StmtTypeReturn;
	result->expr = expr;
	return result;
}

// создание списка stmt
struct StatementList * CreateStatementList(struct Statement *stmt)
{
	struct StatementList *result=(struct StatementList *)malloc(sizeof(struct StatementList));
	result->first = NULL;
	result->last = NULL;

	if(stmt != NULL)
	{
		result->first = stmt;
		result->last = stmt;
		return result;
	}
	else
	{
		return NULL;
	}
}

// добавление в список stmt
struct StatementList * AddToStatementList(struct StatementList * list, struct Statement *stmt)
{
	// если в списке уже чтото есть
	if(list != NULL)
	{
		// и есть что добавлять
		if(stmt != NULL)
		{
			list->last->next = stmt;
			list->last = stmt;
			return list;
		}
	}
	else
		return CreateStatementList(stmt);
}

//создание выражение для id
struct Parameter * CreateParameter(char * name, struct Expression * def, int named)
{
	struct Parameter *result = (struct Parameter *)malloc(sizeof(struct Parameter));
	
	result->def = def;
	result->name = name;
    result->named = named;
	return result;
}

// создание списка param
struct ParameterList * CreateParameterList(struct Parameter *param)
{
	struct ParameterList *result=(struct ParameterList *)malloc(sizeof(struct ParameterList));
	result->first = NULL;
	result->last = NULL;

	if(param != NULL)
	{
		result->first = param;
		result->last = param;
		return result;
	}
	else
	{
		return NULL;
	}
}

// добавление в список param
struct ParameterList * AddToParameterList(struct ParameterList * list, struct Parameter *param)
{
	// если в списке уже чтото есть
	if(list != NULL)
	{
		// и есть что добавлять
		if(param != NULL)
		{
			list->last->next = param;
			list->last = param;
			return list;
		}
	}
	else
		return CreateParameterList(param);
}

struct Definition * CreateDefinition(char *name, struct ParameterList * parameters, struct StatementList * statements)
{
	struct Definition *result = (struct Definition *) malloc(sizeof(struct Definition));
	//очищаем элементы структуры
	result->name = NULL;
	result->parameters = NULL;
	result->statements = NULL;

	result->name = name;
	result->parameters = parameters;
	result->statements = statements;
	return result;
}

struct ClassInfo * CreateClassInfo(char * name, struct Expression *parent, struct StatementList *statements)
{
	struct ClassInfo * result = (struct ClassInfo *) malloc(sizeof(struct ClassInfo));
	result->name = NULL;
	result->parent = NULL;
    result->statements = NULL;
	
	result->name = name;
	result->parent = parent;
	result->statements = statements;
	return result;
}

// создание списка
struct ExternalDeclarationList * CreateExternalDeclarationList(struct ExternalDeclaration * decl)
{
    struct ExternalDeclarationList *result=(struct ExternalDeclarationList *)malloc(sizeof(struct ExternalDeclarationList));
    result->first = NULL;
    result->last = NULL;

    if(decl != NULL)
    {
        result->first = decl;
        result->last = decl;
        return result;
    }
    else
    {
        return NULL;
    }
}

// добавление в список
struct ExternalDeclarationList * AddToExternalDeclarationList(struct ExternalDeclarationList * list, struct ExternalDeclaration * decl)
{
    // если в списке уже чтото есть
    if(list != NULL)
    {
        // и есть что добавлять
        if(decl != NULL)
        {
            list->last->next = decl;
            list->last = decl;
            return list;
        }
    }
    else
        return CreateExternalDeclarationList(decl);
}

void CleanExternalDeclaration(struct ExternalDeclaration * result)
{
    result->function = NULL;
    result->classInfo = NULL;
    result->next = NULL;
}

struct ExternalDeclaration * CreateFuncExternalDeclaration(struct Definition * func)
{
    struct ExternalDeclaration * result = (struct ExternalDeclaration *) malloc(sizeof(struct ExternalDeclaration));
    CleanExternalDeclaration(result);

    result->type = ExternalDeclarationFunction;
    result->function = func;
    return result;
}

struct ExternalDeclaration * CreateStmtExternalDeclaration(struct Statement * stmt)
{
    struct ExternalDeclaration * result = (struct ExternalDeclaration *) malloc(sizeof(struct ExternalDeclaration));
    CleanExternalDeclaration(result);

    result->type = ExternalDeclarationStmt;
    result->stmt = stmt;
    return result;
}

struct ExternalDeclaration * CreateClassExternalDeclaration(struct ClassInfo * classInfo)
{
    struct ExternalDeclaration * result = (struct ExternalDeclaration *) malloc(sizeof(struct ExternalDeclaration));
    CleanExternalDeclaration(result);

    result->type = ExternalDeclarationClassInfo;
    result->classInfo = classInfo;
    return result;
}

void CleanLabeledStatement(struct LabeledStatement *lstmt)
{
    lstmt->type = 0;
    lstmt->block = NULL;
    lstmt->next = NULL;
    lstmt->expr = NULL;
}

struct LabeledStatement * CreateLabeledStatement(enum LabeledStatementType type, struct Expression * expr, struct Statement * block)
{
    struct LabeledStatement *result = (struct LabeledStatement *) malloc(sizeof(struct LabeledStatement));
    CleanLabeledStatement(result);

    result->type = type;
    result->expr = expr;
    result->block = block;

    return result;
}

// создание списка
struct LabeledStatementList * CreateLabeledStatementList(struct LabeledStatement * stmt)
{
    struct LabeledStatementList *result=(struct LabeledStatementList *)malloc(sizeof(struct LabeledStatementList));
    result->first = NULL;
    result->last = NULL;

    if(stmt != NULL)
    {
        result->first = stmt;
        result->last = stmt;
        return result;
    }
    else
    {
        return NULL;
    }
}

// добавление в лист
struct LabeledStatementList * AddToLabeledStatementList(struct LabeledStatementList * list, struct LabeledStatement * stmt)
{
    // если в списке уже чтото есть
    if(list != NULL)
    {
        // и есть что добавлять
        if(stmt != NULL)
        {
            list->last->next = stmt;
            list->last = stmt;
            return list;
        }
    }
    else
        return CreateLabeledStatementList(stmt);
}

struct Statement * CreateSwitchStatement(struct Expression *condition, struct LabeledStatementList *labeled_list)
{
    struct Statement *result = (struct Statement *) malloc(sizeof(struct Statement));
    CleanStructStatement(result);

    //Трансформируем when в else if
    struct LabeledStatement *labeledStmt = labeled_list->first;
    struct Statement * curStmt = result;

    do{
        curStmt->type = StmtTypeIf;
        if(labeledStmt->type != LabeledStatementTypeDefault){
            curStmt->condition = CreateBinaryExpr(ExprTypeEq, condition, labeledStmt->expr);
        }else{
            curStmt->condition = CreateBoolExpr(1);
        }
            
        curStmt->block = labeledStmt->block;
        if(labeledStmt->next != NULL){
            curStmt->elseBlock = (struct Statement *) malloc(sizeof(struct Statement));;
            curStmt = curStmt->elseBlock;
        }
        labeledStmt = labeledStmt->next;
    }while(labeledStmt != NULL);


    return result;
}
