%{
        #include <malloc.h>
        #include "structs.h"
        #include "declarations.h"

        extern int yylex(void);
        extern int yydebug=0;

        struct ExternalDeclarationList *root;

        #define YYERROR_VERBOSE 0
%}

%union {
        int int_const;
        float float_const;
        char *string_const;
        char *id;

        struct Parameter *parameter;
        struct ParameterList *parameterList;
        struct Expression *expr;
        struct ExpressionList *exprList;
        struct Statement *stmt;
        struct StatementList *stmtList;
		struct Definition *def;
		struct ClassInfo *classInfo;
		struct ExternalDeclarationList *program;
		struct ExternalDeclaration *extDecl;
		struct LabeledStatement * lbldStmt;
		struct LabeledStatementList *lbldStmtList;
}

%type <expr>			expression
%type <exprList>        expression_list
%type <stmt> 			statement if_statement if_line_statement selection_statement elsif_statement statement_of_class compound_statement
%type <stmtList> 		statement_list statement_list_of_class definitions_list
%type <def>             definition
%type <program>			translation_unit program_unit
%type <extDecl>			external_declaration
%type <classInfo>       class_definition
%type <lbldStmt> 		labeled_statement
%type <lbldStmtList> 	labeled_statement_list
%type <parameterList>   parameter_list
%type <parameter>       parameter


%token <id> CLASS_ID VAR_METHOD_ID
%token <int_const> CONSTANT
%token <float_const> CONSTANT_F
%token <string_const> STRING_LITERAL
%token IF ELSE WHILE DO RETURN DEF END NEW_LINE CLASS ELSIF UNLESS AND_ASSIGN_OP OR_ASSIGN_OP
%token BEGIN_K ALIAS BREAK CASE DEFINED ENSURE FOR IN MODULE NEXT OR_OP AND_OP
%token REDO RESCUE RETRY SELF SUPER THEN UNDEF UNTIL WHEN TRUE FALSE UMINUS UPLUS UCOLON
%token YIELD NIL ADD_ASSIGN_OP SUB_ASSIGN_OP MULT_ASSIGN_OP COMPARE_OP DOUBLE_COLON_OP RANGE_OUT_OP RANGE_IN_OP
%token DIV_ASSIGN_OP MOD_ASSIGN_OP EXP_ASSIGN_OP EXP_OP EQ_STRONG_OP EQ_OP LE_EQ_OP GR_EQ_OP NOT_OP NOT_EQ_OP PRIVATE

%start program_unit



%nonassoc IF UNLESS WHILE UNTIL IN
%left AND OR
%right NOT
%nonassoc DEFINED
%right AND_ASSIGN_OP OR_ASSIGN_OP
%right EXP_ASSIGN_OP MULT_ASSIGN_OP SUB_ASSIGN_OP ADD_ASSIGN_OP DIV_ASSIGN_OP MOD_ASSIGN_OP
%right '='
%left RESCUE
%nonassoc RANGE_OUT_OP RANGE_IN_OP
%left OR_OP
%left AND_OP
%nonassoc EQ_OP EQ_STRONG_OP NOT_EQ_OP COMPARE_OP
%left LE_EQ_OP GR_EQ_OP '>' '<'
%left PUSH_OP
%left '+' '-'
%left '*' '/' '%'
%right UMINUS
%right EXP_OP
%right '!' UPLUS
%left '.' '['
%nonassoc ')' '('
%right DOUBLE_COLON_OP
%nonassoc UCOLON
%%

new_line        : NEW_LINE
                | new_line NEW_LINE
                ;
                
opt_nl 	: /**/
		| new_line
		;                

expression
                : expression '=' opt_nl expression    {$$ = CreateBinaryExpr(ExprTypeAssign, 	$1, $4);}
                | expression OR_OP opt_nl expression  {$$ = CreateBinaryExpr(ExprTypeOr, 		$1, $4);}
                | expression OR opt_nl expression     {$$ = CreateBinaryExpr(ExprTypeOr, 		$1, $4);}
                | expression AND_OP opt_nl expression {$$ = CreateBinaryExpr(ExprTypeAnd, 	$1, $4);}
                | expression PUSH_OP opt_nl expression {$$ = CreateBinaryExpr(ExprTypePush, 	$1, $4);}
                | expression AND opt_nl expression    {$$ = CreateBinaryExpr(ExprTypeAnd, 	$1, $4);}
                | expression '<' opt_nl expression    {$$ = CreateBinaryExpr(ExprTypeLt, 		$1, $4);}
                | expression LE_EQ_OP opt_nl expression {$$ = CreateBinaryExpr(ExprTypeLE, 	$1, $4);}
                | expression '>' opt_nl expression    {$$ = CreateBinaryExpr(ExprTypeGr, 		$1, $4);}
                | expression GR_EQ_OP opt_nl expression {$$ = CreateBinaryExpr(ExprTypeGE, 	$1, $4);}
                | expression EQ_OP opt_nl expression  {$$ = CreateBinaryExpr(ExprTypeEq, 		$1, $4);}
                | expression '+' opt_nl expression    {$$ = CreateBinaryExpr(ExprTypePlus, 	$1, $4);}
                | expression '-' opt_nl expression    {$$ = CreateBinaryExpr(ExprTypeMinus, 	$1, $4);}
                | expression '*' opt_nl expression    {$$ = CreateBinaryExpr(ExprTypeMul, 	$1, $4);}
                | expression '/' opt_nl expression    {$$ = CreateBinaryExpr(ExprTypeDiv, 	$1, $4);}
                | expression '%' opt_nl expression    {$$ = CreateBinaryExpr(ExprTypeMod, 	$1, $4);}
                | expression '.' opt_nl VAR_METHOD_ID    {$$ = CreateBinaryExpr(ExprTypeDot,     $1, CreateIdentifierExpr($4));}
                | expression '.' opt_nl '(' opt_nl expression_list opt_nl ')'     {$$ = CreateFunctionCallExpr( CreateBinaryExpr(ExprTypeDot, $1, CreateIdentifierExpr("call")), $6);} //Алиас для call
                | expression '.' opt_nl CLASS         {$$ = CreateBinaryExpr(ExprTypeDot,     $1, CreateIdentifierExpr("class"));}
                | expression DOUBLE_COLON_OP opt_nl expression {$$ = CreateBinaryExpr(ExprTypeDot,     $1, $4);}
                | '!' opt_nl expression               {$$ = CreateUnaryExpr(ExprTypeNeg,      $3);}
                | NOT opt_nl expression               {$$ = CreateUnaryExpr(ExprTypeNeg,      $3);}
                | '-' opt_nl expression %prec UMINUS  {$$ = CreateUnaryExpr(ExprTypeUMinus,   $3);}
                | '+' opt_nl expression %prec UPLUS   {$$ = CreateUnaryExpr(ExprTypeUPlus,    $3);}
                | ':' expression %prec UCOLON           {$$ = CreateUnaryExpr(ExprTypeSymbol,   $2);}
                | expression '[' opt_nl expression opt_nl ']' {$$ = CreateBinaryExpr(ExprTypeArrayItemAccess, $1, $4);}
                | '[' opt_nl expression_list opt_nl ']' {$$ = CreateArrayExpr($3);}
                | expression '(' opt_nl expression_list opt_nl ')' {$$ = CreateFunctionCallExpr($1, $4);}
                | VAR_METHOD_ID	                        {$$ = CreateIdentifierExpr($1);}
                | CLASS_ID	                            {$$ = CreateClassIdentifierExpr($1);}
                | CONSTANT                              {$$ = CreateConstantExpr($1);}
                | CONSTANT_F                            {$$ = CreateFloatConstantExpr($1);}
                | TRUE                                  {$$ = CreateBoolExpr(1);}
                | FALSE                                 {$$ = CreateBoolExpr(0);}
                | STRING_LITERAL                        {$$ = CreateStringExpr($1);}
                | SUPER                                 {$$ = CreateSuperExpr();}
                | NIL                                   {$$ = CreateNilExpr();}
                | SELF                                   {$$ = CreateIdentifierExpr("self");}
                | '(' opt_nl expression opt_nl ')'      {$$ = $3;}
                ;
//список аргументов выражения
expression_list
                : expression                                  {$$ = CreateExpressionList($1); }
                | expression_list ',' new_line expression     {if ($1 == NULL) $$ = CreateExpressionList($4); else $$ = AddToExpressionList($1, $4);}
                | expression_list ',' expression              {if ($1 == NULL) $$ = CreateExpressionList($3); else $$ = AddToExpressionList($1, $3);}
                ;
    
    
//выражение
statement
                : expression NEW_LINE		                    {$$ = CreateExprStatement($1);}
                | selection_statement 		                    {$$ = $1;}
                | WHILE expression new_line compound_statement END  {$$ = CreateWhileStatement($2, $4);}
                | expression WHILE expression                   {$$ = CreateWhileStatement($3, CreateExprStatement($1));}
                | FOR VAR_METHOD_ID IN expression new_line compound_statement END  {$$ = CreateForStatement(CreateIdentifierExpr($2), $4, $6);}
                | statement NEW_LINE                            {$$ = $1;}
                | CASE expression new_line labeled_statement_list END	{$$ = CreateSwitchStatement($2, $4);}
                ; 
                
compound_statement 
                : statement_list                                {$$ = CreateCompoundStatement($1);}
                ;
statement_of_class 
                : definition new_line                           {$$ = CreateDefinitionStatement($1);}
                | statement                                     {$$ = CreateStmtExternalDeclaration($1);}
                | PRIVATE opt_nl                                {$$ = CreatePrivateStatement();}
                | CLASS PUSH_OP SELF opt_nl definitions_list END opt_nl {$$ = CreateStaticStatement($5);}
                ;
                
definitions_list
                : /*empty*/         		                    {$$ = NULL;}
                | definitions_list definition new_line          {if ($1 == NULL) $$ = CreateStatementList(CreateDefinitionStatement($2)); else $$ = AddToStatementList($1, CreateDefinitionStatement($2));}
                ;

statement_list
                : /*empty*/         		                    {$$ = NULL;}
                | statement_list statement                      {if ($1 == NULL) $$ = CreateStatementList($2); else $$ = AddToStatementList($1, $2);}
                ;
                  
                  
statement_list_of_class
                : /*empty*/         		                    {$$ = NULL;}
                | statement_list_of_class statement_of_class    {if ($1 == NULL) $$ = CreateStatementList($2); else $$ = AddToStatementList($1, $2);}
                ;                  
                
//операторы выбора
if_statement
                : IF expression new_line compound_statement END                              {$$ = CreateIfStatement($2, $4);}
                | IF expression new_line compound_statement elsif_statement                              {$$ = CreateIfElseStatement($2, $4, $5);}
                | UNLESS expression new_line compound_statement END                          {$$ = CreateIfStatement(CreateUnaryExpr(ExprTypeNeg, $2), $4);}
                | IF expression new_line compound_statement ELSE new_line compound_statement END {$$ = CreateIfElseStatement($2, $4, $7);}
                ;
                
elsif_statement 
                : ELSIF expression new_line compound_statement END                                   {$$ = CreateIfStatement($2, $4);}
                | ELSIF expression new_line compound_statement elsif_statement                       {$$ = CreateIfElseStatement($2, $4, $5);}
                | ELSIF expression new_line compound_statement ELSE new_line compound_statement END  {$$ = CreateIfElseStatement($2, $4, $7);}
                ;
                
selection_statement
                : if_statement                                  {$$ = $1;}
                | if_line_statement                             {$$ = $1;}
                ;
                
if_line_statement
                : expression IF expression                       {$$ = CreateIfStatement($3, CreateExprStatement($1));}
                | expression UNLESS expression                   {$$ = CreateIfStatement(CreateUnaryExpr(ExprTypeNeg, $3), CreateExprStatement($1));}
                ;
                
labeled_statement
                : WHEN expression THEN compound_statement       {$$ = CreateLabeledStatement(LabeledStatementTypeCase, $2, $4);}
                | ELSE compound_statement                       {$$ = CreateLabeledStatement(LabeledStatementTypeDefault, NULL, $2);}
                ;

labeled_statement_list
                : labeled_statement							{$$ = CreateLabeledStatementList($1);}
                | labeled_statement_list labeled_statement	{$$ = AddToLabeledStatementList($1, $2);}
                ;                     

// определение функции
definition
                : DEF VAR_METHOD_ID new_line statement_list	END                         {$$ = CreateDefinition($2, NULL, $4);}
                | DEF VAR_METHOD_ID '(' parameter_list ')' new_line statement_list	END {$$ = CreateDefinition($2, $4, $7);}
                | DEF VAR_METHOD_ID parameter_list new_line statement_list	END         {$$ = CreateDefinition($2, $3, $5);}
                | DEF '+' '(' parameter_list ')' new_line statement_list	END {$$ = CreateDefinition("plusROP", $4, $7);}
                | DEF '+' parameter_list new_line statement_list	END         {$$ = CreateDefinition("plusROP", $3, $5);}
                | DEF '-' '(' parameter_list ')' new_line statement_list	END {$$ = CreateDefinition("minusROP", $4, $7);}
                | DEF '-' parameter_list new_line statement_list	END         {$$ = CreateDefinition("minusROP", $3, $5);}
                | DEF '*' '(' parameter_list ')' new_line statement_list	END {$$ = CreateDefinition("multROP", $4, $7);}
                | DEF '*' parameter_list new_line statement_list	END         {$$ = CreateDefinition("multROP", $3, $5);}
                | DEF '/' '(' parameter_list ')' new_line statement_list	END      {$$ = CreateDefinition("divROP", $4, $7);}
                | DEF '/' parameter_list new_line statement_list	END         {$$ = CreateDefinition("divROP", $3, $5);}
                ;
                
parameter       
                : VAR_METHOD_ID                                                         {$$ = CreateParameter($1, NULL, 0);}
                | VAR_METHOD_ID ':' expression                                          {$$ = CreateParameter($1, $3, 1);}
                | VAR_METHOD_ID '=' expression                                          {$$ = CreateParameter($1, $3, 0);}
                ;
                
parameter_list
                : parameter        		                               {$$ = CreateParameterList($1);}
                | parameter_list ',' opt_nl parameter                  {if ($1 == NULL) $$ = CreateParameterList($4); else $$ = AddToParameterList($1, $4);}
                ;                
                
// определение класса
class_definition
                : CLASS CLASS_ID new_line statement_list_of_class END                     {$$ = CreateClassInfo($2, NULL, $4);}
                | CLASS CLASS_ID '<' CLASS_ID new_line statement_list_of_class END      {$$ = CreateClassInfo($2, CreateIdentifierExpr($4), $6);}
                | class_definition NEW_LINE                                               {$$ = $1;}
                ;
                
program_unit
                : translation_unit		                    {root = $1;}
                ;      
                
translation_unit
                : external_declaration						{$$ = CreateExternalDeclarationList($1);}
                | translation_unit external_declaration		{$$ = AddToExternalDeclarationList($1, $2);}
                ;                     
                
external_declaration
                : definition new_line     {$$ = CreateFuncExternalDeclaration($1);}
                | class_definition        {$$ = CreateClassExternalDeclaration($1);}
                | statement               {$$ = CreateStmtExternalDeclaration($1);}
                ;              
            
%%
