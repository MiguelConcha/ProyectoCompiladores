/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1529 of yacc.c.  */
#line 189 "semantic.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

