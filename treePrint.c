#include "treePrint.h"

int tree_print()
{
	if(root)
	{
		openTag("File");
        externaldeclarationlist_print(root);
		closeTag("File");
	}
	else
	{
		// иначе выводим сообщение об ошибке - ParseError
		printTag("Error", "Parse Error");
	}
	return 0;
}

void externaldeclarationlist_print(struct ExternalDeclarationList * list)
{
	struct ExternalDeclaration* extDecl = NULL;
	if(list != NULL)
	{
		extDecl = list->first;

		while(extDecl != NULL)
		{
			externaldeclaration_print(extDecl);
			extDecl = extDecl->next;
		}
	}
}

void externaldeclaration_print(struct ExternalDeclaration * extDecl)
{
	if(extDecl != NULL)
	{
		switch(extDecl->type)
		{
			case ExternalDeclarationClassInfo:
                openTag("ExternalDeclaration");
                classinfo_print(extDecl->classInfo);
                closeTag("ExternalDeclaration");
            break;
            case ExternalDeclarationFunction:
                openTag("ExternalDeclaration");
                definition_print(extDecl->function);
                closeTag("ExternalDeclaration");
            break;
            case ExternalDeclarationStmt:
                openTag("ExternalDeclaration");
                statement_print(extDecl->stmt);
                closeTag("ExternalDeclaration");
            break;
        }
	}
}

void expressionlist_print(struct ExpressionList * list)
{
	struct Expression * expr = NULL;
	if(list != NULL)
	{
		expr = list->first;

		while(expr != NULL)
		{
            openTag("expr");
			expression_print(expr);
            closeTag("expr");
			expr = expr->next;
		}
	}
}

void expression_print(struct Expression * expr)
{
	char numberString[50] = {0};
				
	if(expr != NULL)
	{
		switch(expr->type)
		{
			case ExprTypeAssign:
				openTag("Assign");
				expression_print(expr->left);
                openTag("Value");
				expression_print(expr->right);
                closeTag("Value");
				closeTag("Assign");
				break;
			case ExprTypeOr:
				openTag("Or");
                openTag("left");
				expression_print(expr->left);
                closeTag("left");
                openTag("right");
				expression_print(expr->right);
                closeTag("right");
				closeTag("Or");
				break;
			case ExprTypeAnd:
				openTag("And");
                openTag("left");
				expression_print(expr->left);
                closeTag("left");
                openTag("right");
				expression_print(expr->right);
                closeTag("right");
				closeTag("And");
				break;
            case ExprTypePush:
				openTag("Push");
                openTag("left");
				expression_print(expr->left);
                closeTag("left");
                openTag("right");
				expression_print(expr->right);
                closeTag("right");
				closeTag("Push");
				break;
			case ExprTypeLt:
				openTag("Lt");
                openTag("left");
				expression_print(expr->left);
                closeTag("left");
                openTag("right");
				expression_print(expr->right);
                closeTag("right");
				closeTag("Lt");
				break;
            case ExprTypeGr:
				openTag("Gt");
                openTag("left");
				expression_print(expr->left);
                closeTag("left");
                openTag("right");
				expression_print(expr->right);
                closeTag("right");
				closeTag("Gt");
				break;
			case ExprTypeLE:
				openTag("Le");
                openTag("left");
				expression_print(expr->left);
                closeTag("left");
                openTag("right");
				expression_print(expr->right);
                closeTag("right");
				closeTag("Le");
				break;
            case ExprTypeGE:
				openTag("Ge");
                openTag("left");
				expression_print(expr->left);
                closeTag("left");
                openTag("right");
				expression_print(expr->right);
                closeTag("right");
				closeTag("Ge");
				break;
			case ExprTypeEq:
				openTag("Eq");
                openTag("left");
				expression_print(expr->left);
                closeTag("left");
                openTag("right");
				expression_print(expr->right);
                closeTag("right");
				closeTag("Eq");
				break;
            case ExprTypeNotEq:
				openTag("NotEq");
				expression_print(expr->left);
				expression_print(expr->right);
				closeTag("NotEq");
				break;
			case ExprTypePlus:
				openTag("Plus");
                openTag("left");
				expression_print(expr->left);
                closeTag("left");
                openTag("right");
				expression_print(expr->right);
                closeTag("right");
				closeTag("Plus");
				break;
			case ExprTypeMinus:
				openTag("Minus");
                openTag("left");
				expression_print(expr->left);
                closeTag("left");
                openTag("right");
				expression_print(expr->right);
                closeTag("right");
				closeTag("Minus");
				break;
			case ExprTypeMul:
				openTag("Mul");
                openTag("left");
				expression_print(expr->left);
                closeTag("left");
                openTag("right");
				expression_print(expr->right);
                closeTag("right");
				closeTag("Mul");
				break;
			case ExprTypeDiv:
				openTag("Div");
                openTag("left");
				expression_print(expr->left);
                closeTag("left");
                openTag("right");
				expression_print(expr->right);
                closeTag("right");
				closeTag("Div");
				break;
			case ExprTypeMod:
				openTag("Mod");
				expression_print(expr->left);
				expression_print(expr->right);
				closeTag("Mod");
				break;
			case ExprTypeNeg:
				openTag("Neg");
				expression_print(expr->right);
				closeTag("Neg");
				break;
            case ExprTypeCompare:
				openTag("Compare");
				expression_print(expr->right);
				closeTag("Compare");
				break;
            case ExprTypeRangeOut:
				openTag("RangeOut");
				expression_print(expr->right);
				closeTag("RangeOut");
				break;
            case ExprTypeRangeIn:
				openTag("RangeIn");
				expression_print(expr->right);
				closeTag("RangeIn");
				break;
			case ExprTypeUMinus:
				openTag("UMinus");
				expression_print(expr->right);
				closeTag("UMinus");
				break;
            case ExprTypeUPlus:
				openTag("UPlus");
				expression_print(expr->right);
				closeTag("UPlus");
				break;
            case ExprTypeSymbol:
				openTag("Symbol");
				expression_print(expr->right);
				closeTag("Symbol");
				break;
            case ExprTypeDot:
				openTag("Dot");
                openTag("left");
				expression_print(expr->left);
                closeTag("left");
                openTag("right");
				expression_print(expr->right);
                closeTag("right");
				closeTag("Dot");
				break;
			case ExprTypeArrayItemAccess:
				openTag("ArrayItemAccess");
				openTag("array");
				expression_print(expr->left);
				closeTag("array");
				openTag("index");
				expression_print(expr->right);
				closeTag("index");
				closeTag("ArrayItemAccess");
				break;
			case ExprTypeIdentifier:
				printf("\n<Identifier name = \"%s\"/>", expr->name);
				break;
            case ExprTypeClassIdentifier:
				printf("\n<ClassIdentifier name = \"%s\"/>", expr->name);
				break;
			case ExprTypeObjectFieldAccess:
				openTag("ObjectFieldAccess");
				openTag("object");
				expression_print(expr->left);
				closeTag("object");
				printf("\n<field name = \"%s\"/>", expr->name);
				closeTag("ObjectFieldAccess");
				break;
            case ExprTypeFunctionCallArgs:
				printf("\n<FuncCall>");
                if(expr->left != NULL)
                {
                    openTag("func");
					expression_print(expr->left);
					closeTag("func");
                }
				if(expr->arguments != NULL)
				{
					openTag("arguments");
					expressionlist_print(expr->arguments);
					closeTag("arguments");
				}
				closeTag("FuncCall");
				break;
			case ExprTypeArray:
                openTag("Array");
				if(expr->arguments != NULL)
				{
					openTag("elements");
					expressionlist_print(expr->arguments);
					closeTag("elements");
				}
				closeTag("Array");
				break;
			case ExprTypeConstant:
				printf("\n<Const value = \"%d\"/>", expr->num);
				break;
            case ExprTypeNil:
				printf("\n<Nil/>");
				break;
            case ExprTypeConstantF:
				printf("\n<ConstF value = \"%f\"/>", expr->float_num);
				break;
			case ExprTypeString:
				printf("\n<String value = \"%s\"/>", expr->string);
				break;
            case ExprTypeBool:
                printf("\n<Bool value = \"%d\"/>", expr->num);
                break;
		}
	}
}

void statementlist_print(struct StatementList* list)
{
	struct Statement *statement;
	if(list != NULL)
	{
		openTag("StatementList");

		statement = list->first;

		while(statement != NULL)
		{
			statement_print(statement);
			statement = statement->next;
		}
		
		closeTag("StatementList");
	}
}

void statement_print(struct Statement *stmt)
{
	char buff[100]={0};
	if (stmt != NULL)
	{
        openTag("Statement");
		switch(stmt->type) 
		{
			case StmtTypeExpr:
				openTag("Expr");
				expression_print(stmt->expr);
				closeTag("Expr");
				break;
			case StmtTypeIf:
				openTag("If");
				openTag("condition");
				expression_print(stmt->condition);
				closeTag("condition");
				openTag("true");
				statement_print(stmt->block);
				closeTag("true");
				if(stmt->elseBlock != NULL)
				{
					openTag("false");
					statement_print(stmt->elseBlock);
					closeTag("false");
				}
				closeTag("If");
				break;
			case StmtTypeWhile:
				openTag("While");
				openTag("condition");
				expression_print(stmt->condition);
				closeTag("condition");
				openTag("block");
				statement_print(stmt->block);
				closeTag("block");
				closeTag("While");
				break;
			case StmtTypeFor:
				openTag("For");
				openTag("identifier");
				expression_print(stmt->condition);
				closeTag("identifier");
                openTag("expression");
				expression_print(stmt->expr);
				closeTag("expression");
				openTag("block");
				statement_print(stmt->block);
				closeTag("block");
				closeTag("For");
				break;
			case StmtTypeBreak:
				printf("\n<Break/>");
				break;
			case StmtTypeReturn:
				openTag("Return");
				expression_print(stmt->expr);
				closeTag("Return");
				break;
            case StmtDefinition:
                definition_print(stmt->definition);
                break;
            case StmtTypeBlock:
                statementlist_print(stmt->block);
                break;

		}
		closeTag("Statement");
	}
}

void definition_print(struct Definition * func)
{
	if(func != NULL)
	{
        printf("\n<Definition name = \"%s\" >", func->name);
		if(func->parameters != NULL)
		{
			openTag("Parameters");
			struct Parameter *parameter = func->parameters->first;

            while(parameter != NULL)
            {
                printf("\n<Parameter name = \"%s\" >", parameter->name);
                if(parameter->def != NULL) {
                    expression_print(parameter->def);
                }
                closeTag("Parameter");
                parameter = parameter->next;
            }
			closeTag("Parameters");
		}
		openTag("Block");
		statementlist_print(func->statements);
		closeTag("Block");
		closeTag("Definition");
	}
}

void classinfo_print(struct ClassInfo * classinfo)
{
	if(classinfo != NULL)
	{
        printf("\n<Class classname = \"%s\" >", classinfo->name);
        if(classinfo->parent != NULL)
        {
            openTag("Parent");
            expression_print(classinfo->parent);
            closeTag("Parent");
        }
        if(classinfo->statements != NULL)
        {
            statementlist_print(classinfo->statements);
        }

        closeTag("Class");
    }
}

