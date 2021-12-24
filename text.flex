%{
    #include "grammar.tab.h"
    #include "structs.h"
    #include "declarations.h"
	#include <string.h>
	extern int yyparse(void);
    extern int yyerror(char * s);
    int tmp;
	float ftmp;
	char comment[1024];
	char literal[1024];
	int error = 0;
%}

%option noyywrap
%option never-interactive
%option yylineno

var_method_id (_|[a-z])[_a-zA-Z0-9]*
method_id (_|[a-z])[_a-zA-Z0-9]*(\?|!)?
var_id (@@|@|$|_|[a-z])[_a-zA-Z0-9]*
class_id [A-Z][_a-zA-Z0-9]*

%x STRING
%x STRING_SINGLE_QUOTES

%%

private return PRIVATE;

true return TRUE;

false return FALSE;

"BEGIN" return BEGIN_K;

END return END;

alias return ALIAS;

"begin" return BEGIN_K;

break return BREAK;

case return CASE;

class return CLASS;

def return DEF;

defined\? return DEFINED;

do return DO;

else return ELSE;

elsif return ELSIF;

end return END;

ensure return ENSURE;

for return FOR;

if return IF;

in return IN;

module return MODULE;

next return NEXT;

redo return REDO;

rescue return RESCUE;

retry return RETRY;

return return RETURN;

self return SELF;

super return SUPER;

then return THEN;

undef return UNDEF;

unless return UNLESS;

until return UNTIL;

when return WHEN;

while return WHILE;

yield return YIELD;

nil return NIL;

"+=" return ADD_ASSIGN_OP;

"-=" return SUB_ASSIGN_OP;

"*=" return MULT_ASSIGN_OP;

"/=" return DIV_ASSIGN_OP;

"%=" return MOD_ASSIGN_OP;

"+" return '+';

"-" return '-';

"**=" return EXP_ASSIGN_OP;

"**" return EXP_OP;

"*" return '*';

"/" return '/';

"%" return '%';

"===" return EQ_STRONG_OP;

"==" return EQ_OP;

"=" return '=';

"!=" return NOT_EQ_OP;

"<=>" return COMPARE_OP;

">=" return GR_EQ_OP;

">" return '>';

"<=" return LE_EQ_OP; 

"<" return '<';

"?" return '?';

"::" return DOUBLE_COLON_OP;

":" return ':';

"..." return RANGE_OUT_OP;

".." return RANGE_IN_OP;

"." return '.';

"," return ',';

"!" return '!';

"not" return NOT;

"&&" return AND_OP;

"&&=" return AND_ASSIGN_OP;

"&&=" return OR_ASSIGN_OP;

"and" return AND;

"||" return OR_OP;

"or" return OR;

"[" return '[';

"]" return ']';

"(" return '(';

")" return ')';

"<<" return PUSH_OP;


-?[0-9]+e[0-9]+ {
    sscanf (yytext, "%d\n", &tmp);
    yylval.int_const = tmp;
    return CONSTANT;
}

-?[0-9]+ {
    sscanf (yytext, "%d\n", &tmp);
    yylval.int_const = tmp;
    return CONSTANT;
}

-?[0-9]+\.e[0-9]+ {
    sscanf (yytext, "%f\n", &ftmp);
    yylval.float_const = ftmp;
    return CONSTANT_F;
}

-?[0-9]+\.[0-9]+ {
    sscanf (yytext, "%f\n", &ftmp);
    yylval.float_const = ftmp;
    return CONSTANT_F;   
}

0[0-7]+ {
    sscanf (yytext, "%o", &tmp);	
    yylval.int_const = tmp;
    return CONSTANT;
}

0x[0-9a-f]+|0X[0-9A-F]+ {
    sscanf(yytext, "%x", &tmp);
	yylval.int_const = tmp;
    return CONSTANT;
}

{class_id} {
	yylval.id = (char *)malloc(strlen(yytext)+1);
	strcpy(yylval.id, yytext);
	return CLASS_ID;
}

{var_method_id} {
	yylval.id = (char *)malloc(strlen(yytext)+1);
	strcpy(yylval.id, yytext);
	return VAR_METHOD_ID;
}

{var_id} {
	yylval.id = (char *)malloc(strlen(yytext)+1);
	strcpy(yylval.id, yytext);
	return VAR_METHOD_ID;
}

{method_id} {
	yylval.id = (char *)malloc(strlen(yytext)+1);
	strcpy(yylval.id, yytext);
	return VAR_METHOD_ID;
}

#.*\n {
    strcpy(comment, yytext);
	return NEW_LINE;
}

\" { strcpy(literal,""); BEGIN(STRING); }
\' { strcpy(literal,""); BEGIN(STRING_SINGLE_QUOTES); }


<STRING,STRING_SINGLE_QUOTES>\\n strcat(literal,"\n");
<STRING,STRING_SINGLE_QUOTES>\\t strcat(literal,"\t");
<STRING,STRING_SINGLE_QUOTES>\\b strcat(literal,"\b");
<STRING,STRING_SINGLE_QUOTES>\\r strcat(literal,"\r");
<STRING,STRING_SINGLE_QUOTES>\\v strcat(literal,"\v");
<STRING,STRING_SINGLE_QUOTES>\\f strcat(literal,"\f");
<STRING,STRING_SINGLE_QUOTES>\\e strcat(literal,"\e");
<STRING,STRING_SINGLE_QUOTES>\\a strcat(literal,"\a");
<STRING,STRING_SINGLE_QUOTES>\\s strcat(literal,"\s");
<STRING,STRING_SINGLE_QUOTES>\\[0-7]{1,3} sprintf(literal, "%s%c", literal, sscanf(yytext, "\\%о", &tmp));
<STRING,STRING_SINGLE_QUOTES>\\x[0-9A-Fa-f]{1,2} sprintf(literal, "%s%c", literal, sscanf(yytext, "x\\%x", &tmp));
<STRING,STRING_SINGLE_QUOTES>\\\\ strcat(literal,"\\");
<STRING>\\\" strcat(literal,"\"");
<STRING_SINGLE_QUOTES>\\\' strcat(literal,"'");
<STRING,STRING_SINGLE_QUOTES><<EOF>> { printf("Unexpected end of input"); error = 1; }


<STRING>\" {
    yylval.string_const = (char *)malloc(strlen(literal) + 1);
    strcpy(yylval.string_const, literal);
    BEGIN(INITIAL);
    return STRING_LITERAL;
}
<STRING_SINGLE_QUOTES>\' {
    yylval.string_const = (char *)malloc(strlen(literal) + 1);
    strcpy(yylval.string_const, literal);
    BEGIN(INITIAL);
    return STRING_LITERAL;
}  
<STRING_SINGLE_QUOTES>. strcat(literal,yytext);
<STRING>. strcat(literal,yytext);

\n return NEW_LINE;


[[:blank:]]+
[\t]+
. { printf("Error, unexpected symbol %s\n", yytext); error = 1; }

%%


int yyerror(char * s)
{
    printf("Error!\n%s on line %d\n", s, yylineno);
    return -1;
}
