#include "treePrint.h"

int index = 1;

int tree_print_dot()
{
	if(root)
	{
		printf("digraph root {\n");
		externaldeclarationlist_print_dot(root);
		printf("}");
	}
	else
	{
		// иначе выводим сообщение об ошибке - ParseError
		printTag("Error", "Parse Error");
	}
	return 0;
}

void externaldeclarationlist_print_dot(struct ExternalDeclarationList * list)
{
	struct ExternalDeclaration* extDecl = NULL;
	if(list != NULL)
	{
		extDecl = list->first;

		while(extDecl != NULL)
		{
			externaldeclaration_print_dot(extDecl);
			extDecl = extDecl->next;
		}
	}
}

void externaldeclaration_print_dot(struct ExternalDeclaration * extDecl)
{
	if(extDecl != NULL)
	{
		switch(extDecl->type)
		{
			case ExternalDeclarationClassInfo:
                classinfo_print_dot(extDecl->classInfo);
            break;
            case ExternalDeclarationFunction:
                index += 1;
                definition_print_dot(extDecl->function);
            break;
            case ExternalDeclarationStmt:
                statement_print_dot(extDecl->stmt);
            break;
        }
	}
}

int expressionlist_print_dot(struct ExpressionList * list)
{
	struct Expression * expr = NULL;
    int current = index;
	if(list != NULL)
	{
        index += 1;
		expr = list->first;
        printf("a%d [label=\"ExprList\"]\n", index);
        current = index;

		while(expr != NULL)
		{
			int next_index = expression_print_dot(expr);
			expr = expr->next;
            printf("a%d -> a%d\n", current, next_index);
		}
	}
	return current;
}

int statementlist_print_dot(struct StatementList* list)
{
	struct Statement *statement;
    int current = index;
	if(list != NULL)
	{
		index += 1;
        
        printf("a%d [label=\"Block\"]\n", index);
        
        current = index;

		statement = list->first;

		while(statement != NULL)
		{
			int next_index = statement_print_dot(statement);
			statement = statement->next;
            printf("a%d -> a%d\n", current, next_index);
		}
		
	}
	return current;
}

int expression_print_dot(struct Expression * expr)
{
	char numberString[50] = {0};
    int current = index;
	if(expr != NULL)
	{
        index += 1;
        current = index;
        int left_index = current;
        int right_index = current;
		switch(expr->type)
		{
			case ExprTypeAssign:
				printf("a%d [label=\"Assign\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
			case ExprTypeOr:
				printf("a%d [label=\"Or\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
			case ExprTypeAnd:
				printf("a%d [label=\"And\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
			case ExprTypeLt:
				printf("a%d [label=\"LT\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
            case ExprTypeGr:
				printf("a%d [label=\"Gr\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
			case ExprTypeLE:
				printf("a%d [label=\"LE\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
            case ExprTypeGE:
				printf("a%d [label=\"GE\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
			case ExprTypeEq:
				printf("a%d [label=\"Eq\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
            case ExprTypeNotEq:
				printf("a%d [label=\"NotEq\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
			case ExprTypePlus:
				printf("a%d [label=\"Plus\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
			case ExprTypeMinus:
				printf("a%d [label=\"Minus\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
			case ExprTypeMul:
				printf("a%d [label=\"Mul\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
			case ExprTypeDiv:
				printf("a%d [label=\"Div\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
			case ExprTypeMod:
				printf("a%d [label=\"Mod\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
			case ExprTypeNeg:
				printf("a%d [label=\"Neg\"]\n", index);
				right_index = expression_print_dot(expr->right);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
            case ExprTypeCompare:
				printf("a%d [label=\"Compare\"]\n", index);
                left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
            case ExprTypeRangeOut:
				printf("a%d [label=\"RangeOut\"]\n", index);
                left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
            case ExprTypeRangeIn:
				printf("a%d [label=\"RangeIn\"]\n", index);
                left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
			case ExprTypeUMinus:
                printf("a%d [label=\"UMinus\"]\n", index);
				right_index = expression_print_dot(expr->right);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
            case ExprTypeUPlus:
				printf("a%d [label=\"UPlus\"]\n", index);
				right_index = expression_print_dot(expr->right);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
            case ExprTypeSymbol:
                printf("a%d [label=\"Symbol\"]\n", index);
				right_index = expression_print_dot(expr->right);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
            case ExprTypeDot:
                printf("a%d [label=\"Dot\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expression_print_dot(expr->right);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
			case ExprTypeArrayItemAccess:
				openTag("ArrayItemAccess");
				openTag("array");
				expression_print_dot(expr->left);
				closeTag("array");
				openTag("index");
				expression_print_dot(expr->right);
				closeTag("index");
				closeTag("ArrayItemAccess");
				break;
			case ExprTypeIdentifier:
                printf("a%d [label=\"Identifier %s\"]\n", index, expr->name);
				break;
			case ExprTypeObjectFieldAccess:
				openTag("ObjectFieldAccess");
				openTag("object");
				expression_print_dot(expr->left);
				closeTag("object");
				printf("\n<field name = \"%s\"/>", expr->name);
				closeTag("ObjectFieldAccess");
				break;
			case ExprTypeFunctionCallArgs:
                printf("a%d [label=\"FuncCall\"]\n", index);
				left_index = expression_print_dot(expr->left);
				right_index = expressionlist_print_dot(expr->arguments);
                if (current != left_index) printf("a%d -> a%d\n", current, left_index);
                if (current != right_index) printf("a%d -> a%d\n", current, right_index);
				break;
			case ExprTypeConstant:
                printf("a%d [label=\"Const %d\"]\n", index, expr->num);
				break;
			case ExprTypeString:
                printf("a%d [label=\"String %s\"]\n", index, expr->string);
				break;
            case ExprTypeBool:
                printf("a%d [label=\"Bool %d\"]\n", index, expr->num);
                break;
		}
	}
	return current;
}

int statement_print_dot(struct Statement *stmt)
{
	char buff[100]={0};
    int current = index;
	if (stmt != NULL)
	{
        index += 1;
        current = index;
        int conditionIndex = current;
        int trueIndex = current;
        int falseIndex = current;
		switch(stmt->type) 
		{
			case StmtTypeExpr:
				printf("a%d [label=\"Expr\"]\n", index);
				expression_print_dot(stmt->expr);
                printf("a%d -> a%d\n", current, current + 1);
				break;
			case StmtTypeIf:
				printf("a%d [label=\"If\"]\n", index);
				
				conditionIndex = expression_print_dot(stmt->condition);
				printf("a%d -> a%d [label=\"Condition\"]\n", current, conditionIndex);
				
				trueIndex = statement_print_dot(stmt->block);
				printf("a%d -> a%d [label=\"True\"]\n", current, trueIndex);
                
				if(stmt->elseBlock != NULL)
				{
					falseIndex = statement_print_dot(stmt->elseBlock);
					printf("a%d -> a%d [label=\"False\"]\n", current, falseIndex);
				}
				break;
			case StmtTypeWhile:
				printf("a%d [label=\"While\"]\n", index);
				
				conditionIndex = expression_print_dot(stmt->condition);
				printf("a%d -> a%d [label=\"Condition\"]\n", current, conditionIndex);
                
				trueIndex = statement_print_dot(stmt->block);
                printf("a%d -> a%d [label=\"Block\"]\n", current, trueIndex);
				break;
			case StmtTypeFor:
				printf("a%d [label=\"For\"]\n", index);
				
				int identifierIndex = expression_print_dot(stmt->condition);
                
                printf("a%d -> a%d [label=\"identifier\"]\n", current, identifierIndex);
				
                int exprIndex = expression_print_dot(stmt->expr);
                printf("a%d -> a%d [label=\"expression\"]\n", current, exprIndex);
				
				int blockIndex = statement_print_dot(stmt->block);
				printf("a%d -> a%d [label=\"block\"]\n", current, blockIndex);
				
				break;
			case StmtTypeBreak:
                printf("a%d [label=\"Break\"]\n", index);
				break;
			case StmtTypeReturn:
				exprIndex = expression_print_dot(stmt->expr);
				printf("a%d -> a%d [label=\"return\"]\n", current, exprIndex);
				break;
            case StmtDefinition:
                definition_print_dot(stmt->definition);
                break;
            case StmtTypeBlock:
                current = statementlist_print_dot(stmt->block);
                break;

		}
	}
	return current;
}


void definition_print_dot(struct Definition * func)
{
	if(func != NULL)
	{
        int current = index;
        printf("a%d [label=\"Definition %s\"]\n", index, func->name);
		if(func->parameters != NULL)
		{
			//parameters
		}
		int current1 = statementlist_print_dot(func->statements);
        if (current != current1) printf("a%d -> a%d\n", current, current1);
	}
}

int classinfo_print_dot(struct ClassInfo * classinfo)
{
	if(classinfo != NULL)
	{
        index += 1;
        printf("a%d [label=\"Class %s\"]\n", index, classinfo->name);
        int current = index;
        if(classinfo->parent != NULL)
        {
            expression_print_dot(classinfo->parent);
            printf("a%d -> a%d [label=\"parent\"]\n", current, current + 1);
        }
    
        if(classinfo->statements != NULL)
        {
            int current1 = statementlist_print_dot(classinfo->statements);
            if (current != current1) printf("a%d -> a%d\n", current, current1);
        }

    }
}

