/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "grammar.y"

        #include <malloc.h>
        #include "structs.h"
        #include "declarations.h"

        extern int yylex(void);
        extern int yydebug=0;

        struct ExternalDeclarationList *root;

        #define YYERROR_VERBOSE 0

#line 83 "grammar.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 226 "grammar.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GRAMMAR_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  82
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1455

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  280

#define YYUNDEFTOK  2
#define YYMAXUTOK   325


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    79,     2,     2,     2,    78,     2,     2,
      83,    82,    76,    74,    86,    75,    80,    77,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    84,     2,
      72,    70,    71,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    81,     2,    85,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    73
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    87,    87,    88,    91,    92,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   138,   139,   140,   146,   147,
     148,   149,   150,   151,   152,   156,   159,   160,   161,   162,
     166,   167,   171,   172,   177,   178,   183,   184,   185,   186,
     190,   191,   192,   196,   197,   201,   202,   206,   207,   211,
     212,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   231,   232,   233,   237,   238,   243,   244,   245,
     249,   253,   254,   258,   259,   260
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS_ID", "VAR_METHOD_ID", "CONSTANT",
  "CONSTANT_F", "STRING_LITERAL", "IF", "ELSE", "WHILE", "DO", "RETURN",
  "DEF", "END", "NEW_LINE", "CLASS", "ELSIF", "UNLESS", "AND_ASSIGN_OP",
  "OR_ASSIGN_OP", "BEGIN_K", "ALIAS", "BREAK", "CASE", "DEFINED", "ENSURE",
  "FOR", "IN", "MODULE", "NEXT", "OR_OP", "AND_OP", "REDO", "RESCUE",
  "RETRY", "SELF", "SUPER", "THEN", "UNDEF", "UNTIL", "WHEN", "TRUE",
  "FALSE", "UMINUS", "UPLUS", "UCOLON", "YIELD", "NIL", "ADD_ASSIGN_OP",
  "SUB_ASSIGN_OP", "MULT_ASSIGN_OP", "COMPARE_OP", "DOUBLE_COLON_OP",
  "RANGE_OUT_OP", "RANGE_IN_OP", "DIV_ASSIGN_OP", "MOD_ASSIGN_OP",
  "EXP_ASSIGN_OP", "EXP_OP", "EQ_STRONG_OP", "EQ_OP", "LE_EQ_OP",
  "GR_EQ_OP", "NOT_OP", "NOT_EQ_OP", "PRIVATE", "AND", "OR", "NOT", "'='",
  "'>'", "'<'", "PUSH_OP", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'.'",
  "'['", "')'", "'('", "':'", "']'", "','", "$accept", "new_line",
  "opt_nl", "expression", "expression_list", "statement",
  "compound_statement", "statement_of_class", "definitions_list",
  "statement_list", "statement_list_of_class", "if_statement",
  "elsif_statement", "selection_statement", "if_line_statement",
  "labeled_statement", "labeled_statement_list", "definition", "parameter",
  "parameter_list", "class_definition", "program_unit", "translation_unit",
  "external_declaration", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
      61,    62,    60,   325,    43,    45,    42,    47,    37,    33,
      46,    91,    41,    40,    58,    93,    44
};
# endif

#define YYPACT_NINF (-145)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     385,  -145,  -145,  -145,  -145,  -145,  1120,  1120,    35,    18,
    1120,  1120,    29,  -145,  -145,  -145,  -145,  -145,    46,    46,
      46,    46,    46,    46,  1120,  1156,    57,  -145,  -145,  -145,
      46,    75,    88,   385,  -145,  1182,  1182,    10,     2,    20,
      24,    25,     5,  1182,  1182,    76,  -145,    91,  1120,  1120,
    1120,  1120,  1120,  1120,  -145,  1120,  1120,  -145,  1120,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,  -145,
      91,  -145,  -145,  -145,    91,    91,   -54,   111,    91,  -145,
      -7,   111,    -7,   111,    -7,   111,    -7,   111,    -7,   113,
      91,    91,    22,  1120,  -145,  1294,   101,   101,   101,  1261,
       0,  1182,  1261,  1261,  1261,  1120,  1120,  1120,  1120,  1120,
    1120,  1120,  1120,  1120,  1120,  1120,  1120,  1120,  1120,  1120,
    1120,  1120,    19,  1120,  1120,    66,   973,   103,  1120,  1120,
     -60,   434,    46,    91,   -50,    91,   -48,    91,    -8,    91,
      40,    91,    46,   254,   110,  -145,  1120,  -145,    73,  1182,
    1022,    44,    43,  1320,  1346,    77,  1372,   241,   241,  1294,
    1294,  1294,   241,   241,   281,   117,   117,   101,   101,   101,
    -145,  -145,    46,  1182,     0,    46,  -145,  1120,  -145,    57,
    -145,  1261,  1261,    46,  -145,   111,   483,    46,   532,    46,
     581,    46,   630,    46,   679,    91,  -145,    58,    46,    57,
    -145,    46,  -145,  -145,  1235,  -145,  -145,    91,  1071,  1261,
    -145,  -145,  1120,    47,    51,    91,  1182,    91,  -145,  -145,
      91,  -145,    91,  -145,    91,  -145,    91,  -145,   336,   100,
    -145,    91,  -145,   129,  1261,     0,  -145,  -145,   134,    91,
     728,   777,   826,   875,   924,  -145,    46,  -145,  -145,    68,
    -145,    67,  -145,  -145,  -145,  -145,  -145,  -145,  -145,    46,
    -145,  -145,    84,    91,    46,    46,   138,  -145,    91,  -145
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    35,    34,    36,    37,    40,     0,     0,     0,     0,
       0,     0,     0,    43,    41,    38,    39,    42,     4,     4,
       4,     4,     4,     4,     0,     0,   105,    73,    49,    74,
       0,   104,     0,   100,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     5,     0,     0,
       0,     0,     0,     0,    30,     0,     0,    48,     0,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,    53,
     103,    99,     1,   102,    62,    62,    92,     0,    62,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      64,    62,     0,     0,     3,    27,    29,    28,    26,    45,
       4,     4,    75,    51,    76,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    55,     0,     0,     0,
       0,     0,     4,    62,     0,    62,     0,    62,     0,    62,
       0,    62,     0,     0,     0,    62,     0,    79,     0,     0,
       0,     0,     0,     7,     9,    25,    16,    13,    15,    11,
       8,     6,    14,    12,    10,    17,    18,    19,    20,    21,
      22,    24,     4,     4,     4,     0,    66,     0,    67,    63,
      50,    94,    93,     0,    81,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    64,    97,     0,     4,    57,
      65,     0,    68,    78,     0,    54,    80,    62,     0,    47,
      32,    44,     0,     0,     0,    62,     0,    62,    96,    83,
      62,    85,    62,    87,    62,    89,    62,    91,     0,     0,
      58,    56,    62,     0,    46,     4,    31,    33,     0,    62,
       0,     0,     0,     0,     0,    98,     4,    77,    52,     0,
      69,     0,    82,    84,    86,    88,    90,    60,    23,     0,
      70,    71,     0,    62,     4,     0,     0,    59,    61,    72
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -145,   -25,   -19,    89,  -121,    27,     4,  -145,  -145,   -81,
     -49,  -145,  -104,  -145,  -145,     3,  -145,  -144,   -37,    80,
    -145,  -145,  -145,   133
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    47,    48,    25,   110,   189,   135,   210,   272,   136,
     153,    27,   188,    28,    29,   157,   158,    30,    89,    90,
      31,    32,    33,    34
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    50,    51,    52,    53,    80,    86,   141,    46,   211,
      84,    85,    88,   184,    86,    46,   138,   100,   101,   102,
      46,    42,   193,   180,    86,    46,   142,    26,    86,    86,
     139,   155,   197,    45,   199,   181,   142,   104,   142,    37,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
      26,    46,   196,   156,   198,   143,   200,   145,   202,   147,
     204,   149,    79,   151,   201,   185,   269,    99,   142,   142,
     186,   270,   155,   187,   187,    91,   160,   215,    82,   137,
      81,   161,   162,    87,   211,    35,    36,     8,   274,    43,
      44,   245,   182,    93,   103,   154,   104,    95,    97,    38,
      39,    40,    41,    54,   156,    86,   152,   190,    92,    94,
      96,    98,   203,   195,   212,   221,   142,   205,   275,   220,
      61,   239,   246,   247,   217,   218,   256,   105,   106,   107,
     108,   109,   111,   258,   112,   113,   250,   114,   260,   251,
     268,   252,   279,   253,    61,   254,   238,   271,   228,   213,
     225,   216,     0,   222,   223,   224,    83,   140,   227,     0,
      61,   144,   230,   146,   232,   148,   234,   150,   236,     0,
     209,    76,    77,     0,    78,     0,   241,     0,     0,   240,
       0,     0,   159,    73,    74,    75,     0,    76,    77,     0,
      78,   249,     0,     0,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   243,   183,   109,     0,     0,   259,   191,   192,   248,
       0,     0,     0,     0,     0,     0,     0,   267,     0,     0,
       0,     0,     0,     0,   273,   214,   257,     0,     0,   219,
     278,     0,     0,   261,     0,   277,     0,     1,     2,     3,
       4,     5,     6,     0,     7,   209,     0,     8,   206,     0,
     207,     0,    10,     0,     0,     0,   226,   276,    11,     0,
       0,    12,     0,     0,     0,     0,     0,     0,     0,     0,
      13,    14,     0,     0,    61,     0,    15,    16,     0,     0,
       0,     0,    17,     0,     0,     0,     0,   244,     0,     0,
       0,   109,     0,     0,    70,    71,    72,    73,    74,    75,
     208,    76,    77,    18,    78,     0,     0,     0,    19,    20,
       0,     0,     0,    21,    61,    22,     0,    23,    24,     1,
       2,     3,     4,     5,     6,     0,     7,     0,     0,     8,
     255,     0,   207,     0,    10,    71,    72,    73,    74,    75,
      11,    76,    77,    12,    78,     0,     0,     0,     0,     0,
       0,     0,    13,    14,     0,     0,     0,     0,    15,    16,
       0,     0,     0,     0,    17,     0,     0,     0,     1,     2,
       3,     4,     5,     6,     0,     7,     0,     0,     8,     0,
       0,     9,   208,    10,     0,    18,     0,     0,     0,    11,
      19,    20,    12,     0,     0,    21,     0,    22,     0,    23,
      24,    13,    14,     0,     0,     0,     0,    15,    16,     0,
       0,     0,     0,    17,     0,     0,     0,     1,     2,     3,
       4,     5,     6,     0,     7,     0,     0,     0,   194,     0,
       0,     0,    10,     0,    18,     0,     0,     0,    11,    19,
      20,    12,     0,     0,    21,     0,    22,     0,    23,    24,
      13,    14,     0,     0,     0,     0,    15,    16,     0,     0,
       0,     0,    17,     0,     0,     0,     1,     2,     3,     4,
       5,     6,     0,     7,     0,     0,     0,   229,     0,     0,
       0,    10,     0,    18,     0,     0,     0,    11,    19,    20,
      12,     0,     0,    21,     0,    22,     0,    23,    24,    13,
      14,     0,     0,     0,     0,    15,    16,     0,     0,     0,
       0,    17,     0,     0,     0,     1,     2,     3,     4,     5,
       6,     0,     7,     0,     0,     0,   231,     0,     0,     0,
      10,     0,    18,     0,     0,     0,    11,    19,    20,    12,
       0,     0,    21,     0,    22,     0,    23,    24,    13,    14,
       0,     0,     0,     0,    15,    16,     0,     0,     0,     0,
      17,     0,     0,     0,     1,     2,     3,     4,     5,     6,
       0,     7,     0,     0,     0,   233,     0,     0,     0,    10,
       0,    18,     0,     0,     0,    11,    19,    20,    12,     0,
       0,    21,     0,    22,     0,    23,    24,    13,    14,     0,
       0,     0,     0,    15,    16,     0,     0,     0,     0,    17,
       0,     0,     0,     1,     2,     3,     4,     5,     6,     0,
       7,     0,     0,     0,   235,     0,     0,     0,    10,     0,
      18,     0,     0,     0,    11,    19,    20,    12,     0,     0,
      21,     0,    22,     0,    23,    24,    13,    14,     0,     0,
       0,     0,    15,    16,     0,     0,     0,     0,    17,     0,
       0,     0,     1,     2,     3,     4,     5,     6,     0,     7,
       0,     0,     0,   237,     0,     0,     0,    10,     0,    18,
       0,     0,     0,    11,    19,    20,    12,     0,     0,    21,
       0,    22,     0,    23,    24,    13,    14,     0,     0,     0,
       0,    15,    16,     0,     0,     0,     0,    17,     0,     0,
       0,     1,     2,     3,     4,     5,     6,     0,     7,     0,
       0,     0,   262,     0,     0,     0,    10,     0,    18,     0,
       0,     0,    11,    19,    20,    12,     0,     0,    21,     0,
      22,     0,    23,    24,    13,    14,     0,     0,     0,     0,
      15,    16,     0,     0,     0,     0,    17,     0,     0,     0,
       1,     2,     3,     4,     5,     6,     0,     7,     0,     0,
       0,   263,     0,     0,     0,    10,     0,    18,     0,     0,
       0,    11,    19,    20,    12,     0,     0,    21,     0,    22,
       0,    23,    24,    13,    14,     0,     0,     0,     0,    15,
      16,     0,     0,     0,     0,    17,     0,     0,     0,     1,
       2,     3,     4,     5,     6,     0,     7,     0,     0,     0,
     264,     0,     0,     0,    10,     0,    18,     0,     0,     0,
      11,    19,    20,    12,     0,     0,    21,     0,    22,     0,
      23,    24,    13,    14,     0,     0,     0,     0,    15,    16,
       0,     0,     0,     0,    17,     0,     0,     0,     1,     2,
       3,     4,     5,     6,     0,     7,     0,     0,     0,   265,
       0,     0,     0,    10,     0,    18,     0,     0,     0,    11,
      19,    20,    12,     0,     0,    21,     0,    22,     0,    23,
      24,    13,    14,     0,     0,     0,     0,    15,    16,     0,
       0,     0,     0,    17,     0,     0,     0,     1,     2,     3,
       4,     5,     6,     0,     7,     0,     0,     0,   266,     0,
       0,     0,    10,     0,    18,     0,     0,     0,    11,    19,
      20,    12,     0,     0,    21,     0,    22,     0,    23,    24,
      13,    14,     0,     0,     0,     0,    15,    16,     0,     0,
       0,     0,    17,     0,     0,     0,     1,     2,     3,     4,
       5,     6,     0,     7,     0,     0,     0,     0,     0,     0,
       0,    10,     0,    18,     0,     0,     0,    11,    19,    20,
      12,     0,     0,    21,     0,    22,     0,    23,    24,    13,
      14,     0,     0,     0,     0,    15,    16,     0,     0,     0,
       0,    17,     0,     0,     0,     1,     2,     3,     4,     5,
       0,     0,     0,     0,     0,     0,     0,    46,     0,     0,
       0,     0,    18,     0,     0,     0,     0,    19,    20,     0,
       0,     0,    21,     0,    22,     0,    23,    24,    13,    14,
       0,     0,     0,     0,    15,    16,     0,     0,     0,     0,
      17,     0,     0,     0,     1,     2,     3,     4,     5,     0,
       0,     0,     0,     0,     0,     0,   104,     0,     0,     0,
       0,    18,     0,     0,     0,     0,    19,    20,     0,     0,
       0,    21,     0,    22,     0,    23,    24,    13,    14,     0,
       0,     0,     0,    15,    16,     0,     0,     0,     0,    17,
       0,     0,     0,     1,     2,     3,     4,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,     0,     0,     0,     0,    19,    20,     0,     0,     0,
      21,     0,    22,     0,    23,    24,    13,    14,     0,     0,
       0,     0,    15,    16,    55,     0,    56,     0,    17,     0,
       0,    57,     0,     0,    58,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,    60,    18,
       0,     0,     0,     0,    19,    20,     0,    46,     0,    21,
       0,    22,     0,    23,    24,     0,     0,     0,     0,    61,
       0,     0,     0,    59,    60,     0,     0,    62,    63,    64,
       0,     0,     0,    65,    66,     0,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    61,    76,    77,     0,    78,
       0,     0,     0,    62,    63,    64,     0,     0,     0,    65,
      66,     0,    67,    68,    69,    70,    71,    72,    73,    74,
      75,     0,    76,    77,     0,    78,    59,    60,     0,     0,
       0,     0,     0,   242,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,     0,
       0,     0,    59,    60,     0,     0,    62,    63,    64,     0,
       0,     0,    65,    66,     0,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    61,    76,    77,     0,    78,     0,
       0,     0,    62,    63,    64,    59,    60,     0,    65,    66,
       0,    67,    68,    69,    70,    71,    72,    73,    74,    75,
       0,    76,    77,     0,    78,     0,     0,    61,     0,     0,
       0,     0,    60,     0,     0,    62,    63,    64,     0,     0,
       0,     0,     0,     0,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    61,    76,    77,     0,    78,     0,     0,
       0,    62,    63,    64,     0,     0,     0,     0,     0,     0,
       0,    68,    69,    70,    71,    72,    73,    74,    75,    61,
      76,    77,     0,    78,     0,     0,     0,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,    68,    69,    70,
      71,    72,    73,    74,    75,    61,    76,    77,     0,    78,
       0,     0,     0,    -1,    63,    64,     0,     0,     0,     0,
       0,     0,     0,    68,    69,    70,    71,    72,    73,    74,
      75,     0,    76,    77,     0,    78
};

static const yytype_int16 yycheck[] =
{
      19,    20,    21,    22,    23,    30,     4,    88,    15,   153,
      35,    36,    37,   134,     4,    15,    70,    42,    43,    44,
      15,     3,    82,     4,     4,    15,    86,     0,     4,     4,
      84,     9,    82,     4,    82,    16,    86,    15,    86,     4,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      33,    15,   143,    41,   145,    90,   147,    92,   149,    94,
     151,    96,    15,    98,    82,     9,     9,    72,    86,    86,
      14,    14,     9,    17,    17,    83,    86,    14,     0,    85,
      15,   110,   111,    83,   238,     6,     7,    13,    14,    10,
      11,   222,    83,    83,    28,   101,    15,    83,    83,    74,
      75,    76,    77,    24,    41,     4,     3,    14,    38,    39,
      40,    41,    82,   142,    14,    82,    86,   152,   272,    85,
      53,    73,    85,    82,   159,   160,    36,    48,    49,    50,
      51,    52,    53,    14,    55,    56,   227,    58,    14,   230,
      82,   232,    14,   234,    53,   236,   205,   261,   195,   155,
     185,   158,    -1,   182,   183,   184,    33,    87,   193,    -1,
      53,    91,   197,    93,   199,    95,   201,    97,   203,    -1,
     153,    80,    81,    -1,    83,    -1,   211,    -1,    -1,   208,
      -1,    -1,   103,    76,    77,    78,    -1,    80,    81,    -1,
      83,   226,    -1,    -1,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   217,   133,   134,    -1,    -1,   245,   138,   139,   225,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   256,    -1,    -1,
      -1,    -1,    -1,    -1,   269,   156,   242,    -1,    -1,   160,
     275,    -1,    -1,   249,    -1,   274,    -1,     3,     4,     5,
       6,     7,     8,    -1,    10,   238,    -1,    13,    14,    -1,
      16,    -1,    18,    -1,    -1,    -1,   187,   273,    24,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    -1,    -1,    53,    -1,    42,    43,    -1,    -1,
      -1,    -1,    48,    -1,    -1,    -1,    -1,   218,    -1,    -1,
      -1,   222,    -1,    -1,    73,    74,    75,    76,    77,    78,
      66,    80,    81,    69,    83,    -1,    -1,    -1,    74,    75,
      -1,    -1,    -1,    79,    53,    81,    -1,    83,    84,     3,
       4,     5,     6,     7,     8,    -1,    10,    -1,    -1,    13,
      14,    -1,    16,    -1,    18,    74,    75,    76,    77,    78,
      24,    80,    81,    27,    83,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    37,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,    -1,    10,    -1,    -1,    13,    -1,
      -1,    16,    66,    18,    -1,    69,    -1,    -1,    -1,    24,
      74,    75,    27,    -1,    -1,    79,    -1,    81,    -1,    83,
      84,    36,    37,    -1,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,    10,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    18,    -1,    69,    -1,    -1,    -1,    24,    74,
      75,    27,    -1,    -1,    79,    -1,    81,    -1,    83,    84,
      36,    37,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,
      -1,    -1,    48,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,    -1,    10,    -1,    -1,    -1,    14,    -1,    -1,
      -1,    18,    -1,    69,    -1,    -1,    -1,    24,    74,    75,
      27,    -1,    -1,    79,    -1,    81,    -1,    83,    84,    36,
      37,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,    10,    -1,    -1,    -1,    14,    -1,    -1,    -1,
      18,    -1,    69,    -1,    -1,    -1,    24,    74,    75,    27,
      -1,    -1,    79,    -1,    81,    -1,    83,    84,    36,    37,
      -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
      -1,    10,    -1,    -1,    -1,    14,    -1,    -1,    -1,    18,
      -1,    69,    -1,    -1,    -1,    24,    74,    75,    27,    -1,
      -1,    79,    -1,    81,    -1,    83,    84,    36,    37,    -1,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,    -1,
      10,    -1,    -1,    -1,    14,    -1,    -1,    -1,    18,    -1,
      69,    -1,    -1,    -1,    24,    74,    75,    27,    -1,    -1,
      79,    -1,    81,    -1,    83,    84,    36,    37,    -1,    -1,
      -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,    -1,    10,
      -1,    -1,    -1,    14,    -1,    -1,    -1,    18,    -1,    69,
      -1,    -1,    -1,    24,    74,    75,    27,    -1,    -1,    79,
      -1,    81,    -1,    83,    84,    36,    37,    -1,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,    -1,    10,    -1,
      -1,    -1,    14,    -1,    -1,    -1,    18,    -1,    69,    -1,
      -1,    -1,    24,    74,    75,    27,    -1,    -1,    79,    -1,
      81,    -1,    83,    84,    36,    37,    -1,    -1,    -1,    -1,
      42,    43,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,    -1,    10,    -1,    -1,
      -1,    14,    -1,    -1,    -1,    18,    -1,    69,    -1,    -1,
      -1,    24,    74,    75,    27,    -1,    -1,    79,    -1,    81,
      -1,    83,    84,    36,    37,    -1,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,    -1,    10,    -1,    -1,    -1,
      14,    -1,    -1,    -1,    18,    -1,    69,    -1,    -1,    -1,
      24,    74,    75,    27,    -1,    -1,    79,    -1,    81,    -1,
      83,    84,    36,    37,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,    -1,    10,    -1,    -1,    -1,    14,
      -1,    -1,    -1,    18,    -1,    69,    -1,    -1,    -1,    24,
      74,    75,    27,    -1,    -1,    79,    -1,    81,    -1,    83,
      84,    36,    37,    -1,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,    10,    -1,    -1,    -1,    14,    -1,
      -1,    -1,    18,    -1,    69,    -1,    -1,    -1,    24,    74,
      75,    27,    -1,    -1,    79,    -1,    81,    -1,    83,    84,
      36,    37,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,
      -1,    -1,    48,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,    -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    18,    -1,    69,    -1,    -1,    -1,    24,    74,    75,
      27,    -1,    -1,    79,    -1,    81,    -1,    83,    84,    36,
      37,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,    -1,    -1,
      -1,    -1,    69,    -1,    -1,    -1,    -1,    74,    75,    -1,
      -1,    -1,    79,    -1,    81,    -1,    83,    84,    36,    37,
      -1,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,
      -1,    69,    -1,    -1,    -1,    -1,    74,    75,    -1,    -1,
      -1,    79,    -1,    81,    -1,    83,    84,    36,    37,    -1,
      -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    -1,    -1,    -1,    -1,    74,    75,    -1,    -1,    -1,
      79,    -1,    81,    -1,    83,    84,    36,    37,    -1,    -1,
      -1,    -1,    42,    43,     8,    -1,    10,    -1,    48,    -1,
      -1,    15,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    69,
      -1,    -1,    -1,    -1,    74,    75,    -1,    15,    -1,    79,
      -1,    81,    -1,    83,    84,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    31,    32,    -1,    -1,    61,    62,    63,
      -1,    -1,    -1,    67,    68,    -1,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    53,    80,    81,    -1,    83,
      -1,    -1,    -1,    61,    62,    63,    -1,    -1,    -1,    67,
      68,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    -1,    80,    81,    -1,    83,    31,    32,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    31,    32,    -1,    -1,    61,    62,    63,    -1,
      -1,    -1,    67,    68,    -1,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    53,    80,    81,    -1,    83,    -1,
      -1,    -1,    61,    62,    63,    31,    32,    -1,    67,    68,
      -1,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      -1,    80,    81,    -1,    83,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    32,    -1,    -1,    61,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    53,    80,    81,    -1,    83,    -1,    -1,
      -1,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    77,    78,    53,
      80,    81,    -1,    83,    -1,    -1,    -1,    61,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    75,    76,    77,    78,    53,    80,    81,    -1,    83,
      -1,    -1,    -1,    61,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    76,    77,
      78,    -1,    80,    81,    -1,    83
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    10,    13,    16,
      18,    24,    27,    36,    37,    42,    43,    48,    69,    74,
      75,    79,    81,    83,    84,    90,    92,    98,   100,   101,
     104,   107,   108,   109,   110,    90,    90,     4,    74,    75,
      76,    77,     3,    90,    90,     4,    15,    88,    89,    89,
      89,    89,    89,    89,    90,     8,    10,    15,    18,    31,
      32,    53,    61,    62,    63,    67,    68,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    80,    81,    83,    15,
      88,    15,     0,   110,    88,    88,     4,    83,    88,   105,
     106,    83,   106,    83,   106,    83,   106,    83,   106,    72,
      88,    88,    88,    28,    15,    90,    90,    90,    90,    90,
      91,    90,    90,    90,    90,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    93,    96,    93,    70,    84,
     106,    96,    86,    88,   106,    88,   106,    88,   106,    88,
     106,    88,     3,    97,    93,     9,    41,   102,   103,    90,
      86,    89,    89,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
       4,    16,    83,    90,    91,     9,    14,    17,    99,    92,
      14,    90,    90,    82,    14,    89,    96,    82,    96,    82,
      96,    82,    96,    82,    96,    88,    14,    16,    66,    92,
      94,   104,    14,    93,    90,    14,   102,    88,    88,    90,
      85,    82,    89,    89,    89,    88,    90,    88,   105,    14,
      88,    14,    88,    14,    88,    14,    88,    14,    97,    73,
      89,    88,    38,    93,    90,    91,    85,    82,    93,    88,
      96,    96,    96,    96,    96,    14,    36,    93,    14,    89,
      14,    93,    14,    14,    14,    14,    14,    89,    82,     9,
      14,    99,    95,    88,    14,   104,    93,    89,    88,    14
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    87,    88,    88,    89,    89,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    91,    91,    91,    92,    92,
      92,    92,    92,    92,    92,    93,    94,    94,    94,    94,
      95,    95,    96,    96,    97,    97,    98,    98,    98,    98,
      99,    99,    99,   100,   100,   101,   101,   102,   102,   103,
     103,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   105,   105,   105,   106,   106,   107,   107,   107,
     108,   109,   109,   110,   110,   110
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     8,     4,     4,     3,     3,     3,     3,
       2,     6,     5,     6,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     1,     4,     3,     2,     1,
       5,     3,     7,     2,     5,     1,     2,     1,     2,     7,
       0,     3,     0,     2,     0,     2,     5,     5,     5,     8,
       5,     5,     8,     1,     1,     3,     3,     4,     2,     1,
       2,     5,     8,     6,     8,     6,     8,     6,     8,     6,
       8,     6,     1,     3,     3,     1,     4,     5,     7,     2,
       1,     1,     2,     2,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 6:
#line 96 "grammar.y"
                                                      {(yyval.expr) = CreateBinaryExpr(ExprTypeAssign, 	(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1826 "grammar.tab.c"
    break;

  case 7:
#line 97 "grammar.y"
                                                      {(yyval.expr) = CreateBinaryExpr(ExprTypeOr, 		(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1832 "grammar.tab.c"
    break;

  case 8:
#line 98 "grammar.y"
                                                      {(yyval.expr) = CreateBinaryExpr(ExprTypeOr, 		(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1838 "grammar.tab.c"
    break;

  case 9:
#line 99 "grammar.y"
                                                      {(yyval.expr) = CreateBinaryExpr(ExprTypeAnd, 	(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1844 "grammar.tab.c"
    break;

  case 10:
#line 100 "grammar.y"
                                                       {(yyval.expr) = CreateBinaryExpr(ExprTypePush, 	(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1850 "grammar.tab.c"
    break;

  case 11:
#line 101 "grammar.y"
                                                      {(yyval.expr) = CreateBinaryExpr(ExprTypeAnd, 	(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1856 "grammar.tab.c"
    break;

  case 12:
#line 102 "grammar.y"
                                                      {(yyval.expr) = CreateBinaryExpr(ExprTypeLt, 		(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1862 "grammar.tab.c"
    break;

  case 13:
#line 103 "grammar.y"
                                                        {(yyval.expr) = CreateBinaryExpr(ExprTypeLE, 	(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1868 "grammar.tab.c"
    break;

  case 14:
#line 104 "grammar.y"
                                                      {(yyval.expr) = CreateBinaryExpr(ExprTypeGr, 		(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1874 "grammar.tab.c"
    break;

  case 15:
#line 105 "grammar.y"
                                                        {(yyval.expr) = CreateBinaryExpr(ExprTypeGE, 	(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1880 "grammar.tab.c"
    break;

  case 16:
#line 106 "grammar.y"
                                                      {(yyval.expr) = CreateBinaryExpr(ExprTypeEq, 		(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1886 "grammar.tab.c"
    break;

  case 17:
#line 107 "grammar.y"
                                                      {(yyval.expr) = CreateBinaryExpr(ExprTypePlus, 	(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1892 "grammar.tab.c"
    break;

  case 18:
#line 108 "grammar.y"
                                                      {(yyval.expr) = CreateBinaryExpr(ExprTypeMinus, 	(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1898 "grammar.tab.c"
    break;

  case 19:
#line 109 "grammar.y"
                                                      {(yyval.expr) = CreateBinaryExpr(ExprTypeMul, 	(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1904 "grammar.tab.c"
    break;

  case 20:
#line 110 "grammar.y"
                                                      {(yyval.expr) = CreateBinaryExpr(ExprTypeDiv, 	(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1910 "grammar.tab.c"
    break;

  case 21:
#line 111 "grammar.y"
                                                      {(yyval.expr) = CreateBinaryExpr(ExprTypeMod, 	(yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1916 "grammar.tab.c"
    break;

  case 22:
#line 112 "grammar.y"
                                                         {(yyval.expr) = CreateBinaryExpr(ExprTypeDot,     (yyvsp[-3].expr), CreateIdentifierExpr((yyvsp[0].id)));}
#line 1922 "grammar.tab.c"
    break;

  case 23:
#line 113 "grammar.y"
                                                                                  {(yyval.expr) = CreateFunctionCallExpr( CreateBinaryExpr(ExprTypeDot, (yyvsp[-7].expr), CreateIdentifierExpr("call")), (yyvsp[-2].exprList));}
#line 1928 "grammar.tab.c"
    break;

  case 24:
#line 114 "grammar.y"
                                                      {(yyval.expr) = CreateBinaryExpr(ExprTypeDot,     (yyvsp[-3].expr), CreateIdentifierExpr("class"));}
#line 1934 "grammar.tab.c"
    break;

  case 25:
#line 115 "grammar.y"
                                                               {(yyval.expr) = CreateBinaryExpr(ExprTypeDot,     (yyvsp[-3].expr), (yyvsp[0].expr));}
#line 1940 "grammar.tab.c"
    break;

  case 26:
#line 116 "grammar.y"
                                                      {(yyval.expr) = CreateUnaryExpr(ExprTypeNeg,      (yyvsp[0].expr));}
#line 1946 "grammar.tab.c"
    break;

  case 27:
#line 117 "grammar.y"
                                                      {(yyval.expr) = CreateUnaryExpr(ExprTypeNeg,      (yyvsp[0].expr));}
#line 1952 "grammar.tab.c"
    break;

  case 28:
#line 118 "grammar.y"
                                                      {(yyval.expr) = CreateUnaryExpr(ExprTypeUMinus,   (yyvsp[0].expr));}
#line 1958 "grammar.tab.c"
    break;

  case 29:
#line 119 "grammar.y"
                                                      {(yyval.expr) = CreateUnaryExpr(ExprTypeUPlus,    (yyvsp[0].expr));}
#line 1964 "grammar.tab.c"
    break;

  case 30:
#line 120 "grammar.y"
                                                        {(yyval.expr) = CreateUnaryExpr(ExprTypeSymbol,   (yyvsp[0].expr));}
#line 1970 "grammar.tab.c"
    break;

  case 31:
#line 121 "grammar.y"
                                                              {(yyval.expr) = CreateBinaryExpr(ExprTypeArrayItemAccess, (yyvsp[-5].expr), (yyvsp[-2].expr));}
#line 1976 "grammar.tab.c"
    break;

  case 32:
#line 122 "grammar.y"
                                                        {(yyval.expr) = CreateArrayExpr((yyvsp[-2].exprList));}
#line 1982 "grammar.tab.c"
    break;

  case 33:
#line 123 "grammar.y"
                                                                   {(yyval.expr) = CreateFunctionCallExpr((yyvsp[-5].expr), (yyvsp[-2].exprList));}
#line 1988 "grammar.tab.c"
    break;

  case 34:
#line 124 "grammar.y"
                                                        {(yyval.expr) = CreateIdentifierExpr((yyvsp[0].id));}
#line 1994 "grammar.tab.c"
    break;

  case 35:
#line 125 "grammar.y"
                                                            {(yyval.expr) = CreateClassIdentifierExpr((yyvsp[0].id));}
#line 2000 "grammar.tab.c"
    break;

  case 36:
#line 126 "grammar.y"
                                                        {(yyval.expr) = CreateConstantExpr((yyvsp[0].int_const));}
#line 2006 "grammar.tab.c"
    break;

  case 37:
#line 127 "grammar.y"
                                                        {(yyval.expr) = CreateFloatConstantExpr((yyvsp[0].float_const));}
#line 2012 "grammar.tab.c"
    break;

  case 38:
#line 128 "grammar.y"
                                                        {(yyval.expr) = CreateBoolExpr(1);}
#line 2018 "grammar.tab.c"
    break;

  case 39:
#line 129 "grammar.y"
                                                        {(yyval.expr) = CreateBoolExpr(0);}
#line 2024 "grammar.tab.c"
    break;

  case 40:
#line 130 "grammar.y"
                                                        {(yyval.expr) = CreateStringExpr((yyvsp[0].string_const));}
#line 2030 "grammar.tab.c"
    break;

  case 41:
#line 131 "grammar.y"
                                                        {(yyval.expr) = CreateSuperExpr();}
#line 2036 "grammar.tab.c"
    break;

  case 42:
#line 132 "grammar.y"
                                                        {(yyval.expr) = CreateNilExpr();}
#line 2042 "grammar.tab.c"
    break;

  case 43:
#line 133 "grammar.y"
                                                         {(yyval.expr) = CreateIdentifierExpr("self");}
#line 2048 "grammar.tab.c"
    break;

  case 44:
#line 134 "grammar.y"
                                                        {(yyval.expr) = (yyvsp[-2].expr);}
#line 2054 "grammar.tab.c"
    break;

  case 45:
#line 138 "grammar.y"
                                                              {(yyval.exprList) = CreateExpressionList((yyvsp[0].expr)); }
#line 2060 "grammar.tab.c"
    break;

  case 46:
#line 139 "grammar.y"
                                                              {if ((yyvsp[-3].exprList) == NULL) (yyval.exprList) = CreateExpressionList((yyvsp[0].expr)); else (yyval.exprList) = AddToExpressionList((yyvsp[-3].exprList), (yyvsp[0].expr));}
#line 2066 "grammar.tab.c"
    break;

  case 47:
#line 140 "grammar.y"
                                                              {if ((yyvsp[-2].exprList) == NULL) (yyval.exprList) = CreateExpressionList((yyvsp[0].expr)); else (yyval.exprList) = AddToExpressionList((yyvsp[-2].exprList), (yyvsp[0].expr));}
#line 2072 "grammar.tab.c"
    break;

  case 48:
#line 146 "grammar.y"
                                                                    {(yyval.stmt) = CreateExprStatement((yyvsp[-1].expr));}
#line 2078 "grammar.tab.c"
    break;

  case 49:
#line 147 "grammar.y"
                                                                    {(yyval.stmt) = (yyvsp[0].stmt);}
#line 2084 "grammar.tab.c"
    break;

  case 50:
#line 148 "grammar.y"
                                                                    {(yyval.stmt) = CreateWhileStatement((yyvsp[-3].expr), (yyvsp[-1].stmt));}
#line 2090 "grammar.tab.c"
    break;

  case 51:
#line 149 "grammar.y"
                                                                {(yyval.stmt) = CreateWhileStatement((yyvsp[0].expr), CreateExprStatement((yyvsp[-2].expr)));}
#line 2096 "grammar.tab.c"
    break;

  case 52:
#line 150 "grammar.y"
                                                                                   {(yyval.stmt) = CreateForStatement(CreateIdentifierExpr((yyvsp[-5].id)), (yyvsp[-3].expr), (yyvsp[-1].stmt));}
#line 2102 "grammar.tab.c"
    break;

  case 53:
#line 151 "grammar.y"
                                                                {(yyval.stmt) = (yyvsp[-1].stmt);}
#line 2108 "grammar.tab.c"
    break;

  case 54:
#line 152 "grammar.y"
                                                                        {(yyval.stmt) = CreateSwitchStatement((yyvsp[-3].expr), (yyvsp[-1].lbldStmtList));}
#line 2114 "grammar.tab.c"
    break;

  case 55:
#line 156 "grammar.y"
                                                                {(yyval.stmt) = CreateCompoundStatement((yyvsp[0].stmtList));}
#line 2120 "grammar.tab.c"
    break;

  case 56:
#line 159 "grammar.y"
                                                                {(yyval.stmt) = CreateDefinitionStatement((yyvsp[-1].def));}
#line 2126 "grammar.tab.c"
    break;

  case 57:
#line 160 "grammar.y"
                                                                {(yyval.stmt) = CreateStmtExternalDeclaration((yyvsp[0].stmt));}
#line 2132 "grammar.tab.c"
    break;

  case 58:
#line 161 "grammar.y"
                                                                {(yyval.stmt) = CreatePrivateStatement();}
#line 2138 "grammar.tab.c"
    break;

  case 59:
#line 162 "grammar.y"
                                                                        {(yyval.stmt) = CreateStaticStatement((yyvsp[-2].stmtList));}
#line 2144 "grammar.tab.c"
    break;

  case 60:
#line 166 "grammar.y"
                                                                    {(yyval.stmtList) = NULL;}
#line 2150 "grammar.tab.c"
    break;

  case 61:
#line 167 "grammar.y"
                                                                {if ((yyvsp[-2].stmtList) == NULL) (yyval.stmtList) = CreateStatementList(CreateDefinitionStatement((yyvsp[-1].def))); else (yyval.stmtList) = AddToStatementList((yyvsp[-2].stmtList), CreateDefinitionStatement((yyvsp[-1].def)));}
#line 2156 "grammar.tab.c"
    break;

  case 62:
#line 171 "grammar.y"
                                                                    {(yyval.stmtList) = NULL;}
#line 2162 "grammar.tab.c"
    break;

  case 63:
#line 172 "grammar.y"
                                                                {if ((yyvsp[-1].stmtList) == NULL) (yyval.stmtList) = CreateStatementList((yyvsp[0].stmt)); else (yyval.stmtList) = AddToStatementList((yyvsp[-1].stmtList), (yyvsp[0].stmt));}
#line 2168 "grammar.tab.c"
    break;

  case 64:
#line 177 "grammar.y"
                                                                    {(yyval.stmtList) = NULL;}
#line 2174 "grammar.tab.c"
    break;

  case 65:
#line 178 "grammar.y"
                                                                {if ((yyvsp[-1].stmtList) == NULL) (yyval.stmtList) = CreateStatementList((yyvsp[0].stmt)); else (yyval.stmtList) = AddToStatementList((yyvsp[-1].stmtList), (yyvsp[0].stmt));}
#line 2180 "grammar.tab.c"
    break;

  case 66:
#line 183 "grammar.y"
                                                                                             {(yyval.stmt) = CreateIfStatement((yyvsp[-3].expr), (yyvsp[-1].stmt));}
#line 2186 "grammar.tab.c"
    break;

  case 67:
#line 184 "grammar.y"
                                                                                                         {(yyval.stmt) = CreateIfElseStatement((yyvsp[-3].expr), (yyvsp[-1].stmt), (yyvsp[0].stmt));}
#line 2192 "grammar.tab.c"
    break;

  case 68:
#line 185 "grammar.y"
                                                                                             {(yyval.stmt) = CreateIfStatement(CreateUnaryExpr(ExprTypeNeg, (yyvsp[-3].expr)), (yyvsp[-1].stmt));}
#line 2198 "grammar.tab.c"
    break;

  case 69:
#line 186 "grammar.y"
                                                                                                 {(yyval.stmt) = CreateIfElseStatement((yyvsp[-6].expr), (yyvsp[-4].stmt), (yyvsp[-1].stmt));}
#line 2204 "grammar.tab.c"
    break;

  case 70:
#line 190 "grammar.y"
                                                                                                     {(yyval.stmt) = CreateIfStatement((yyvsp[-3].expr), (yyvsp[-1].stmt));}
#line 2210 "grammar.tab.c"
    break;

  case 71:
#line 191 "grammar.y"
                                                                                                     {(yyval.stmt) = CreateIfElseStatement((yyvsp[-3].expr), (yyvsp[-1].stmt), (yyvsp[0].stmt));}
#line 2216 "grammar.tab.c"
    break;

  case 72:
#line 192 "grammar.y"
                                                                                                     {(yyval.stmt) = CreateIfElseStatement((yyvsp[-6].expr), (yyvsp[-4].stmt), (yyvsp[-1].stmt));}
#line 2222 "grammar.tab.c"
    break;

  case 73:
#line 196 "grammar.y"
                                                                {(yyval.stmt) = (yyvsp[0].stmt);}
#line 2228 "grammar.tab.c"
    break;

  case 74:
#line 197 "grammar.y"
                                                                {(yyval.stmt) = (yyvsp[0].stmt);}
#line 2234 "grammar.tab.c"
    break;

  case 75:
#line 201 "grammar.y"
                                                                 {(yyval.stmt) = CreateIfStatement((yyvsp[0].expr), CreateExprStatement((yyvsp[-2].expr)));}
#line 2240 "grammar.tab.c"
    break;

  case 76:
#line 202 "grammar.y"
                                                                 {(yyval.stmt) = CreateIfStatement(CreateUnaryExpr(ExprTypeNeg, (yyvsp[0].expr)), CreateExprStatement((yyvsp[-2].expr)));}
#line 2246 "grammar.tab.c"
    break;

  case 77:
#line 206 "grammar.y"
                                                                {(yyval.lbldStmt) = CreateLabeledStatement(LabeledStatementTypeCase, (yyvsp[-2].expr), (yyvsp[0].stmt));}
#line 2252 "grammar.tab.c"
    break;

  case 78:
#line 207 "grammar.y"
                                                                {(yyval.lbldStmt) = CreateLabeledStatement(LabeledStatementTypeDefault, NULL, (yyvsp[0].stmt));}
#line 2258 "grammar.tab.c"
    break;

  case 79:
#line 211 "grammar.y"
                                                                                        {(yyval.lbldStmtList) = CreateLabeledStatementList((yyvsp[0].lbldStmt));}
#line 2264 "grammar.tab.c"
    break;

  case 80:
#line 212 "grammar.y"
                                                                {(yyval.lbldStmtList) = AddToLabeledStatementList((yyvsp[-1].lbldStmtList), (yyvsp[0].lbldStmt));}
#line 2270 "grammar.tab.c"
    break;

  case 81:
#line 217 "grammar.y"
                                                                                            {(yyval.def) = CreateDefinition((yyvsp[-3].id), NULL, (yyvsp[-1].stmtList));}
#line 2276 "grammar.tab.c"
    break;

  case 82:
#line 218 "grammar.y"
                                                                                            {(yyval.def) = CreateDefinition((yyvsp[-6].id), (yyvsp[-4].parameterList), (yyvsp[-1].stmtList));}
#line 2282 "grammar.tab.c"
    break;

  case 83:
#line 219 "grammar.y"
                                                                                            {(yyval.def) = CreateDefinition((yyvsp[-4].id), (yyvsp[-3].parameterList), (yyvsp[-1].stmtList));}
#line 2288 "grammar.tab.c"
    break;

  case 84:
#line 220 "grammar.y"
                                                                                    {(yyval.def) = CreateDefinition("plusROP", (yyvsp[-4].parameterList), (yyvsp[-1].stmtList));}
#line 2294 "grammar.tab.c"
    break;

  case 85:
#line 221 "grammar.y"
                                                                                    {(yyval.def) = CreateDefinition("plusROP", (yyvsp[-3].parameterList), (yyvsp[-1].stmtList));}
#line 2300 "grammar.tab.c"
    break;

  case 86:
#line 222 "grammar.y"
                                                                                    {(yyval.def) = CreateDefinition("minusROP", (yyvsp[-4].parameterList), (yyvsp[-1].stmtList));}
#line 2306 "grammar.tab.c"
    break;

  case 87:
#line 223 "grammar.y"
                                                                                    {(yyval.def) = CreateDefinition("minusROP", (yyvsp[-3].parameterList), (yyvsp[-1].stmtList));}
#line 2312 "grammar.tab.c"
    break;

  case 88:
#line 224 "grammar.y"
                                                                                    {(yyval.def) = CreateDefinition("multROP", (yyvsp[-4].parameterList), (yyvsp[-1].stmtList));}
#line 2318 "grammar.tab.c"
    break;

  case 89:
#line 225 "grammar.y"
                                                                                    {(yyval.def) = CreateDefinition("multROP", (yyvsp[-3].parameterList), (yyvsp[-1].stmtList));}
#line 2324 "grammar.tab.c"
    break;

  case 90:
#line 226 "grammar.y"
                                                                                         {(yyval.def) = CreateDefinition("divROP", (yyvsp[-4].parameterList), (yyvsp[-1].stmtList));}
#line 2330 "grammar.tab.c"
    break;

  case 91:
#line 227 "grammar.y"
                                                                                    {(yyval.def) = CreateDefinition("divROP", (yyvsp[-3].parameterList), (yyvsp[-1].stmtList));}
#line 2336 "grammar.tab.c"
    break;

  case 92:
#line 231 "grammar.y"
                                                                                        {(yyval.parameter) = CreateParameter((yyvsp[0].id), NULL, 0);}
#line 2342 "grammar.tab.c"
    break;

  case 93:
#line 232 "grammar.y"
                                                                                        {(yyval.parameter) = CreateParameter((yyvsp[-2].id), (yyvsp[0].expr), 1);}
#line 2348 "grammar.tab.c"
    break;

  case 94:
#line 233 "grammar.y"
                                                                                        {(yyval.parameter) = CreateParameter((yyvsp[-2].id), (yyvsp[0].expr), 0);}
#line 2354 "grammar.tab.c"
    break;

  case 95:
#line 237 "grammar.y"
                                                                               {(yyval.parameterList) = CreateParameterList((yyvsp[0].parameter));}
#line 2360 "grammar.tab.c"
    break;

  case 96:
#line 238 "grammar.y"
                                                                       {if ((yyvsp[-3].parameterList) == NULL) (yyval.parameterList) = CreateParameterList((yyvsp[0].parameter)); else (yyval.parameterList) = AddToParameterList((yyvsp[-3].parameterList), (yyvsp[0].parameter));}
#line 2366 "grammar.tab.c"
    break;

  case 97:
#line 243 "grammar.y"
                                                                                          {(yyval.classInfo) = CreateClassInfo((yyvsp[-3].id), NULL, (yyvsp[-1].stmtList));}
#line 2372 "grammar.tab.c"
    break;

  case 98:
#line 244 "grammar.y"
                                                                                        {(yyval.classInfo) = CreateClassInfo((yyvsp[-5].id), CreateIdentifierExpr((yyvsp[-3].id)), (yyvsp[-1].stmtList));}
#line 2378 "grammar.tab.c"
    break;

  case 99:
#line 245 "grammar.y"
                                                                                          {(yyval.classInfo) = (yyvsp[-1].classInfo);}
#line 2384 "grammar.tab.c"
    break;

  case 100:
#line 249 "grammar.y"
                                                                    {root = (yyvsp[0].program);}
#line 2390 "grammar.tab.c"
    break;

  case 101:
#line 253 "grammar.y"
                                                                                {(yyval.program) = CreateExternalDeclarationList((yyvsp[0].extDecl));}
#line 2396 "grammar.tab.c"
    break;

  case 102:
#line 254 "grammar.y"
                                                                {(yyval.program) = AddToExternalDeclarationList((yyvsp[-1].program), (yyvsp[0].extDecl));}
#line 2402 "grammar.tab.c"
    break;

  case 103:
#line 258 "grammar.y"
                                          {(yyval.extDecl) = CreateFuncExternalDeclaration((yyvsp[-1].def));}
#line 2408 "grammar.tab.c"
    break;

  case 104:
#line 259 "grammar.y"
                                          {(yyval.extDecl) = CreateClassExternalDeclaration((yyvsp[0].classInfo));}
#line 2414 "grammar.tab.c"
    break;

  case 105:
#line 260 "grammar.y"
                                          {(yyval.extDecl) = CreateStmtExternalDeclaration((yyvsp[0].stmt));}
#line 2420 "grammar.tab.c"
    break;


#line 2424 "grammar.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 263 "grammar.y"

