/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_GRAMMAR_TAB_H_INCLUDED
# define YY_YY_GRAMMAR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CLASS_ID = 258,
    VAR_METHOD_ID = 259,
    CONSTANT = 260,
    CONSTANT_F = 261,
    STRING_LITERAL = 262,
    IF = 263,
    ELSE = 264,
    WHILE = 265,
    DO = 266,
    RETURN = 267,
    DEF = 268,
    END = 269,
    NEW_LINE = 270,
    CLASS = 271,
    ELSIF = 272,
    UNLESS = 273,
    AND_ASSIGN_OP = 274,
    OR_ASSIGN_OP = 275,
    BEGIN_K = 276,
    ALIAS = 277,
    BREAK = 278,
    CASE = 279,
    DEFINED = 280,
    ENSURE = 281,
    FOR = 282,
    IN = 283,
    MODULE = 284,
    NEXT = 285,
    OR_OP = 286,
    AND_OP = 287,
    REDO = 288,
    RESCUE = 289,
    RETRY = 290,
    SELF = 291,
    SUPER = 292,
    THEN = 293,
    UNDEF = 294,
    UNTIL = 295,
    WHEN = 296,
    TRUE = 297,
    FALSE = 298,
    UMINUS = 299,
    UPLUS = 300,
    UCOLON = 301,
    YIELD = 302,
    NIL = 303,
    ADD_ASSIGN_OP = 304,
    SUB_ASSIGN_OP = 305,
    MULT_ASSIGN_OP = 306,
    COMPARE_OP = 307,
    DOUBLE_COLON_OP = 308,
    RANGE_OUT_OP = 309,
    RANGE_IN_OP = 310,
    DIV_ASSIGN_OP = 311,
    MOD_ASSIGN_OP = 312,
    EXP_ASSIGN_OP = 313,
    EXP_OP = 314,
    EQ_STRONG_OP = 315,
    EQ_OP = 316,
    LE_EQ_OP = 317,
    GR_EQ_OP = 318,
    NOT_OP = 319,
    NOT_EQ_OP = 320,
    PRIVATE = 321,
    AND = 322,
    OR = 323,
    NOT = 324,
    PUSH_OP = 325
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "grammar.y"

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

#line 148 "grammar.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GRAMMAR_TAB_H_INCLUDED  */
