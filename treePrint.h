#include <stdio.h>
#include <stdlib.h>
#include "xml.h"
#include "structs.h"

extern struct ExternalDeclarationList *root;

int tree_print();

void expression_print(struct Expression * expr);
void expressionlist_print(struct ExpressionList * list);

void statement_print(struct Statement *stmt);
void statementlist_print(struct StatementList* stmts);

void definition_print(struct Definition * func);

void classinfo_print(struct ClassInfo * classinfo);

void externaldeclarationlist_print(struct ExternalDeclarationList * list);

void externaldeclaration_print(struct ExternalDeclaration * extDecl);

int labeled_stmt_print_dot(struct LabeledStatement * labeledStmt);
