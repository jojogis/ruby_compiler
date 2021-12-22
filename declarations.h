#pragma once
#include "structs.h"
#ifdef __cplusplus
        #define EXTERN_C extern "C" {
#else
        #define EXTERN_C extern
#endif


#ifdef __cplusplus
        #define EXTERN_C_END }
#else
        #define EXTERN_C_END
#endif

EXTERN_C

void CleanStructExpression(struct Expression * expr);

struct Expression * CreateIdentifierExpr(char * id);

struct Expression * CreateBoolExpr(int num);

struct Expression * CreateSuperExpr();

struct Expression * CreateConstantExpr(int num);

struct Expression * CreateFloatConstantExpr(float num);

struct Expression * CreateStringExpr(char * string);

struct Expression * CreateBinaryExpr(enum ExprType type, struct Expression *left_expr, struct Expression *right_expr);

struct Expression * CreateUnaryExpr(enum ExprType type, struct Expression *expr);

struct Expression * CreateObjectFieldAccessExpr(struct Expression * object, char * field);

struct Expression * CreateFunctionCallExpr(struct Expression * object, struct ExpressionList * args);

struct ExpressionList * CreateExpressionList(struct Expression * expr);

struct ExpressionList * AddToExpressionList(struct ExpressionList * list, struct Expression * expr);

void CleanStructStatement(struct Statement * stmt);

struct Statement * CreateExprStatement(struct Expression *expr);

struct Statement * CreateIfStatement(struct Expression *condition, struct Statement *block);

struct Statement * CreateDefinitionStatement(struct Definition *definition);

struct Statement * CreateIfElseStatement(struct Expression *condition, struct Statement *true_stmt, struct Statement *false_stmt);

struct Statement * CreateWhileStatement(struct Expression *condition, struct Statement *block);

struct Statement * CreateForStatement(struct Expression *identifier, struct Expression *expr, struct Statement *block);

struct Statement * CreateBreakStatement();

struct Statement * CreateReturnStatement(struct Expression *expr);

struct StatementList * CreateStatementList(struct Statement *stmt);

struct StatementList * AddToStatementList(struct StatementList * list, struct Statement *stmt);

struct Definition * CreateDefinition(char *name, struct ParameterList * parameters, struct StatementList * statements);

struct ClassInfo * CreateClassInfo(char * name, struct Expression *parent, struct StatementList *statements);

struct ExternalDeclaration * CreateClassExternalDeclaration(struct ClassInfo * classInfo);

struct ExternalDeclaration * CreateStmtExternalDeclaration(struct Statement * stmt);

struct ExternalDeclaration * CreateFuncExternalDeclaration(struct Definition * func);

void CleanExternalDeclaration(struct ExternalDeclaration * result);

struct ExternalDeclarationList * AddToExternalDeclarationList(struct ExternalDeclarationList * list, struct ExternalDeclaration * decl);

struct ExternalDeclarationList * CreateExternalDeclarationList(struct ExternalDeclaration * decl);

void CleanLabeledStatement(struct LabeledStatement *lstmt);

struct LabeledStatement * CreateLabeledStatement(enum LabeledStatementType type, struct Expression * expr, struct Statement * block);

struct LabeledStatementList * CreateLabeledStatementList(struct LabeledStatement * stmt);

struct LabeledStatementList * AddToLabeledStatementList(struct LabeledStatementList * list, struct LabeledStatement * stmt);

struct Statement * CreateSwitchStatement(struct Expression *condition, struct LabeledStatementList *labeled_list);

struct Statement * CreateCompoundStatement(struct StatementList *stmtList);

struct Parameter * CreateParameter(char * name, struct Expression * def, int named);

struct ParameterList * CreateParameterList(struct Parameter *param);

struct ParameterList * AddToParameterList(struct ParameterList * list, struct Parameter *param);

struct Expression * CreateNilExpr();

struct Expression * CreateArrayExpr(struct ExpressionList * args);

EXTERN_C_END
