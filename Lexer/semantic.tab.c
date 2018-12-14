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
#line 12 "semantic.y" /* yacc.c:339  */

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

    /*Archivo para gaurdar los errores*/
    FILE * errores_sintacticos;

    /*Variable auxilir para detectar si el programa tuvo errores*/
    int hay_error = 0;

    /* Funciones para escribir errores */
    void yyerror(char *);
    void yyerror2(char*, char*);

    /* Última función que se ejecutara. */
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

    /* Variables para contar las temporales, etiquetas e indices */
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
    void verificar_main();

#line 166 "semantic.tab.c" /* yacc.c:339  */

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
#line 113 "semantic.y" /* yacc.c:355  */

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

#line 294 "semantic.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SEMANTIC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 311 "semantic.tab.c" /* yacc.c:358  */

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
       0,   223,   223,   223,   243,   243,   254,   262,   263,   264,
     265,   266,   267,   267,   301,   313,   332,   333,   334,   340,
     341,   342,   348,   371,   378,   390,   414,   426,   378,   448,
     454,   462,   468,   496,   525,   526,   532,   532,   549,   572,
     582,   572,   610,   610,   635,   635,   661,   661,   685,   689,
     706,   720,   729,   729,   744,   760,   771,   789,   790,   790,
     809,   847,   809,   858,   859,   868,   869,   870,   876,   935,
     980,   984,   987,   991,   995,   999,  1005,  1009,  1014,  1018,
    1023,  1045,  1057,  1067,  1081,  1101,  1101,  1119,  1119,  1137,
    1143,  1149,  1187,  1201,  1222,  1226,  1230,  1234,  1238,  1242
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
#line 223 "semantic.y" /* yacc.c:1646  */
    { init(); 
      errores_sintacticos = fopen("errores.txt", "w");
    }
#line 1530 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 228 "semantic.y" /* yacc.c:1646  */
    {
        fclose(errores_sintacticos);
        if(hay_error) {
            printf("El programa tiene errores sintacticos\n");
        } else {
            finish();
        }
    }
#line 1543 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 243 "semantic.y" /* yacc.c:1646  */
    { 
         current_type = (yyvsp[0].tipo).type;
        if((yyvsp[0].tipo).type == 4) {
            yyerror("No puedes declarar variables tipo void\n");
            
        }
        current_dim = (yyvsp[0].tipo).bytes;
        current_dim_arr = current_dim; 
        current_arr_type = current_type;
     }
#line 1558 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 253 "semantic.y" /* yacc.c:1646  */
    {(yyval.cant).cantidad = (yyvsp[-2].cant).cantidad; (yyval.cant).cantidad += (yyvsp[0].cant).cantidad; }
#line 1564 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 254 "semantic.y" /* yacc.c:1646  */
    { (yyval.cant).cantidad = 0; }
#line 1570 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 262 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 0; (yyval.tipo).bytes = 4; }
#line 1576 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 263 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 1; (yyval.tipo).bytes = 4; }
#line 1582 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 264 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 2; (yyval.tipo).bytes = 8; }
#line 1588 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 265 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 3; (yyval.tipo).bytes = 1; }
#line 1594 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 266 "semantic.y" /* yacc.c:1646  */
    { (yyval.tipo).type = 4; (yyval.tipo).bytes = 1; }
#line 1600 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 267 "semantic.y" /* yacc.c:1646  */
    {
        /* Creamos una nueva mastertab donde guardaremos las declaraciones dentro del struct. Además
        agregamos este nuevo mastertab del struct al tope de la pila de mastertabs. */
        struct mastertab* ntab = (struct mastertab *) malloc(sizeof(struct mastertab));
        ntab->tt = (typetab *) malloc(sizeof(typetab));
        ntab->st= (symtab *) malloc(sizeof(symtab));
        create_table(ntab->st);
        create_type_table(ntab->tt);
        stack_masterchefs = mete(stack_masterchefs, ntab);
    }
#line 1615 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 277 "semantic.y" /* yacc.c:1646  */
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
        renglon.tam = (yyvsp[-1].cant).cantidad;
        renglon.base.renglon = -2;
        renglon.base.smt = sacada;
        insert_type_table(stack_masterchefs->tabla->tt, renglon);

        (yyval.tipo).type = stack_masterchefs->tabla->tt->count-1; (yyval.tipo).bytes = (yyvsp[-1].cant).cantidad; 
    }
#line 1638 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 301 "semantic.y" /* yacc.c:1646  */
    {
        /* Agregamos a la tabla de simbolos que esté en el tope de mastertabs. */
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
#line 1655 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 313 "semantic.y" /* yacc.c:1646  */
    {
        /* Agregamos a la tabla de simbolos que esté en el tope de mastertabs. */
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
#line 1672 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 332 "semantic.y" /* yacc.c:1646  */
    { (yyval.num).type = (yyvsp[0].num).type; strcpy((yyval.num).val, (yyvsp[-1].char_signo)); strcat((yyval.num).val, (yyvsp[0].num).val); }
#line 1678 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 333 "semantic.y" /* yacc.c:1646  */
    { (yyval.num).type = (yyvsp[0].num).type; strcpy((yyval.num).val, (yyvsp[-1].char_signo)); strcat((yyval.num).val, (yyvsp[0].num).val); }
#line 1684 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 334 "semantic.y" /* yacc.c:1646  */
    { (yyval.num).type = (yyvsp[0].num).type; strcpy((yyval.num).val, (yyvsp[-1].char_signo)); strcat((yyval.num).val, (yyvsp[0].num).val); }
#line 1690 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 340 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.char_signo),""); }
#line 1696 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 341 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.char_signo), "-"); }
#line 1702 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 342 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.char_signo),""); }
#line 1708 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 348 "semantic.y" /* yacc.c:1646  */
    {
        /* Obtenemos el las dimenciones del arreglo hijo y le agregamos el de la actual
            dimensión. */
        if ((yyvsp[-2].num).type != 0) {
            yyerror("El número para declarar en el arreglo debe ser entero.");
            
        }
        if ((yyvsp[-2].num).val[0] == '-') {
            yyerror("Error: No se puede declarar dimensión negativa.");
            
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
#line 1736 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 371 "semantic.y" /* yacc.c:1646  */
    { (yyval.arr).tam = 0; }
#line 1742 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 378 "semantic.y" /* yacc.c:1646  */
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
        current_function_type = (yyvsp[-1].tipo).type;
     }
#line 1759 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 390 "semantic.y" /* yacc.c:1646  */
    {
        /* Agregamos una etiqueta que nos diga donde está el código de la función. */
        cuadrupla c;
        c.op = LABEL;
        char lab[32];
        strcpy(lab, newLabel());
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, (yyvsp[-4].id));
        insert_cuad(&codigo_intermedio, c);

        /* Agregamos la función a la tabla de simbolos global junto con los tipos de los argumentos. */
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
#line 1788 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 414 "semantic.y" /* yacc.c:1646  */
    {
        /* Aquí se hace backpatch para que se actualicen las etiquetas. */
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
#line 1805 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 426 "semantic.y" /* yacc.c:1646  */
    {
        struct mastertab* sacada;
        sacada = tope(stack_masterchefs); 
        stack_masterchefs = saca(stack_masterchefs);

        /* Agregamos la referencia del masterchef de la función */
        typerow renglon;
        renglon.type = 7;
        renglon.tam = (yyvsp[-3].cant).cantidad;
        renglon.base.renglon = -2;
        renglon.base.smt = sacada;
        insert_type_table(stack_masterchefs->tabla->tt, renglon);

        cuadrupla c;
        char label2[32];
        strcpy(label2, newLabel());
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, label2);
        //insert_cuad(&codigo_intermedio, c);                
     }
#line 1832 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 454 "semantic.y" /* yacc.c:1646  */
    {
        (yyval.argu).num = (yyvsp[0].argu).num; 
        /* Copiamos los argumentos en que tiene el hijo lista_args. */
		for(int i = 0; i < (yyvsp[0].argu).num; i++){
			(yyval.argu).lista_args[i][0] = (yyvsp[0].argu).lista_args[i][0];
			(yyval.argu).lista_args[i][1] = (yyvsp[0].argu).lista_args[i][1];
		}
    }
#line 1845 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 462 "semantic.y" /* yacc.c:1646  */
    { (yyval.argu).num = 0; }
#line 1851 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 468 "semantic.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].tipo).type == 4) {
			yyerror("Los argumentos no pueden ser tipo void\n");
			
		}
        /* Agregamos a la tabla de simbolos y tipos el argumento de la función */
		typerow renglon;
		renglon.type = (yyvsp[-2].tipo).type;
		renglon.tam = (yyvsp[-2].tipo).type;
		renglon.base.renglon = (yyvsp[-2].tipo).type;
		insert_type_table(stack_masterchefs->tabla->tt, renglon);
			
		sym s;
		strcpy(s.id, (yyvsp[-1].id));
		s.type = (yyvsp[-2].tipo).type;
		s.dir = dir;
		dir+= renglon.tam;
		insert(stack_masterchefs->tabla->st, s);
        
        /* Aumentamos el número de argumentos que llevamos guardados. */
		(yyval.argu).num = 1 + (yyvsp[-4].argu).num;
		for(int i = 0; i < (yyvsp[-4].argu).num; i++){
			(yyval.argu).lista_args[i][0] = (yyvsp[-4].argu).lista_args[i][0];
			(yyval.argu).lista_args[i][1] = (yyvsp[-4].argu).lista_args[i][1];
		}
		(yyval.argu).lista_args[(yyval.argu).num-1][0] = (yyvsp[-2].tipo).type;
		(yyval.argu).lista_args[(yyval.argu).num-1][1] = (yyvsp[0].dims);
	}
#line 1884 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 496 "semantic.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].tipo).type == 4) {
			yyerror("Los argumentos no pueden ser tipo void\n");
			
		}
        /* Ponemos los casos base de la lista de argumentos y del número de argumentos */
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
		s.type = (yyvsp[-2].tipo).type;
		s.dir = dir;
		dir+= renglon.tam;
		insert(stack_masterchefs->tabla->st, s);

	}
#line 1913 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 525 "semantic.y" /* yacc.c:1646  */
    { (yyval.dims) = (yyvsp[0].dims) + 1; }
#line 1919 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 526 "semantic.y" /* yacc.c:1646  */
    { (yyval.dims) = 0; }
#line 1925 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 532 "semantic.y" /* yacc.c:1646  */
    {
        /* Creamos una etiqueta */
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[0].siguientes)));
        insert_cuad(&codigo_intermedio, c);                                
    }
#line 1939 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 541 "semantic.y" /* yacc.c:1646  */
    {
        /* Hacemos Backbatch */
        char label[32];
        strcpy(label, newLabel());                                
        (yyval.siguientes) = (yyvsp[0].siguientes);                
        backpatch(&(yyvsp[-2].siguientes), label, &codigo_intermedio);                
        //printf("ss->ss s\n");
    }
#line 1952 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 549 "semantic.y" /* yacc.c:1646  */
    {
        /* Hacemos Backbatch */
        char label[32];
        strcpy(label, newLabel());
        (yyval.siguientes) = (yyvsp[0].siguientes);
        backpatch(&(yyvsp[0].siguientes), label, &codigo_intermedio);
        //printf("ss->s\n");
    }
#line 1965 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 572 "semantic.y" /* yacc.c:1646  */
    {
        /* Obtenemos la etiqueta que está en el tope de trues de la condición y la agregamos
           a nuestro código */
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[-1].booleanos).trues));
        insert_cuad(&codigo_intermedio, c);
    }
#line 1980 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 582 "semantic.y" /* yacc.c:1646  */
    {
        /* Agregamos a los falses globales la primer etiqueta que tenemos en la condición.
           Además agregamos a nuestro código el goto que tenemos en el tope de sent */
        cuadrupla c, c1;
        c.op = GOTO;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[0].siguientes)));
        push_label(&lfalses, get_first(&(yyvsp[-3].booleanos).falses));
        insert_cuad(&codigo_intermedio, c);
    }
#line 1996 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 592 "semantic.y" /* yacc.c:1646  */
    {
        /* Verificamos si tenemos un else en sentp y hacemos backpatch en ambos casos */
        char label[32];
        strcpy(label, newLabel());
        
        if((yyvsp[0].siguientesp).ifelse==false){
            (yyval.siguientes) = merge(&(yyvsp[-5].booleanos).falses, &(yyvsp[0].siguientesp).siguientes);
            backpatch(&(yyvsp[-5].booleanos).falses, label, &codigo_intermedio);                                
            printf("s->if(b) s\n");
        }else{
            char label2[32];                                    
            strcpy(label2, newLabel());                
            (yyval.siguientes) = merge(&(yyvsp[-2].siguientes),&(yyvsp[0].siguientesp).siguientes);
            backpatch(&(yyvsp[-5].booleanos).trues, label, &codigo_intermedio);
            backpatch(&(yyvsp[-5].booleanos).falses, label2, &codigo_intermedio);                 
            printf("s->if(b)s else s\n");
        }
    }
#line 2019 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 610 "semantic.y" /* yacc.c:1646  */
    {
        /* Creamos nuevas etiquetas que las agregaremos a los trues y falses de cond.  */
        breakeablecitos += 1;
        strcpy(siguiente_breakable_pila[siguiente_count], (yyval.siguientes).label[0]);
        siguiente_count++;
    }
#line 2030 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 615 "semantic.y" /* yacc.c:1646  */
    {
        char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                
        strcpy(label2, newIndex());         
        strcpy(temp, newTemp());
        (yyval.siguientes) = (yyvsp[-3].booleanos).falses;
        cuadrupla c1;
        c1.op = IFF;
        /* Agregamos un goto para que evalue la condición otra vez */
        strcpy(c1.op2, "GOTO");
        strcpy(c1.res, label);                
        insert_cuad(&codigo_intermedio, c1);
        /* Hacemos backpatch */
        backpatch(&(yyvsp[-3].booleanos).trues, label, &codigo_intermedio);
        backpatch(&(yyvsp[-3].booleanos).falses, label2, &codigo_intermedio);
        printf("S->while(B)S\n");
        breakeablecitos -= 1; 
        strcpy(siguiente_breakable_pila[siguiente_count], (yyval.siguientes).label[0]);
        siguiente_count--;
    }
#line 2055 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 635 "semantic.y" /* yacc.c:1646  */
    {
        /* Muy parecido al while */
        breakeablecitos += 1;
        strcpy(siguiente_breakable_pila[siguiente_count], (yyval.siguientes).label[0]);
        siguiente_count++;
    }
#line 2066 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 640 "semantic.y" /* yacc.c:1646  */
    {
        char label[32], label2[32], temp[32];
        strcpy(label, newIndex());                

        /* Ejecución incondicional de la sentencia */
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
        printf("s->do s while(b)\n");
        breakeablecitos -= 1;
        siguiente_count++;
    }
#line 2092 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 661 "semantic.y" /* yacc.c:1646  */
    { 
        /* Muy parecido al while */
        breakeablecitos += 1; 
        strcpy(siguiente_breakable_pila[siguiente_count], (yyval.siguientes).label[0]);
        siguiente_count++;
    }
#line 2103 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 666 "semantic.y" /* yacc.c:1646  */
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
        //printf("s->for(ass; cond; ass) sent\n");
        breakeablecitos -= 1;
        siguiente_count--;
    }
#line 2127 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 685 "semantic.y" /* yacc.c:1646  */
    {
        /* meter_assign ya hace todo el trabajo */
        meter_assign((yyvsp[-1].siguientes).arr_codigo, (yyvsp[-1].siguientes).count_codigo);
    }
#line 2136 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 689 "semantic.y" /* yacc.c:1646  */
    {
        /* Verificamos el tipo de retorno con el de la función */
        if((yyvsp[-1].expresion).type != current_function_type) {
            yyerror("tipo de retorno distinto al tipo de la funcion \n");
            
        }
        /* Agregamos el goto adecuado */
        cuadrupla c1;
        c1.op = GOTO;
        char label1[32];
        strcpy(label1, newLabel());
        strcpy(c1.op1, "");
        strcpy(c1.op2, "");
        strcpy(c1.res, label1);
        insert_cuad(&codigo_intermedio, c1);
    
    }
#line 2158 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 706 "semantic.y" /* yacc.c:1646  */
    {
        /* Verificamos que el tipo de la función sea void */
        if(4 != current_function_type) {
            yyerror("tipo de retorno void distinto al tipo de la funcion \n");
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
#line 2177 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 720 "semantic.y" /* yacc.c:1646  */
    {
        /* Aquí es donde se hace la concatenación de sentencias */
        char label[32];
        (yyval.siguientes) = (yyvsp[-1].siguientes);                
        strcpy(label, newLabel());                
        /* Se hace backpatch */
        backpatch(&(yyvsp[-1].siguientes), label, &codigo_intermedio);                                
        //printf("s->{ss}\n");
    }
#line 2191 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 729 "semantic.y" /* yacc.c:1646  */
    {
		if((yyvsp[-1].expresion).type != 0) {
			yyerror("La expresion del switch debe ser un numero entero\n");
			
		}
		breakeablecitos++;
		strcpy(siguiente_breakable_pila[siguiente_count], (yyval.siguientes).label[0]);
		siguiente_count++;
    
		strcpy(pila_switch[count_switch], (yyvsp[-1].expresion).dir); count_switch++; 
	}
#line 2207 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 739 "semantic.y" /* yacc.c:1646  */
    {
		count_switch--;
		breakeablecitos--;
		siguiente_count--;
	}
#line 2217 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 744 "semantic.y" /* yacc.c:1646  */
    {
        /* Verificamos que el break sea dentro de un break */
		if(breakeablecitos < 1) {
			yyerror("El break debe estar dentro de un ciclo \n");
			
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
#line 2238 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 760 "semantic.y" /* yacc.c:1646  */
    {
        char i[32];
        strcpy(i, newIndex());
        (yyval.siguientes) = create_list(i);
        //printf("s->print(e);\n");
    }
#line 2249 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 771 "semantic.y" /* yacc.c:1646  */
    {
		char i[32];
		strcpy(i, newIndex());
		(yyval.siguientes) = create_list(i);
		/* asignacion es lo que hace todo el trabajo */
		exp e = asignacion((yyvsp[-2].pi).id1, (yyvsp[-2].pi).id2, (yyvsp[0].expresion), (yyvsp[-2].pi).type); 
		//printf("S->parte_izq = E;\n");
		int iterador;
		(yyval.siguientes).count_codigo = e.count_codigo;
		for(iterador = 0; iterador < e.count_codigo; iterador++) {
			(yyval.siguientes).arr_codigo[iterador] = e.arr_codigo[iterador];
		}
    }
#line 2267 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 789 "semantic.y" /* yacc.c:1646  */
    { /* Decimos que no tenemos un else */ (yyval.siguientesp).ifelse= false;}
#line 2273 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 790 "semantic.y" /* yacc.c:1646  */
    {        
        /* Agregamos la etiqueta que tenemos en los falses al código*/
        cuadrupla c1;
        c1.op = LABEL;
        strcpy(c1.op1, "");
        strcpy(c1.op2, "");
        strcpy(c1.res, pop_label(&lfalses));
        insert_cuad(&codigo_intermedio, c1);
    }
#line 2287 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 799 "semantic.y" /* yacc.c:1646  */
    {
        /* Decimos que tenemos un else */
        (yyval.siguientesp).ifelse= true;
        (yyval.siguientesp).siguientes = (yyvsp[0].siguientes);
    }
#line 2297 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 809 "semantic.y" /* yacc.c:1646  */
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
        //printf("B-> case num: sent \n");

        cuadrupla c3;
        c3.op = LABEL;
        strcpy(c3.op1, "");
        strcpy(c3.op2, "");
        strcpy(c3.res, i);
        insert_cuad(&codigo_intermedio, c3);
    }
#line 2341 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 847 "semantic.y" /* yacc.c:1646  */
    {
        cuadrupla c, c1;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, current_label);
        push_label(&lfalses, get_first(&(yyval.booleanos).falses));
        insert_cuad(&codigo_intermedio, c);

     }
#line 2356 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 857 "semantic.y" /* yacc.c:1646  */
    {}
#line 2362 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 858 "semantic.y" /* yacc.c:1646  */
    {}
#line 2368 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 859 "semantic.y" /* yacc.c:1646  */
    {}
#line 2374 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 868 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.pi).id1, (yyvsp[0].id)); strcpy((yyval.pi).id2,""); (yyval.pi).type = -1; }
#line 2380 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 869 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.pi).id1, (yyvsp[0].vararr).representacion); (yyval.pi).type = (yyvsp[0].vararr).type; }
#line 2386 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 870 "semantic.y" /* yacc.c:1646  */
    { strcpy((yyval.pi).id1, (yyvsp[-2].id)); strcpy((yyval.pi).id2, (yyvsp[0].id)); (yyval.pi).type = -1; }
#line 2392 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 876 "semantic.y" /* yacc.c:1646  */
    {
        // Verificando que se indexe el arreglo con una expresión de tipo entera.
	    if((yyvsp[-1].expresion).type != 0) { 
			yyerror("Debes indexar el arreglo con un entero.\n"); 
		}
		if((yyvsp[-1].expresion).dir[0] != 't' && (yyvsp[-1].expresion).dir[0] == '-') {
			yyerror("No puedes indexar el arreglo con un arreglo con un número negativo");
		}
		// Formando la cadena que representa a la variable de arreglo indexada.
		strcpy((yyval.vararr).representacion, (yyvsp[-3].id));
		strcat((yyval.vararr).representacion, "[");
		strcat((yyval.vararr).representacion, (yyvsp[-1].expresion).dir);
		strcat((yyval.vararr).representacion, "]");
        // Creando un nuevo nodo para iterar la pila de tablas maestras.
		struct nodo* it = stack_masterchefs;
        // Recorremos la pila para buscar el identificador en ella.
		int encontrado = 0;
			
		while(it != NULL) {
			// Estamos buscando con el identificador en la tabla de símbolos a la que apunta el iterador.
			int x = search(it->tabla->st, (yyvsp[-3].id)); 
			if(x != -1) {
				// Si ya la encontramos, podemos consultar el tipo en dicho renglón encontrado.
				encontrado = 1;
				int type_row = it->tabla->st->symbols[x].type;
				(yyval.vararr).type = it->tabla->tt->trs[type_row].base.renglon;
				(yyval.vararr).tipo_basico = (yyval.vararr).type;
				// En el ciclo seguiremos subiendo a partir de los tipos hasta llegar al de la base.
				// Sin embargo, si en algún punto llegaos a ver un -1 es porque estamos indexando a un arreglo
				// que fue declarado con un número menor de dimensiones y reportamos el error. 
				if((yyval.vararr).type == -1) {
					yyerror("Mayor cantidad de dimensiones que las definidas");
					
				}
				(yyval.vararr).tamanios[0] = it->tabla->tt->trs[(yyval.vararr).tipo_basico+1].tam;
				int mydims = 1;
				while((yyval.vararr).tipo_basico > 4){
					(yyval.vararr).tamanios[mydims] = it->tabla->tt->trs[(yyval.vararr).tipo_basico].tam;
					mydims++;
					(yyval.vararr).tipo_basico = it->tabla->tt->trs[(yyval.vararr).tipo_basico].base.renglon;    
				}
				if((yyvsp[-1].expresion).dir[0] != 't' && (yyval.vararr).tamanios[(yyval.vararr).indice_tamanios] <= atoi((yyvsp[-1].expresion).dir)) {
					//yyerror("Index out of bounds exception\n");
					
				}
				(yyval.vararr).indice_tamanios++;
				(yyval.vararr).dims = mydims - 1;
				break;
			}
			it = it->siguiente;
		}
        // Si saliendo del ciclo ocurre que el identificador jamás fue encontrado, entonces
        // no había sido declarado antes y reportamos el error.
		if(!encontrado) {
			yyerror("El arreglo no fue declarado antes.\n");
			
		} 
        // Especificando que la tabla de tipos del lado izquierdo es la tabla a la que apunta el iterador. 
		(yyval.vararr).tt = it->tabla->tt; }
#line 2456 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 935 "semantic.y" /* yacc.c:1646  */
    { 
		// Regla de producción recursiva para seguir metiendo indexaciones.
		// Armando la representación de la indexación.
		(yyval.vararr).tipo_basico = (yyvsp[-3].vararr).tipo_basico;
		(yyval.vararr).dims = (yyvsp[-3].vararr).dims - 1;
		strcat((yyval.vararr).representacion, "[");
		strcat((yyval.vararr).representacion, (yyvsp[-1].expresion).dir);
		strcat((yyval.vararr).representacion, "]");
		// Checando que se indexe con una expresión de tipo entera.
		if((yyvsp[-1].expresion).type != 0) { 
			yyerror("Debes indexar el arreglo con un entero.\n"); 
		}
		if((yyvsp[-1].expresion).dir[0] != 't' && (yyvsp[-1].expresion).dir[0] == '-') {
            yyerror("No puedes indexar el arreglo con un arreglo con un número negativo");
            
        }
        // Comprobando si se indexó con más dimensiones de aquellas con que fue definido.
		if((yyvsp[-3].vararr).type == -1) {
			yyerror("Mayor cantidad de dimensiones que las definidas");
			
		}  
        // Checando el tipo del rengón del varr_arr del cuerpo de la producción.
		int row_hijo = (yyvsp[-3].vararr).type;
		(yyval.vararr).type = (*(yyvsp[-3].vararr).tt).trs[row_hijo].base.renglon;
        // Comprobando si se indexó con más dimensiones de aquellas con que fue definido.
		if((yyval.vararr).type == -1) {
			yyerror("Mayor cantidad de dimensiones que las definidas");
			
		}  
		if((yyvsp[-1].expresion).dir[0] != 't' && (yyval.vararr).tamanios[(yyval.vararr).indice_tamanios] <= atoi((yyvsp[-1].expresion).dir)) {
			yyerror("Index out of bounds exception\n");
			
		}
		(yyval.vararr).indice_tamanios++;

        // La tabla de tipos de la cabecera es la del varr_arr del cuerpo.
		(yyval.vararr).tt = (yyvsp[-3].vararr).tt;

	}
#line 2500 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 980 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.expresion) = suma((yyvsp[-2].expresion), (yyvsp[0].expresion)); 
        //printf("E -> E + E\n"); 
    }
#line 2509 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 984 "semantic.y" /* yacc.c:1646  */
    { (yyval.expresion) = resta((yyvsp[-2].expresion), (yyvsp[0].expresion)); 
        //printf("E -> E - E\n");
    }
#line 2517 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 987 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.expresion) = multiplicacion((yyvsp[-2].expresion), (yyvsp[0].expresion)); 
        //printf("E -> E * E\n");
    }
#line 2526 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 991 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.expresion) = division((yyvsp[-2].expresion), (yyvsp[0].expresion)); 
        //printf("E -> E / E\n");
    }
#line 2535 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 995 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.expresion) = modulo((yyvsp[-2].expresion), (yyvsp[0].expresion)); 
        //printf("E -> E mod E\n");
    }
#line 2544 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 999 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.expresion) = envolver_varr((yyvsp[0].vararr)); 
		(yyval.expresion).tipo_basico = (yyvsp[0].vararr).tipo_basico;
		(yyval.expresion).dims = (yyvsp[0].vararr).dims;
        //printf("E -> id[E]\n"); 
    }
#line 2555 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1005 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.expresion) = identificador((yyvsp[0].id)); 
        //printf("E->id\n");
    }
#line 2564 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1009 "semantic.y" /* yacc.c:1646  */
    { 
        // Pasando la cadena de la expresión regular a un tipo expresión.
        (yyval.expresion) = envolver_cadena((yyvsp[0].cad)); 
        //printf("E -> CADENA\n"); 
    }
#line 2574 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1014 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.expresion) = get_numero((yyvsp[0].num));
        //printf("E->numero\n");
    }
#line 2583 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1018 "semantic.y" /* yacc.c:1646  */
    { 
        // Pasando el carácter de la expresión regular a un tipo expresión.
        (yyval.expresion) = envolver_caracter((yyvsp[0].car)); 
        //printf("E -> CARACTER\n");
    }
#line 2593 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1023 "semantic.y" /* yacc.c:1646  */
    {
        // Verificamos que la llama a la función sea válida 
        // de acuerdo a la lista de tipos con que fue declarada y los tipos de los
        // argumentos.
        verifica_call((yyvsp[-3].id), (yyvsp[-1].parrams).lista_tipos, (yyvsp[-1].parrams).count);    
        char temp[32];
        strcpy(temp, newTemp());
        // Creando la cuadrupla para el código.
        cuadrupla c;
        // Es una llamada a función.
        c.op = CALL;
        strcpy(c.op1, (yyvsp[-3].id));
        sprintf(c.op2, "%d", (yyvsp[-1].parrams).count);
        strcpy(c.res, temp);
        insert_cuad(&codigo_intermedio, c);                    
        strcpy((yyval.expresion).dir, temp);
    }
#line 2615 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1045 "semantic.y" /* yacc.c:1646  */
    {
        // El número de parámetros es el que carga la lista.
        (yyval.parrams).p = (yyvsp[0].parrams).p;
        // Copiamos los tipos parámetros de la lista de parámetros.
        int i;
		for (i = 0; i < (yyvsp[0].parrams).count; i++) {
			(yyval.parrams).lista_tipos[i][0] = (yyvsp[0].parrams).lista_tipos[i][0];
			(yyval.parrams).lista_tipos[i][1] = (yyvsp[0].parrams).lista_tipos[i][1];
		}
        // El número de parámetros son los de la lista de parámetros.
        (yyval.parrams).count = (yyvsp[0].parrams).count;
    }
#line 2632 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1057 "semantic.y" /* yacc.c:1646  */
    {
        // Si cae en este caso, el número de parámetros es cero. 
        (yyval.parrams).p = 0; 
        (yyval.parrams).count = 0;
    }
#line 2642 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1067 "semantic.y" /* yacc.c:1646  */
    {
		// Creando la cuadrupla e insertándola en el código intermedio.
		cuadrupla c;
		c.op = PARAM;
		strcpy(c.op1, "");
		strcpy(c.op2, "");
		strcpy(c.res, (yyvsp[0].expresion).dir);
		insert_cuad(&codigo_intermedio, c);                    
		// Incrementando la cantidad de argumentos y copiando el tipo del actual.                  
		(yyval.parrams).p = (yyvsp[-2].parrams).p + 1;
		(yyval.parrams).lista_tipos[(yyvsp[-2].parrams).count][0] = (yyvsp[0].expresion).tipo_basico;
		(yyval.parrams).lista_tipos[(yyvsp[-2].parrams).count][1] = (yyvsp[0].expresion).dims;
		(yyval.parrams).count = (yyvsp[-2].parrams).count + 1;
	}
#line 2661 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1081 "semantic.y" /* yacc.c:1646  */
    {
		// Creando la cuadrupla e insertándola en el código intermedio.
		cuadrupla c;
		c.op = PARAM;
		strcpy(c.op1, "");
		strcpy(c.op2, "");
		strcpy(c.res, (yyvsp[0].expresion).dir);
		insert_cuad(&codigo_intermedio, c);                    
		// Como es el caso base, tenemos un solo argumento y su tipo es el tipo de la expresión.                    
		(yyval.parrams).p = 1;
		(yyval.parrams).lista_tipos[0][0] = (yyvsp[0].expresion).tipo_basico;
		(yyval.parrams).lista_tipos[0][1] = (yyvsp[0].expresion).dims;
		(yyval.parrams).count = 1;
	}
#line 2680 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1101 "semantic.y" /* yacc.c:1646  */
    {
        // Creación de la cuadrupla con la operación de label.
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[-1].booleanos).falses));
        // Inserción de la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);                    
    }
#line 2695 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1110 "semantic.y" /* yacc.c:1646  */
    { 
        char label[32];
        strcpy(label, newLabel());
        // Haciendo backpatch con la nueva etiqueta. 
        backpatch(&(yyvsp[-3].booleanos).falses, label, &codigo_intermedio);
        (yyval.booleanos).trues = merge(&(yyvsp[-3].booleanos).trues, &(yyvsp[0].booleanos).trues);
        (yyval.booleanos).falses = (yyvsp[0].booleanos).falses;
        //printf("b -> b || b\n");
    }
#line 2709 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1119 "semantic.y" /* yacc.c:1646  */
    {
        // Creación de la cuadrupla con la operación de label.
        cuadrupla c;
        c.op = LABEL;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, get_first(&(yyvsp[-1].booleanos).trues));
        // Inserción de la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);                    
    }
#line 2724 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1128 "semantic.y" /* yacc.c:1646  */
    {
        char label[32];
        strcpy(label, newLabel());                        
        (yyval.booleanos).falses = merge(&(yyvsp[-3].booleanos).falses, &(yyvsp[0].booleanos).falses);
        (yyval.booleanos).trues = (yyvsp[0].booleanos).trues;
        // Haciendo backpatch con la nueva etiqueta. 
        backpatch(&(yyvsp[-3].booleanos).trues, label, &codigo_intermedio);
        //printf("b -> b && b\n");
    }
#line 2738 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1137 "semantic.y" /* yacc.c:1646  */
    {
        // Se invierten flases y trues.
        (yyval.booleanos).falses = (yyvsp[0].booleanos).trues;
        (yyval.booleanos).trues = (yyvsp[0].booleanos).falses;
        //printf("b -> !b\n");
    }
#line 2749 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1143 "semantic.y" /* yacc.c:1646  */
    {
        // Dependen de los falses y trues de la condución del cuerpo.
        (yyval.booleanos).trues = (yyvsp[-1].booleanos).trues;
        (yyval.booleanos).falses = (yyvsp[-1].booleanos).falses;
        //printf("B->(B)\n");
    }
#line 2760 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1149 "semantic.y" /* yacc.c:1646  */
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
        c.op = (yyvsp[-1].rel) ;
        strcpy(c.op1, (yyvsp[-2].expresion).dir);
        strcpy(c.op2, (yyvsp[0].expresion).dir);
        strcpy(c.res, temp);            
        
        // Especificación de la segunda cuadrupla.
        c1.op = IFF;
        strcpy(c1.op1, temp);
        strcpy(c1.op2, "GOTO");
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
        //printf("b->e rel e\n");
    }
#line 2803 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1187 "semantic.y" /* yacc.c:1646  */
    {
        char i[32];
        strcpy(i, newIndex());
        (yyval.booleanos).trues = create_list(i);
        // Creación de la cuadrupla y con la operación de goto.
        cuadrupla c;
        c.op = GOTO;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, i);
        // Inserción de la cuadrupla.
        insert_cuad(&codigo_intermedio, c);
        //printf("b->true\n");
    }
#line 2822 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1201 "semantic.y" /* yacc.c:1646  */
    {
        char i[32];
        strcpy(i, newIndex());
        (yyval.booleanos).falses = create_list(i);
        // Creación de la cuadrupla y con la operación de goto.
        cuadrupla c;
        c.op = GOTO;
        strcpy(c.op1, "");
        strcpy(c.op2, "");
        strcpy(c.res, i);
        // Inserción de la cuadrupla.
        insert_cuad(&codigo_intermedio, c);
        //printf("b->false\n");
    }
#line 2841 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1222 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.rel) = LESS_THAN; 
        //printf("R-> <\n"); 
    }
#line 2850 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1226 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.rel) = GREATER_THAN; 
        //printf("R-> >\n");
    }
#line 2859 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1230 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.rel) = LESS_OR_EQUAL_THAN; 
        //printf("R-> <=\n");
    }
#line 2868 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1234 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.rel) = GREATER_OR_EQUAL_THAN; 
        //printf("R-> >=\n");
    }
#line 2877 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1238 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.rel) = NOT_EQUALS;
        //printf("R-> !=\n"); 
    }
#line 2886 "semantic.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1242 "semantic.y" /* yacc.c:1646  */
    { 
        (yyval.rel) = EQUALS; 
        //printf("R-> ==\n");
    }
#line 2895 "semantic.tab.c" /* yacc.c:1646  */
    break;


#line 2899 "semantic.tab.c" /* yacc.c:1646  */
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
#line 1248 "semantic.y" /* yacc.c:1906  */


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
    e.tipo_basico = e.type;
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
    e.tipo_basico = e.type;
    
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
    e.tipo_basico = e.type;
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
    e.tipo_basico = e.type;
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
        
    }
    exp e;
    cuadrupla c;
    // El tipo de la expresión es el mayor de los dos tipos de las expresiones.
    e.type = max(e1.type, e2.type);
    e.tipo_basico = e.type;
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
void verifica_call(char id[], int params[][2], int params_count) {
    // Buscando el renglón en la tabla de símbolos del identificador.
    int renglon = search(masterchef->st, id);
    if (renglon == -1) {
        // Error en caso de que no sea encontrada.
        yyerror("La funcion que quieres llamra no ha sido declarado\n");
        
    }
    // Checando que sea llamda con el mismo número de argumentos con que fue declarada.
    if (masterchef->st->symbols[renglon].num_args != params_count) {
        char error[1000];
        strcpy(error, "El número de argumentos con la que fue llamada la función es incorrecto: ");
        yyerror2(error, id);
        
    }
    // Checando que el tipo de los parámetros con que es llamda coincida con los de la declaración.
    for (int j = 0; j < params_count; j++) {
        if (masterchef->st->symbols[renglon].args[j][0] != params[j][0] || masterchef->st->symbols[renglon].args[j][1] != params[j][1]) {
            char error[1000];
            strcpy(error, "Los tipos de los argumentos que ingresaste no son correcto con la funcion: ");
            yyerror2(error, id);
            
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
exp asignacion(char *id, char *id2, exp e, int trecibido) {
    // La expresión que será devuelta.
    exp e1;
    e1.count_codigo = 0;
    // Cuando no es un var_arr:
    if (trecibido == -1) {
        int tipo = -1;
        int es_estruct = 0;
        // Si no es de la forma id.id, el segundo id es vacío y podemos obtener el tipo del primero.
        if(strcmp(id2, "") == 0) {
            tipo = get_tipo_tablas(id);
        } else {
            // En otro caso, es de la forma id.id, entonces debemos buscar el primer identificador.
            es_estruct = 1;
            // Buscamos el id antes del punto en la tabla de símbolos global para saber si fue declarado antes.
            int renglon = search(masterchef->st, id);
            if(renglon == -1) {
                //Ya que no se encontro el id en la tabla global, lo buscamos en la tabla local
                renglon = search(stack_masterchefs->tabla->st, id);
                if(renglon == -1) {
                    //En caso de que no se encontro en ningun lugar entonces gurdamos el error
                    yyerror("El identificador no fue declarado\n");
                } else {
                    //Se encontro el id en la tabla local, ahora lo buscamos el segundo id en su tabla asociada
                    renglon = stack_masterchefs->tabla->st->symbols[renglon].type;
                    //revisamos que el tipo del id sea un struct
                    if(stack_masterchefs->tabla->tt->trs[renglon].base.renglon != -2) {
                        yyerror("el identificador que buscas no es parte de un struct");
                    } else {
                        //buscamos el segundo id en ls tabla se simbolos de la estructura
                        int renglon2 = search(stack_masterchefs->tabla->tt->trs[renglon].base.smt->st, id2);
                        if(renglon2 == -1) {
                            //lanzamos error si no se encontro el segundo id
                            yyerror("el identidicador que buscas no es parte de un struct");
                        } else {
                            //Encontramos el segundo id, obtenemos su tipo con la tabla de tipos asociada y guardamos su tipo.     
                            renglon2 = stack_masterchefs->tabla->tt->trs[renglon].base.smt->st->symbols[renglon2].type; 
                            tipo = stack_masterchefs->tabla->tt->trs[renglon].base.smt->tt->trs[renglon2].type;
                        }
                    }
                }
            } else {
                //Se encontro el id en la tabla global, ahora lo buscamos el segundo id en su tabla de tipos asociada
                renglon = masterchef->st->symbols[renglon].type;
                //revisamos que el tipo del id sea un struct
                if(masterchef->tt->trs[renglon].base.renglon != -2) {
                    yyerror("el identificador que buscas no es parte de un struct");
                } else {
                    //buscamos el segundo id en ls tabla se simbolos de la estructura
                    int renglon2 = search(masterchef->tt->trs[renglon].base.smt->st, id2);
                    if(renglon2 == -1) {
                        //lanzamos error si no se encontro el segundo id
                        yyerror("el identidicador que buscas no es parte de un struct");
                    } else {
                        //Encontramos el segundo id, por lo que guardamos su tipo.
                        renglon2 = masterchef->tt->trs[renglon].base.smt->st->symbols[renglon2].type;
                        tipo = masterchef->tt->trs[renglon].base.smt->tt->trs[renglon2].type;
                    }
                }
            }
        }    
        if ( tipo != -1) {        
            // El tipo de la expresión a devolver es el de la expresión luego de la asignación.
            e1.type = e.type;
            strcpy(e1.dir, id);
            // Creando la cuadrupla para la asignación y colocando la operación.
            cuadrupla c;
            c.op = ASSIGNATION;
            // Colocando lo necesario de la cuadrupla.
            if(reducir(e.dir, tipo, e.type) != NULL) { 
                strcpy(c.op1, reducir(e.dir, tipo, e.type));
            } else if (ampliar(e.dir, e.type, tipo) != NULL){
                strcpy(c.op1, ampliar(e.dir, e.type, tipo));
            } else {
                yyerror("Asignacion inconsistente de tipos");
            }
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
            // Colocando lo respectivo al código a la expresión.
            e1.arr_codigo[e1.count_codigo] = c;    
            e1.count_codigo++;
        } else {
            // Caso para el error semántico.
            yyerror("El identificador no fue declarado\n"); 
        }
    } else { // Aquí se maneja el caso para var_arr.
        // VARARR
        e1.type = e.type;
        strcpy(e1.dir, id);
        // Creando la cuadrupla.
        cuadrupla c;
        c.op = ASSIGNATION;
        if(reducir(e.dir, trecibido, e.type) != NULL) { 
            strcpy(c.op1, reducir(e.dir, trecibido, e.type));
        } else if (ampliar(e.dir, e.type, trecibido) != NULL) {
            strcpy(c.op1, ampliar(e.dir, e.type, trecibido));
        } else {
                yyerror("Asignacion inconsistente de tipos");
        }
        strcpy(c.op2, "");
        // En este caso id es la representacin de var_arr.
        strcpy(c.res, id);//en este caso id es la representacin de vararr
        // Asociando lo respectivo al código a la expresión.
        e1.arr_codigo[e1.count_codigo] = c;
        e1.count_codigo++;
	}
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
    e.tipo_basico = e.type;
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
    e.tipo_basico = e.type;
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
    e.tipo_basico = e.type;
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
        e.tipo_basico = e.type;
        int mydims = 0;
        while(e.tipo_basico > 4){
            e.tipo_basico = stack_masterchefs->tabla->tt->trs[e.tipo_basico].base.renglon;    
            mydims++;
        }
        e.dims = mydims;
        strcpy(e.dir, id);
    }else{
        // En otro caso buscamos el identificador en la tabla global.
        if(search(masterchef->st, id) !=-1){
            // Si ya lo encontramos, copiamos su valor en el dirección de la expresión.
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
            // Si no, entonces error porque no fue declarada antes.
            yyerror("Error: el identificador no existe");
            
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
        c.op = EQUALS;
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
        c.op = EQUALS;
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
        c.op = EQUALS;
        strcpy(c.op1, "(double)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla en el código intermedio.
        insert_cuad(&codigo_intermedio, c);
        return t;
    }         
    return NULL;   
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
        c.op = EQUALS;
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
        c.op = EQUALS;
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
        c.op = EQUALS;
        strcpy(c.op1, "(float)");
        strcpy(c.op2, dir);
        strcpy(t, newTemp());
        strcpy(c.res, t);
        // Insertando la cuadrupla.
        insert_cuad(&codigo_intermedio, c);
        printf("perdida de información se esta asignando un double a un float\n");
        return t;
    }
    return NULL;
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
    printf("Línea: %d\n%s\n", yylineno, msg);
    hay_error = 1;
    fprintf(errores_sintacticos,"Línea: %d\n%s\n", yylineno, msg);
    exit(1);
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
    verificar_main();
    /* Imprimimos las tablas de tipo y símbolos y finalizamos. */
    printf("Tabla de tipos\n");
    print_type_table(masterchef->tt);
    printf("Tabla de simbolos\n");
    print_table(masterchef->st); 
    //printf("P -> D funcs\n");
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
    }
}

/**
 * Función que verifica que exista la declaración de la función
 * 'main' y que no haya funciones declaradas después de esta.
 * 
 * Autores: Concha Vázquez Miguel
 *          Flores Martínez Andrés
 *          Gladín García Ángel Iván
 *          Sánchez Pérez Pedro Juan Salvador
 *          Vázquez Salcedo Eduardo Eder
 * 
 * Creada el 12 de diciembre de 2018.
 */
void verificar_main() {
    // Buscamos la función 'main' en la tabla de símbolos global.
    int renglon = search(masterchef->st, "main");
    // Error en caso de que no se haya declarado.
    if (renglon == -1) {
        yyerror("Error: La función 'main' no fue declarada. ");
        
    }
    // Recorremos desde el renglón en que fue declarada hacia abajo
    // a ver si hay otra función, en cuyo caso habrá un error.
    for (int i = renglon + 1; i < masterchef->st->count; i++) {
        // Verificación de que haya una función.
        if (masterchef->st->symbols[i].var == 1) {
            yyerror("No puedes declarar funciones después del 'main'.");
            
        }
    }
}
