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
	char current_label[32];

	/* Variables para guardar el tipo y ancho actual */
	int current_type;
	int current_dim;
	int current_arr_type;
	int current_dim_arr;
	int current_function_type;
	char siguiente_breakable_pila[100][32];
	int siguiente_count = 0;

	/* Varaibles para contar las temporales, etiquetas e indices */
	int label;
	int temp;
	int indice;
	int breakeablecitos = 0;
	char pila_switch[100][32];
	int count_switch = 0;

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
	void verifica_call(char[], int[][2], int);


#line 150 "semantic.tab.c" /* yacc.c:339  */

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
#line 85 "semantic.y" /* yacc.c:355  */

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
	int dims;
    int rel;
	char char_signo[1];
	struct {
		int p;
		int lista_tipos[100][2];
		int count;
	} parrams;

#line 278 "semantic.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SEMANTIC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 295 "semantic.tab.c" /* yacc.c:358  */

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
#define YYLAST   219

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  187

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
       0,   189,   189,   189,   202,   202,   213,   217,   218,   219,
     220,   221,   222,   222,   247,   258,   273,   274,   275,   279,
     280,   281,   285,   302,   306,   315,   338,   349,   306,   371,
     375,   381,   385,   413,   440,   441,   445,   445,   460,   470,
     478,   470,   503,   503,   525,   525,   550,   550,   573,   574,
     589,   595,   602,   602,   616,   630,   639,   655,   657,   656,
     672,   711,   672,   722,   723,   727,   728,   729,   733,   782,
     814,   815,   816,   817,   818,   819,   820,   821,   822,   823,
     824,   839,   848,   852,   864,   879,   879,   894,   894,   909,
     914,   920,   952,   964,   979,   980,   981,   982,   983,   984
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
  "numero", "signo", "arreglo", "funcs", "$@4", "$@5", "$@6", "$@7",
  "args", "lista_args", "parte_arr", "sents", "$@8", "sent", "$@9", "$@10",
  "@11", "@12", "@13", "@14", "assign", "sentp", "$@15", "casos", "@16",
  "@17", "parte_izq", "var_arr", "exp", "params", "lista_param", "cond",
  "$@18", "$@19", "rel", YY_NULLPTR
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

#define YYTABLE_NINF -83

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -84,     7,   191,   -84,   -84,   -84,   -84,   -84,   -84,     6,
       4,   -84,   -84,   191,   -84,    10,   191,    20,    22,    -7,
      38,   -84,    17,   -84,   191,    45,   -84,    25,   -84,   -84,
      80,    -1,   -84,    22,   191,    22,   -84,   -84,   -84,   -84,
      67,    50,    72,   -84,   105,   -84,   191,   115,   -84,   133,
     112,   105,   191,   105,   -84,   138,   -84,   138,    95,    96,
     -84,    98,   136,    84,     2,   109,   102,   140,   -84,   154,
     134,   157,   160,    53,    53,   138,    84,   -84,   -11,   -84,
     -84,   -84,   157,    73,    84,   147,   -84,    86,   150,   167,
     138,   -84,    84,    84,   -84,   -84,   -84,    53,    53,   144,
      54,    75,   159,    19,   130,   -84,    84,    84,    84,    84,
      84,    -3,   -84,   -84,   166,   -84,   -84,   156,    12,   -84,
     100,   -84,   -84,   -84,   -84,   -84,   -84,    84,   -84,   -84,
     -84,   -84,   148,   -84,   156,   155,   173,    41,    41,   -84,
     -84,   -84,   -84,    53,     4,   -84,   -84,   156,    53,    53,
     138,   138,    53,   198,   -84,    84,    37,   -84,   171,   -84,
     -84,   -84,   129,     0,   156,   150,   192,   196,    17,   138,
     201,   161,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   138,
     138,   138,   -84,   -84,   -84,     0,   -84
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     6,     1,     7,     8,     9,    10,    11,     0,
      29,     4,    12,     0,     3,     0,     6,     0,    23,     0,
       0,    24,    21,    15,     6,     0,    13,     0,    19,    20,
       0,     0,     5,    23,    31,    23,    16,    17,    18,    14,
       0,     0,    30,    22,    35,    25,     0,     0,    33,     0,
       0,    35,     6,    35,    34,     0,    32,     0,     0,     0,
      44,     0,     0,    21,    65,    21,     0,    36,    38,     0,
       0,    66,    36,    21,    21,     0,    21,    54,    76,    77,
      79,    78,    75,     0,    21,     0,    50,     0,     0,     0,
       0,    48,    21,    21,    51,    92,    93,    21,    21,     0,
       0,     0,     0,     0,    21,    55,    21,    21,    21,    21,
      21,     0,    67,    49,     0,    27,    37,    56,     0,    89,
       0,    99,    98,    95,    97,    94,    96,    21,    85,    87,
      39,    42,     0,    52,    84,     0,    81,    70,    71,    72,
      73,    74,    68,    21,    29,    69,    90,    91,    21,    21,
       0,     0,    21,     0,    80,    21,     0,    28,    86,    88,
      40,    43,     0,    64,    83,     0,    57,     0,    21,     0,
       0,     0,    58,    41,    45,    60,    63,    53,    46,     0,
       0,     0,    59,    61,    47,    64,    62
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -84,   -84,   -84,   -10,   -84,     3,   -84,   -84,   -22,   -84,
     -13,    71,   -84,   -84,   -84,   -84,   -84,   -84,    92,   162,
     -84,   -71,   -84,   -84,   -84,   -84,   -84,   -84,   -83,   -84,
     -84,    31,   -84,   -84,   -84,   -54,   -53,   -84,   -84,   -65,
     -84,   -84,   -84
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    10,    15,    11,    16,    19,    81,    31,
      23,    14,    27,    49,    89,   144,    41,    42,    48,    67,
      90,    68,   150,   166,   151,    75,   181,   153,    69,   173,
     179,   170,   180,   185,    70,    82,    99,   135,   136,   100,
     148,   149,   127
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      30,    71,    84,    71,   102,   114,    20,     3,    24,   101,
      83,   142,    87,    13,    32,    84,    17,    12,    85,   116,
      39,    71,    43,   103,   168,   169,   145,    25,    36,    37,
      38,   111,   119,   120,    71,    22,    71,    40,    18,   117,
     118,   104,    55,   106,   107,   108,   109,   110,    21,    50,
      26,   134,   165,   137,   138,   139,   140,   141,   106,   107,
     108,   109,   110,    28,    29,   106,   107,   108,   109,   110,
      95,    96,   133,    33,   147,   128,   129,    34,   156,   160,
     161,    78,   171,   158,   159,    79,    80,   162,   105,   108,
     109,   110,   128,   129,    35,    44,    71,    71,   176,    28,
      29,   113,   164,    45,    97,    98,    46,   130,   182,   183,
     184,    71,    78,   128,   129,    71,    79,    80,    47,   106,
     107,   108,   109,   110,    86,    71,    71,    71,   131,    51,
      28,    29,   106,   107,   108,   109,   110,    78,   128,   129,
      53,    79,    80,    54,    52,    56,   175,    73,    74,    57,
      76,    77,   -26,   146,    88,    28,    29,    58,    78,    59,
      60,    61,    79,    80,    62,    63,    64,   128,   129,    91,
      93,    92,    94,    65,    66,   112,    28,    29,    64,   115,
     132,   143,   167,   -82,   121,   122,   123,   124,   125,   126,
     106,   107,   108,   109,   110,     4,     5,     6,     7,     8,
     152,     9,   106,   107,   108,   109,   110,   155,   154,   163,
     129,   174,   172,   177,   178,   157,   186,     0,     0,    72
};

static const yytype_int16 yycheck[] =
{
      22,    55,    13,    57,    75,    88,    16,     0,    15,    74,
      63,    14,    65,     9,    24,    13,    13,    11,    16,    90,
      33,    75,    35,    76,    24,    25,    14,    34,    29,    30,
      31,    84,    97,    98,    88,    13,    90,    34,    28,    92,
      93,    52,    52,    46,    47,    48,    49,    50,    28,    46,
      12,   104,    15,   106,   107,   108,   109,   110,    46,    47,
      48,    49,    50,    46,    47,    46,    47,    48,    49,    50,
      17,    18,    53,    28,   127,    38,    39,    52,   143,   150,
     151,    28,   165,   148,   149,    32,    33,   152,    15,    48,
      49,    50,    38,    39,    14,    28,   150,   151,   169,    46,
      47,    15,   155,    53,    51,    52,    34,    53,   179,   180,
     181,   165,    28,    38,    39,   169,    32,    33,    13,    46,
      47,    48,    49,    50,    15,   179,   180,   181,    53,    14,
      46,    47,    46,    47,    48,    49,    50,    28,    38,    39,
      28,    32,    33,    51,    11,    53,   168,    52,    52,    11,
      52,    15,    12,    53,    52,    46,    47,    19,    28,    21,
      22,    23,    32,    33,    26,    27,    28,    38,    39,    15,
      13,    37,    12,    35,    36,    28,    46,    47,    28,    12,
      21,    15,    53,    53,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,     4,     5,     6,     7,     8,
      52,    10,    46,    47,    48,    49,    50,    34,    53,    11,
      39,    15,    20,    12,    53,   144,   185,    -1,    -1,    57
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    56,    57,     0,     4,     5,     6,     7,     8,    10,
      58,    60,    11,     9,    66,    59,    61,    60,    28,    62,
      58,    28,    13,    65,    15,    34,    12,    67,    46,    47,
      63,    64,    58,    28,    52,    14,    29,    30,    31,    65,
      60,    71,    72,    65,    28,    53,    34,    13,    73,    68,
      60,    14,    11,    28,    73,    58,    73,    11,    19,    21,
      22,    23,    26,    27,    28,    35,    36,    74,    76,    83,
      89,    90,    74,    52,    52,    80,    52,    15,    28,    32,
      33,    63,    90,    91,    13,    16,    15,    91,    52,    69,
      75,    15,    37,    13,    12,    17,    18,    51,    52,    91,
      94,    94,    76,    91,    52,    15,    46,    47,    48,    49,
      50,    91,    28,    15,    83,    12,    76,    91,    91,    94,
      94,    40,    41,    42,    43,    44,    45,    97,    38,    39,
      53,    53,    21,    53,    91,    92,    93,    91,    91,    91,
      91,    91,    14,    15,    70,    14,    53,    91,    95,    96,
      77,    79,    52,    82,    53,    34,    94,    66,    94,    94,
      76,    76,    94,    11,    91,    15,    78,    53,    24,    25,
      86,    83,    20,    84,    15,    63,    76,    12,    53,    85,
      87,    81,    76,    76,    76,    88,    86
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    57,    56,    59,    58,    58,    60,    60,    60,
      60,    60,    61,    60,    62,    62,    63,    63,    63,    64,
      64,    64,    65,    65,    67,    68,    69,    70,    66,    66,
      71,    71,    72,    72,    73,    73,    75,    74,    74,    77,
      78,    76,    79,    76,    80,    76,    81,    76,    76,    76,
      76,    76,    82,    76,    76,    76,    83,    84,    85,    84,
      87,    88,    86,    86,    86,    89,    89,    89,    90,    90,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    92,    92,    93,    93,    95,    94,    96,    94,    94,
      94,    94,    94,    94,    97,    97,    97,    97,    97,    97
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     0,     5,     0,     1,     1,     1,
       1,     1,     0,     5,     4,     2,     2,     2,     2,     1,
       1,     0,     4,     0,     0,     0,     0,     0,    15,     0,
       1,     0,     5,     3,     3,     0,     0,     3,     1,     0,
       0,     8,     0,     6,     0,     8,     0,    10,     2,     3,
       2,     3,     0,     8,     2,     3,     3,     0,     0,     3,
       0,     0,     6,     2,     0,     1,     1,     3,     4,     4,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     1,
       4,     1,     0,     3,     1,     0,     4,     0,     4,     2,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1
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
#line 189 "semantic.y" /* yacc.c:1646  */
    { init(); }
#line 1512 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 191 "semantic.y" /* yacc.c:1646  */
    {
		printf("tabla de tipos\n");
	 	print_type_table(masterchef->tt);
		printf("tabla de simbolos\n");
		print_table(masterchef->st); 
        printf("P -> D funcs\n"); /*finish()*/
		finish(); 
    }
#line 1525 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 202 "semantic.y" /* yacc.c:1646  */
    { 
	 	current_type = (yyvsp[0].tipo).type;
		if((yyvsp[0].tipo).type == 4) {
			yyerror("No puedes declarar variables tipo void\n");
			exit(1);
		}
		current_dim = (yyvsp[0].tipo).bytes;
		current_dim_arr = current_dim; 
		current_arr_type = current_type;
     }
#line 1540 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 212 "semantic.y" /* yacc.c:1646  */
    {(yyval.cant).cantidad = (yyvsp[-2].cant).cantidad; (yyval.cant).cantidad += (yyvsp[0].cant).cantidad; }
#line 1546 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 213 "semantic.y" /* yacc.c:1646  */
    { (yyval.cant).cantidad = 0; }
#line 1552 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 217 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 0; (yyval.tipo).bytes = 4; }
#line 1558 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 218 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 1; (yyval.tipo).bytes = 4; }
#line 1564 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 219 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 2; (yyval.tipo).bytes = 8; }
#line 1570 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 220 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 3; (yyval.tipo).bytes = 1; }
#line 1576 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 221 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 4; (yyval.tipo).bytes = 1; }
#line 1582 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 222 "semantic.y" /* yacc.c:1646  */
    {
		struct mastertab* ntab = (struct mastertab *) malloc(sizeof(struct mastertab));
		ntab->tt = (typetab *) malloc(sizeof(typetab));
		ntab->st= (symtab *) malloc(sizeof(symtab));
		create_table(ntab->st);
		create_type_table(ntab->tt);
		stack_masterchefs = mete(stack_masterchefs, ntab);
	  }
#line 1595 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 230 "semantic.y" /* yacc.c:1646  */
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
#line 1614 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 247 "semantic.y" /* yacc.c:1646  */
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
#line 1630 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 258 "semantic.y" /* yacc.c:1646  */
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
#line 1647 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 273 "semantic.y" /* yacc.c:1646  */
    { (yyval.num).type = (yyvsp[0].num).type; strcpy((yyval.num).val, (yyvsp[-1].char_signo)); strcat((yyval.num).val, (yyvsp[0].num).val); }
#line 1653 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 274 "semantic.y" /* yacc.c:1646  */
    { (yyval.num).type = (yyvsp[0].num).type; strcpy((yyval.num).val, (yyvsp[-1].char_signo)); strcat((yyval.num).val, (yyvsp[0].num).val); }
#line 1659 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 275 "semantic.y" /* yacc.c:1646  */
    { (yyval.num).type = (yyvsp[0].num).type; strcpy((yyval.num).val, (yyvsp[-1].char_signo)); strcat((yyval.num).val, (yyvsp[0].num).val); }
#line 1665 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 279 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.char_signo),""); }
#line 1671 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 280 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.char_signo), "-"); }
#line 1677 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 281 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.char_signo),""); }
#line 1683 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 285 "semantic.y" /* yacc.c:1646  */
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
#line 1705 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 302 "semantic.y" /* yacc.c:1646  */
    { (yyval.arr).tam = 0; }
#line 1711 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 306 "semantic.y" /* yacc.c:1646  */
    {
		struct mastertab* ntab = (struct mastertab *) malloc(sizeof(struct mastertab));
		ntab->tt = (typetab *) malloc(sizeof(typetab));
		ntab->st = (symtab *) malloc(sizeof(symtab));
		create_table(ntab->st);
		create_type_table(ntab->tt);
		stack_masterchefs = mete(stack_masterchefs, ntab);
		current_function_type = (yyvsp[-1].tipo).type;
	 }
#line 1725 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 315 "semantic.y" /* yacc.c:1646  */
    {
		cuadrupla c;
		c.op = LABEL;
		char lab[32];
		strcpy(lab, newLabel());
		strcpy(c.op1, "");
		strcpy(c.op2, "");
		strcpy(c.res, (yyvsp[-4].id));
		insert_cuad(&codigo_intermedio, c);

	 	sym s;
		strcpy(s.id, (yyvsp[-4].id));
		s.type = (yyvsp[-5].tipo).type;
		s.dir = masterchef->tt->count;
		s.var = 1;
		for(int j = 0; j < (yyvsp[-1].argu).num; j++){
			s.args[j][0] = (yyvsp[-1].argu).lista_args[j][0];
			s.args[j][1] = (yyvsp[-1].argu).lista_args[j][1];
		}
		s.num_args = (yyvsp[-1].argu).num;
		insert(masterchef->st, s);

	 }
#line 1753 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 338 "semantic.y" /* yacc.c:1646  */
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
#line 1769 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 349 "semantic.y" /* yacc.c:1646  */
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
		cuadrupla c;
		char label2[32];
		strcpy(label2, newLabel());
		c.op = GOTO;
		strcpy(c.op1, "");
		strcpy(c.op2, "");
		strcpy(c.res, label2);
        insert_cuad(&codigo_intermedio, c);                
	 }
#line 1796 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 375 "semantic.y" /* yacc.c:1646  */
    { (yyval.argu).num = (yyvsp[0].argu).num; 
				 for(int i = 0; i < (yyvsp[0].argu).num; i++){
					(yyval.argu).lista_args[i][0] = (yyvsp[0].argu).lista_args[i][0];
					(yyval.argu).lista_args[i][1] = (yyvsp[0].argu).lista_args[i][1];
				 }
			   }
#line 1807 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 381 "semantic.y" /* yacc.c:1646  */
    { (yyval.argu).num = 0; }
#line 1813 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 385 "semantic.y" /* yacc.c:1646  */
    {
			if((yyvsp[-2].tipo).type == 4) {
				yyerror("Los argumentos no pueden ser tipo void\n");
				exit(1);
			}
			typerow renglon;
			renglon.type = (yyvsp[-2].tipo).type;
			renglon.tam = (yyvsp[-2].tipo).type;
			renglon.base.renglon = (yyvsp[-2].tipo).type;
			insert_type_table(stack_masterchefs->tabla->tt, renglon);
	 		
			sym s;
			strcpy(s.id, (yyvsp[-1].id));
			//s.type = stack_masterchefs->tabla->tt->count-1;
			s.type = (yyvsp[-2].tipo).type;
			s.dir = dir;
			dir+= renglon.tam;
			insert(stack_masterchefs->tabla->st, s);
		
			(yyval.argu).num = 1 + (yyvsp[-4].argu).num;
			for(int i = 0; i < (yyvsp[-4].argu).num; i++){
				(yyval.argu).lista_args[i][0] = (yyvsp[-4].argu).lista_args[i][0];
				(yyval.argu).lista_args[i][1] = (yyvsp[-4].argu).lista_args[i][1];
			}
			//FALTA CHECAR BIEN EL TIPO PARA CASOS MULTIDIMENSIONALES
			(yyval.argu).lista_args[(yyval.argu).num-1][0] = (yyvsp[-2].tipo).type;
			(yyval.argu).lista_args[(yyval.argu).num-1][1] = (yyvsp[0].dims);
		  }
#line 1846 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 413 "semantic.y" /* yacc.c:1646  */
    {
			if((yyvsp[-2].tipo).type == 4) {
				yyerror("Los argumentos no pueden ser tipo void\n");
				exit(1);
			}
			(yyval.argu).num = 1;
			(yyval.argu).lista_args[0][0] = (yyvsp[-2].tipo).type;
			(yyval.argu).lista_args[0][1] = (yyvsp[0].dims);
			
			typerow renglon;
			renglon.type = (yyvsp[-2].tipo).type;
			renglon.tam = (yyvsp[-2].tipo).type;
			renglon.base.renglon = (yyvsp[-2].tipo).type;
			insert_type_table(stack_masterchefs->tabla->tt, renglon);
		
			sym s;
			strcpy(s.id, (yyvsp[-1].id));
			//s.type = stack_masterchefs->tabla->tt->count-1;
			s.type = (yyvsp[-2].tipo).type;
			s.dir = dir;
			dir+= renglon.tam;
			insert(stack_masterchefs->tabla->st, s);

		  }
#line 1875 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 440 "semantic.y" /* yacc.c:1646  */
    { (yyval.dims) = (yyvsp[0].dims) + 1; }
#line 1881 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 441 "semantic.y" /* yacc.c:1646  */
    { (yyval.dims) = 0; }
#line 1887 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 445 "semantic.y" /* yacc.c:1646  */
    {
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[0].siguientes)));
        insert_cuad(&codigo_intermedio, c);                                
    }
#line 1900 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 453 "semantic.y" /* yacc.c:1646  */
    {
        char label[32];
        strcpy(label, newLabel());                                
        (yyval.siguientes) = (yyvsp[0].siguientes);                
        backpatch(&(yyvsp[-2].siguientes), label, &codigo_intermedio);                
        printf("SS->SS S\n");
    }
#line 1912 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 460 "semantic.y" /* yacc.c:1646  */
    {
        char label[32];
        strcpy(label, newLabel());
        (yyval.siguientes) = (yyvsp[0].siguientes);
        backpatch(&(yyvsp[0].siguientes), label, &codigo_intermedio);
        printf("SS->S\n");
    }
#line 1924 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 470 "semantic.y" /* yacc.c:1646  */
    {
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[-1].booleanos).trues));
        insert_cuad(&codigo_intermedio, c);
    }
#line 1937 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 478 "semantic.y" /* yacc.c:1646  */
    {
        cuadrupla c, c1;
        c.op = GOTO;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[0].siguientes)));
        push_label(&lfalses, get_first(&(yyvsp[-3].booleanos).falses));
        insert_cuad(&codigo_intermedio, c);
    }
#line 1951 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 486 "semantic.y" /* yacc.c:1646  */
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
#line 1973 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 503 "semantic.y" /* yacc.c:1646  */
    {
		breakeablecitos += 1;
		strcpy(siguiente_breakable_pila[siguiente_count], (yyval.siguientes).label[0]);
		siguiente_count++;
	}
#line 1983 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 507 "semantic.y" /* yacc.c:1646  */
    {
        char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                
        strcpy(label2, newIndex());         
        strcpy(temp, newTemp());
        (yyval.siguientes) = (yyvsp[-3].booleanos).falses;
        cuadrupla c1;
        c1.op = IFF;
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&(yyvsp[-3].booleanos).trues, label, &codigo_intermedio);
        backpatch(&(yyvsp[-3].booleanos).falses, label2, &codigo_intermedio);
        printf("S->while(B)S\n");
		breakeablecitos -= 1; 
		strcpy(siguiente_breakable_pila[siguiente_count], (yyval.siguientes).label[0]);
		siguiente_count--;
    }
#line 2006 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 525 "semantic.y" /* yacc.c:1646  */
    {
		breakeablecitos += 1;
		strcpy(siguiente_breakable_pila[siguiente_count], (yyval.siguientes).label[0]);
		siguiente_count++;
	}
#line 2016 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 529 "semantic.y" /* yacc.c:1646  */
    {
		char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                

		//Ejecucion incondicional de la sentencia
		backpatch(&(yyvsp[-2].booleanos).trues, label, &codigo_intermedio);

        strcpy(label2, newIndex());         
        strcpy(temp, newTemp());
        (yyval.siguientes) = (yyvsp[-2].booleanos).falses;
        cuadrupla c1;
        c1.op = IFF;
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&(yyvsp[-2].booleanos).trues, label, &codigo_intermedio);
        backpatch(&(yyvsp[-2].booleanos).falses, label2, &codigo_intermedio);
        printf("S->do S while(B)\n");
		breakeablecitos -= 1;
		siguiente_count++;
	}
#line 2042 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 550 "semantic.y" /* yacc.c:1646  */
    { 
		breakeablecitos += 1; 
		strcpy(siguiente_breakable_pila[siguiente_count], (yyval.siguientes).label[0]);
		siguiente_count++;
	}
#line 2052 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 554 "semantic.y" /* yacc.c:1646  */
    {
		meter_assign((yyvsp[-7].siguientes).arr_codigo, (yyvsp[-7].siguientes).count_codigo);
        char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                
        strcpy(label2, newIndex());         
        strcpy(temp, newTemp());
        (yyval.siguientes) = (yyvsp[-5].booleanos).falses;
        cuadrupla c1;
        c1.op = IFF;
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        backpatch(&(yyvsp[-5].booleanos).trues, label, &codigo_intermedio);
        backpatch(&(yyvsp[-5].booleanos).falses, label2, &codigo_intermedio);
		meter_assign((yyvsp[-3].siguientes).arr_codigo, (yyvsp[-3].siguientes).count_codigo);
        printf("S->for(ass; cond; ass) sent\n");
		breakeablecitos -= 1;
		siguiente_count--;
    }
#line 2076 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 573 "semantic.y" /* yacc.c:1646  */
    { meter_assign((yyvsp[-1].siguientes).arr_codigo, (yyvsp[-1].siguientes).count_codigo); }
#line 2082 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 574 "semantic.y" /* yacc.c:1646  */
    {
			if((yyvsp[-1].expresion).type != current_function_type) {
				yyerror("Tipo de retorno distinto al tipo de la funcion \n");
				exit(1);
			}
			cuadrupla c1;
			c1.op = GOTO;
			char label1[32];
			strcpy(label1, newLabel());
			strcpy(c1.op1, "");
			strcpy(c1.op2, "");
			strcpy(c1.res, label1);
			insert_cuad(&codigo_intermedio, c1);
	
	}
#line 2102 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 589 "semantic.y" /* yacc.c:1646  */
    {
			if(4 != current_function_type) {
				yyerror("Tipo de retorno void distinto al tipo de la funcion \n");
				exit(1);
			}
	  }
#line 2113 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 595 "semantic.y" /* yacc.c:1646  */
    {
        char label[32];
        (yyval.siguientes) = (yyvsp[-1].siguientes);                
        strcpy(label, newLabel());                
        backpatch(&(yyvsp[-1].siguientes), label, &codigo_intermedio);                                
        printf("S->{SS}\n");
    }
#line 2125 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 602 "semantic.y" /* yacc.c:1646  */
    { if((yyvsp[-1].expresion).type != 0) {
								yyerror("La expresion del switch debe ser un numero entero\n");
								exit(1);
							 }
							breakeablecitos++;
							strcpy(siguiente_breakable_pila[siguiente_count], (yyval.siguientes).label[0]);
							siguiente_count++;
	
				     		strcpy(pila_switch[count_switch], (yyvsp[-1].expresion).dir); count_switch++; 
						}
#line 2140 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 611 "semantic.y" /* yacc.c:1646  */
    {
							count_switch--;
							breakeablecitos--;
							siguiente_count--;
						}
#line 2150 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 616 "semantic.y" /* yacc.c:1646  */
    { if(breakeablecitos < 1) {
							yyerror("El break debe estar dentro de un ciclo \n");
							exit(1);
			     		}
						cuadrupla c1;
						c1.op = GOTO;
						char label1[32];
						strcpy(label1, newLabel());//siguiente_breakable_pila[siguiente_count]);
						strcpy(c1.op1, "");
						strcpy(c1.op2, "");
						strcpy(c1.res, label1);
						insert_cuad(&codigo_intermedio, c1);

	}
#line 2169 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 630 "semantic.y" /* yacc.c:1646  */
    {
        char i[32];
        strcpy(i, newIndex());
        (yyval.siguientes) = create_list(i);
        printf("S->print(E);\n");
    }
#line 2180 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 639 "semantic.y" /* yacc.c:1646  */
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
#line 2198 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 655 "semantic.y" /* yacc.c:1646  */
    { (yyval.siguientesp).ifelse= false;}
#line 2204 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 657 "semantic.y" /* yacc.c:1646  */
    {        
            cuadrupla c1;
            c1.op = LABEL;
            strcpy(c1.op1, "");
            strcpy(c1.op2, "");
            strcpy(c1.res, pop_label(&lfalses));
            insert_cuad(&codigo_intermedio, c1);
        }
#line 2217 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 665 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.siguientesp).ifelse= true;
        (yyval.siguientesp).siguientes = (yyvsp[0].siguientes);
    }
#line 2226 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 672 "semantic.y" /* yacc.c:1646  */
    { 
        char i[32];
        char i2[32];
        char temp[32];
        strcpy(i, newIndex());
        strcpy(i2, newIndex());
        strcpy(temp, newTemp());
        strcpy(current_label, i2);

        (yyval.booleanos).trues = create_list(i);
        (yyval.booleanos).falses = create_list(i2);

        cuadrupla c, c1, c2;
        c.op = EQUALS;
		char tope_dir[32];
		strcpy(tope_dir, pila_switch[count_switch-1]);
        strcpy(c.op1, tope_dir);
        strcpy(c.op2, (yyvsp[0].num).val);
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
        printf("B-> case num: sent \n");

		//quiza esto es basura
        cuadrupla c3;
        c3.op = LABEL;
        strcpy(c3.op1, "");
        strcpy(c3.op2, "");
        strcpy(c3.res, i);
        insert_cuad(&codigo_intermedio, c3);
    }
#line 2271 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 711 "semantic.y" /* yacc.c:1646  */
    {
        cuadrupla c, c1;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, current_label);
        push_label(&lfalses, get_first(&(yyval.booleanos).falses));
        insert_cuad(&codigo_intermedio, c);

	 }
#line 2286 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 727 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.pi).id1, (yyvsp[0].id)); strcpy((yyval.pi).id2,""); (yyval.pi).type = -1;}
#line 2292 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 728 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.pi).id1, (yyvsp[0].vararr).representacion); (yyval.pi).type = (yyvsp[0].vararr).type;}
#line 2298 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 729 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.pi).id1, (yyvsp[-2].id)); strcpy((yyval.pi).id2, (yyvsp[0].id)); (yyval.pi).type = -1;}
#line 2304 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 733 "semantic.y" /* yacc.c:1646  */
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
										(yyval.vararr).tipo_basico = (yyval.vararr).type;
                                        if((yyval.vararr).type == -1) {
                                            yyerror("No seas pendejo. Mayor cantidad de dimensiones que las definidas");
                                            exit(1);
                                        }
										(yyval.vararr).tamanios[0] = it->tabla->tt->trs[(yyval.vararr).tipo_basico+1].tam;
										int mydims = 1;
										while((yyval.vararr).tipo_basico > 4){
											(yyval.vararr).tamanios[mydims] = it->tabla->tt->trs[(yyval.vararr).tipo_basico].tam;
											mydims++;
											(yyval.vararr).tipo_basico = it->tabla->tt->trs[(yyval.vararr).tipo_basico].base.renglon;	
										}
										if((yyvsp[-1].expresion).dir[0] != 't' && (yyval.vararr).tamanios[(yyval.vararr).indice_tamanios] <= atoi((yyvsp[-1].expresion).dir)) {
											yyerror("Index out of bounds exception\n");
											exit(1);
										}
										(yyval.vararr).indice_tamanios++;
										(yyval.vararr).dims = mydims - 1;
                                        break;
                                    }
									//printf("el pinche dir %s mydims: %d\n", $3.dir, mydims);
									/*
									for(int i = 0; i < mydims; i++){
										printf("tamani es %d, ", $$.tamanios[i]);
									}
									*/
                                    it = it->siguiente;
                                  }
                                  if(!encontrado) {
                                    yyerror("El arreglo no fue declarado antes.\n");
                                    exit(1);
                                  } 
                                  (yyval.vararr).tt = it->tabla->tt; }
#line 2358 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 782 "semantic.y" /* yacc.c:1646  */
    { 
	   							  (yyval.vararr).tipo_basico = (yyvsp[-3].vararr).tipo_basico;
								  (yyval.vararr).dims = (yyvsp[-3].vararr).dims - 1;
								  strcat((yyval.vararr).representacion, "[");
								  strcat((yyval.vararr).representacion, (yyvsp[-1].expresion).dir);
								  strcat((yyval.vararr).representacion, "]");
								  //$$.dims = $1.dims;
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
							      if((yyvsp[-1].expresion).dir[0] != 't' && (yyval.vararr).tamanios[(yyval.vararr).indice_tamanios] <= atoi((yyvsp[-1].expresion).dir)) {
								  	yyerror("Index out of bounds exceptionkk\n");
									exit(1);
							      }
								  (yyval.vararr).indice_tamanios++;

                                  (yyval.vararr).tt = (yyvsp[-3].vararr).tt;

       }
#line 2392 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 814 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = suma((yyvsp[-2].expresion), (yyvsp[0].expresion)); printf("E -> E + E\n"); }
#line 2398 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 815 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = resta((yyvsp[-2].expresion), (yyvsp[0].expresion)); printf("E -> E - E\n"); }
#line 2404 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 816 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = multiplicacion((yyvsp[-2].expresion), (yyvsp[0].expresion)); printf("E -> E * E\n"); }
#line 2410 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 817 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = division((yyvsp[-2].expresion), (yyvsp[0].expresion)); printf("E -> E / E\n"); }
#line 2416 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 818 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = modulo((yyvsp[-2].expresion), (yyvsp[0].expresion)); printf("E -> E mod E\n"); }
#line 2422 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 819 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = envolver_varr((yyvsp[0].vararr)); (yyval.expresion).tipo_basico = (yyvsp[0].vararr).tipo_basico; (yyval.expresion).dims = (yyvsp[0].vararr).dims; printf("E -> id[E]\n"); }
#line 2428 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 820 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = identificador((yyvsp[0].id)); printf("E->id\n"); printf("%s\n",(yyvsp[0].id)); }
#line 2434 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 821 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = envolver_cadena((yyvsp[0].cad)); printf("E -> CADENA\n"); }
#line 2440 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 822 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = get_numero((yyvsp[0].num)); printf("E->numero\n"); printf("%s\n",(yyvsp[0].num).val); }
#line 2446 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 823 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = envolver_caracter((yyvsp[0].car)); printf("E -> CARACTER\n"); }
#line 2452 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 824 "semantic.y" /* yacc.c:1646  */
    {
   		verifica_call((yyvsp[-3].id), (yyvsp[-1].parrams).lista_tipos, (yyvsp[-1].parrams).count);	
		char temp[32];
		strcpy(temp, newTemp());
		cuadrupla c;
		c.op = CALL;
		strcpy(c.op1, (yyvsp[-3].id));
		sprintf(c.op2, "%d", (yyvsp[-1].parrams).count);
		strcpy(c.res, temp);
		insert_cuad(&codigo_intermedio, c);                    
		strcpy((yyval.expresion).dir, temp);
   }
#line 2469 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 839 "semantic.y" /* yacc.c:1646  */
    {
	  		(yyval.parrams).p = (yyvsp[0].parrams).p;
			int i;
			for (i = 0; i < (yyvsp[0].parrams).count; i++) {
				(yyval.parrams).lista_tipos[i][0] = (yyvsp[0].parrams).lista_tipos[i][0];
				(yyval.parrams).lista_tipos[i][1] = (yyvsp[0].parrams).lista_tipos[i][1];
			}
			(yyval.parrams).count = (yyvsp[0].parrams).count;
	  }
#line 2483 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 848 "semantic.y" /* yacc.c:1646  */
    { (yyval.parrams).p = 0; (yyval.parrams).count = 0; }
#line 2489 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 852 "semantic.y" /* yacc.c:1646  */
    {
				cuadrupla c;
				c.op = PARAM;
				strcpy(c.op1, "");
				strcpy(c.op2, "");
				strcpy(c.res, (yyvsp[0].expresion).dir);
				insert_cuad(&codigo_intermedio, c);                    
				(yyval.parrams).p = (yyvsp[-2].parrams).p + 1;
				(yyval.parrams).lista_tipos[(yyvsp[-2].parrams).count][0] = (yyvsp[0].expresion).tipo_basico;
				(yyval.parrams).lista_tipos[(yyvsp[-2].parrams).count][1] = (yyvsp[0].expresion).dims;
				(yyval.parrams).count = (yyvsp[-2].parrams).count + 1;
		   }
#line 2506 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 864 "semantic.y" /* yacc.c:1646  */
    {
				cuadrupla c;
				c.op = PARAM;
				strcpy(c.op1, "");
				strcpy(c.op2, "");
				strcpy(c.res, (yyvsp[0].expresion).dir);
				insert_cuad(&codigo_intermedio, c);                    
				(yyval.parrams).p = 1;
				(yyval.parrams).lista_tipos[0][0] = (yyvsp[0].expresion).tipo_basico;
				(yyval.parrams).lista_tipos[0][1] = (yyvsp[0].expresion).dims;
				(yyval.parrams).count = 1;
		   }
#line 2523 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 879 "semantic.y" /* yacc.c:1646  */
    {
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[-1].booleanos).falses));
        insert_cuad(&codigo_intermedio, c);                    
    }
#line 2536 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 886 "semantic.y" /* yacc.c:1646  */
    { 
        char label[32];
        strcpy(label, newLabel());
        backpatch(&(yyvsp[-3].booleanos).falses, label, &codigo_intermedio);
        (yyval.booleanos).trues = merge(&(yyvsp[-3].booleanos).trues, &(yyvsp[0].booleanos).trues);
        (yyval.booleanos).falses = (yyvsp[0].booleanos).falses;
        printf("B -> B || B\n");
    }
#line 2549 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 894 "semantic.y" /* yacc.c:1646  */
    {
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[-1].booleanos).trues));
        insert_cuad(&codigo_intermedio, c);                    
    }
#line 2562 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 901 "semantic.y" /* yacc.c:1646  */
    {
        char label[32];
        strcpy(label, newLabel());                        
        (yyval.booleanos).falses = merge(&(yyvsp[-3].booleanos).falses, &(yyvsp[0].booleanos).falses);
        (yyval.booleanos).trues = (yyvsp[0].booleanos).trues;
        backpatch(&(yyvsp[-3].booleanos).trues, label, &codigo_intermedio);
        printf("B -> B && B\n");
    }
#line 2575 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 909 "semantic.y" /* yacc.c:1646  */
    {
        (yyval.booleanos).falses = (yyvsp[0].booleanos).trues;
        (yyval.booleanos).trues = (yyvsp[0].booleanos).falses;
        printf("B -> !B\n");
    }
#line 2585 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 914 "semantic.y" /* yacc.c:1646  */
    {
        (yyval.booleanos).trues = (yyvsp[-1].booleanos).trues;
        (yyval.booleanos).falses = (yyvsp[-1].booleanos).falses;
        //strcpy($$.dir, $2.dir);
        printf("B->(B)\n");
    }
#line 2596 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 920 "semantic.y" /* yacc.c:1646  */
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
#line 2633 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 952 "semantic.y" /* yacc.c:1646  */
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
#line 2650 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 964 "semantic.y" /* yacc.c:1646  */
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
#line 2667 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 979 "semantic.y" /* yacc.c:1646  */
    { (yyval.rel) = LESS_THAN; printf("R-> <\n"); }
#line 2673 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 980 "semantic.y" /* yacc.c:1646  */
    { (yyval.rel) = GREATER_THAN; printf("R-> >\n"); }
#line 2679 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 981 "semantic.y" /* yacc.c:1646  */
    { (yyval.rel) = LESS_OR_EQUAL_THAN; printf("R-> <=\n"); }
#line 2685 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 982 "semantic.y" /* yacc.c:1646  */
    { (yyval.rel) = GREATER_OR_EQUAL_THAN; printf("R-> >=\n"); }
#line 2691 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 983 "semantic.y" /* yacc.c:1646  */
    { (yyval.rel) = NOT_EQUALS; printf("R-> !=\n"); }
#line 2697 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 984 "semantic.y" /* yacc.c:1646  */
    { (yyval.rel) = EQUALS; printf("R-> ==\n"); }
#line 2703 "semantic.tab.c" /* yacc.c:1646  */
    break;


#line 2707 "semantic.tab.c" /* yacc.c:1646  */
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
#line 987 "semantic.y" /* yacc.c:1906  */


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
	e.tipo_basico = e.type;
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
	e.tipo_basico = e.type;
    
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
	e.tipo_basico = e.type;
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
	e.tipo_basico = e.type;
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
	e.tipo_basico = e.type;
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

void verifica_call(char id[], int params[][2], int params_count) {
	int renglon = search(masterchef->st, id);
	if (renglon == -1) {
		yyerror("La funcion que quieres llamra no ha sido declarado\n");
		exit(1);
	}
	if (masterchef->st->symbols[renglon].num_args != params_count) {
		char error[1000];
		strcpy(error, "El número de argumentos con la que fue llamada la función es incorrecto: ");
		yyerror2(error, id);
		exit(1);
	}
	for (int j = 0; j < params_count; j++) {
		if (masterchef->st->symbols[renglon].args[j][0] != params[j][0] || masterchef->st->symbols[renglon].args[j][1] != params[j][1]) {
			char error[1000];
			strcpy(error, "Los tipos de los argumentos que ingresaste no son correcto con la funcion: ");
			yyerror2(error, id);
			exit(1);
		} 
	}
	
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
			e1.type = e.type;
			strcpy(e1.dir, id);
			cuadrupla c;
			c.op = ASSIGNATION;
			printf("%s %d %d\n", e.dir, tipo, e.type);
			strcpy(c.op1, reducir(e.dir, tipo, e.type));
			printf("o\n");
			strcpy(c.op2, "");
			if(es_estruct == 1) {
				char id_con_punto[65];
				strcpy(id_con_punto, id);
				strcat(id_con_punto, ".");
				strcat(id_con_punto, id2);
				strcpy(c.res, id_con_punto);
			} else {
				printf("llega\n");
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
	e.tipo_basico = e.type;
    strcpy(e.dir, n.val);
    return e;
}

exp envolver_cadena(cadena cadenita) {
    exp e;
    e.type = cadenita.type;
	e.tipo_basico = e.type;
    strcpy(e.dir, cadenita.val);
    return e;
}

exp envolver_caracter(caracter caractercito) {
    exp e;
    e.type = caractercito.type;
	e.tipo_basico = e.type;
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
		e.tipo_basico = e.type;
		int mydims = 0;
		while(e.tipo_basico > 4){
			e.tipo_basico = stack_masterchefs->tabla->tt->trs[e.tipo_basico].base.renglon;	
			mydims++;
		}
		e.dims = mydims;
        strcpy(e.dir, id);
    }else{
    	if(search(masterchef->st, id) !=-1){
         	e.type = get_type(masterchef->st, id);
			e.tipo_basico = e.type;
			int mydims = 0;
			while(e.tipo_basico > 4){
				mydims++;
				e.tipo_basico = masterchef->tt->trs[e.tipo_basico].base.renglon;	
			}
			e.dims = mydims;
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
	printf("Asignacion inconsistente krnal\n");
	exit(1);
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
