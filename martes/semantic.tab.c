/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "semantic.y" /* yacc.c:339  */

	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <string.h>

	#include "attributes.h"
	#include "mastertab.h"
	#include "backpatch.h"
	#include "intermediate_code.h"
	#include "pila.h"

	extern int yylex();
	extern int yylineno;
	extern FILE *yyin;
	void yyerror(char *);
	void yyerror2(char*, char*);

	void finish();
	/* Variable para el conteo de direcciones */
	int dir=0;

	/* Variables para guardar el tipo y ancho actual */
	int current_type;
	int current_dim;
	int current_arr_type;
	int current_dim_arr;

	/* Varaibles para contar las temporales, etiquetas e indices */
	int label;
	int temp;
	int indice;

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


#line 140 "semantic.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "semantic.tab.h".  */
#ifndef YY_YY_SEMANTIC_TAB_H_INCLUDED
# define YY_YY_SEMANTIC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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
    EQ = 295,
    NEQ = 296,
    GT = 297,
    GEQ = 298,
    LT = 299,
    LEQ = 300,
    PLUS = 301,
    MINUS = 302,
    PROD = 303,
    DIV = 304,
    MOD = 305,
    NOT = 306,
    LPAR = 307,
    RPAR = 308,
    IFX = 309
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 75 "semantic.y" /* yacc.c:355  */

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

#line 262 "semantic.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SEMANTIC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 279 "semantic.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   217

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  180

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   168,   168,   168,   179,   179,   186,   190,   191,   192,
     193,   194,   195,   195,   220,   231,   246,   247,   248,   252,
     253,   254,   258,   275,   279,   299,   310,   279,   324,   328,
     333,   337,   345,   352,   353,   357,   357,   372,   382,   390,
     382,   415,   431,   451,   469,   470,   471,   472,   479,   480,
     481,   490,   506,   508,   507,   523,   524,   525,   529,   530,
     531,   535,   563,   586,   587,   588,   589,   590,   591,   592,
     593,   594,   595,   596,   600,   601,   605,   606,   610,   610,
     625,   625,   640,   645,   651,   683,   695,   710,   711,   712,
     713,   714,   715
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "END", "INTTYPE", "FLOATTYPE",
  "DOUBLETYPE", "CHARTYPE", "VOID", "FUNC", "STRUCT", "LCURLYB", "RCURLYB",
  "LBRACKET", "RBRACKET", "SEMICOLON", "DOT", "TRUE", "FALSE", "IF",
  "ELSE", "WHILE", "DO", "SWITCH", "CASE", "DEFAULT", "BREAK", "PRINT",
  "ID", "INT", "DOUBLE", "FLOAT", "CADENA", "CARACTER", "COMMA", "RETURN",
  "FOR", "ASSIG", "OR", "AND", "EQ", "NEQ", "GT", "GEQ", "LT", "LEQ",
  "PLUS", "MINUS", "PROD", "DIV", "MOD", "NOT", "LPAR", "RPAR", "IFX",
  "$accept", "prog", "$@1", "decls", "$@2", "tipo", "$@3", "lista",
  "numero", "signo", "arreglo", "funcs", "$@4", "$@5", "$@6", "args",
  "lista_args", "parte_arr", "sents", "$@7", "sent", "$@8", "$@9",
  "assign", "sentp", "$@10", "casos", "parte_izq", "var_arr", "exp",
  "params", "lista_param", "cond", "$@11", "$@12", "rel", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
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

#define YYPACT_NINF -84

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-84)))

#define YYTABLE_NINF -76

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -84,    23,   184,   -84,   -84,   -84,   -84,   -84,   -84,    14,
      18,   -84,   -84,   184,   -84,    22,   184,    35,    61,    56,
      64,    26,    42,   -84,   184,    53,   -84,   184,   -84,   -84,
      83,    54,   -84,    61,    76,    57,    72,    61,   -84,   -84,
     -84,   -84,   104,   -84,   184,   -84,   110,   -84,   114,   103,
     104,   184,   104,   -84,   121,   -84,   121,    84,    98,   121,
     141,   126,   -16,     2,    88,   146,   143,   -84,   144,   132,
     186,   188,    47,    47,   180,   -16,   -84,    -8,   -84,   -84,
     -84,   186,    20,   -16,   174,   -84,    80,   175,   192,   121,
     -84,   -16,   -16,   -84,   -84,   -84,    47,    47,   137,    48,
     107,   153,   117,   105,   -84,   -16,   -16,   -16,   -16,   -16,
      -7,   -84,   -84,   191,   -84,   -84,   125,    12,   -84,   115,
     -84,   -84,   -84,   -84,   -84,   -84,   -16,   -84,   -84,   -84,
     121,    47,   196,   125,   155,   176,   147,   147,   -84,   -84,
     -84,   -84,    47,    18,   -84,   -84,   125,    47,    47,   121,
     -84,   123,    89,   -84,   -16,     9,   -84,   170,   -84,   -84,
     197,    42,   121,   199,   125,   175,   193,   -84,   121,   -84,
     -84,   161,   -84,   -84,    89,   121,   121,   -84,   -84,   -84
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     6,     1,     7,     8,     9,    10,    11,     0,
      28,     4,    12,     0,     3,     0,     6,     0,    23,     0,
       0,     0,    21,    15,     6,     0,    13,    30,    19,    20,
       0,     0,     5,    23,     0,     0,    29,    23,    16,    17,
      18,    14,    34,    24,     0,    22,     0,    32,     0,     0,
      34,     6,    34,    33,     0,    31,     0,     0,     0,     0,
       0,     0,    21,    58,    21,     0,    35,    37,     0,     0,
      59,    35,    21,    21,     0,    21,    49,    69,    70,    72,
      71,    68,     0,    21,     0,    46,     0,     0,     0,     0,
      44,    21,    21,    47,    85,    86,    21,    21,     0,     0,
       0,     0,     0,    21,    50,    21,    21,    21,    21,    21,
       0,    60,    45,     0,    26,    36,    51,     0,    82,     0,
      92,    91,    88,    90,    87,    89,    21,    78,    80,    38,
       0,    21,     0,    77,     0,    74,    63,    64,    65,    66,
      67,    61,    21,    28,    62,    83,    84,    21,    21,     0,
      41,     0,    57,    73,    21,     0,    27,    79,    81,    39,
       0,    21,     0,     0,    76,     0,    52,    42,     0,    56,
      48,     0,    53,    40,    57,     0,     0,    55,    43,    54
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -84,   -84,   -84,    -5,   -84,     1,   -84,   -84,   -22,   -84,
     -24,    73,   -84,   -84,   -84,   -84,   -84,   -30,   159,   -84,
     -57,   -84,   -84,   -83,   -84,   -84,    43,   -84,   -53,   -54,
     -84,   -84,   -40,   -84,   -84,   -84
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    10,    15,    11,    16,    19,    80,    31,
      23,    14,    48,    88,   143,    35,    36,    47,    66,    89,
      67,   149,   166,    68,   173,   176,   163,    69,    81,    98,
     134,   135,    99,   147,   148,   126
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      30,    70,    74,    70,   113,    83,    70,   141,    82,    41,
      86,    20,    77,    45,    17,    83,    78,    79,    84,    32,
      53,   102,    55,     3,   165,    12,   144,    13,    34,   110,
      28,    29,   115,   100,    70,   104,    70,   116,   117,   105,
     106,   107,   108,   109,   103,    49,    54,   127,   128,   133,
      18,   136,   137,   138,   139,   140,   118,   119,   105,   106,
     107,   108,   109,    21,    94,    95,   105,   106,   107,   108,
     109,    24,   146,   150,    22,    77,    26,    70,    27,    78,
      79,    33,   171,    38,    39,    40,   127,   128,    28,    29,
      25,   151,   159,    28,    29,   112,    70,    37,    96,    97,
     164,   129,   155,    85,    42,   169,    44,   157,   158,    70,
      43,   174,    70,   161,   162,    70,    77,    46,   178,   179,
      78,    79,    70,    70,    50,    51,   105,   106,   107,   108,
     109,    52,    56,    77,    28,    29,    72,    78,    79,   168,
      57,    76,    58,    59,    60,   127,   128,    61,    62,    63,
      73,    28,    29,   127,   128,   -25,    64,    65,   -75,    90,
     130,   127,   128,   105,   106,   107,   108,   109,   145,    91,
     132,   105,   106,   107,   108,   109,   160,   120,   121,   122,
     123,   124,   125,   105,   106,   107,   108,   109,     4,     5,
       6,     7,     8,    75,     9,   107,   108,   109,    87,    92,
      93,   101,   111,    63,   114,   131,   142,   152,   153,   128,
     154,   170,   167,   172,   175,    71,   156,   177
};

static const yytype_uint8 yycheck[] =
{
      22,    54,    59,    56,    87,    13,    59,    14,    62,    33,
      64,    16,    28,    37,    13,    13,    32,    33,    16,    24,
      50,    75,    52,     0,    15,    11,    14,     9,    27,    83,
      46,    47,    89,    73,    87,    15,    89,    91,    92,    46,
      47,    48,    49,    50,    52,    44,    51,    38,    39,   103,
      28,   105,   106,   107,   108,   109,    96,    97,    46,    47,
      48,    49,    50,    28,    17,    18,    46,    47,    48,    49,
      50,    15,   126,   130,    13,    28,    12,   130,    52,    32,
      33,    28,   165,    29,    30,    31,    38,    39,    46,    47,
      34,   131,   149,    46,    47,    15,   149,    14,    51,    52,
     154,    53,   142,    15,    28,   162,    34,   147,   148,   162,
      53,   168,   165,    24,    25,   168,    28,    13,   175,   176,
      32,    33,   175,   176,    14,    11,    46,    47,    48,    49,
      50,    28,    11,    28,    46,    47,    52,    32,    33,   161,
      19,    15,    21,    22,    23,    38,    39,    26,    27,    28,
      52,    46,    47,    38,    39,    12,    35,    36,    53,    15,
      53,    38,    39,    46,    47,    48,    49,    50,    53,    37,
      53,    46,    47,    48,    49,    50,    53,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,     4,     5,
       6,     7,     8,    52,    10,    48,    49,    50,    52,    13,
      12,    21,    28,    28,    12,    52,    15,    11,    53,    39,
      34,    12,    15,    20,    53,    56,   143,   174
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    56,    57,     0,     4,     5,     6,     7,     8,    10,
      58,    60,    11,     9,    66,    59,    61,    60,    28,    62,
      58,    28,    13,    65,    15,    34,    12,    52,    46,    47,
      63,    64,    58,    28,    60,    70,    71,    14,    29,    30,
      31,    65,    28,    53,    34,    65,    13,    72,    67,    60,
      14,    11,    28,    72,    58,    72,    11,    19,    21,    22,
      23,    26,    27,    28,    35,    36,    73,    75,    78,    82,
      83,    73,    52,    52,    75,    52,    15,    28,    32,    33,
      63,    83,    84,    13,    16,    15,    84,    52,    68,    74,
      15,    37,    13,    12,    17,    18,    51,    52,    84,    87,
      87,    21,    84,    52,    15,    46,    47,    48,    49,    50,
      84,    28,    15,    78,    12,    75,    84,    84,    87,    87,
      40,    41,    42,    43,    44,    45,    90,    38,    39,    53,
      53,    52,    53,    84,    85,    86,    84,    84,    84,    84,
      84,    14,    15,    69,    14,    53,    84,    88,    89,    76,
      75,    87,    11,    53,    34,    87,    66,    87,    87,    75,
      53,    24,    25,    81,    84,    15,    77,    15,    63,    75,
      12,    78,    20,    79,    75,    53,    80,    81,    75,    75
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    57,    56,    59,    58,    58,    60,    60,    60,
      60,    60,    61,    60,    62,    62,    63,    63,    63,    64,
      64,    64,    65,    65,    67,    68,    69,    66,    66,    70,
      70,    71,    71,    72,    72,    74,    73,    73,    76,    77,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    78,    79,    80,    79,    81,    81,    81,    82,    82,
      82,    83,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    85,    85,    86,    86,    88,    87,
      89,    87,    87,    87,    87,    87,    87,    90,    90,    90,
      90,    90,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     0,     5,     0,     1,     1,     1,
       1,     1,     0,     5,     4,     2,     2,     2,     2,     1,
       1,     0,     4,     0,     0,     0,     0,    14,     0,     1,
       0,     5,     3,     3,     0,     0,     3,     1,     0,     0,
       8,     5,     7,     9,     2,     3,     2,     3,     7,     2,
       3,     3,     0,     0,     3,     4,     2,     0,     1,     1,
       3,     4,     4,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     4,     1,     0,     3,     1,     0,     4,
       0,     4,     2,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 2:
#line 168 "semantic.y" /* yacc.c:1646  */
    { init(); }
#line 1490 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 170 "semantic.y" /* yacc.c:1646  */
    {
	 	print_type_table(masterchef->tt);
		print_table(masterchef->st); 
        printf("P -> D funcs\n"); /*finish()*/
		finish(); 
    }
#line 1501 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 179 "semantic.y" /* yacc.c:1646  */
    { 
	 	current_type = (yyvsp[0].tipo).type;
		current_dim = (yyvsp[0].tipo).bytes;
		current_dim_arr = current_dim; 
		current_arr_type = current_type;
     }
#line 1512 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 185 "semantic.y" /* yacc.c:1646  */
    {(yyval.cant).cantidad = (yyvsp[-2].cant).cantidad; (yyval.cant).cantidad += (yyvsp[0].cant).cantidad; }
#line 1518 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 186 "semantic.y" /* yacc.c:1646  */
    { (yyval.cant).cantidad = 0; }
#line 1524 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 190 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 0; (yyval.tipo).bytes = 4; }
#line 1530 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 191 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 1; (yyval.tipo).bytes = 4; }
#line 1536 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 192 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 2; (yyval.tipo).bytes = 8; }
#line 1542 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 193 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 3; (yyval.tipo).bytes = 1; }
#line 1548 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 194 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 4; (yyval.tipo).bytes = 1; }
#line 1554 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 195 "semantic.y" /* yacc.c:1646  */
    {
		struct mastertab* ntab = (struct mastertab *) malloc(sizeof(struct mastertab));
		ntab->tt = (typetab *) malloc(sizeof(typetab));
		ntab->st= (symtab *) malloc(sizeof(symtab));
		create_table(ntab->st);
		create_type_table(ntab->tt);
		stack_masterchefs = mete(stack_masterchefs, ntab);
	  }
#line 1567 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 203 "semantic.y" /* yacc.c:1646  */
    { 
		struct mastertab* sacada;// = (struct mastertab *) malloc(sizeof(struct mastertab));
		sacada = tope(stack_masterchefs); 
		stack_masterchefs = saca(stack_masterchefs);

		typerow renglon;
		renglon.type = 6;
		renglon.tam = (yyvsp[-1].cant).cantidad;
		renglon.base.renglon = -2;
		renglon.base.smt = sacada;
		insert_type_table(stack_masterchefs->tabla->tt, renglon);

	  	(yyval.tipo).type = stack_masterchefs->tabla->tt->count-1; (yyval.tipo).bytes = (yyvsp[-1].cant).cantidad; 
	  }
#line 1586 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 220 "semantic.y" /* yacc.c:1646  */
    {
	 	sym s;
		strcpy(s.id, (yyvsp[-1].id));
		s.type = current_arr_type;
		s.dir = dir;
		dir+= current_dim_arr;
		insert(stack_masterchefs->tabla->st, s);
		(yyval.cant).cantidad  = current_dim_arr;
		current_arr_type = current_type;
		current_dim_arr = current_dim;
	 }
#line 1602 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 231 "semantic.y" /* yacc.c:1646  */
    {
	 	sym s;
		strcpy(s.id, (yyvsp[-1].id));
		s.type = current_arr_type;
		s.dir = dir;
		dir+= current_dim_arr;
		//insert(&tabla_de_simbolos, s);
		insert(stack_masterchefs->tabla->st, s);
		(yyval.cant).cantidad  = current_dim_arr;
		current_arr_type = current_type;
		current_dim_arr = current_dim;
	 }
#line 1619 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 246 "semantic.y" /* yacc.c:1646  */
    { (yyval.num).type = (yyvsp[0].num).type; strcpy((yyval.num).val, (yyvsp[-1].char_signo)); strcat((yyval.num).val, (yyvsp[0].num).val); }
#line 1625 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 247 "semantic.y" /* yacc.c:1646  */
    { (yyval.num).type = (yyvsp[0].num).type; strcpy((yyval.num).val, (yyvsp[-1].char_signo)); strcat((yyval.num).val, (yyvsp[0].num).val); }
#line 1631 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 248 "semantic.y" /* yacc.c:1646  */
    { (yyval.num).type = (yyvsp[0].num).type; strcpy((yyval.num).val, (yyvsp[-1].char_signo)); strcat((yyval.num).val, (yyvsp[0].num).val); }
#line 1637 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 252 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.char_signo),""); }
#line 1643 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 253 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.char_signo), "-"); }
#line 1649 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 254 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.char_signo),""); }
#line 1655 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 258 "semantic.y" /* yacc.c:1646  */
    {
	       if ((yyvsp[-2].num).type != 0) {
		       yyerror("Te pasaste de verga. Mete tu entero!");
			   exit(1);
		   }
	       (yyval.arr).tam = (yyvsp[0].arr).tam + 1;
		   current_dim_arr *= atoi((yyvsp[-2].num).val);
		   memcpy((yyval.arr).dims, (yyvsp[0].arr).dims, 1000);
		   (yyval.arr).dims[(yyval.arr).tam-1] = atoi((yyvsp[-2].num).val);
		   typerow renglon;
		   renglon.type = 5;
		   renglon.tam = atoi((yyvsp[-2].num).val);
		   renglon.base.renglon = current_arr_type;
		   renglon.base.smt = NULL;
		   insert_type_table(stack_masterchefs->tabla->tt, renglon);
		   current_arr_type = stack_masterchefs->tabla->tt->count-1;
	   }
#line 1677 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 275 "semantic.y" /* yacc.c:1646  */
    { (yyval.arr).tam = 0; }
#line 1683 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 279 "semantic.y" /* yacc.c:1646  */
    {
	 	sym s;
		strcpy(s.id, (yyvsp[-3].id));
		s.type = (yyvsp[-4].tipo).type;
		s.dir = stack_masterchefs->tabla->tt->count;
		s.var = 1;
		for(int j = 0; j < (yyvsp[-1].argu).num; j++){
			s.args[j] = (yyvsp[-1].argu).lista_args[j];
		}
		s.num_args = (yyvsp[-1].argu).num;
		insert(stack_masterchefs->tabla->st, s);

		struct mastertab* ntab = (struct mastertab *) malloc(sizeof(struct mastertab));
		ntab->tt = (typetab *) malloc(sizeof(typetab));
		ntab->st= (symtab *) malloc(sizeof(symtab));
		create_table(ntab->st);
		create_type_table(ntab->tt);
		stack_masterchefs = mete(stack_masterchefs, ntab);

	 }
#line 1708 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 299 "semantic.y" /* yacc.c:1646  */
    {
        cuadrupla c;
        char label[32];
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[0].siguientes)));
        insert_cuad(&codigo_intermedio, c);                
        strcpy(label, newLabel());                                                
        backpatch(&(yyvsp[0].siguientes), label, &codigo_intermedio);
	 }
#line 1724 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 310 "semantic.y" /* yacc.c:1646  */
    {
		struct mastertab* sacada;// = (struct mastertab *) malloc(sizeof(struct mastertab));
		sacada = tope(stack_masterchefs); 
		stack_masterchefs = saca(stack_masterchefs);

		typerow renglon;
		renglon.type = 7;
		renglon.tam = (yyvsp[-3].cant).cantidad;
		renglon.base.renglon = -2;
		renglon.base.smt = sacada;
		insert_type_table(stack_masterchefs->tabla->tt, renglon);
	  	//$$.type = stack_masterchefs->tabla->tt->count-1; 
		//$$.bytes = $4.cantidad; 
	 }
#line 1743 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 328 "semantic.y" /* yacc.c:1646  */
    { (yyval.argu).num = (yyvsp[0].argu).num; 
				 for(int i = 0; i < (yyvsp[0].argu).num; i++){
					(yyval.argu).lista_args[i] = (yyvsp[0].argu).lista_args[i];
				 }
			   }
#line 1753 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 333 "semantic.y" /* yacc.c:1646  */
    { (yyval.argu).num = 0; }
#line 1759 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 337 "semantic.y" /* yacc.c:1646  */
    {
		  		(yyval.argu).num = 1 + (yyvsp[-4].argu).num;
				 for(int i = 0; i < (yyvsp[-4].argu).num; i++){
					(yyval.argu).lista_args[i] = (yyvsp[-4].argu).lista_args[i];
				 }
				 //FALTA CHECAR BIEN EL TIPO PARA CASOS MULTIDIMENSIONALES
				 (yyval.argu).lista_args[(yyval.argu).num-1] = (yyvsp[-2].tipo).type;
		  }
#line 1772 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 345 "semantic.y" /* yacc.c:1646  */
    {
			     (yyval.argu).num = 1;
				 (yyval.argu).lista_args[0] = (yyvsp[-2].tipo).type;
		  }
#line 1781 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 357 "semantic.y" /* yacc.c:1646  */
    {
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[0].siguientes)));
        insert_cuad(&codigo_intermedio, c);                                
    }
#line 1794 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 365 "semantic.y" /* yacc.c:1646  */
    {
        char label[32];
        strcpy(label, newLabel());                                
        (yyval.siguientes) = (yyvsp[0].siguientes);                
        backpatch(&(yyvsp[-2].siguientes), label, &codigo_intermedio);                
        printf("SS->SS S\n");
    }
#line 1806 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 372 "semantic.y" /* yacc.c:1646  */
    {
        char label[32];
        strcpy(label, newLabel());
        (yyval.siguientes) = (yyvsp[0].siguientes);
        backpatch(&(yyvsp[0].siguientes), label, &codigo_intermedio);
        printf("SS->S\n");
    }
#line 1818 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 382 "semantic.y" /* yacc.c:1646  */
    {
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[-1].booleanos).trues));
        insert_cuad(&codigo_intermedio, c);
    }
#line 1831 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 390 "semantic.y" /* yacc.c:1646  */
    {
        cuadrupla c, c1;
        c.op = GOTO;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[0].siguientes)));
        push_label(&lfalses, get_first(&(yyvsp[-3].booleanos).falses));
        insert_cuad(&codigo_intermedio, c);
    }
#line 1845 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 398 "semantic.y" /* yacc.c:1646  */
    {
        char label[32];
        strcpy(label, newLabel());
        
        if((yyvsp[0].siguientesp).ifelse==false){
            (yyval.siguientes) = merge(&(yyvsp[-5].booleanos).falses, &(yyvsp[0].siguientesp).siguientes);
            backpatch(&(yyvsp[-5].booleanos).falses, label, &codigo_intermedio);                                
            printf("S->if(B) S\n");
        }else{
            char label2[32];                                    
            strcpy(label2, newLabel());                
            (yyval.siguientes) = merge(&(yyvsp[-2].siguientes),&(yyvsp[0].siguientesp).siguientes);
            backpatch(&(yyvsp[-5].booleanos).trues, label, &codigo_intermedio);
            backpatch(&(yyvsp[-5].booleanos).falses, label2, &codigo_intermedio);                 
            printf("S->if(B)S else S\n");
        }
    }
#line 1867 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 415 "semantic.y" /* yacc.c:1646  */
    {
        char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                
        strcpy(label2, newIndex());         
        strcpy(temp, newTemp());
		printf("tempito %s /n", temp);
        (yyval.siguientes) = (yyvsp[-2].booleanos).falses;
        cuadrupla c1;
        c1.op = IFF;
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&(yyvsp[-2].booleanos).trues, label, &codigo_intermedio);
        backpatch(&(yyvsp[-2].booleanos).falses, label2, &codigo_intermedio);
        printf("S->while(B)S\n");
    }
#line 1888 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 431 "semantic.y" /* yacc.c:1646  */
    {
		char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                

		//Ejecucion incondicional de la sentencia
		backpatch(&(yyvsp[-2].booleanos).trues, label, &codigo_intermedio);

        strcpy(label2, newIndex());         
        strcpy(temp, newTemp());
		printf("tempito %s /n", temp);
        (yyval.siguientes) = (yyvsp[-2].booleanos).falses;
        cuadrupla c1;
        c1.op = IFF;
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&(yyvsp[-2].booleanos).trues, label, &codigo_intermedio);
        backpatch(&(yyvsp[-2].booleanos).falses, label2, &codigo_intermedio);
        printf("S->do S while(B)\n");
	}
#line 1913 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 451 "semantic.y" /* yacc.c:1646  */
    {
		meter_assign((yyvsp[-6].siguientes).arr_codigo, (yyvsp[-6].siguientes).count_codigo);
        char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                
        strcpy(label2, newIndex());         
        strcpy(temp, newTemp());
        printf("tempito %s /n", temp);
        (yyval.siguientes) = (yyvsp[-4].booleanos).falses;
        cuadrupla c1;
        c1.op = IFF;
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&(yyvsp[-4].booleanos).trues, label, &codigo_intermedio);
        backpatch(&(yyvsp[-4].booleanos).falses, label2, &codigo_intermedio);
		meter_assign((yyvsp[-2].siguientes).arr_codigo, (yyvsp[-2].siguientes).count_codigo);
        printf("S->for(ass; cond; ass) sent\n");
    }
#line 1936 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 469 "semantic.y" /* yacc.c:1646  */
    { meter_assign((yyvsp[-1].siguientes).arr_codigo, (yyvsp[-1].siguientes).count_codigo); }
#line 1942 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 472 "semantic.y" /* yacc.c:1646  */
    {
        char label[32];
        (yyval.siguientes) = (yyvsp[-1].siguientes);                
        strcpy(label, newLabel());                
        backpatch(&(yyvsp[-1].siguientes), label, &codigo_intermedio);                                
        printf("S->{SS}\n");
    }
#line 1954 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 481 "semantic.y" /* yacc.c:1646  */
    {
        char i[32];
        strcpy(i, newIndex());
        (yyval.siguientes) = create_list(i);
        printf("S->print(E);\n");
    }
#line 1965 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 490 "semantic.y" /* yacc.c:1646  */
    {
                char i[32];
                strcpy(i, newIndex());
                (yyval.siguientes) = create_list(i);
                printf("%s, %s, %d\n", (yyvsp[-2].pi).id1, (yyvsp[-2].pi).id2,(yyvsp[-2].pi).type);
                exp e = asignacion((yyvsp[-2].pi).id1, (yyvsp[-2].pi).id2, (yyvsp[0].expresion), (yyvsp[-2].pi).type); 
                printf("S->parte_izq = E;\n");
				int iterador;
				(yyval.siguientes).count_codigo = e.count_codigo;
				for(iterador = 0; iterador < e.count_codigo; iterador++) {
					(yyval.siguientes).arr_codigo[iterador] = e.arr_codigo[iterador];
				}
	}
#line 1983 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 506 "semantic.y" /* yacc.c:1646  */
    { printf("sin else\n"); (yyval.siguientesp).ifelse= false;}
#line 1989 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 508 "semantic.y" /* yacc.c:1646  */
    {        
            cuadrupla c1;
            c1.op = LABEL;
            strcpy(c1.op1, "");
            strcpy(c1.op2, "");
            strcpy(c1.res, pop_label(&lfalses));
            insert_cuad(&codigo_intermedio, c1);
        }
#line 2002 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 516 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.siguientesp).ifelse= true;
        (yyval.siguientesp).siguientes = (yyvsp[0].siguientes);
    }
#line 2011 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 529 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.pi).id1, (yyvsp[0].id)); strcpy((yyval.pi).id2,""); (yyval.pi).type = -1;}
#line 2017 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 530 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.pi).id1, (yyvsp[0].vararr).representacion); (yyval.pi).type = (yyvsp[0].vararr).type;}
#line 2023 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 531 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.pi).id1, (yyvsp[-2].id)); strcpy((yyval.pi).id2, (yyvsp[0].id)); (yyval.pi).type = -1;}
#line 2029 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 535 "semantic.y" /* yacc.c:1646  */
    { if((yyvsp[-1].expresion).type != 0) { 
                                    yyerror("Debes indexar el arreglo con un entero.\n"); 
                                  }
								  strcpy((yyval.vararr).representacion, (yyvsp[-3].id));
								  strcat((yyval.vararr).representacion, "[");
								  strcat((yyval.vararr).representacion, (yyvsp[-1].expresion).dir);
								  strcat((yyval.vararr).representacion, "]");
                                  struct nodo* it = stack_masterchefs;
                                  int encontrado = 0;
                                  while(it != NULL) {
                                    int x = search(it->tabla->st, (yyvsp[-3].id)); 
                                    if(x != -1) {
                                        encontrado = 1;
                                        int type_row = it->tabla->st->symbols[x].type;
                                        (yyval.vararr).type = it->tabla->tt->trs[type_row].base.renglon;
                                        if((yyval.vararr).type == -1) {
                                            yyerror("No seas pendejo. Mayor cantidad de dimensiones que las definidas");
                                            exit(1);
                                        }
                                        break;
                                    }
                                    it = it->siguiente;
                                  }
                                  if(!encontrado) {
                                    yyerror("El arreglo no fue declarado antes.\n");
                                    exit(1);
                                  } 
                                  (yyval.vararr).tt = it->tabla->tt; }
#line 2062 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 563 "semantic.y" /* yacc.c:1646  */
    { 
								  strcat((yyval.vararr).representacion, "[");
								  strcat((yyval.vararr).representacion, (yyvsp[-1].expresion).dir);
								  strcat((yyval.vararr).representacion, "]");
                                  if((yyvsp[-1].expresion).type != 0) { 
                                    yyerror("Debes indexar el arreglo con un entero.\n"); 
                                  }
                                  if((yyvsp[-3].vararr).type == -1) {
                                    yyerror("No seas pendejo. Mayor cantidad de dimensiones que las definidas");
                                    exit(1);
                                  }  
                                  int row_hijo = (yyvsp[-3].vararr).type;
                                  (yyval.vararr).type = (*(yyvsp[-3].vararr).tt).trs[row_hijo].base.renglon;
                                  if((yyval.vararr).type == -1) {
                                    yyerror("No seas pendejo. Mayor cantidad de dimensiones que las definidas");
                                    exit(1);
                                  }  
                                  (yyval.vararr).tt = (yyvsp[-3].vararr).tt;

       }
#line 2087 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 586 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = suma((yyvsp[-2].expresion), (yyvsp[0].expresion)); printf("E -> E + E\n"); }
#line 2093 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 587 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = resta((yyvsp[-2].expresion), (yyvsp[0].expresion)); printf("E -> E - E\n"); }
#line 2099 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 588 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = multiplicacion((yyvsp[-2].expresion), (yyvsp[0].expresion)); printf("E -> E * E\n"); }
#line 2105 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 589 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = division((yyvsp[-2].expresion), (yyvsp[0].expresion)); printf("E -> E / E\n"); }
#line 2111 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 590 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = modulo((yyvsp[-2].expresion), (yyvsp[0].expresion)); printf("E -> E mod E\n"); }
#line 2117 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 591 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = envolver_varr((yyvsp[0].vararr)); printf("E -> id[E]\n"); }
#line 2123 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 592 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = identificador((yyvsp[0].id)); printf("E->id\n"); printf("%s\n",(yyvsp[0].id)); }
#line 2129 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 593 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = envolver_cadena((yyvsp[0].cad)); printf("E -> CADENA\n"); }
#line 2135 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 594 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = get_numero((yyvsp[0].num)); printf("E->numero\n"); printf("%s\n",(yyvsp[0].num).val); }
#line 2141 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 595 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = envolver_caracter((yyvsp[0].car)); printf("E -> CARACTER\n"); }
#line 2147 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 596 "semantic.y" /* yacc.c:1646  */
    {}
#line 2153 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 610 "semantic.y" /* yacc.c:1646  */
    {
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[-1].booleanos).falses));
        insert_cuad(&codigo_intermedio, c);                    
    }
#line 2166 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 617 "semantic.y" /* yacc.c:1646  */
    { 
        char label[32];
        strcpy(label, newLabel());
        backpatch(&(yyvsp[-3].booleanos).falses, label, &codigo_intermedio);
        (yyval.booleanos).trues = merge(&(yyvsp[-3].booleanos).trues, &(yyvsp[0].booleanos).trues);
        (yyval.booleanos).falses = (yyvsp[0].booleanos).falses;
        printf("B -> B || B\n");
    }
#line 2179 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 625 "semantic.y" /* yacc.c:1646  */
    {
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[-1].booleanos).trues));
        insert_cuad(&codigo_intermedio, c);                    
    }
#line 2192 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 632 "semantic.y" /* yacc.c:1646  */
    {
        char label[32];
        strcpy(label, newLabel());                        
        (yyval.booleanos).falses = merge(&(yyvsp[-3].booleanos).falses, &(yyvsp[0].booleanos).falses);
        (yyval.booleanos).trues = (yyvsp[0].booleanos).trues;
        backpatch(&(yyvsp[-3].booleanos).trues, label, &codigo_intermedio);
        printf("B -> B && B\n");
    }
#line 2205 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 640 "semantic.y" /* yacc.c:1646  */
    {
        (yyval.booleanos).falses = (yyvsp[0].booleanos).trues;
        (yyval.booleanos).trues = (yyvsp[0].booleanos).falses;
        printf("B -> !B\n");
    }
#line 2215 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 645 "semantic.y" /* yacc.c:1646  */
    {
        (yyval.booleanos).trues = (yyvsp[-1].booleanos).trues;
        (yyval.booleanos).falses = (yyvsp[-1].booleanos).falses;
        //strcpy($$.dir, $2.dir);
        printf("B->(B)\n");
    }
#line 2226 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 651 "semantic.y" /* yacc.c:1646  */
    {
        char i[32];
        char i2[32];
        char temp[32];
        strcpy(i, newIndex());
        strcpy(i2, newIndex());
        strcpy(temp, newTemp());
        //strcpy($$.dir, temp);
        (yyval.booleanos).trues = create_list(i);
        (yyval.booleanos).falses = create_list(i2);
        cuadrupla c, c1, c2;
        c.op = (yyvsp[-1].rel) ;
        strcpy(c.op1, (yyvsp[-2].expresion).dir);
        strcpy(c.op2, (yyvsp[0].expresion).dir);
        strcpy(c.res, temp);            
        
        c1.op = IFF;
        strcpy(c1.op1, temp);
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, i);            
        
        c2.op = GOTO;
        strcpy(c2.op1, "");
        strcpy(c2.op2, "");
        strcpy(c2.res, i2);
        
        insert_cuad(&codigo_intermedio, c);
        insert_cuad(&codigo_intermedio, c1);
        insert_cuad(&codigo_intermedio, c2);
        printf("B->E rel E\n");
        printf("E1.dir %s rel E2.dir %s\n", (yyvsp[-2].expresion).dir, (yyvsp[0].expresion).dir);
    }
#line 2263 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 683 "semantic.y" /* yacc.c:1646  */
    {
        char i[32];
        strcpy(i, newIndex());
        (yyval.booleanos).trues = create_list(i);
        cuadrupla c;
        c.op = GOTO;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, i);
        insert_cuad(&codigo_intermedio, c);
        printf("B->true\n");
    }
#line 2280 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 695 "semantic.y" /* yacc.c:1646  */
    {
        char i[32];
        strcpy(i, newIndex());
        (yyval.booleanos).falses = create_list(i);
        cuadrupla c;
        c.op = GOTO;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, i);
        insert_cuad(&codigo_intermedio, c);
        printf("B->false\n");
    }
#line 2297 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 710 "semantic.y" /* yacc.c:1646  */
    { (yyval.rel) = LESS_THAN; printf("R-> <\n"); }
#line 2303 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 711 "semantic.y" /* yacc.c:1646  */
    { (yyval.rel) = GREATER_THAN; printf("R-> >\n"); }
#line 2309 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 712 "semantic.y" /* yacc.c:1646  */
    { (yyval.rel) = LESS_OR_EQUAL_THAN; printf("R-> <=\n"); }
#line 2315 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 713 "semantic.y" /* yacc.c:1646  */
    { (yyval.rel) = GREATER_OR_EQUAL_THAN; printf("R-> >=\n"); }
#line 2321 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 714 "semantic.y" /* yacc.c:1646  */
    { (yyval.rel) = NOT_EQUALS; printf("R-> !=\n"); }
#line 2327 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 715 "semantic.y" /* yacc.c:1646  */
    { (yyval.rel) = EQUALS; printf("R-> ==\n"); }
#line 2333 "semantic.tab.c" /* yacc.c:1646  */
    break;


#line 2337 "semantic.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
  return yyresult;
}
#line 718 "semantic.y" /* yacc.c:1906  */


void init(){    
	masterchef = (struct mastertab *) malloc(sizeof(struct mastertab));
	masterchef->tt = (typetab *) malloc(sizeof(typetab));
	masterchef->st = (symtab *) malloc(sizeof(symtab));
	stack_masterchefs = (struct nodo*) malloc(sizeof(struct nodo));
	stack_masterchefs = NULL;
    create_table(masterchef->st);
    create_type_table(masterchef->tt);

	stack_masterchefs = mete(stack_masterchefs, masterchef);

    create_code(&codigo_intermedio);
    create_labels(&lfalses);    
}

int max(int t1, int t2){
	if( t1==t2) return t1;
	if( t1 ==0 && t2 == 1) return 1;
	if( t1 ==1 && t2 == 0) return 1;
	if( t1 ==0 && t2 == 2) return 2;
	if( t1 ==2 && t2 == 0) return 2;
	if( t1 ==2 && t2 == 1) return 2;
	if( t1 ==1 && t2 == 2) return 2;
	else return -1;
}

exp suma(exp e1, exp e2){
    exp e;
    cuadrupla c;
    e.type = max(e1.type, e2.type);
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        c.op = MAS;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

exp resta(exp e1, exp e2){
    exp e;
    cuadrupla c;
    char t[32];
    e.type = max(e1.type, e2.type);
    
    if( e.type==-1) yyerror("Error de tipos");
    else{
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        c.op = MENOS;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

exp multiplicacion(exp e1, exp e2){
    exp e;
    cuadrupla c;
    e.type = max(e1.type, e2.type);
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        c.op = MULTIPLICACION;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

exp division(exp e1, exp e2){
    exp e;
    cuadrupla c;
    e.type = max(e1.type, e2.type);
    if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        c.op = DIVISION;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

exp modulo(exp e1, exp e2){
	if(e1.type != 0 || e2.type != 0) {
		yyerror("La operación módulo requiere operandos enteros.\n");
		exit(1);
	}
    exp e;
    cuadrupla c;
    e.type = max(e1.type, e2.type);
	if( e.type==-1) yyerror("Error de tipos");
    else{
        char t[32];
        strcpy(t,newTemp());
        strcpy(e.dir, t);
        c.op = MODULO;
        strcpy(c.op1, ampliar(e1.dir, e1.type, e.type));
        strcpy(c.op2, ampliar(e2.dir, e2.type, e.type));
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
    }
    return e;    
}

int get_tipo_tablas(char *id) {
	int tipo;
	int busqueda = search(stack_masterchefs->tabla->st, id);
	if (busqueda == -1) {
		busqueda = search(masterchef->st, id);
		if (busqueda == -1) {
			yyerror("El identificador para la variable no fue declarada antes.\n");
			exit(1);
		} else {	
			tipo = get_type(masterchef->st, id);
		}
	} else {
		tipo = get_type(stack_masterchefs->tabla->st, id);
	}
	return tipo;
}

exp asignacion(char *id, char *id2, exp e, int trecibido){
	exp e1;
	e1.count_codigo = 0;
	if(trecibido == -1) {
		int tipo;
		int es_estruct = 0;
		if(strcmp(id2, "") == 0) {
			tipo = get_tipo_tablas(id);
		} else {
			es_estruct = 1;
			int renglon = search(masterchef->st, id);
			if (renglon == -1) {
				yyerror("El identificador no fue declarado\n");
				exit(1);
			}
			typetab tabla_tipos_actual= (*masterchef->tt);
			int tiene_struct = tabla_tipos_actual.trs[masterchef->st->symbols[renglon].type].base.renglon;
			if(tiene_struct == -2) {
				symtab *st_struct = tabla_tipos_actual.trs[stack_masterchefs->tabla->st->symbols[renglon].type].base.smt->st;
				int renglon2 = search(st_struct, id2);
				if (renglon2 == -1) {
					st_struct = tabla_tipos_actual.trs[masterchef->st->symbols[renglon].type].base.smt->st;
					renglon2 = search(st_struct, id2);
					if(renglon2 == -1) {
						yyerror("El struct no fue declarado\n");
						exit(1);
					}
				}
				tipo = get_type(st_struct, id2);
			} else {
				yyerror2("Intento de acceso a atributo de no estructura: ", id);
				exit(1);
			}
		}

		if( tipo != -1){        
			printf("djekjde");
			e1.type = e.type;
			strcpy(e1.dir, id);
			cuadrupla c;
			c.op = ASSIGNATION;
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
			//insert_cuad(&codigo_intermedio, c);  
			e1.arr_codigo[e1.count_codigo] = c;	
			e1.count_codigo++;
		}else{
			yyerror("El identificador no fue declarado\n");
			exit(1);
		}
	} else {
		// VARARR
		e1.type = e.type;
		strcpy(e1.dir, id);
		cuadrupla c;
		c.op = ASSIGNATION;
		strcpy(c.op1, reducir(e.dir, trecibido, e.type));
		strcpy(c.op2, "");
		strcpy(c.res, id);//en este caso id es la representacin de vararr
		//insert_cuad(&codigo_intermedio, c);  
		e1.arr_codigo[e1.count_codigo] = c;
		e1.count_codigo++;}
		return e1;
}

exp get_numero(numero n){
    exp e;
    e.type = n.type;
    strcpy(e.dir, n.val);
    return e;
}

exp envolver_cadena(cadena cadenita) {
    exp e;
    e.type = cadenita.type;
    strcpy(e.dir, cadenita.val);
    return e;
}

exp envolver_caracter(caracter caractercito) {
    exp e;
    e.type = caractercito.type;
    e.dir[0] = caractercito.val;
    return e;
}

exp envolver_varr(varr arreglito) {
    exp e;
    e.type = arreglito.type;
    strcpy(e.dir, arreglito.representacion);
    return e;
}

exp identificador(char *id){
    exp e;
    if(search(stack_masterchefs->tabla->st, id) !=-1){
        e.type = get_type(stack_masterchefs->tabla->st, id);
        strcpy(e.dir, id);
    }else{
    	if(search(masterchef->st, id) !=-1){
         	e.type = get_type(masterchef->st, id);
        	strcpy(e.dir, id);
        } else {
        	yyerror("Error semantico: el identificador no existe");
    		exit(1);
    	}
    }
    return e;
}

char *ampliar(char *dir, int t1, int t2){
    cuadrupla c;
    char *t= (char*) malloc(32*sizeof(char));
    
    if( t1==t2) return dir;
    if( t1 ==0 && t2 == 1){
        c.op = EQ;
        strcpy(c.op1, "(float)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        return t;
    }        
    if( t1 ==0 && t2 == 2){
        c.op = EQ;
        strcpy(c.op1, "(double)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        return t;
    }        
    
    if( t1 ==1 && t2 == 2) {
        c.op = EQ;
        strcpy(c.op1, "(double)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        return t;
    }            
}

char *reducir(char *dir, int t1, int t2){
    cuadrupla c;
    char *t= (char*) malloc(32*sizeof(char));
    
    if( t1==t2) return dir;
    if( t1 ==0 && t2 == 1){
        c.op = EQ;
        strcpy(c.op1, "(int)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        printf("perdida de información se esta asignando un float a un int\n");
        return t;
    }        
    if( t1 ==0 && t2 == 2){
        c.op = EQ;
        strcpy(c.op1, "(int)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        printf("perdida de información se esta asignando un double a un int\n");
        return t;
    }        
    if( t1 ==1 && t2 == 2) {
        c.op = EQ;
        strcpy(c.op1, "(float)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        insert_cuad(&codigo_intermedio, c);
        printf("perdida de información se esta asignando un double a un float\n");
        return t;
    }            
	//faltan casos inconsistentes chars vs numeros vs arrays
}

char* newTemp(){
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "t");
    char num[30];
    sprintf(num, "%d", temp);
    strcat(temporal, num);
    temp++;
    return temporal;
}

char* newLabel(){
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "L");
    char num[30];
    sprintf(num, "%d", label);
    strcat(temporal, num);
    label++;
    return temporal;
}

char* newIndex(){
    char *temporal= (char*) malloc(32*sizeof(char));
    strcpy(temporal , "I");
    char num[30];
    sprintf(num, "%d", indice);
    strcat(temporal, num);
    indice++;
    return temporal;
}

void yyerror(char *msg) {
	printf("%s\n", msg);
}

void yyerror2(char *c, char *c2){
    strcat(c, c2);
	yyerror(c);
}

void finish(){    
    print_code(&codigo_intermedio);    
}

void meter_assign(cuadrupla c[], int cou){
	for(int j = 0; j < cou; j++){
		insert_cuad(&codigo_intermedio, c[j]);
		printf("metemos ass\n");
		printf("%s, %s, %s, %d", c[j].op1, c[j].op2, c[j].res, c[j].op);
	}
}

int main(int argc, char **argv) {
	yyin = fopen(argv[1], "r");
	//int a = yylex();
	//	printf("<<<<<%d\n", a);
	int result = yyparse();
	printf("resultado del analisis: %d\n", result);
	fclose(yyin);
	return 0;
}