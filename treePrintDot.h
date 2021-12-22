#include <stdio.h>
#include <stdlib.h>
#include "xml.h"
#include "structs.h"

extern struct ExternalDeclarationList *root;

int tree_print_dot();

int expression_print_dot(struct Expression * expr);
int expressionlist_print_dot(struct ExpressionList * list);

int statement_print_dot(struct Statement *stmt);
int statementlist_print_dot(struct StatementList* stmts);

void definition_print_dot(struct Definition * func);

void classinfo_print_dot(struct ClassInfo * classinfo);

void externaldeclarationlist_print_dot(struct ExternalDeclarationList * list);

void externaldeclaration_print_dot(struct ExternalDeclaration * extDecl);


