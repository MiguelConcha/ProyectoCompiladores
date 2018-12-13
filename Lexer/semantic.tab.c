/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END = 258,
     INTTYPE = 259,
     FLOATTYPE = 260,
     DOUBLETYPE = 261,
     CHARTYPE = 262,
     VOID = 263,
     FUNC = 264,
     STRUCT = 265,
     LCURLYB = 266,
     RCURLYB = 267,
     LBRACKET = 268,
     RBRACKET = 269,
     SEMICOLON = 270,
     DOT = 271,
     TRUE = 272,
     FALSE = 273,
     IF = 274,
     ELSE = 275,
     WHILE = 276,
     DO = 277,
     SWITCH = 278,
     CASE = 279,
     DEFAULT = 280,
     BREAK = 281,
     PRINT = 282,
     ID = 283,
     INT = 284,
     DOUBLE = 285,
     FLOAT = 286,
     CADENA = 287,
     CARACTER = 288,
     COMMA = 289,
     RETURN = 290,
     FOR = 291,
     ASSIG = 292,
     OR = 293,
     AND = 294,
     NEQ = 295,
     EQ = 296,
     GEQ = 297,
     GT = 298,
     LEQ = 299,
     LT = 300,
     MINUS = 301,
     PLUS = 302,
     MOD = 303,
     DIV = 304,
     PROD = 305,
     NOT = 306,
     RPAR = 307,
     LPAR = 308,
     IFX = 309
   };
#endif
/* Tokens.  */
#define END 258
#define INTTYPE 259
#define FLOATTYPE 260
#define DOUBLETYPE 261
#define CHARTYPE 262
#define VOID 263
#define FUNC 264
#define STRUCT 265
#define LCURLYB 266
#define RCURLYB 267
#define LBRACKET 268
#define RBRACKET 269
#define SEMICOLON 270
#define DOT 271
#define TRUE 272
#define FALSE 273
#define IF 274
#define ELSE 275
#define WHILE 276
#define DO 277
#define SWITCH 278
#define CASE 279
#define DEFAULT 280
#define BREAK 281
#define PRINT 282
#define ID 283
#define INT 284
#define DOUBLE 285
#define FLOAT 286
#define CADENA 287
#define CARACTER 288
#define COMMA 289
#define RETURN 290
#define FOR 291
#define ASSIG 292
#define OR 293
#define AND 294
#define NEQ 295
#define EQ 296
#define GEQ 297
#define GT 298
#define LEQ 299
#define LT 300
#define MINUS 301
#define PLUS 302
#define MOD 303
#define DIV 304
#define PROD 305
#define NOT 306
#define RPAR 307
#define LPAR 308
#define IFX 309




/* Copy the first part of user declarations.  */
#line 12 "semantic.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <string.h>

    /* Atributos utilizados en los tokens y en los no terminales */
	#include "attributes.h"
	/* Tablas de tipos y símbolos */
	#include "mastertab.h"
	/* Backpatch */
	#include "backpatch.h"
	/* Código intermedio */
	#include "intermediate_code.h"
	/* Para las pilas de mastertabs */
	#include "pila.h"

    /* Variables que heredamos del analizador léxico. */
	extern int yylex();
	extern int yylineno;
	extern FILE *yyin;

    /* Funciones para escribir errores */
	void yyerror(char *);
	void yyerror2(char*, char*);

    /* Última función que se ejecutara. */
	void finish();

	/* Variable para el conteo de direcciones */
	int dir=0;

	/* Variables para guardar el tipo y ancho actual */
	int current_type;
	int current_dim;
	int current_arr_type;
	int current_dim_arr;
	int current_function_type;

	/* Variables para contar las temporales, etiquetas e indices */
	int label;
	int temp;
	int indice;
	int breakeablecitos = 0;

	/* Variable para el unico atributo heredado de sentencia prima*/
	labels lfalses;

	/*pila para las tablas*/
	struct nodo *stack_masterchefs; 

	/* Variable para la tabla de símbolos*/
	struct mastertab *masterchef;

	/* Variable para guardar el código intermedio que se va generando */
	ic codigo_intermedio;


	/* Funciones auxiliares al análisis semántico y generación de código intermedio */
	void init();

	exp suma(exp e1, exp e2);
	exp resta(exp e1, exp e2);
	exp multiplicacion(exp e1, exp e2);
	exp division(exp e1, exp e2);
	exp modulo(exp e1, exp e2);
	exp get_numero(numero);
	exp identificador(char *);
	exp asignacion(char *, char *, exp, int);

    exp envolver_varr(varr);
    exp envolver_cadena(cadena);
    exp envolver_caracter(caracter);

    void meter_assign(cuadrupla [], int);
    int max(int t1, int t2);
    char *ampliar(char *dir, int t1, int t2);
    char *reducir(char *dir, int t1, int t2);

    /* Funciones para generar temporales, etiquetas e indices */
    char *newTemp();
    char *newLabel();
    char *newIndex();

    /* Para funciones */
    void verifica_call(char[], int[], int);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 102 "semantic.y"
{
    struct {
        int cantidad;
    } cant;
    varr vararr;
    numero num;    
    cadena cad;    
    caracter car;    
    arreglo arr;    
    argumentos argu;
    char id[32];
    pii pi; 
    exp expresion;
    type tipo;
    struct{
        labels falses;
        labels trues;
    } booleanos;
    labels siguientes;
    struct{
        labels siguientes;
        int ifelse;
    } siguientesp;
    int rel;
    char char_signo[1];
    struct {
        int p;
        int lista_tipos[100];
        int count;
    } parrams;
}
/* Line 193 of yacc.c.  */
#line 325 "semantic.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 338 "semantic.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   217

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNRULES -- Number of states.  */
#define YYNSTATES  184

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     8,     9,    15,    16,    18,    20,
      22,    24,    26,    27,    33,    38,    41,    44,    47,    50,
      52,    54,    55,    60,    61,    62,    63,    64,    65,    81,
      82,    84,    85,    91,    95,    99,   100,   101,   105,   107,
     108,   109,   118,   119,   126,   127,   136,   137,   148,   151,
     155,   158,   162,   170,   173,   177,   181,   182,   183,   187,
     192,   195,   196,   198,   200,   204,   209,   214,   218,   222,
     226,   230,   234,   236,   238,   240,   242,   244,   249,   251,
     252,   256,   258,   259,   264,   265,   270,   273,   277,   281,
     283,   285,   287,   289,   291,   293,   295
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      56,     0,    -1,    -1,    57,    58,    66,    -1,    -1,    60,
      59,    62,    15,    58,    -1,    -1,     4,    -1,     5,    -1,
       6,    -1,     7,    -1,     8,    -1,    -1,    10,    11,    61,
      58,    12,    -1,    62,    34,    28,    65,    -1,    28,    65,
      -1,    64,    29,    -1,    64,    30,    -1,    64,    31,    -1,
      47,    -1,    46,    -1,    -1,    13,    63,    14,    65,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    60,    28,    67,    53,
      71,    52,    68,    11,    58,    74,    69,    12,    70,    66,
      -1,    -1,    72,    -1,    -1,    72,    34,    60,    28,    73,
      -1,    60,    28,    73,    -1,    13,    14,    73,    -1,    -1,
      -1,    74,    75,    76,    -1,    76,    -1,    -1,    -1,    19,
      53,    91,    52,    77,    76,    78,    83,    -1,    -1,    21,
      53,    91,    52,    79,    76,    -1,    -1,    22,    80,    76,
      21,    53,    91,    52,    15,    -1,    -1,    36,    53,    82,
      15,    91,    15,    82,    52,    81,    76,    -1,    82,    15,
      -1,    35,    88,    15,    -1,    35,    15,    -1,    11,    74,
      12,    -1,    23,    53,    88,    52,    11,    85,    12,    -1,
      26,    15,    -1,    27,    88,    15,    -1,    86,    37,    88,
      -1,    -1,    -1,    20,    84,    76,    -1,    24,    63,    76,
      85,    -1,    25,    76,    -1,    -1,    28,    -1,    87,    -1,
      28,    16,    28,    -1,    28,    13,    88,    14,    -1,    87,
      13,    88,    14,    -1,    88,    47,    88,    -1,    88,    46,
      88,    -1,    88,    50,    88,    -1,    88,    49,    88,    -1,
      88,    48,    88,    -1,    87,    -1,    28,    -1,    32,    -1,
      63,    -1,    33,    -1,    28,    53,    89,    52,    -1,    90,
      -1,    -1,    90,    34,    88,    -1,    88,    -1,    -1,    91,
      38,    92,    91,    -1,    -1,    91,    39,    93,    91,    -1,
      51,    91,    -1,    53,    91,    52,    -1,    88,    94,    88,
      -1,    17,    -1,    18,    -1,    45,    -1,    43,    -1,    44,
      -1,    42,    -1,    40,    -1,    41,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   208,   208,   208,   224,   224,   231,   239,   240,   241,
     242,   243,   244,   244,   278,   290,   309,   310,   311,   317,
     318,   319,   325,   344,   351,   363,   386,   398,   351,   420,
     426,   433,   439,   461,   489,   490,   496,   496,   513,   536,
     546,   536,   574,   574,   593,   593,   614,   614,   633,   637,
     654,   661,   670,   671,   687,   698,   715,   716,   716,   735,
     736,   737,   746,   747,   748,   754,   796,   828,   832,   835,
     839,   843,   847,   851,   856,   861,   866,   871,   893,   904,
     914,   927,   946,   946,   964,   964,   982,   988,   994,  1033,
    1047,  1068,  1072,  1076,  1080,  1084,  1088
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "END", "INTTYPE", "FLOATTYPE",
  "DOUBLETYPE", "CHARTYPE", "VOID", "FUNC", "STRUCT", "LCURLYB", "RCURLYB",
  "LBRACKET", "RBRACKET", "SEMICOLON", "DOT", "TRUE", "FALSE", "IF",
  "ELSE", "WHILE", "DO", "SWITCH", "CASE", "DEFAULT", "BREAK", "PRINT",
  "ID", "INT", "DOUBLE", "FLOAT", "CADENA", "CARACTER", "COMMA", "RETURN",
  "FOR", "ASSIG", "OR", "AND", "NEQ", "EQ", "GEQ", "GT", "LEQ", "LT",
  "MINUS", "PLUS", "MOD", "DIV", "PROD", "NOT", "RPAR", "LPAR", "IFX",
  "$accept", "prog", "@1", "decls", "@2", "tipo", "@3", "lista", "numero",
  "signo", "arreglo", "funcs", "@4", "@5", "@6", "@7", "args",
  "lista_args", "parte_arr", "sents", "@8", "sent", "@9", "@10", "@11",
  "@12", "@13", "assign", "sentp", "@14", "casos", "parte_izq", "var_arr",
  "exp", "params", "lista_param", "cond", "@15", "@16", "rel", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    57,    56,    59,    58,    58,    60,    60,    60,
      60,    60,    61,    60,    62,    62,    63,    63,    63,    64,
      64,    64,    65,    65,    67,    68,    69,    70,    66,    66,
      71,    71,    72,    72,    73,    73,    75,    74,    74,    77,
      78,    76,    79,    76,    80,    76,    81,    76,    76,    76,
      76,    76,    76,    76,    76,    82,    83,    84,    83,    85,
      85,    85,    86,    86,    86,    87,    87,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    89,    89,
      90,    90,    92,    91,    93,    91,    91,    91,    91,    91,
      91,    94,    94,    94,    94,    94,    94
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     0,     5,     0,     1,     1,     1,
       1,     1,     0,     5,     4,     2,     2,     2,     2,     1,
       1,     0,     4,     0,     0,     0,     0,     0,    15,     0,
       1,     0,     5,     3,     3,     0,     0,     3,     1,     0,
       0,     8,     0,     6,     0,     8,     0,    10,     2,     3,
       2,     3,     7,     2,     3,     3,     0,     0,     3,     4,
       2,     0,     1,     1,     3,     4,     4,     3,     3,     3,
       3,     3,     1,     1,     1,     1,     1,     4,     1,     0,
       3,     1,     0,     4,     0,     4,     2,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     6,     1,     7,     8,     9,    10,    11,     0,
      29,     4,    12,     0,     3,     0,     6,     0,    23,     0,
       0,    24,    21,    15,     6,     0,    13,     0,    20,    19,
       0,     0,     5,    23,    31,    23,    16,    17,    18,    14,
       0,     0,    30,    22,    35,    25,     0,     0,    33,     0,
       0,    35,     6,    35,    34,     0,    32,     0,     0,     0,
      44,     0,     0,    21,    62,    21,     0,    36,    38,     0,
       0,    63,    36,    21,    21,     0,    21,    53,    73,    74,
      76,    75,    72,     0,    21,     0,    50,     0,     0,     0,
       0,    48,    21,    21,    51,    89,    90,    21,    21,     0,
       0,     0,     0,     0,    21,    54,    21,    21,    21,    21,
      21,     0,    64,    49,     0,    27,    37,    55,     0,    86,
       0,    95,    96,    94,    92,    93,    91,    21,    82,    84,
      39,    42,     0,     0,    81,     0,    78,    68,    67,    71,
      70,    69,    65,    21,    29,    66,    87,    88,    21,    21,
       0,     0,    21,    61,    77,    21,     0,    28,    83,    85,
      40,    43,     0,    21,     0,     0,    80,     0,    56,     0,
       0,    60,    52,     0,    57,    41,    45,    61,    46,     0,
      59,     0,    58,    47
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    10,    15,    11,    16,    19,    81,    31,
      23,    14,    27,    49,    89,   144,    41,    42,    48,    67,
      90,    68,   150,   168,   151,    75,   181,    69,   175,   179,
     165,    70,    82,    99,   135,   136,   100,   148,   149,   127
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -85
static const yytype_int16 yypact[] =
{
     -85,     7,   177,   -85,   -85,   -85,   -85,   -85,   -85,    11,
      24,   -85,   -85,   177,   -85,    13,   177,    22,    39,    -6,
      48,   -85,    -1,   -85,   177,    33,   -85,    15,   -85,   -85,
      61,    93,   -85,    39,   177,    39,   -85,   -85,   -85,   -85,
      51,    35,    42,   -85,    82,   -85,   177,    94,   -85,    92,
      79,    82,   177,    82,   -85,   129,   -85,   129,   105,   106,
     -85,   109,   111,   121,    49,    73,   110,   117,   -85,   154,
     156,   173,   188,    31,    31,   129,   121,   -85,   -11,   -85,
     -85,   -85,   173,    43,   121,   174,   -85,    89,   175,   189,
     129,   -85,   121,   121,   -85,   -85,   -85,    31,    31,   130,
     -20,   -14,   183,   142,   114,   -85,   121,   121,   121,   121,
     121,    23,   -85,   -85,   190,   -85,   -85,   149,    84,   -85,
      47,   -85,   -85,   -85,   -85,   -85,   -85,   121,   -85,   -85,
     -85,   -85,   153,   196,   149,   157,   176,    95,    95,   -85,
     -85,   -85,   -85,    31,    24,   -85,   -85,   149,    31,    31,
     129,   129,    31,     2,   -85,   121,    -9,   -85,   169,   -85,
     -85,   -85,    76,    -1,   129,   199,   149,   175,   192,   198,
     129,   -85,   -85,   162,   -85,   -85,   -85,     2,   -85,   129,
     -85,   129,   -85,   -85
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -85,   -85,   -85,    -8,   -85,     1,   -85,   -85,   -22,   -85,
     -18,    71,   -85,   -85,   -85,   -85,   -85,   -85,   -40,   159,
     -85,   -70,   -85,   -85,   -85,   -85,   -85,   -84,   -85,   -85,
      40,   -85,   -54,   -53,   -85,   -85,   -31,   -85,   -85,   -85
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -80
static const yytype_int16 yytable[] =
{
      30,    71,    84,    71,   114,   102,   167,     3,    20,    24,
      83,    54,    87,    56,    17,    39,    32,    43,   128,   129,
     116,    71,    12,   103,   128,   129,   163,   164,    25,   128,
     129,   111,   130,    13,    71,    40,    71,   142,   131,   117,
     118,    18,   104,   101,    55,    28,    29,    50,    95,    96,
      21,   134,    22,   137,   138,   139,   140,   141,   105,    78,
      26,    33,    84,    79,    80,    85,   119,   120,    34,   106,
     107,   108,   109,   110,   147,    35,    46,    28,    29,    44,
     160,   161,    97,   173,    98,   128,   129,    45,    86,   106,
     107,   108,   109,   110,   171,    47,    71,    71,   145,   146,
     177,    78,   166,    52,   113,    79,    80,    53,    51,   182,
      71,   183,   156,    71,   128,   129,    71,   158,   159,    28,
      29,   162,    36,    37,    38,    71,    77,    71,   169,   -26,
     106,   107,   108,   109,   110,   106,   107,   108,   109,   110,
      57,   170,    78,   108,   109,   110,    79,    80,    58,    78,
      59,    60,    61,    79,    80,    62,    63,    64,    73,    74,
      28,    29,    76,    88,    65,    66,   -79,    28,    29,    91,
     121,   122,   123,   124,   125,   126,   106,   107,   108,   109,
     110,     4,     5,     6,     7,     8,    93,     9,   106,   107,
     108,   109,   110,    92,   133,   106,   107,   108,   109,   110,
      94,   115,   112,    64,   132,   143,   152,   153,   129,   154,
     155,   172,   174,   176,   178,   157,    72,   180
};

static const yytype_uint8 yycheck[] =
{
      22,    55,    13,    57,    88,    75,    15,     0,    16,    15,
      63,    51,    65,    53,    13,    33,    24,    35,    38,    39,
      90,    75,    11,    76,    38,    39,    24,    25,    34,    38,
      39,    84,    52,     9,    88,    34,    90,    14,    52,    92,
      93,    28,    53,    74,    52,    46,    47,    46,    17,    18,
      28,   104,    13,   106,   107,   108,   109,   110,    15,    28,
      12,    28,    13,    32,    33,    16,    97,    98,    53,    46,
      47,    48,    49,    50,   127,    14,    34,    46,    47,    28,
     150,   151,    51,   167,    53,    38,    39,    52,    15,    46,
      47,    48,    49,    50,   164,    13,   150,   151,    14,    52,
     170,    28,   155,    11,    15,    32,    33,    28,    14,   179,
     164,   181,   143,   167,    38,    39,   170,   148,   149,    46,
      47,   152,    29,    30,    31,   179,    15,   181,    52,    12,
      46,    47,    48,    49,    50,    46,    47,    48,    49,    50,
      11,   163,    28,    48,    49,    50,    32,    33,    19,    28,
      21,    22,    23,    32,    33,    26,    27,    28,    53,    53,
      46,    47,    53,    53,    35,    36,    52,    46,    47,    15,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,     4,     5,     6,     7,     8,    13,    10,    46,    47,
      48,    49,    50,    37,    52,    46,    47,    48,    49,    50,
      12,    12,    28,    28,    21,    15,    53,    11,    39,    52,
      34,    12,    20,    15,    52,   144,    57,   177
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    56,    57,     0,     4,     5,     6,     7,     8,    10,
      58,    60,    11,     9,    66,    59,    61,    60,    28,    62,
      58,    28,    13,    65,    15,    34,    12,    67,    46,    47,
      63,    64,    58,    28,    53,    14,    29,    30,    31,    65,
      60,    71,    72,    65,    28,    52,    34,    13,    73,    68,
      60,    14,    11,    28,    73,    58,    73,    11,    19,    21,
      22,    23,    26,    27,    28,    35,    36,    74,    76,    82,
      86,    87,    74,    53,    53,    80,    53,    15,    28,    32,
      33,    63,    87,    88,    13,    16,    15,    88,    53,    69,
      75,    15,    37,    13,    12,    17,    18,    51,    53,    88,
      91,    91,    76,    88,    53,    15,    46,    47,    48,    49,
      50,    88,    28,    15,    82,    12,    76,    88,    88,    91,
      91,    40,    41,    42,    43,    44,    45,    94,    38,    39,
      52,    52,    21,    52,    88,    89,    90,    88,    88,    88,
      88,    88,    14,    15,    70,    14,    52,    88,    92,    93,
      77,    79,    53,    11,    52,    34,    91,    66,    91,    91,
      76,    76,    91,    24,    25,    85,    88,    15,    78,    52,
      63,    76,    12,    82,    20,    83,    15,    76,    52,    84,
      85,    81,    76,    76
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 208 "semantic.y"
    { init(); ;}
    break;

  case 3:
#line 210 "semantic.y"
    {
        /* Imprimimos las tablas de tipo y símbolos y finalizamos. */
	 	print_type_table(masterchef->tt);
		print_table(masterchef->st); 
        printf("P -> D funcs\n");
		finish(); 
    ;}
    break;

  case 4:
#line 224 "semantic.y"
    { 
        current_type = (yyvsp[(1) - (1)].tipo).type;
        current_dim = (yyvsp[(1) - (1)].tipo).bytes;
        current_dim_arr = current_dim; 
        current_arr_type = current_type;
     ;}
    break;

  case 5:
#line 230 "semantic.y"
    {(yyval.cant).cantidad = (yyvsp[(3) - (5)].cant).cantidad; (yyval.cant).cantidad += (yyvsp[(5) - (5)].cant).cantidad; ;}
    break;

  case 6:
#line 231 "semantic.y"
    { (yyval.cant).cantidad = 0; ;}
    break;

  case 7:
#line 239 "semantic.y"
    { (yyval.tipo).type = 0; (yyval.tipo).bytes = 4; ;}
    break;

  case 8:
#line 240 "semantic.y"
    { (yyval.tipo).type = 1; (yyval.tipo).bytes = 4; ;}
    break;

  case 9:
#line 241 "semantic.y"
    { (yyval.tipo).type = 2; (yyval.tipo).bytes = 8; ;}
    break;

  case 10:
#line 242 "semantic.y"
    { (yyval.tipo).type = 3; (yyval.tipo).bytes = 1; ;}
    break;

  case 11:
#line 243 "semantic.y"
    { (yyval.tipo).type = 4; (yyval.tipo).bytes = 1; ;}
    break;

  case 12:
#line 244 "semantic.y"
    {
        /* Creamos una nueva mastertab donde guardaremos las declaraciones dentro del struct. Además
        agregamos este nuevo mastertab del struct al tope de la pila de mastertabs. */
        struct mastertab* ntab = (struct mastertab *) malloc(sizeof(struct mastertab));
        ntab->tt = (typetab *) malloc(sizeof(typetab));
        ntab->st= (symtab *) malloc(sizeof(symtab));
        create_table(ntab->st);
        create_type_table(ntab->tt);
        stack_masterchefs = mete(stack_masterchefs, ntab);
    ;}
    break;

  case 13:
#line 254 "semantic.y"
    { 
        /* Una vez que ya se hicieron todas las declaraciones del struct, entonces agregamos a la tabla
            de tipos el nuevo tipo del struct donde también le asociamos el mastertab que creamos para el
            struct. También quitamos de la pila de mastertabs el mastertab del struct. No se perderá ya
            que tendremos una referencia en la tabla de tipos a este mastertab. */
        struct mastertab* sacada;
        sacada = tope(stack_masterchefs); 
        stack_masterchefs = saca(stack_masterchefs);

        typerow renglon;
        renglon.type = 6;
        renglon.tam = (yyvsp[(4) - (5)].cant).cantidad;
        renglon.base.renglon = -2;
        renglon.base.smt = sacada;
        insert_type_table(stack_masterchefs->tabla->tt, renglon);

        (yyval.tipo).type = stack_masterchefs->tabla->tt->count-1; (yyval.tipo).bytes = (yyvsp[(4) - (5)].cant).cantidad; 
    ;}
    break;

  case 14:
#line 278 "semantic.y"
    {
	    /* Agregamos a la tabla de simbolos que esté en el tope de mastertabs. */
	 	sym s;
		strcpy(s.id, (yyvsp[(3) - (4)].id));
		s.type = current_arr_type;
		s.dir = dir;
		dir+= current_dim_arr;
		insert(stack_masterchefs->tabla->st, s);
		(yyval.cant).cantidad  = current_dim_arr;
		current_arr_type = current_type;
		current_dim_arr = current_dim;
	 ;}
    break;

  case 15:
#line 290 "semantic.y"
    {
	    /* Agregamos a la tabla de simbolos que esté en el tope de mastertabs. */
	 	sym s;
		strcpy(s.id, (yyvsp[(1) - (2)].id));
		s.type = current_arr_type;
		s.dir = dir;
		dir+= current_dim_arr;
		insert(stack_masterchefs->tabla->st, s);
		(yyval.cant).cantidad  = current_dim_arr;
		current_arr_type = current_type;
		current_dim_arr = current_dim;
	 ;}
    break;

  case 16:
#line 309 "semantic.y"
    { (yyval.num).type = (yyvsp[(2) - (2)].num).type; strcpy((yyval.num).val, (yyvsp[(1) - (2)].char_signo)); strcat((yyval.num).val, (yyvsp[(2) - (2)].num).val); ;}
    break;

  case 17:
#line 310 "semantic.y"
    { (yyval.num).type = (yyvsp[(2) - (2)].num).type; strcpy((yyval.num).val, (yyvsp[(1) - (2)].char_signo)); strcat((yyval.num).val, (yyvsp[(2) - (2)].num).val); ;}
    break;

  case 18:
#line 311 "semantic.y"
    { (yyval.num).type = (yyvsp[(2) - (2)].num).type; strcpy((yyval.num).val, (yyvsp[(1) - (2)].char_signo)); strcat((yyval.num).val, (yyvsp[(2) - (2)].num).val); ;}
    break;

  case 19:
#line 317 "semantic.y"
    { strcpy((yyval.char_signo),""); ;}
    break;

  case 20:
#line 318 "semantic.y"
    { strcpy((yyval.char_signo), "-"); ;}
    break;

  case 21:
#line 319 "semantic.y"
    { strcpy((yyval.char_signo),""); ;}
    break;

  case 22:
#line 325 "semantic.y"
    {
        /* Obtenemos el las dimenciones del arreglo hijo y le agregamos el de la actual
            dimensión. */
        if ((yyvsp[(2) - (4)].num).type != 0) {
            yyerror("El número para indexar en el arreglo debe ser entero.");
            exit(1);
        }
        (yyval.arr).tam = (yyvsp[(4) - (4)].arr).tam + 1;
        current_dim_arr *= atoi((yyvsp[(2) - (4)].num).val);
        memcpy((yyval.arr).dims, (yyvsp[(4) - (4)].arr).dims, 1000);
        (yyval.arr).dims[(yyval.arr).tam-1] = atoi((yyvsp[(2) - (4)].num).val);
        typerow renglon;
        renglon.type = 5;
        renglon.tam = atoi((yyvsp[(2) - (4)].num).val);
        renglon.base.renglon = current_arr_type;
        renglon.base.smt = null;
        insert_type_table(stack_masterchefs->tabla->tt, renglon);
        current_arr_type = stack_masterchefs->tabla->tt->count-1;
    ;}
    break;

  case 23:
#line 344 "semantic.y"
    { (yyval.arr).tam = 0; ;}
    break;

  case 24:
#line 351 "semantic.y"
    {
	    /* Creamos el mastertab de la función y la agregamos a la pila de mastertabs
	       ya que decls agrega sus declaraciones al tope de la pila y queremos que se agreguen
	       al mastertab de la función. */
		struct mastertab* ntab = (struct mastertab *) malloc(sizeof(struct mastertab));
		ntab->tt = (typetab *) malloc(sizeof(typetab));
		ntab->st = (symtab *) malloc(sizeof(symtab));
		create_table(ntab->st);
		create_type_table(ntab->tt);
		stack_masterchefs = mete(stack_masterchefs, ntab);
		current_function_type = (yyvsp[(2) - (3)].tipo).type;
	 ;}
    break;

  case 25:
#line 363 "semantic.y"
    {
	    /* Agregamos una etiqueta que nos diga donde está el código de la función. */
		cuadrupla c;
		c.op = label;
		char lab[32];
		strcpy(lab, newlabel());
		strcpy(c.op1, "");
		strcpy(c.op2, "");
		strcpy(c.res, (yyvsp[(3) - (7)].id));
		insert_cuad(&codigo_intermedio, c);

        /* Agregamos la función a la tabla de simbolos global junto con los tipos de los argumentos. */
	 	sym s;
		strcpy(s.id, (yyvsp[(3) - (7)].id));
		s.type = (yyvsp[(2) - (7)].tipo).type;
		s.dir = masterchef->tt->count;
		s.var = 1;
		for(int j = 0; j < (yyvsp[(6) - (7)].argu).num; j++){
			s.args[j] = (yyvsp[(6) - (7)].argu).lista_args[j];
		}
		s.num_args = (yyvsp[(6) - (7)].argu).num;
		insert(masterchef->st, s);
	 ;}
    break;

  case 26:
#line 386 "semantic.y"
    {
	    /* Aquí se hace backpatch para que se actualicen las etiquetas. */
        cuadrupla c;
        char label[32];
        c.op = label;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[(11) - (11)].siguientes)));
        insert_cuad(&codigo_intermedio, c);                
        strcpy(label, newlabel());                                                
        backpatch(&(yyvsp[(11) - (11)].siguientes), label, &codigo_intermedio);
	 ;}
    break;

  case 27:
#line 398 "semantic.y"
    {
		struct mastertab* sacada;
		sacada = tope(stack_masterchefs); 
		stack_masterchefs = saca(stack_masterchefs);

        /* Agregamos la referencia del masterchef de la función */
		typerow renglon;
		renglon.type = 7;
		renglon.tam = (yyvsp[(10) - (13)].cant).cantidad;
		renglon.base.renglon = -2;
		renglon.base.smt = sacada;
		insert_type_table(stack_masterchefs->tabla->tt, renglon);

		cuadrupla c;
		char label2[32];
		strcpy(label2, newlabel());
		c.op = goto;
		strcpy(c.op1, "");
		strcpy(c.op2, "");
		strcpy(c.res, label2);
        insert_cuad(&codigo_intermedio, c);                
     ;}
    break;

  case 30:
#line 426 "semantic.y"
    {
	    (yyval.argu).num = (yyvsp[(1) - (1)].argu).num; 
        /* Copiamos los argumentos en que tiene el hijo lista_args. */
        for(int i = 0; i < (yyvsp[(1) - (1)].argu).num; i++){
            (yyval.argu).lista_args[i] = (yyvsp[(1) - (1)].argu).lista_args[i];
        }
    ;}
    break;

  case 31:
#line 433 "semantic.y"
    { (yyval.argu).num = 0; ;}
    break;

  case 32:
#line 439 "semantic.y"
    {
        /* Agregamos a la tabla de simbolos y tipos el argumento de la función */
        typerow renglon;
        renglon.type = (yyvsp[(3) - (5)].tipo).type;
        renglon.tam = (yyvsp[(3) - (5)].tipo).type;
        renglon.base.renglon = (yyvsp[(3) - (5)].tipo).type;
        insert_type_table(stack_masterchefs->tabla->tt, renglon);
        
        sym s;
        strcpy(s.id, (yyvsp[(4) - (5)].id));
        s.type = (yyvsp[(3) - (5)].tipo).type;
        s.dir = dir;
        dir+= renglon.tam;
        insert(stack_masterchefs->tabla->st, s);

        /* Aumentamos el número de argumentos que llevamos guardados. */
        (yyval.argu).num = 1 + (yyvsp[(1) - (5)].argu).num;
        for(int i = 0; i < (yyvsp[(1) - (5)].argu).num; i++){
            (yyval.argu).lista_args[i] = (yyvsp[(1) - (5)].argu).lista_args[i];
        }
        (yyval.argu).lista_args[(yyval.argu).num-1] = (yyvsp[(3) - (5)].tipo).type;
        ;}
    break;

  case 33:
#line 461 "semantic.y"
    {
        /* Ponemos los casos base de la lista de argumentos y del número de argumentos */
        (yyval.argu).num = 1;
        (yyval.argu).lista_args[0] = (yyvsp[(1) - (3)].tipo).type;
        
        /* Agregamos a la tabla de simbolos y tipos el argumento de la función */
        typerow renglon;
        renglon.type = (yyvsp[(1) - (3)].tipo).type;
        renglon.tam = (yyvsp[(1) - (3)].tipo).type;
        renglon.base.renglon = (yyvsp[(1) - (3)].tipo).type;
        insert_type_table(stack_masterchefs->tabla->tt, renglon);
    
        print_type_table(stack_masterchefs->tabla->tt);
        sym s;
        strcpy(s.id, (yyvsp[(2) - (3)].id));
        //s.type = stack_masterchefs->tabla->tt->count-1;
        s.type = (yyvsp[(1) - (3)].tipo).type;
        s.dir = dir;
        dir+= renglon.tam;
        insert(stack_masterchefs->tabla->st, s);

        print_table(stack_masterchefs->tabla->st);
    ;}
    break;

  case 36:
#line 496 "semantic.y"
    {
	    /* Creamos una etiqueta */
        cuadrupla c;
        c.op = label;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[(1) - (1)].siguientes)));
        insert_cuad(&codigo_intermedio, c);                                
    ;}
    break;

  case 37:
#line 505 "semantic.y"
    {
	    /* Hacemos Backbatch */
        char label[32];
        strcpy(label, newlabel());                                
        (yyval.siguientes) = (yyvsp[(3) - (3)].siguientes);                
        backpatch(&(yyvsp[(1) - (3)].siguientes), label, &codigo_intermedio);                
        printf("ss->ss s\n");
    ;}
    break;

  case 38:
#line 513 "semantic.y"
    {
	    /* Hacemos Backbatch */
        char label[32];
        strcpy(label, newlabel());
        (yyval.siguientes) = (yyvsp[(1) - (1)].siguientes);
        backpatch(&(yyvsp[(1) - (1)].siguientes), label, &codigo_intermedio);
        printf("ss->s\n");
    ;}
    break;

  case 39:
#line 536 "semantic.y"
    {
	    /* Obtenemos la etiqueta que está en el tope de trues de la condición y la agregamos
	       a nuestro código */
        cuadrupla c;
        c.op = label;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[(3) - (4)].booleanos).trues));
        insert_cuad(&codigo_intermedio, c);
    ;}
    break;

  case 40:
#line 546 "semantic.y"
    {
        /* Agregamos a los falses globales la primer etiqueta que tenemos en la condición.
           Además agregamos a nuestro código el goto que tenemos en el tope de sent */
        cuadrupla c, c1;
        c.op = goto;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[(6) - (6)].siguientes)));
        push_label(&lfalses, get_first(&(yyvsp[(3) - (6)].booleanos).falses));
        insert_cuad(&codigo_intermedio, c);
    ;}
    break;

  case 41:
#line 556 "semantic.y"
    {
        /* Verificamos si tenemos un else en sentp y hacemos backpatch en ambos casos */
        char label[32];
        strcpy(label, newlabel());
        
        if((yyvsp[(8) - (8)].siguientesp).ifelse==false){
            (yyval.siguientes) = merge(&(yyvsp[(3) - (8)].booleanos).falses, &(yyvsp[(8) - (8)].siguientesp).siguientes);
            backpatch(&(yyvsp[(3) - (8)].booleanos).falses, label, &codigo_intermedio);                                
            printf("s->if(b) s\n");
        }else{
            char label2[32];                                    
            strcpy(label2, newlabel());                
            (yyval.siguientes) = merge(&(yyvsp[(6) - (8)].siguientes),&(yyvsp[(8) - (8)].siguientesp).siguientes);
            backpatch(&(yyvsp[(3) - (8)].booleanos).trues, label, &codigo_intermedio);
            backpatch(&(yyvsp[(3) - (8)].booleanos).falses, label2, &codigo_intermedio);                 
            printf("s->if(b)s else s\n");
        }
    ;}
    break;

  case 42:
#line 574 "semantic.y"
    { breakeablecitos += 1; ;}
    break;

  case 43:
#line 574 "semantic.y"
    {
        /* Creamos nuevas etiquetas que las agregaremos a los trues y falses de cond.  */
        char label[32], label2[32], temp[32];
        strcpy(label, newindex());                
        strcpy(label2, newindex());         
        strcpy(temp, newtemp());
        (yyval.siguientes) = (yyvsp[(3) - (6)].booleanos).falses;
        cuadrupla c1;
        c1.op = iff;
        /* Agregamos un goto para que evalue la condición otra vez */
        strcpy(c1.op2, "goto");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        /* Hacemos backpatch */
        backpatch(&(yyvsp[(3) - (6)].booleanos).trues, label, &codigo_intermedio);
        backpatch(&(yyvsp[(3) - (6)].booleanos).falses, label2, &codigo_intermedio);
        printf("s->while(b)s\n");
		breakeablecitos -= 1;
    ;}
    break;

  case 44:
#line 593 "semantic.y"
    { breakeablecitos += 1; ;}
    break;

  case 45:
#line 593 "semantic.y"
    {
        /* Muy parecido al while */
		char label[32], label2[32], temp[32];
        strcpy(label, newindex());                

		/* Ejecución incondicional de la sentencia */
		backpatch(&(yyvsp[(6) - (8)].booleanos).trues, label, &codigo_intermedio);

        strcpy(label2, newindex());         
        strcpy(temp, newtemp());
        (yyval.siguientes) = (yyvsp[(6) - (8)].booleanos).falses;
        cuadrupla c1;
        c1.op = iff;
        strcpy(c1.op2, "goto");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&(yyvsp[(6) - (8)].booleanos).trues, label, &codigo_intermedio);
        backpatch(&(yyvsp[(6) - (8)].booleanos).falses, label2, &codigo_intermedio);
        printf("s->do s while(b)\n");
		breakeablecitos -= 1;
	;}
    break;

  case 46:
#line 614 "semantic.y"
    { breakeablecitos += 1; ;}
    break;

  case 47:
#line 614 "semantic.y"
    {
        /* Muy parecido al while */
		meter_assign((yyvsp[(3) - (10)].siguientes).arr_codigo, (yyvsp[(3) - (10)].siguientes).count_codigo);
        char label[32], label2[32], temp[32];
        strcpy(label, newindex());                
        strcpy(label2, newindex());         
        strcpy(temp, newtemp());
        (yyval.siguientes) = (yyvsp[(5) - (10)].booleanos).falses;
        cuadrupla c1;
        c1.op = iff;
        strcpy(c1.op2, "goto");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&(yyvsp[(5) - (10)].booleanos).trues, label, &codigo_intermedio);
        backpatch(&(yyvsp[(5) - (10)].booleanos).falses, label2, &codigo_intermedio);
		meter_assign((yyvsp[(7) - (10)].siguientes).arr_codigo, (yyvsp[(7) - (10)].siguientes).count_codigo);
        printf("s->for(ass; cond; ass) sent\n");
		breakeablecitos -= 1;
    ;}
    break;

  case 48:
#line 633 "semantic.y"
    {
	    /* meter_assign ya hace todo el trabajo */
	    meter_assign((yyvsp[(1) - (2)].siguientes).arr_codigo, (yyvsp[(1) - (2)].siguientes).count_codigo);
	;}
    break;

  case 49:
#line 637 "semantic.y"
    {
        /* Verificamos el tipo de retorno con el de la función */
        if((yyvsp[(2) - (3)].expresion).type != current_function_type) {
            yyerror("tipo de retorno distinto al tipo de la funcion \n");
            exit(1);
        }
        /* Agregamos el goto adecuado */
        cuadrupla c1;
        c1.op = goto;
        char label1[32];
        strcpy(label1, newlabel());
        strcpy(c1.op1, "");
        strcpy(c1.op2, "");
        strcpy(c1.res, label1);
        insert_cuad(&codigo_intermedio, c1);
	
	;}
    break;

  case 50:
#line 654 "semantic.y"
    {
        /* Verificamos que el tipo de la función sea void */
        if(4 != current_function_type) {
            yyerror("tipo de retorno void distinto al tipo de la funcion \n");
            exit(1);
        }
    ;}
    break;

  case 51:
#line 661 "semantic.y"
    {
        /* Aquí es donde se hace la concatenación de sentencias */
        char label[32];
        (yyval.siguientes) = (yyvsp[(2) - (3)].siguientes);                
        strcpy(label, newlabel());                
        /* Se hace backpatch */
        backpatch(&(yyvsp[(2) - (3)].siguientes), label, &codigo_intermedio);                                
        printf("s->{ss}\n");
    ;}
    break;

  case 53:
#line 671 "semantic.y"
    {
        /* Verificamos que el break sea dentro de un break */
	    if(breakeablecitos < 1) {
            yyerror("el break debe estar dentro de un ciclo \n");
            exit(1);
        }
        cuadrupla c1;
        c1.op = goto;
        char label1[32];
        strcpy(label1, newlabel());
        strcpy(c1.op1, "");
        strcpy(c1.op2, "");
        strcpy(c1.res, label1);
        insert_cuad(&codigo_intermedio, c1);

	;}
    break;

  case 54:
#line 687 "semantic.y"
    {
        char i[32];
        strcpy(i, newindex());
        (yyval.siguientes) = create_list(i);
        printf("s->print(e);\n");
    ;}
    break;

  case 55:
#line 698 "semantic.y"
    {
        char i[32];
        strcpy(i, newindex());
        (yyval.siguientes) = create_list(i);
        /* asignacion es lo que hace todo el trabajo */
        exp e = asignacion((yyvsp[(1) - (3)].pi).id1, (yyvsp[(1) - (3)].pi).id2, (yyvsp[(3) - (3)].expresion), (yyvsp[(1) - (3)].pi).type); 
        int iterador;
        (yyval.siguientes).count_codigo = e.count_codigo;
        for(iterador = 0; iterador < e.count_codigo; iterador++) {
            (yyval.siguientes).arr_codigo[iterador] = e.arr_codigo[iterador];
        }
	;}
    break;

  case 56:
#line 715 "semantic.y"
    { /* Decimos que no tenemos un else */ (yyval.siguientesp).ifelse= false;;}
    break;

  case 57:
#line 716 "semantic.y"
    {        
	    /* Agregamos la etiqueta que tenemos en los falses al código*/
        cuadrupla c1;
        c1.op = label;
        strcpy(c1.op1, "");
        strcpy(c1.op2, "");
        strcpy(c1.res, pop_label(&lfalses));
        insert_cuad(&codigo_intermedio, c1);
    ;}
    break;

  case 58:
#line 725 "semantic.y"
    {
        /* Decimos que tenemos un else */
        (yyval.siguientesp).ifelse= true;
        (yyval.siguientesp).siguientes = (yyvsp[(3) - (3)].siguientes);
    ;}
    break;

  case 62:
#line 746 "semantic.y"
    { strcpy((yyval.pi).id1, (yyvsp[(1) - (1)].id)); strcpy((yyval.pi).id2,""); (yyval.pi).type = -1; ;}
    break;

  case 63:
#line 747 "semantic.y"
    { strcpy((yyval.pi).id1, (yyvsp[(1) - (1)].vararr).representacion); (yyval.pi).type = (yyvsp[(1) - (1)].vararr).type; ;}
    break;

  case 64:
#line 748 "semantic.y"
    { strcpy((yyval.pi).id1, (yyvsp[(1) - (3)].id)); strcpy((yyval.pi).id2, (yyvsp[(3) - (3)].id)); (yyval.pi).type = -1; ;}
    break;

  case 65:
#line 754 "semantic.y"
    { 
                                  // Verificando que se indexe el arreglo con una expresión de tipo entera.
                                  if((yyvsp[(3) - (4)].expresion).type != 0) { 
                                    yyerror("Error: Debes indexar el arreglo con un entero.\n"); 
                                  }
                                  // Formando la cadena que representa a la variable de arreglo indexada.
                                  strcpy((yyval.vararr).representacion, (yyvsp[(1) - (4)].id));
                                  strcat((yyval.vararr).representacion, "[");
                                  strcat((yyval.vararr).representacion, (yyvsp[(3) - (4)].expresion).dir);
                                  strcat((yyval.vararr).representacion, "]");
                                  // Creando un nuevo nodo para iterar la pila de tablas maestras.
                                  struct nodo* it = stack_masterchefs;
                                  // Recorremos la pila para buscar el identificador en ella.
                                  int encontrado = 0;
                                  while(it != NULL) {
                                    // Estamos buscando con el identificador en la tabla de símbolos a la que apunta el iterador.
                                    int x = search(it->tabla->st, (yyvsp[(1) - (4)].id)); 
                                    if(x != -1) {
                                        // Si ya la encontramos, podemos consultar el tipo en dicho renglón encontrado.
                                        encontrado = 1;
                                        int type_row = it->tabla->st->symbols[x].type;
                                        (yyval.vararr).type = it->tabla->tt->trs[type_row].base.renglon;
                                        // En el ciclo seguiremos subiendo a partir de los tipos hasta llegar al de la base.
                                        // Sin embargo, si en algún punto llegaos a ver un -1 es porque estamos indexando a un arreglo
                                        // que fue declarado con un número menor de dimensiones y reportamos el error. 
                                        if((yyval.vararr).type == -1) {
                                            yyerror("Error: Mayor cantidad de dimensiones que las definidas.");
                                            exit(1);
                                        }
                                        break;
                                    }
                                    it = it->siguiente;
                                  }
                                  // Si saliendo del ciclo ocurre que el identificador jamás fue encontrado, entonces
                                  // no había sido declarado antes y reportamos el error.
                                  if(!encontrado) {
                                    yyerror("Error: El arreglo no fue declarado antes.\n");
                                    exit(1);
                                  }
                                  // Especificando que la tabla de tipos del lado izquierdo es la tabla a la que apunta el iterador. 
                                  (yyval.vararr).tt = it->tabla->tt; 
       ;}
    break;

  case 66:
#line 796 "semantic.y"
    {
                                  // Regla de producción recursiva para seguir metiendo indexaciones.
                                  // Armando la representación de la indexación.
                                  strcat((yyval.vararr).representacion, "[");
                                  strcat((yyval.vararr).representacion, (yyvsp[(3) - (4)].expresion).dir);
                                  strcat((yyval.vararr).representacion, "]");
                                  // Checando que se indexe con una expresión de tipo entera.
                                  if((yyvsp[(3) - (4)].expresion).type != 0) { 
                                    yyerror("Error: Debes indexar el arreglo con un entero.\n"); 
                                  }
                                  // Comprobando si se indexó con más dimensiones de aquellas con que fue definido.
                                  if((yyvsp[(1) - (4)].vararr).type == -1) {
                                    yyerror("Error: Mayor cantidad de dimensiones que las definidas");
                                    exit(1);
                                  } 
                                  // Checando el tipo del rengón del varr_arr del cuerpo de la producción.
                                  int row_hijo = (yyvsp[(1) - (4)].vararr).type;
                                  (yyval.vararr).type = (*(yyvsp[(1) - (4)].vararr).tt).trs[row_hijo].base.renglon;
                                  // Comprobando si se indexó con más dimensiones de aquellas con que fue definido.
                                  if((yyval.vararr).type == -1) {
                                    yyerror("Error: Mayor cantidad de dimensiones que las definidas");
                                    exit(1);
                                  } 
                                  // La tabla de tipos de la cabecera es la del varr_arr del cuerpo.
                                  (yyval.vararr).tt = (yyvsp[(1) - (4)].vararr).tt;
       ;}
    break;

  case 67:
#line 828 "semantic.y"
    { 
                  (yyval.expresion) = suma((yyvsp[(1) - (3)].expresion), (yyvsp[(3) - (3)].expresion)); 
                  printf("E -> E + E\n"); 
                ;}
    break;

  case 68:
#line 832 "semantic.y"
    { (yyval.expresion) = resta((yyvsp[(1) - (3)].expresion), (yyvsp[(3) - (3)].expresion)); 
                     printf("E -> E - E\n");
                   ;}
    break;

  case 69:
#line 835 "semantic.y"
    { 
                    (yyval.expresion) = multiplicacion((yyvsp[(1) - (3)].expresion), (yyvsp[(3) - (3)].expresion)); 
                    printf("E -> E * E\n");
                  ;}
    break;

  case 70:
#line 839 "semantic.y"
    { 
                   (yyval.expresion) = division((yyvsp[(1) - (3)].expresion), (yyvsp[(3) - (3)].expresion)); 
                   printf("E -> E / E\n");
                 ;}
    break;

  case 71:
#line 843 "semantic.y"
    { 
                   (yyval.expresion) = modulo((yyvsp[(1) - (3)].expresion), (yyvsp[(3) - (3)].expresion)); 
                   printf("E -> E mod E\n");
                 ;}
    break;

  case 72:
#line 847 "semantic.y"
    { 
               (yyval.expresion) = envolver_varr((yyvsp[(1) - (1)].vararr)); 
               printf("E -> id[E]\n"); 
             ;}
    break;

  case 73:
#line 851 "semantic.y"
    { 
          (yyval.expresion) = identificador((yyvsp[(1) - (1)].id)); 
          printf("E->id\n");
          printf("%s\n", (yyvsp[(1) - (1)].id)); 
        ;}
    break;

  case 74:
#line 856 "semantic.y"
    { 
              // Pasando la cadena de la expresión regular a un tipo expresión.
              (yyval.expresion) = envolver_cadena((yyvsp[(1) - (1)].cad)); 
              printf("E -> CADENA\n"); 
            ;}
    break;

  case 75:
#line 861 "semantic.y"
    { 
              (yyval.expresion) = get_numero((yyvsp[(1) - (1)].num));
              printf("E->numero\n");
              printf("%s\n",(yyvsp[(1) - (1)].num).val);
            ;}
    break;

  case 76:
#line 866 "semantic.y"
    { 
                // Pasando el carácter de la expresión regular a un tipo expresión.
                (yyval.expresion) = envolver_caracter((yyvsp[(1) - (1)].car)); 
                printf("E -> CARACTER\n");
              ;}
    break;

  case 77:
#line 871 "semantic.y"
    {
                            // Verificamos que la llama a la función sea válida 
                            // de acuerdo a la lista de tipos con que fue declarada y los tipos de los
                            // argumentos.
                            verifica_call((yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].parrams).lista_tipos, (yyvsp[(3) - (4)].parrams).count);    
                            char temp[32];
                            strcpy(temp, newTemp());
                            // Creando la cuadrupla para el código.
                            cuadrupla c;
                            // Es una llamada a función.
                            c.op = CALL;
                            strcpy(c.op1, (yyvsp[(1) - (4)].id));
                            sprintf(c.op2, "%d", (yyvsp[(3) - (4)].parrams).count);
                            strcpy(c.res, temp);
                            insert_cuad(&codigo_intermedio, c);                    
                            strcpy((yyval.expresion).dir, temp);
                        ;}
    break;

  case 78:
#line 893 "semantic.y"
    {
            // El número de parámetros es el que carga la lista.
            (yyval.parrams).p = (yyvsp[(1) - (1)].parrams).p;
            // Copiamos los tipos parámetros de la lista de parámetros.
            int i;
            for (i = 0; i < (yyvsp[(1) - (1)].parrams).count; i++) {
                (yyval.parrams).lista_tipos[i] = (yyvsp[(1) - (1)].parrams).lista_tipos[i];
            }
            // El número de parámetros son los de la lista de parámetros.
            (yyval.parrams).count = (yyvsp[(1) - (1)].parrams).count;
      ;}
    break;

  case 79:
#line 904 "semantic.y"
    {
                // Si cae en este caso, el número de parámetros es cero. 
                (yyval.parrams).p = 0; 
                (yyval.parrams).count = 0;
               ;}
    break;

  case 80:
#line 914 "semantic.y"
    {
                // Creando la cuadrupla e insertándola en el código intermedio.
                cuadrupla c;
                c.op = PARAM;
                strcpy(c.op1, "");
                strcpy(c.op2, "");
                strcpy(c.res, (yyvsp[(3) - (3)].expresion).dir);
                insert_cuad(&codigo_intermedio, c);  
                // Incrementando la cantidad de argumentos y copiando el tipo del actual.                  
                (yyval.parrams).p = (yyvsp[(1) - (3)].parrams).p + 1;
                (yyval.parrams).lista_tipos[(yyvsp[(1) - (3)].parrams).count] = (yyvsp[(3) - (3)].expresion).type;
                (yyval.parrams).count = (yyvsp[(1) - (3)].parrams).count + 1;
           ;}
    break;

  case 81:
#line 927 "semantic.y"
    {
                // Creando la cuadrupla e insertándola en el código intermedio.
                cuadrupla c;
                c.op = PARAM;
                strcpy(c.op1, "");
                strcpy(c.op2, "");
                strcpy(c.res, (yyvsp[(1) - (1)].expresion).dir);
                insert_cuad(&codigo_intermedio, c);
                // Como es el caso base, tenemos un solo argumento y su tipo es el tipo de la expresión.                    
                (yyval.parrams).p = 1;
                (yyval.parrams).lista_tipos[0] = (yyvsp[(1) - (1)].expresion).type;
                (yyval.parrams).count = 1;
           ;}
    break;

  case 82:
#line 946 "semantic.y"
    {
        // Creación de la cuadrupla con la operación de label.
        cuadrupla c;
        c.op = label;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[(1) - (2)].booleanos).falses));
        // Inserción de la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);                    
    ;}
    break;

  case 83:
#line 955 "semantic.y"
    { 
        char label[32];
        strcpy(label, newLabel());
        // Haciendo backpatch con la nueva etiqueta. 
        backpatch(&(yyvsp[(1) - (4)].booleanos).falses, label, &codigo_intermedio);
        (yyval.booleanos).trues = merge(&(yyvsp[(1) - (4)].booleanos).trues, &(yyvsp[(4) - (4)].booleanos).trues);
        (yyval.booleanos).falses = (yyvsp[(4) - (4)].booleanos).falses;
        printf("b -> b || b\n");
    ;}
    break;

  case 84:
#line 964 "semantic.y"
    {
        // Creación de la cuadrupla con la operación de label.
        cuadrupla c;
        c.op = label;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[(1) - (2)].booleanos).trues));
        // Inserción de la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);                    
    ;}
    break;

  case 85:
#line 973 "semantic.y"
    {
        char label[32];
        strcpy(label, newlabel());                        
        (yyval.booleanos).falses = merge(&(yyvsp[(1) - (4)].booleanos).falses, &(yyvsp[(4) - (4)].booleanos).falses);
        (yyval.booleanos).trues = (yyvsp[(4) - (4)].booleanos).trues;
        // Haciendo backpatch con la nueva etiqueta. 
        backpatch(&(yyvsp[(1) - (4)].booleanos).trues, label, &codigo_intermedio);
        printf("b -> b && b\n");
    ;}
    break;

  case 86:
#line 982 "semantic.y"
    {
        // Se invierten flases y trues.
        (yyval.booleanos).falses = (yyvsp[(2) - (2)].booleanos).trues;
        (yyval.booleanos).trues = (yyvsp[(2) - (2)].booleanos).falses;
        printf("b -> !b\n");
    ;}
    break;

  case 87:
#line 988 "semantic.y"
    {
        // Dependen de los falses y trues de la condución del cuerpo.
        (yyval.booleanos).trues = (yyvsp[(2) - (3)].booleanos).trues;
        (yyval.booleanos).falses = (yyvsp[(2) - (3)].booleanos).falses;
        printf("B->(B)\n");
    ;}
    break;

  case 88:
#line 994 "semantic.y"
    {
        char i[32];
        char i2[32];
        char temp[32];
        // Crenado dos nuevos índices y un temporal.
        strcpy(i, newIndex());
        strcpy(i2, newIndex());
        strcpy(temp, newTemp());
        (yyval.booleanos).trues = create_list(i);
        (yyval.booleanos).falses = create_list(i2);
        
        // Creando las cuadruplas.
        cuadrupla c, c1, c2;
        
        // Especificación de la primera cuadrupla.
        c.op = (yyvsp[(2) - (3)].rel) ;
        strcpy(c.op1, (yyvsp[(1) - (3)].expresion).dir);
        strcpy(c.op2, (yyvsp[(3) - (3)].expresion).dir);
        strcpy(c.res, temp);            
        
        // Especificación de la segunda cuadrupla.
        c1.op = IFF;
        strcpy(c1.op1, temp);
        strcpy(c1.op2, "goto");
        strcpy(c1.res, i);            
            
        // Especificación de la tercera cuadrupla.
        c2.op = GOTO;
        strcpy(c2.op1, "");
        strcpy(c2.op2, "");
        strcpy(c2.res, i2);
        
        // Insertando cuadruplas para el código intermedio.
        insert_cuad(&codigo_intermedio, c);
        insert_cuad(&codigo_intermedio, c1);
        insert_cuad(&codigo_intermedio, c2);
        printf("b->e rel e\n");
        printf("e1.dir %s rel e2.dir %s\n", (yyvsp[(1) - (3)].expresion).dir, (yyvsp[(3) - (3)].expresion).dir);
    ;}
    break;

  case 89:
#line 1033 "semantic.y"
    {
        char i[32];
        strcpy(i, newindex());
        (yyval.booleanos).trues = create_list(i);
        // Creación de la cuadrupla y con la operación de goto.
        cuadrupla c;
        c.op = goto;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, i);
        // Inserción de la cuadrupla.
        insert_cuad(&codigo_intermedio, c);
        printf("b->true\n");
    ;}
    break;

  case 90:
#line 1047 "semantic.y"
    {
        char i[32];
        strcpy(i, newindex());
        (yyval.booleanos).falses = create_list(i);
        // Creación de la cuadrupla y con la operación de goto.
        cuadrupla c;
        c.op = goto;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, i);
        // Inserción de la cuadrupla.
        insert_cuad(&codigo_intermedio, c);
        printf("b->false\n");
    ;}
    break;

  case 91:
#line 1068 "semantic.y"
    { 
        (yyval.rel) = LESS_THAN; 
        printf("R-> <\n"); 
      ;}
    break;

  case 92:
#line 1072 "semantic.y"
    { 
          (yyval.rel) = GREATER_THAN; 
          printf("R-> >\n");
        ;}
    break;

  case 93:
#line 1076 "semantic.y"
    { 
           (yyval.rel) = LESS_OR_EQUAL_THAN; 
           printf("R-> <=\n");
         ;}
    break;

  case 94:
#line 1080 "semantic.y"
    { 
           (yyval.rel) = GREATER_OR_EQUAL_THAN; 
           printf("R-> >=\n");
         ;}
    break;

  case 95:
#line 1084 "semantic.y"
    { 
           (yyval.rel) = NOT_EQUALS;
           printf("R-> !=\n"); 
         ;}
    break;

  case 96:
#line 1088 "semantic.y"
    { 
          (yyval.rel) = EQUALS; 
          printf("R-> ==\n");
        ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2799 "semantic.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1094 "semantic.y"


/**
 * Inicializa la tabla maestra que tiene los apuntadores
 * a una tabla de símbolos y a una de tipos.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
void init(){    
    // Reservando memoria dinámicamente para la tabla maestra y sus dos tablas.
    masterchef = (struct mastertab *) malloc(sizeof(struct mastertab));
    masterchef->tt = (typetab *) malloc(sizeof(typetab));
    masterchef->st = (symtab *) malloc(sizeof(symtab));
    stack_masterchefs = (struct nodo*) malloc(sizeof(struct nodo));
    stack_masterchefs = NULL;
    
    // Creando las dos tablas que tendrá como apuntadores.
    create_table(masterchef->st);
    create_type_table(masterchef->tt);

    // Metiéndo la tabla maestra a la pila de las tablas maestras. 
    // Esta que metemos es la tabla del alcance global.
    stack_masterchefs = mete(stack_masterchefs, masterchef);

    // Creamos el contenedor del código intermedio e inicializamos las labels para los falses.
    create_code(&codigo_intermedio);
    create_labels(&lfalses);    
}

/**
 * Función que determina cuál de los dos tipos de los que se pasan 
 * como parámetros (representador por enteros) es mayor que el otro.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
int max(int t1, int t2){
    // Basta con ir checando por casos y en cada tipo regresar el mayor.
    // Esto se debe a que double > float > int y los enteros que los
    // representan son respectivamente 2 > 1 > 0.
    if( t1==t2) return t1;
    if( t1 ==0 && t2 == 1) return 1;
    if( t1 ==1 && t2 == 0) return 1;
    if( t1 ==0 && t2 == 2) return 2;
    if( t1 ==2 && t2 == 0) return 2;
    if( t1 ==2 && t2 == 1) return 2;
    if( t1 ==1 && t2 == 2) return 2;
    // Si no cae en ninguno de los casos anteriores, regresamos -1.
    else return -1;
}

/**
 * Función que genera el código intermedio para la adición de dos
 * números. Devuelve la expresión resultante de la suma de las dos expresiones
 * que se pasan como parámetros.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
exp suma(exp e1, exp e2){
    exp e;
    cuadrupla c;
    // El tipo de la expresión es el mayor de los dos tipos de las expresiones.
    e.type = max(e1.type, e2.type);
    // Checando por errores de tipos.
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        // La operación de es suma.
        c.op = MAS;
        // Realizando los casts necesarios en el código intermedio generado.
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

/**
 * Función que genera el código intermedio para la sustracción de dos
 * números. Devuelve la expresión resultante de la resta de las dos expresiones
 * que se pasan como parámetros.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
exp resta(exp e1, exp e2){
    exp e;
    cuadrupla c;
    char t[32];
    // El tipo de la expresión es el mayor de los dos tipos de las expresiones.
    e.type = max(e1.type, e2.type);
    // Checando por errores de tipos.
    if( e.type==-1) yyerror("Error de tipos");
    else{
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        // La operación de es resta.
        c.op = MENOS;
        // Realizando los casts necesarios en el código intermedio generado.
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

/**
 * Función que genera el código intermedio para el producto de dos
 * números. Devuelve la expresión resultante de la multiplicación de las dos expresiones
 * que se pasan como parámetros.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
exp multiplicacion(exp e1, exp e2){
    exp e;
    cuadrupla c;
    // El tipo de la expresión es el mayor de los dos tipos de las expresiones.
    e.type = max(e1.type, e2.type);
    // Checando por errores de tipos.
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        // La operación de es multiplicación.
        c.op = MULTIPLICACION;
        // Realizando los casts necesarios en el código intermedio generado.
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

/**
 * Función que genera el código intermedio para el cociente de dos
 * números. Devuelve la expresión resultante de la división de las dos expresiones
 * que se pasan como parámetros.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
exp division(exp e1, exp e2){
    exp e;
    cuadrupla c;
    // El tipo de la expresión es el mayor de los dos tipos de las expresiones.
    e.type = max(e1.type, e2.type);
    // Checando por errores de tipos.
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        // La operación de es división.
        c.op = DIVISION;
        // Realizando los casts necesarios en el código intermedio generado.
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

/**
 * Función que genera el código intermedio para el módulo de dos
 * números. Devuelve la expresión resultante del módulo de las dos expresiones
 * que se pasan como parámetros.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 5 de diciembre de 2018.
 */
exp modulo(exp e1, exp e2){
    // Para hacer el módulo ambos tipos de las expresiones deben ser enteros.
    if(e1.type != 0 || e2.type != 0) {
        yyerror("Error: La operación módulo requiere operandos enteros.\n");
        exit(1);
    }
    exp e;
    cuadrupla c;
    // El tipo de la expresión es el mayor de los dos tipos de las expresiones.
    e.type = max(e1.type, e2.type);
    // Checando por errores de tipos.
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        // La operación de es módulo.
        c.op = MODULO;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

/**
 * Función que busca un identificador en la tabla del tope de la pila
 * de tablas maestras y si no lo encuentra lo busca también en la tabla
 * de símbolos global. Esto sirve para las funciones.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 9 de diciembre de 2018.
 */
int get_tipo_tablas(char *id) {
    int tipo;
    // Buscándolo en la tabla de símbolos del tope.
    int busqueda = search(stack_masterchefs->tabla->st, id);
    if (busqueda == -1) {
        // Si no lo encontramos lo buscamos en la global.
        busqueda = search(masterchef->st, id);
        if (busqueda == -1) {
            // Si no está es porque no fue declarado antes.
            yyerror("Error: El identificador para la variable no fue declarada antes.\n");
            exit(1);
        } else {    
            // Si sí lo encontramos en la global, obtenemos su tipo.
            tipo = get_type(masterchef->st, id);
        }
    } else {
        // Si lo encontramos en la global, obtenemos su tipo.
        tipo = get_type(stack_masterchefs->tabla->st, id);
    }
    return tipo;
}

/**
 * Función que verifica que la llamada a una función sea válida.
 * Checa que lo que se llama en efecto sea una función, tenga la 
 * misma cantidad de parámetros que los argumentos con que fue 
 * declarada y además los tipos de cada uno coincidan.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 9 de diciembre de 2018.
 */
void verifica_call(char id[], int params[], int params_count) {
    // Buscando el renglón en la tabla de símbolos del identificador.
    int renglon = search(masterchef->st, id);
    if (renglon == -1) {
        // Erroe en caso de que no sea encontrada.
        yyerror("Error: La funcion que quieres llamar no ha sido declarado\n");
        exit(1);
    }
    // Checando que sea llamda con el mismo número de argumentos con que fue declarada.
    if (masterchef->st->symbols[renglon].num_args != params_count) {
        char error[1000];
        strcpy(error, "Error: El número de argumentos con la que fue llamada la función es incorrecto: ");
        yyerror2(error, id);
        exit(1);
    }
    // Checando que el tipo de los parámetros con que es llamda coincida con los de la declaración.
    for (int j = 0; j < params_count; j++) {
        if (masterchef->st->symbols[renglon].args[j] != params[j]) {
            char error[1000];
            strcpy(error, "Error: Los tipos de los argumentos que ingresaste no son correcto con la funcion: ");
            yyerror2(error, id);
            exit(1);
        }
    }
}

/**
 * Función que sirve para generar y llevar a cabo la creación
 * de código itermedio para una asignación del tipo parte_izq = exp . 
 * Recibe como parámetros el identificador de la parte izquierda en dos partes
 * (puede ser id . id y se reciben ambos), la expresión del lado derecho de la expresión
 * y el entero que representa su tipo.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 10 de diciembre de 2018.
 */
exp asignacion(char *id, char *id2, exp e, int trecibido){
    // La expresión que será devuelta.
    exp e1;
    e1.count_codigo = 0;
    // Cuando no es un var_arr:
    if(trecibido == -1) {
        int tipo;
        int es_estruct = 0;
        // Si no es de la forma id.id, el segundo id es vacío y podemos obtener el tipo del primero.
        if(strcmp(id2, "") == 0) {
            tipo = get_tipo_tablas(id);
        } else {
            // En otro caso, es de la forma id.id, entonces debemos buscar el primer identificador.
            es_estruct = 1;
            // Buscamos el id antes del punto en la tabla de símbolos para saber si fue declarado antes.
            int renglon = search(masterchef->st, id);
            if (renglon == -1) {
                yyerror("Error: El identificador no fue declarado\n");
                exit(1);
            }
            // Tenemos la tabla de tipos global.
            typetab tabla_tipos_actual= (*masterchef->tt);
            // Vemos si es de tipo struct la variable para poder hacer lo de id.id.
            int tiene_struct = tabla_tipos_actual.trs[masterchef->st->symbols[renglon].type].base.renglon;
            // Si sí tiene:
            if(tiene_struct == -2) {
                symtab *st_struct = tabla_tipos_actual.trs[stack_masterchefs->tabla->st->symbols[renglon].type].base.smt->st;
                // Buscando lo que hay después del punto en id.id.
                int renglon2 = search(st_struct, id2);
                if (renglon2 == -1) {
                    // Si no lo encontramos, tenemos que buscar en la global.
                    st_struct = tabla_tipos_actual.trs[masterchef->st->symbols[renglon].type].base.smt->st;
                    renglon2 = search(st_struct, id2);
                    // En este caso la estructura así antes.
                    if(renglon2 == -1) {
                        yyerror("Error: El struct no fue declarado como lo usaste.\n");
                        exit(1);
                    }
                }
                tipo = get_type(st_struct, id2);
                // En el caso contrario hay un error semántico.
            } else {
                yyerror2("Error: Intento de acceso a atributo de no estructura: ", id);
                exit(1);
            }
        }
        if( tipo != -1){        
            // El tipo de la expresión a devolver es el de la expresión luego de la asignación.
            e1.type = e.type;
            strcpy(e1.dir, id);
            // Creando la cuadrupla para la asignación y colocando la operación.
            cuadrupla c;
            c.op = ASSIGNATION;
            printf("%s %d %d\n", e.dir, tipo, e.type);
            // Colocando lo necesario de la cuadrupla.
            strcpy(c.op1, reducir(e.dir, tipo, e.type));
            strcpy(c.op2, "");
            if(es_estruct == 1) {
                char id_con_punto[65];
                strcpy(id_con_punto, id);
                strcat(id_con_punto, ".");
                strcat(id_con_punto, id2);
                strcpy(c.res, id_con_punto);
            } else {
                strcpy(c.res, id);
            }
            // Colocando lo respectivo al código a la expresión.
            e1.arr_codigo[e1.count_codigo] = c; 
            e1.count_codigo++;
        } else{
            // Caso para el error semántico.
            yyerror("Error: El identificador no fue declarado\n");
            exit(1);
        }
    } else {        // Aquí se maneja el caso para var_arr.
        e1.type = e.type;
        strcpy(e1.dir, id);
        // Crando la cuadrupla.
        cuadrupla c;
        c.op = ASSIGNATION;
        strcpy(c.op1, reducir(e.dir, trecibido, e.type));
        strcpy(c.op2, "");
        // En este caso id es la representacin de var_arr.
        strcpy(c.res, id);
        // Asociando lo respectivo al código a la expresión.
        e1.arr_codigo[e1.count_codigo] = c;
        e1.count_codigo++;}
        return e1;
}

/**
 * Función que copia el valor del número a la dirección de una
 * expresión creada.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
exp get_numero(numero n){
    exp e;
    e.type = n.type;
    strcpy(e.dir, n.val);
    return e;
}

/**
 * Función que copia el valor de una cadena en la dirección
 * de una nueva expresión que es creada.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
exp envolver_cadena(cadena cadenita) {
    exp e;
    e.type = cadenita.type;
    strcpy(e.dir, cadenita.val);
    return e;
}

/**
 * Función que copia el valor de una carácter en la dirección
 * de una nueva expresión que es creada.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
exp envolver_caracter(caracter caractercito) {
    exp e;
    e.type = caractercito.type;
    e.dir[0] = caractercito.val;
    return e;
}

/**
 * Función que copia la representación de un arreglo
 * en la dirección de una expresión que es creada.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
exp envolver_varr(varr arreglito) {
    exp e;
    e.type = arreglito.type;
    strcpy(e.dir, arreglito.representacion);
    return e;
}

/**
 * Función que copia el id en la dirección de una 
 * nueva expresión creada que al final devuelta.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 6 de diciembre de 2018.
 */
exp identificador(char *id){
    exp e;
    // Buscamos el identificador en la tabla de símbolos del tipo de la pila.
    if(search(stack_masterchefs->tabla->st, id) !=-1){
        // Si lo encontramos, podemos copiar su valor en la dirección de la expresión.
        e.type = get_type(stack_masterchefs->tabla->st, id);
        strcpy(e.dir, id);
    }else{
        // En otro caso buscamos el identificador en la tabla global.
        if(search(masterchef->st, id) !=-1){
            // Si ya lo encontramos, copiamos su valor en el dirección de la expresión.
            e.type = get_type(masterchef->st, id);
            strcpy(e.dir, id);
        } else {
            // Si no, entonces error porque no fue declarada antes.
            yyerror("Error: el identificador no existe");
            exit(1);
        }
    }
    return e;
}

/**
 * Función que genera el código intermedio
 * para los casts necesarios para lost tipos.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 6 de diciembre de 2018.
 */
char *ampliar(char *dir, int t1, int t2){
    cuadrupla c;
    char *t= (char*) malloc(32*sizeof(char));
    if( t1==t2) return dir;
    // Cast de entero a float.
    if( t1 ==0 && t2 == 1){
        c.op = EQ;
        strcpy(c.op1, "(float)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
        return t;
    }
    // Cast de entero a double.
    if( t1 ==0 && t2 == 2){
        c.op = EQ;
        strcpy(c.op1, "(double)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
        return t;
    }        
    // Cast de float a double.
    if( t1 ==1 && t2 == 2) {
        c.op = EQ;
        strcpy(c.op1, "(double)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
        return t;
    }            
}

/**
 * Función que genera el código intermedio
 * para los casts necesarios para lost tipos, cuando
 * el cast es a uno menor.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 6 de diciembre de 2018.
 */
char *reducir(char *dir, int t1, int t2){
    cuadrupla c;
    char *t= (char*) malloc(32*sizeof(char));
    if( t1==t2) return dir;
    // Cast de float a int.
    if( t1 ==0 && t2 == 1){
        c.op = EQ;
        strcpy(c.op1, "(int)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla.
        insert_cuad(&codigo_intermedio, c);
        printf("perdida de información se esta asignando un float a un int\n");
        return t;
    }
    // Cast de double a int.
    if( t1 ==0 && t2 == 2){
        c.op = EQ;
        strcpy(c.op1, "(int)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla.
        insert_cuad(&codigo_intermedio, c);
        printf("perdida de información se esta asignando un double a un int\n");
        return t;
    }        
    // Cast de double a float.
    if( t1 ==1 && t2 == 2) {
        c.op = EQ;
        strcpy(c.op1, "(float)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla.
        insert_cuad(&codigo_intermedio, c);
        printf("perdida de información se esta asignando un double a un float\n");
        return t;
    }
    // En otro caso hay un error semántico.  
    printf("Error: Asignacion inconsistente de tipos.\n");
    exit(1);
}

/**
 * Función que crea un nuevo tempora.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 7 de diciembre de 2018.
 */
char* newTemp(){
    // Reservando memoria dinámicamente para el temporal.
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "t");
    char num[30];
    sprintf(num, "%d", temp);
    strcat(temporal, num);
    temp++;
    return temporal;
}

/**
 * Función que crea un nueva etiqueta.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 7 de diciembre de 2018.
 */
char* newLabel(){
    // Reservando memoria dinámicamente para la etiqueta.
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "L");
    char num[30];
    sprintf(num, "%d", label);
    strcat(temporal, num);
    label++;
    return temporal;
}

/**
 * Función que crea un nuevo índice.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 7 de diciembre de 2018.
 */
char* newIndex(){
    // Reservando memoria dinámicamente para la cadena del índice.
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "I");
    char num[30];
    sprintf(num, "%d", indice);
    strcat(temporal, num);
    indice++;
    return temporal;
}

/**
 * Función que imprime los mensajes de error.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
void yyerror(char *msg) {
    printf("%s\n", msg);
}

/**
 * Función que concatena dos cadenas que serán 
 * impresas como el mensaje de error.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 4 de diciembre de 2018.
 */
void yyerror2(char *c, char *c2){
    strcat(c, c2);
    yyerror(c);
}

/**
 * Función que imprime el código intermedio
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 6 de diciembre de 2018.
 */
void finish(){    
    print_code(&codigo_intermedio);    
}

/**
 * Función que itera tantas veces como indica el segundo 
 * parámetro de la función y va metiendo el contenido
 * de la cuadrúpla dada como parámetro en el código intermedio.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 6 de diciembre de 2018.
 */
void meter_assign(cuadrupla c[], int cou){
    for(int j = 0; j < cou; j++){
        insert_cuad(&codigo_intermedio, c[j]);
        printf("metemos ass\n");
        printf("%s, %s, %s, %d", c[j].op1, c[j].op2, c[j].res, c[j].op);
    }
}

int main(int argc, char **argv) {
    yyin = fopen(argv[1], "r");
    int result = yyparse();
    printf("resultado del analisis: %d\n", result);
    fclose(yyin);
    return 0;
}

