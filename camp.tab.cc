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
     ID = 258,
     ADD = 259,
     SUBTRACT = 260,
     TIMES = 261,
     DIVIDE = 262,
     MOD = 263,
     EXPONENT = 264,
     DOTS = 265,
     COLONS = 266,
     DASHES = 267,
     INCR = 268,
     LONGDASH = 269,
     CONTROLS = 270,
     TENSION = 271,
     ATLEAST = 272,
     CURL = 273,
     COR = 274,
     CAND = 275,
     BAR = 276,
     AMPERSAND = 277,
     EQ = 278,
     NEQ = 279,
     LT = 280,
     LE = 281,
     GT = 282,
     GE = 283,
     CARETS = 284,
     LOGNOT = 285,
     OPERATOR = 286,
     STRING = 287,
     LOOSE = 288,
     ASSIGN = 289,
     DIRTAG = 290,
     JOIN_PREC = 291,
     AND = 292,
     ELLIPSIS = 293,
     ACCESS = 294,
     UNRAVEL = 295,
     IMPORT = 296,
     INCLUDE = 297,
     FROM = 298,
     QUOTE = 299,
     STRUCT = 300,
     TYPEDEF = 301,
     NEW = 302,
     IF = 303,
     ELSE = 304,
     WHILE = 305,
     DO = 306,
     FOR = 307,
     BREAK = 308,
     CONTINUE = 309,
     RETURN_ = 310,
     THIS = 311,
     EXPLICIT = 312,
     GARBAGE = 313,
     LIT = 314,
     PERM = 315,
     MODIFIER = 316,
     UNARY = 317,
     EXP_IN_PARENS_RULE = 318
   };
#endif
/* Tokens.  */
#define ID 258
#define ADD 259
#define SUBTRACT 260
#define TIMES 261
#define DIVIDE 262
#define MOD 263
#define EXPONENT 264
#define DOTS 265
#define COLONS 266
#define DASHES 267
#define INCR 268
#define LONGDASH 269
#define CONTROLS 270
#define TENSION 271
#define ATLEAST 272
#define CURL 273
#define COR 274
#define CAND 275
#define BAR 276
#define AMPERSAND 277
#define EQ 278
#define NEQ 279
#define LT 280
#define LE 281
#define GT 282
#define GE 283
#define CARETS 284
#define LOGNOT 285
#define OPERATOR 286
#define STRING 287
#define LOOSE 288
#define ASSIGN 289
#define DIRTAG 290
#define JOIN_PREC 291
#define AND 292
#define ELLIPSIS 293
#define ACCESS 294
#define UNRAVEL 295
#define IMPORT 296
#define INCLUDE 297
#define FROM 298
#define QUOTE 299
#define STRUCT 300
#define TYPEDEF 301
#define NEW 302
#define IF 303
#define ELSE 304
#define WHILE 305
#define DO 306
#define FOR 307
#define BREAK 308
#define CONTINUE 309
#define RETURN_ 310
#define THIS 311
#define EXPLICIT 312
#define GARBAGE 313
#define LIT 314
#define PERM 315
#define MODIFIER 316
#define UNARY 317
#define EXP_IN_PARENS_RULE 318




/* Copy the first part of user declarations.  */
#line 1 "camp.y"

/*****
 * camp.y
 * Andy Hammerlindl 08/12/2002
 *
 * The grammar of the camp language.
 *****/

#include "errormsg.h"
#include "exp.h"
#include "newexp.h"
#include "dec.h"
#include "fundec.h"
#include "stm.h"
#include "modifier.h"

// Avoid error messages with unpatched bison-1.875:
#ifndef __attribute__
#define __attribute__(x)
#endif

// Used when a position needs to be determined and no token is
// available.  Defined in camp.l.
position lexerPos();

bool lexerEOF();

int yylex(void); /* function prototype */

void yyerror(const char *s)
{
  if (!lexerEOF()) {
    em.error(lexerPos());
    em << s;
    em.cont();
  }
}

namespace absyntax { file *root; }

using namespace absyntax;
using sym::symbol;
using mem::string;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
#line 46 "camp.y"
{
  position pos;
  bool boo;
  struct {
    position pos;
    sym::symbol *sym;
  } ps;
  absyntax::name *n;
  absyntax::varinit *vi;
  absyntax::arrayinit *ai;
  absyntax::exp *e;
  absyntax::specExp *se;
  absyntax::joinExp *j;
  absyntax::explist *elist;
  absyntax::argument arg;
  absyntax::arglist *alist;
  absyntax::dimensions *dim;
  absyntax::ty  *t;
  absyntax::decid *di;
  absyntax::decidlist *dil;
  absyntax::decidstart *dis;
  absyntax::runnable *run;
  struct {
    position pos;
    trans::permission val;
  } perm;
  struct {
    position pos;
    trans::modifier val;
  } mod;
  absyntax::modifierList *ml;
  //absyntax::program *prog;
  absyntax::vardec *vd;
  //absyntax::vardecs *vds;
  absyntax::dec *d;
  absyntax::idpair *ip;
  absyntax::idpairlist *ipl;
  absyntax::stm *s;
  absyntax::block *b;
  absyntax::stmExpList *sel;
  //absyntax::funheader *fh;
  absyntax::formal *fl;
  absyntax::formals *fls;
}
/* Line 193 of yacc.c.  */
#line 312 "camp.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 325 "camp.tab.c"

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
# if YYENABLE_NLS
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
#define YYLAST   2203

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  197
/* YYNRULES -- Number of states.  */
#define YYNSTATES  380

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   318

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    34,     2,     2,
      48,    49,    32,    29,    51,    31,    50,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    42,    54,
       2,     2,     2,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    53,    35,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    47,     2,     2,     2,     2,
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
      25,    26,    27,    28,    30,    36,    37,    38,    39,    41,
      43,    44,    46,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    10,    13,    15,    19,
      21,    23,    26,    29,    31,    33,    36,    39,    41,    43,
      45,    49,    55,    61,    65,    71,    77,    81,    85,    89,
      91,    95,    97,   101,   103,   105,   107,   111,   113,   117,
     120,   123,   125,   128,   130,   133,   137,   141,   146,   148,
     152,   154,   158,   160,   163,   167,   172,   174,   176,   180,
     183,   188,   192,   198,   200,   202,   205,   207,   211,   213,
     217,   220,   222,   226,   228,   229,   232,   236,   242,   248,
     255,   259,   262,   266,   271,   276,   280,   285,   289,   294,
     298,   302,   304,   306,   310,   312,   316,   319,   321,   325,
     327,   329,   331,   333,   336,   341,   347,   350,   353,   356,
     360,   364,   368,   372,   376,   380,   384,   388,   392,   396,
     400,   404,   408,   412,   416,   420,   424,   428,   432,   435,
     439,   444,   448,   453,   459,   466,   473,   481,   487,   491,
     497,   505,   519,   523,   526,   529,   532,   535,   539,   543,
     547,   551,   555,   559,   564,   566,   568,   571,   574,   578,
     583,   587,   593,   601,   603,   607,   611,   613,   615,   618,
     623,   627,   633,   636,   641,   643,   645,   648,   654,   662,
     668,   676,   686,   695,   698,   701,   704,   708,   710,   712,
     713,   715,   717,   718,   720,   721,   723,   725
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      82,     0,    -1,    83,    -1,    -1,    83,    86,    -1,    -1,
      84,    86,    -1,     3,    -1,    85,    50,     3,    -1,    88,
      -1,   124,    -1,    87,    88,    -1,    87,   124,    -1,    78,
      -1,    77,    -1,    87,    78,    -1,    87,    77,    -1,    94,
      -1,   112,    -1,   113,    -1,    56,    93,    54,    -1,    60,
      85,    57,    90,    54,    -1,    60,    85,    57,    32,    54,
      -1,    57,    85,    54,    -1,    60,    91,    56,    90,    54,
      -1,    60,    91,    56,    32,    54,    -1,    58,    92,    54,
      -1,    59,     3,    54,    -1,    59,    38,    54,    -1,     3,
      -1,     3,     3,     3,    -1,    89,    -1,    90,    51,    89,
      -1,    38,    -1,     3,    -1,     3,    -1,    91,     3,     3,
      -1,    92,    -1,    93,    51,    92,    -1,    95,    54,    -1,
      96,   100,    -1,    97,    -1,    85,    98,    -1,    85,    -1,
      52,    53,    -1,    98,    52,    53,    -1,    52,   118,    53,
      -1,    99,    52,   118,    53,    -1,   101,    -1,   100,    51,
     101,    -1,   102,    -1,   102,    41,   103,    -1,     3,    -1,
       3,    98,    -1,     3,    48,    49,    -1,     3,    48,   108,
      49,    -1,   118,    -1,   105,    -1,    45,    84,    47,    -1,
      45,    47,    -1,    45,    55,   103,    47,    -1,    45,   106,
      47,    -1,    45,   106,    55,   103,    47,    -1,    51,    -1,
     107,    -1,   107,    51,    -1,   103,    -1,   107,    51,   103,
      -1,   109,    -1,   109,    55,   111,    -1,    55,   111,    -1,
     111,    -1,   109,    51,   111,    -1,    74,    -1,    -1,   110,
      96,    -1,   110,    96,   102,    -1,   110,    96,   102,    41,
     103,    -1,    96,     3,    48,    49,   126,    -1,    96,     3,
      48,   108,    49,   126,    -1,    62,     3,   104,    -1,    63,
      94,    -1,   114,    50,     3,    -1,    85,    52,   118,    53,
      -1,   114,    52,   118,    53,    -1,    85,    48,    49,    -1,
      85,    48,   116,    49,    -1,   114,    48,    49,    -1,   114,
      48,   116,    49,    -1,    48,   118,    49,    -1,    48,    85,
      49,    -1,    73,    -1,   118,    -1,     3,    41,   118,    -1,
     117,    -1,   117,    55,   115,    -1,    55,   115,    -1,   115,
      -1,   117,    51,   115,    -1,    85,    -1,   114,    -1,    76,
      -1,    38,    -1,    76,   118,    -1,    48,    85,    49,   118,
      -1,    48,    85,    98,    49,   118,    -1,    29,   118,    -1,
      31,   118,    -1,    36,   118,    -1,   118,    29,   118,    -1,
     118,    31,   118,    -1,   118,    32,   118,    -1,   118,    33,
     118,    -1,   118,    34,   118,    -1,   118,    35,   118,    -1,
     118,    25,   118,    -1,   118,    26,   118,    -1,   118,    27,
     118,    -1,   118,    28,   118,    -1,   118,    23,   118,    -1,
     118,    24,   118,    -1,   118,    20,   118,    -1,   118,    19,
     118,    -1,   118,    30,   118,    -1,   118,    22,   118,    -1,
     118,    21,   118,    -1,   118,    37,   118,    -1,   118,    13,
     118,    -1,    64,    97,    -1,    64,    97,    99,    -1,    64,
      97,    99,    98,    -1,    64,    97,    98,    -1,    64,    97,
      98,   105,    -1,    64,    97,    48,    49,   126,    -1,    64,
      97,    98,    48,    49,   126,    -1,    64,    97,    48,   108,
      49,   126,    -1,    64,    97,    98,    48,   108,    49,   126,
      -1,   118,    40,   118,    42,   118,    -1,   118,    41,   118,
      -1,    48,   118,    51,   118,    49,    -1,    48,   118,    51,
     118,    51,   118,    49,    -1,    48,   118,    51,   118,    51,
     118,    51,   118,    51,   118,    51,   118,    49,    -1,   118,
     119,   118,    -1,   118,   120,    -1,    13,   118,    -1,    12,
     118,    -1,   118,    13,    -1,   118,     4,   118,    -1,   118,
       5,   118,    -1,   118,     6,   118,    -1,   118,     7,   118,
      -1,   118,     8,   118,    -1,   118,     9,   118,    -1,    61,
      45,    83,    47,    -1,    12,    -1,   121,    -1,   120,   121,
      -1,   121,   120,    -1,   120,   121,   120,    -1,    45,    18,
     118,    47,    -1,    45,   118,    47,    -1,    45,   118,    51,
     118,    47,    -1,    45,   118,    51,   118,    51,   118,    47,
      -1,    10,    -1,    10,   122,    10,    -1,    10,   123,    10,
      -1,    11,    -1,    14,    -1,    16,   118,    -1,    16,   118,
      46,   118,    -1,    16,    17,   118,    -1,    16,    17,   118,
      46,   118,    -1,    15,   118,    -1,    15,   118,    46,   118,
      -1,    54,    -1,   126,    -1,   125,    54,    -1,    65,    48,
     118,    49,   124,    -1,    65,    48,   118,    49,   124,    66,
     124,    -1,    67,    48,   118,    49,   124,    -1,    68,   124,
      67,    48,   118,    49,    54,    -1,    69,    48,   127,    54,
     128,    54,   129,    49,   124,    -1,    69,    48,    96,     3,
      42,   118,    49,   124,    -1,    70,    54,    -1,    71,    54,
      -1,    72,    54,    -1,    72,   118,    54,    -1,   118,    -1,
     104,    -1,    -1,   130,    -1,    95,    -1,    -1,   118,    -1,
      -1,   130,    -1,   125,    -1,   130,    51,   125,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   175,   175,   179,   180,   185,   186,   191,   192,   196,
     197,   198,   200,   205,   206,   207,   209,   214,   215,   216,
     217,   219,   221,   223,   224,   226,   228,   230,   231,   236,
     238,   242,   243,   248,   249,   253,   255,   259,   260,   265,
     269,   273,   274,   278,   282,   283,   287,   288,   293,   294,
     299,   300,   305,   306,   307,   309,   314,   315,   319,   324,
     325,   327,   329,   334,   335,   336,   340,   342,   347,   348,
     350,   354,   355,   360,   361,   365,   367,   369,   374,   376,
     381,   382,   387,   388,   390,   391,   394,   398,   399,   401,
     403,   405,   409,   410,   414,   415,   417,   421,   422,   428,
     429,   430,   431,   433,   434,   436,   438,   440,   442,   443,
     444,   445,   446,   447,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   462,   464,
     466,   468,   470,   472,   474,   479,   481,   486,   488,   490,
     492,   494,   496,   498,   504,   506,   509,   511,   512,   514,
     515,   516,   517,   519,   526,   527,   529,   532,   535,   541,
     542,   543,   546,   552,   553,   555,   557,   558,   562,   564,
     567,   570,   576,   577,   582,   583,   584,   585,   587,   589,
     591,   593,   595,   597,   598,   599,   600,   604,   608,   612,
     613,   614,   618,   619,   623,   624,   628,   629
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "ADD", "SUBTRACT", "TIMES",
  "DIVIDE", "MOD", "EXPONENT", "DOTS", "COLONS", "DASHES", "INCR",
  "LONGDASH", "CONTROLS", "TENSION", "ATLEAST", "CURL", "COR", "CAND",
  "BAR", "AMPERSAND", "EQ", "NEQ", "LT", "LE", "GT", "GE", "'+'", "CARETS",
  "'-'", "'*'", "'/'", "'%'", "'^'", "LOGNOT", "OPERATOR", "STRING",
  "LOOSE", "'?'", "ASSIGN", "':'", "DIRTAG", "JOIN_PREC", "'{'", "AND",
  "'}'", "'('", "')'", "'.'", "','", "'['", "']'", "';'", "ELLIPSIS",
  "ACCESS", "UNRAVEL", "IMPORT", "INCLUDE", "FROM", "QUOTE", "STRUCT",
  "TYPEDEF", "NEW", "IF", "ELSE", "WHILE", "DO", "FOR", "BREAK",
  "CONTINUE", "RETURN_", "THIS", "EXPLICIT", "GARBAGE", "LIT", "PERM",
  "MODIFIER", "UNARY", "EXP_IN_PARENS_RULE", "$accept", "file",
  "fileblock", "bareblock", "name", "runnable", "modifiers", "dec",
  "idpair", "idpairlist", "strid", "stridpair", "stridpairlist", "vardec",
  "barevardec", "type", "celltype", "dims", "dimexps", "decidlist",
  "decid", "decidstart", "varinit", "block", "arrayinit", "basearrayinit",
  "varinits", "formals", "baseformals", "explicitornot", "formal",
  "fundec", "typedec", "value", "argument", "arglist", "basearglist",
  "exp", "join", "dir", "basicjoin", "tension", "controls", "stm",
  "stmexp", "blockstm", "forinit", "fortest", "forupdate", "stmexplist", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    43,
     284,    45,    42,    47,    37,    94,   285,   286,   287,   288,
      63,   289,    58,   290,   291,   123,   292,   125,    40,    41,
      46,    44,    91,    93,    59,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    84,    84,    85,    85,    86,
      86,    86,    86,    87,    87,    87,    87,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    89,
      89,    90,    90,    91,    91,    92,    92,    93,    93,    94,
      95,    96,    96,    97,    98,    98,    99,    99,   100,   100,
     101,   101,   102,   102,   102,   102,   103,   103,   104,   105,
     105,   105,   105,   106,   106,   106,   107,   107,   108,   108,
     108,   109,   109,   110,   110,   111,   111,   111,   112,   112,
     113,   113,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   115,   115,   116,   116,   116,   117,   117,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   119,   119,   119,   119,   119,   120,
     120,   120,   120,   121,   121,   121,   121,   121,   122,   122,
     122,   122,   123,   123,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   125,   126,   127,
     127,   127,   128,   128,   129,   129,   130,   130
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     0,     2,     1,     3,     1,
       1,     2,     2,     1,     1,     2,     2,     1,     1,     1,
       3,     5,     5,     3,     5,     5,     3,     3,     3,     1,
       3,     1,     3,     1,     1,     1,     3,     1,     3,     2,
       2,     1,     2,     1,     2,     3,     3,     4,     1,     3,
       1,     3,     1,     2,     3,     4,     1,     1,     3,     2,
       4,     3,     5,     1,     1,     2,     1,     3,     1,     3,
       2,     1,     3,     1,     0,     2,     3,     5,     5,     6,
       3,     2,     3,     4,     4,     3,     4,     3,     4,     3,
       3,     1,     1,     3,     1,     3,     2,     1,     3,     1,
       1,     1,     1,     2,     4,     5,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       4,     3,     4,     5,     6,     6,     7,     5,     3,     5,
       7,    13,     3,     2,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     4,     1,     1,     2,     2,     3,     4,
       3,     5,     7,     1,     3,     3,     1,     1,     2,     4,
       3,     5,     2,     4,     1,     1,     2,     5,     7,     5,
       7,     9,     8,     2,     2,     2,     3,     1,     1,     0,
       1,     1,     0,     1,     0,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     7,     0,     0,     0,     0,     0,
     102,     5,     0,   174,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,   101,    14,    13,    99,     4,     0,     9,    17,     0,
       0,    41,   188,    18,    19,   100,   187,    10,     0,   175,
      99,   145,   144,   106,   107,   108,     0,    99,     0,    35,
      33,     0,    37,     0,     0,     0,     0,     0,     7,     0,
       0,     3,     0,    43,    81,     0,    43,   128,     0,     0,
       0,   189,   183,   184,   185,     0,   103,     0,     0,     0,
      42,    16,    15,    11,    12,    39,    52,    40,    48,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   163,
     166,   154,   146,   167,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   143,   155,   176,     0,
      58,     6,    90,     0,    89,     0,     0,     0,    20,    23,
      26,    27,    28,     0,     0,     0,    80,     0,    52,    74,
       0,   131,   129,     0,     0,     0,   191,     0,   196,     0,
     190,   186,     7,    85,     0,    97,     0,    94,    92,     8,
      44,     0,     0,    74,    53,     0,     0,    87,     0,    82,
       0,   147,   148,   149,   150,   151,   152,     0,     0,     0,
       0,   127,   122,   121,   125,   124,   119,   120,   115,   116,
     117,   118,   109,   123,   110,   111,   112,   113,   114,   126,
       0,   138,     0,     0,   142,   156,   157,   104,     0,     0,
      36,    38,    29,     0,    31,     0,     0,     0,   153,    74,
       0,    74,    73,     0,    68,     0,    71,     0,     0,    74,
     132,     0,   130,     0,     0,     0,    52,   192,     0,     0,
      96,    86,     0,     0,    83,    45,    54,     0,    49,    51,
      57,    56,    88,    84,   172,     0,   168,   164,   165,     0,
       0,   160,     0,   158,   105,   139,     0,     0,    22,     0,
      21,    25,    24,    54,     0,   133,    70,     0,    74,    74,
      75,    46,    59,    63,     0,    66,     0,    64,     0,     0,
       0,   177,   179,     0,     0,   193,     0,   197,    93,    98,
      95,    78,    55,     0,   170,     0,   137,   159,     0,     0,
      30,    32,    55,   135,    72,    69,    76,     0,    61,     0,
      65,   134,     0,    47,     0,     0,     0,   194,    79,   173,
       0,   169,   161,     0,   140,     0,     0,    60,     0,    67,
     136,   178,   180,     0,     0,   195,   171,     0,     0,    77,
      62,   182,     0,   162,     0,   181,     0,     0,     0,   141
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    56,    50,    35,    36,    37,   234,   235,
      61,    62,    63,    38,    39,    40,    41,   184,   162,    97,
      98,    99,   269,    42,   270,   306,   307,   243,   244,   245,
     246,    43,    44,    45,   175,   176,   177,    46,   135,   136,
     137,   199,   200,    47,    48,    49,   169,   316,   364,   170
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -229
static const yytype_int16 yypact[] =
{
    -229,    29,   468,  -229,  -229,   760,   760,   760,   760,   760,
    -229,  -229,   760,  -229,    15,    54,    15,    18,    20,    22,
      66,    54,    54,    45,    46,   130,    96,    91,   103,   624,
    -229,   183,  -229,  -229,    11,  -229,   539,  -229,  -229,   108,
     161,  -229,  -229,  -229,  -229,   106,  1923,  -229,   123,  -229,
     122,   147,   147,   147,   147,  -229,   326,    40,  1098,   170,
    -229,   185,  -229,   125,    27,   142,   151,   160,   166,    30,
     168,  -229,   175,    86,  -229,   204,   176,   -10,   760,   760,
     158,   760,  -229,  -229,  -229,   847,   147,   610,   224,   677,
     178,  -229,  -229,  -229,  -229,  -229,    -1,   184,  -229,   187,
     618,   226,   760,   760,   760,   760,   760,   760,   760,    70,
    -229,  -229,   183,  -229,   760,   760,   760,   760,   760,   760,
     760,   760,   760,   760,   760,   760,   760,   760,   760,   760,
     760,   760,   760,   760,   698,   760,  -229,   191,  -229,   760,
    -229,  -229,   183,   138,  -229,   760,   234,    15,  -229,  -229,
    -229,  -229,  -229,    12,    16,   397,  -229,   186,   119,   -22,
     677,    31,   188,  1434,  1480,   190,  -229,   238,  -229,   194,
     198,  -229,   201,  -229,   774,  -229,   196,   134,  1923,  -229,
    -229,   898,   200,   -19,   178,   204,   706,  -229,   202,  -229,
     948,  1923,  1923,  1923,  1923,  1923,  1923,   760,   752,   250,
     251,   118,  2037,  2065,  2093,  2121,  2149,  2149,  2158,  2158,
    2158,  2158,   177,   405,   177,   147,   147,   147,   147,   272,
    1881,  1923,   760,  1146,   118,   191,  -229,  -229,   760,  1194,
    -229,  -229,   259,   209,  -229,   162,   210,   164,  -229,   -14,
     175,   192,  -229,   216,   153,    54,  -229,   998,   285,   -12,
    -229,   677,   178,   130,   130,   760,    -3,   760,   760,   760,
    -229,  -229,   774,   774,  -229,  -229,   175,   218,  -229,  -229,
    -229,  1923,  -229,  -229,  1752,   760,  1795,  -229,  -229,   760,
    1664,  -229,   760,  -229,  -229,  -229,   760,   265,  -229,   266,
    -229,  -229,  -229,  -229,   222,  -229,  -229,   175,   192,   192,
     204,  -229,  -229,  -229,   706,  -229,    17,   225,   175,   229,
    1048,   207,  -229,  1526,   760,  1923,   221,  -229,  1923,  -229,
    -229,  -229,   175,   760,  1838,   760,  2001,  -229,  1242,  1290,
    -229,  -229,  -229,  -229,  -229,  -229,   239,   232,  -229,   706,
     706,  -229,   175,  -229,   130,   233,  1572,   760,  -229,  1965,
     760,  1965,  -229,   760,  -229,   760,   706,  -229,   242,  -229,
    -229,  -229,  -229,   130,   241,   198,  1965,  1708,  1338,  -229,
    -229,  -229,   130,  -229,   760,  -229,  1386,   760,  1618,  -229
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -229,  -229,   220,  -229,    10,   236,  -229,   257,     5,   141,
     278,    -6,  -229,   279,   227,   -13,   288,   -23,  -229,  -229,
     126,    13,  -208,   240,   154,  -229,  -229,  -174,  -229,  -229,
    -228,  -229,  -229,  -229,  -157,   219,  -229,    -5,  -229,  -117,
     189,  -229,  -229,   -20,   -75,  -162,  -229,  -229,  -229,   -25
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -44
static const yytype_int16 yytable[] =
{
      51,    52,    53,    54,    55,    80,   168,    58,    75,   267,
      65,    90,    34,   296,   -43,   232,    94,   260,    59,   232,
     226,    66,    57,    68,    85,    64,    86,   240,    69,     3,
     266,    73,    76,   241,   143,   293,   241,   308,   159,   314,
     305,   241,   160,   241,   233,   239,    34,   183,   236,   157,
      90,   157,   242,    60,   161,   242,    67,     4,    60,    87,
     242,    88,   242,    89,   338,   294,    34,    71,   167,    72,
     334,   335,   339,   163,   164,   309,   248,    88,   295,   249,
      88,   149,   178,   182,   181,   197,   198,   153,    87,   142,
      88,    34,    89,    78,    79,   178,   337,   190,   191,   192,
     193,   194,   195,   196,   321,   319,   320,   201,   283,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   223,
     224,   358,   359,     4,   181,   333,    88,   227,   157,   252,
     229,   231,     5,     6,    81,    82,   341,   124,   369,   126,
     127,   128,   129,   130,   100,   247,   101,    83,   102,     7,
     348,     8,    95,   134,    96,    34,     9,   239,    10,   178,
      87,   157,    88,   -34,   139,    11,   147,   138,    12,   148,
     360,   271,   130,   317,    13,   262,     4,   228,   146,   263,
     182,    19,   274,   276,    22,    23,   150,    24,    25,    26,
      27,    28,    29,    30,   298,   151,    31,   158,   299,   127,
     128,   129,   130,   289,   152,   289,   290,   280,   292,     9,
      11,    10,   -34,   284,   154,   165,    88,   179,   186,   189,
     182,    12,   300,   311,   312,   185,   134,   230,   255,   180,
     251,   256,   259,   271,    19,   261,   310,    22,   257,   258,
     313,   272,   315,   265,   318,    73,    30,   178,   178,    31,
     277,   278,   287,   288,   291,   297,   242,   322,   330,   232,
     324,   332,   168,   344,   326,   347,   340,   328,   342,   357,
     356,   329,   109,   110,   111,   112,   113,   362,     4,   370,
     372,   155,   141,    93,   331,   237,    70,     5,     6,   271,
      74,   124,   125,   126,   127,   128,   129,   130,   166,   346,
      77,   268,   156,   336,     7,   250,     8,   134,   349,   188,
     351,     9,   365,    10,   361,   225,     0,     0,     0,     4,
     248,     0,   302,    12,   271,   271,   303,     0,     5,     6,
     304,     0,     0,   371,     0,   366,    19,     0,   367,    22,
     368,   271,   375,     0,     0,     7,     0,     8,    30,     0,
       0,    31,     9,     0,    10,     0,     0,     0,     0,   376,
       0,    11,   378,   140,    12,     0,     0,     0,     0,     0,
      13,     0,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,     0,    24,    25,    26,    27,    28,    29,    30,
       4,     0,    31,    32,    33,     0,     0,     0,     0,     5,
       6,     0,     0,     0,     0,   109,   110,   111,   112,   113,
       0,     0,     0,     0,     0,     0,     7,     0,     8,     0,
       0,     0,     0,     9,   124,    10,   126,   127,   128,   129,
     130,     0,    11,     0,   238,    12,     0,     0,     0,     0,
     134,    13,     0,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,     0,    24,    25,    26,    27,    28,    29,
      30,     4,     0,    31,    32,    33,     0,     0,     0,     0,
       5,     6,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     0,     8,
       0,     0,     0,     0,     9,     0,    10,     0,     0,     0,
       0,     0,     0,    11,     0,     0,    12,     0,     0,     0,
       0,     0,    13,     0,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,     0,    24,    25,    26,    27,    28,
      29,    30,     4,     0,    31,    32,    33,     0,     0,     0,
       0,     5,     6,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     7,     0,
       8,     0,     0,     0,     0,     9,     0,    10,     0,     0,
       0,     0,     0,     0,    11,     0,     0,    12,     0,     0,
       0,     0,     0,    13,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     0,    24,    25,    26,    27,
      28,    29,    30,   172,     0,    31,    91,    92,     0,     0,
       0,   172,     5,     6,     0,     0,     0,     4,     0,     0,
       5,     6,     0,     0,     0,     0,     5,     6,     0,     7,
       0,     8,     0,     0,     0,     0,     9,     7,    10,     8,
       0,     0,     0,     7,     9,     8,    10,     0,    12,   173,
       9,     0,    10,     0,     0,   174,    12,   187,     0,     0,
       0,    19,    12,   174,    22,     0,     0,     0,    84,    19,
       4,     0,    22,    30,     0,    19,    31,     0,    22,     5,
       6,    30,     0,     0,    31,     0,     0,    30,     0,     0,
      31,     4,     0,     0,     0,     0,     7,     0,     8,     4,
       5,     6,     0,     9,     0,    10,   222,     0,     5,     6,
       0,     0,     0,     0,     0,    12,     0,     7,     0,     8,
     180,     0,     0,     0,     9,     7,    10,     8,    19,     0,
       0,    22,     9,     0,    10,     0,    12,     0,     0,     0,
      30,   248,     0,    31,    12,     4,     0,     0,     0,    19,
       0,     0,    22,     4,     5,     6,     0,    19,     0,   275,
      22,    30,     5,     6,    31,     0,     0,   172,     0,    30,
       0,     7,    31,     8,     0,     0,     5,     6,     9,     7,
      10,     8,     0,     0,     0,     0,     9,     0,    10,     0,
      12,     0,     0,     7,     0,     8,     0,     0,    12,     0,
       9,     0,    10,    19,     0,     0,    22,     0,     0,     0,
       0,    19,    12,     0,    22,    30,     0,     0,    31,     0,
       0,     0,     0,    30,     0,    19,    31,     0,    22,     0,
       0,     0,     0,     0,     0,     0,     0,    30,     0,     0,
      31,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     0,     0,     0,     0,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,     0,   131,     0,     0,   132,   133,     0,
       0,     0,   134,     0,     0,     0,     0,     0,     0,     0,
       0,   171,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     0,     0,     0,     0,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,     0,   131,     0,     0,   132,   133,
       0,     0,     0,   134,     0,     0,     0,     0,     0,     0,
       0,   264,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     0,     0,     0,     0,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,     0,   131,     0,     0,   132,   133,
       0,     0,     0,   134,     0,     0,     0,     0,     0,     0,
       0,   273,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     0,     0,     0,     0,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,     0,   131,     0,     0,   132,   133,
       0,     0,     0,   134,     0,     0,     0,     0,     0,     0,
       0,   301,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     0,     0,     0,     0,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,     0,   131,     0,     0,   132,   133,
       0,     0,     0,   134,     0,     0,     0,     0,     0,     0,
       0,   343,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     0,     0,     0,     0,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,     0,   131,     0,     0,   132,   133,
       0,     0,     0,   134,     0,     0,     0,   144,     0,   145,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,     0,     0,     0,     0,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,     0,   131,     0,     0,   132,   133,     0,     0,
       0,   134,     0,   281,     0,     0,     0,   282,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,     0,
       0,     0,     0,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
       0,   131,     0,     0,   132,   133,     0,     0,     0,   134,
       0,     0,     0,   285,     0,   286,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,     0,   131,
       0,     0,   132,   133,     0,     0,     0,   134,     0,   352,
       0,     0,     0,   353,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,     0,     0,     0,     0,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,     0,   131,     0,     0,
     132,   133,     0,     0,     0,   134,     0,     0,     0,   354,
       0,   355,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     0,     0,     0,     0,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,     0,   131,     0,     0,   132,   133,
       0,     0,     0,   134,     0,     0,     0,     0,     0,   374,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,     0,     0,     0,     0,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,     0,   131,     0,     0,   132,   133,     0,     0,
       0,   134,     0,     0,     0,     0,     0,   377,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,     0,
       0,     0,     0,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
       0,   131,     0,     0,   132,   133,     0,     0,     0,   134,
       0,     0,     0,   253,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,     0,     0,     0,     0,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,     0,   131,     0,     0,
     132,   133,     0,     0,     0,   134,     0,     0,     0,   254,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,     0,     0,     0,     0,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,     0,   131,     0,     0,   132,   133,     0,     0,
       0,   134,     0,     0,     0,   345,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,     0,   131,
       0,     0,   132,   133,     0,     0,     0,   134,     0,     0,
       0,   363,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     0,     0,     0,     0,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,     0,   131,     0,     0,   132,   133,
       0,     0,     0,   134,     0,     0,     0,   379,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,     0,
       0,     0,     0,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
       0,   131,     0,     0,   132,   133,     0,     0,     0,   134,
       0,   327,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     0,     0,     0,     0,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,     0,   131,     0,     0,   132,   133,
       0,     0,     0,   134,     0,   373,   103,   104,   105,   106,
     107,   108,     0,   110,   111,   112,   113,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,     0,   131,
       0,     0,   132,   133,     0,     0,     0,   134,   323,   103,
     104,   105,   106,   107,   108,     0,   110,   111,   112,   113,
       0,     0,     0,     0,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,     0,   131,     0,     0,   132,   133,     0,     0,     0,
     134,   325,   103,   104,   105,   106,   107,   108,     0,   110,
     111,   112,   113,     0,     0,     0,     0,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,     0,   131,     0,     0,   132,   133,
       0,     0,     0,   134,   350,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,     0,     0,     0,     0,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,     0,   131,     0,
       0,   132,   133,   279,     0,     0,   134,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,     0,     0,
       0,     0,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,     0,
     131,     0,     0,   132,   133,     0,     0,     0,   134,   103,
     104,   105,   106,   107,   108,     0,   110,   111,   112,   113,
       0,     0,     0,     0,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,     0,   131,     0,     0,   132,   133,     0,     0,     0,
     134,   109,   110,   111,   112,   113,     0,     0,     0,     0,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,     0,   131,     0,
       0,   132,     0,     0,     0,     0,   134,   109,   110,   111,
     112,   113,     0,     0,     0,     0,     0,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,     0,   131,   109,   110,   111,   112,   113,
       0,     0,   134,     0,     0,     0,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,     0,   131,   109,   110,   111,   112,   113,     0,     0,
     134,     0,     0,     0,     0,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,     0,
     131,   109,   110,   111,   112,   113,     0,     0,   134,     0,
       0,     0,     0,     0,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,     0,   131,   109,
     110,   111,   112,   113,     0,     0,   134,     0,   109,   110,
     111,   112,   113,     0,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,     0,   131,   124,   125,   126,
     127,   128,   129,   130,   134,   131,     0,     0,     0,     0,
       0,     0,     0,   134
};

static const yytype_int16 yycheck[] =
{
       5,     6,     7,     8,     9,    25,    81,    12,    21,   183,
      16,    34,     2,   241,     3,     3,    36,   174,     3,     3,
     137,     3,    12,     3,    29,    15,    31,    49,    18,     0,
      49,    21,    22,    55,    57,    49,    55,    49,    48,    42,
     248,    55,    52,    55,    32,    48,    36,    48,    32,    52,
      73,    52,    74,    38,    77,    74,    38,     3,    38,    48,
      74,    50,    74,    52,    47,   239,    56,    45,    81,     3,
     298,   299,    55,    78,    79,   249,    45,    50,   240,    48,
      50,    54,    87,    52,    89,    15,    16,    57,    48,    49,
      50,    81,    52,    48,    48,   100,   304,   102,   103,   104,
     105,   106,   107,   108,   266,   262,   263,   112,   225,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   339,   340,     3,   139,   297,    50,   142,    52,   162,
     145,   147,    12,    13,    48,    54,   308,    29,   356,    31,
      32,    33,    34,    35,    48,   160,    50,    54,    52,    29,
     322,    31,    54,    45,     3,   155,    36,    48,    38,   174,
      48,    52,    50,     3,    52,    45,    51,    54,    48,    54,
     342,   186,    35,   258,    54,    51,     3,    49,     3,    55,
      52,    61,   197,   198,    64,    65,    54,    67,    68,    69,
      70,    71,    72,    73,    51,    54,    76,     3,    55,    32,
      33,    34,    35,    51,    54,    51,    54,   222,    54,    36,
      45,    38,    56,   228,    56,    67,    50,     3,    41,     3,
      52,    48,   245,   253,   254,    51,    45,     3,    48,    53,
      52,     3,    41,   248,    61,    49,   251,    64,    54,    51,
     255,    49,   257,    53,   259,   245,    73,   262,   263,    76,
      10,    10,     3,    54,    54,    49,    74,    49,     3,     3,
     275,    49,   347,    66,   279,    54,    51,   282,    49,    47,
      41,   286,    10,    11,    12,    13,    14,    54,     3,    47,
      49,    71,    56,    36,   289,   154,    18,    12,    13,   304,
      21,    29,    30,    31,    32,    33,    34,    35,    81,   314,
      22,   185,    72,   300,    29,   161,    31,    45,   323,   100,
     325,    36,   347,    38,   344,   136,    -1,    -1,    -1,     3,
      45,    -1,    47,    48,   339,   340,    51,    -1,    12,    13,
      55,    -1,    -1,   363,    -1,   350,    61,    -1,   353,    64,
     355,   356,   372,    -1,    -1,    29,    -1,    31,    73,    -1,
      -1,    76,    36,    -1,    38,    -1,    -1,    -1,    -1,   374,
      -1,    45,   377,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    -1,    67,    68,    69,    70,    71,    72,    73,
       3,    -1,    76,    77,    78,    -1,    -1,    -1,    -1,    12,
      13,    -1,    -1,    -1,    -1,    10,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,
      -1,    -1,    -1,    36,    29,    38,    31,    32,    33,    34,
      35,    -1,    45,    -1,    47,    48,    -1,    -1,    -1,    -1,
      45,    54,    -1,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    -1,    67,    68,    69,    70,    71,    72,
      73,     3,    -1,    76,    77,    78,    -1,    -1,    -1,    -1,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      -1,    -1,    -1,    -1,    36,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    54,    -1,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    -1,    67,    68,    69,    70,    71,
      72,    73,     3,    -1,    76,    77,    78,    -1,    -1,    -1,
      -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      31,    -1,    -1,    -1,    -1,    36,    -1,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    54,    -1,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    -1,    67,    68,    69,    70,
      71,    72,    73,     3,    -1,    76,    77,    78,    -1,    -1,
      -1,     3,    12,    13,    -1,    -1,    -1,     3,    -1,    -1,
      12,    13,    -1,    -1,    -1,    -1,    12,    13,    -1,    29,
      -1,    31,    -1,    -1,    -1,    -1,    36,    29,    38,    31,
      -1,    -1,    -1,    29,    36,    31,    38,    -1,    48,    49,
      36,    -1,    38,    -1,    -1,    55,    48,    49,    -1,    -1,
      -1,    61,    48,    55,    64,    -1,    -1,    -1,    54,    61,
       3,    -1,    64,    73,    -1,    61,    76,    -1,    64,    12,
      13,    73,    -1,    -1,    76,    -1,    -1,    73,    -1,    -1,
      76,     3,    -1,    -1,    -1,    -1,    29,    -1,    31,     3,
      12,    13,    -1,    36,    -1,    38,    18,    -1,    12,    13,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    29,    -1,    31,
      53,    -1,    -1,    -1,    36,    29,    38,    31,    61,    -1,
      -1,    64,    36,    -1,    38,    -1,    48,    -1,    -1,    -1,
      73,    45,    -1,    76,    48,     3,    -1,    -1,    -1,    61,
      -1,    -1,    64,     3,    12,    13,    -1,    61,    -1,    17,
      64,    73,    12,    13,    76,    -1,    -1,     3,    -1,    73,
      -1,    29,    76,    31,    -1,    -1,    12,    13,    36,    29,
      38,    31,    -1,    -1,    -1,    -1,    36,    -1,    38,    -1,
      48,    -1,    -1,    29,    -1,    31,    -1,    -1,    48,    -1,
      36,    -1,    38,    61,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    61,    48,    -1,    64,    73,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    73,    -1,    61,    76,    -1,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,    -1,
      76,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    37,    -1,    -1,    40,    41,    -1,
      -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    37,    -1,    -1,    40,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    37,    -1,    -1,    40,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    37,    -1,    -1,    40,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    37,    -1,    -1,    40,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    37,    -1,    -1,    40,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    49,    -1,    51,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    37,    -1,    -1,    40,    41,    -1,    -1,
      -1,    45,    -1,    47,    -1,    -1,    -1,    51,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    37,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    49,    -1,    51,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    37,
      -1,    -1,    40,    41,    -1,    -1,    -1,    45,    -1,    47,
      -1,    -1,    -1,    51,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    37,    -1,    -1,
      40,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,    49,
      -1,    51,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    37,    -1,    -1,    40,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    51,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    37,    -1,    -1,    40,    41,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    51,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    37,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    49,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    37,    -1,    -1,
      40,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,    49,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    37,    -1,    -1,    40,    41,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    49,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    37,
      -1,    -1,    40,    41,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    49,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    37,    -1,    -1,    40,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    49,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    37,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,
      -1,    47,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    37,    -1,    -1,    40,    41,
      -1,    -1,    -1,    45,    -1,    47,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    -1,    37,
      -1,    -1,    40,    41,    -1,    -1,    -1,    45,    46,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    37,    -1,    -1,    40,    41,    -1,    -1,    -1,
      45,    46,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    -1,    37,    -1,    -1,    40,    41,
      -1,    -1,    -1,    45,    46,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    37,    -1,
      -1,    40,    41,    42,    -1,    -1,    45,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      37,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    37,    -1,    -1,    40,    41,    -1,    -1,    -1,
      45,    10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    37,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    45,    10,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    37,    10,    11,    12,    13,    14,
      -1,    -1,    45,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    37,    10,    11,    12,    13,    14,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      37,    10,    11,    12,    13,    14,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    37,    10,
      11,    12,    13,    14,    -1,    -1,    45,    -1,    10,    11,
      12,    13,    14,    -1,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    37,    29,    30,    31,
      32,    33,    34,    35,    45,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    82,    83,     0,     3,    12,    13,    29,    31,    36,
      38,    45,    48,    54,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    67,    68,    69,    70,    71,    72,
      73,    76,    77,    78,    85,    86,    87,    88,    94,    95,
      96,    97,   104,   112,   113,   114,   118,   124,   125,   126,
      85,   118,   118,   118,   118,   118,    84,    85,   118,     3,
      38,    91,    92,    93,    85,    92,     3,    38,     3,    85,
      91,    45,     3,    85,    94,    96,    85,    97,    48,    48,
     124,    48,    54,    54,    54,   118,   118,    48,    50,    52,
      98,    77,    78,    88,   124,    54,     3,   100,   101,   102,
      48,    50,    52,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    37,    40,    41,    45,   119,   120,   121,    54,    52,
      47,    86,    49,    98,    49,    51,     3,    51,    54,    54,
      54,    54,    54,    57,    56,    83,   104,    52,     3,    48,
      52,    98,    99,   118,   118,    67,    95,    96,   125,   127,
     130,    54,     3,    49,    55,   115,   116,   117,   118,     3,
      53,   118,    52,    48,    98,    51,    41,    49,   116,     3,
     118,   118,   118,   118,   118,   118,   118,    15,    16,   122,
     123,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,    18,   118,   118,   121,   120,   118,    49,   118,
       3,    92,     3,    32,    89,    90,    32,    90,    47,    48,
      49,    55,    74,   108,   109,   110,   111,   118,    45,    48,
     105,    52,    98,    49,    49,    48,     3,    54,    51,    41,
     115,    49,    51,    55,    53,    53,    49,   108,   101,   103,
     105,   118,    49,    53,   118,    17,   118,    10,    10,    42,
     118,    47,    51,   120,   118,    49,    51,     3,    54,    51,
      54,    54,    54,    49,   108,   126,   111,    49,    51,    55,
      96,    53,    47,    51,    55,   103,   106,   107,    49,   108,
     118,   124,   124,   118,    42,   118,   128,   125,   118,   115,
     115,   126,    49,    46,   118,    46,   118,    47,   118,   118,
       3,    89,    49,   126,   111,   111,   102,   103,    47,    55,
      51,   126,    49,    53,    66,    49,   118,    54,   126,   118,
      46,   118,    47,    51,    49,    51,    41,    47,   103,   103,
     126,   124,    54,    49,   129,   130,   118,   118,   118,   103,
      47,   124,    49,    47,    51,   124,   118,    51,   118,    49
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
# if YYLTYPE_IS_TRIVIAL
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
#line 175 "camp.y"
    { absyntax::root = (yyvsp[(1) - (1)].b); ;}
    break;

  case 3:
#line 179 "camp.y"
    { (yyval.b) = new file(lexerPos(), false); ;}
    break;

  case 4:
#line 181 "camp.y"
    { (yyval.b) = (yyvsp[(1) - (2)].b); (yyval.b)->add((yyvsp[(2) - (2)].run)); ;}
    break;

  case 5:
#line 185 "camp.y"
    { (yyval.b) = new block(lexerPos(), true); ;}
    break;

  case 6:
#line 187 "camp.y"
    { (yyval.b) = (yyvsp[(1) - (2)].b); (yyval.b)->add((yyvsp[(2) - (2)].run)); ;}
    break;

  case 7:
#line 191 "camp.y"
    { (yyval.n) = new simpleName((yyvsp[(1) - (1)].ps).pos, (yyvsp[(1) - (1)].ps).sym); ;}
    break;

  case 8:
#line 192 "camp.y"
    { (yyval.n) = new qualifiedName((yyvsp[(2) - (3)].pos), (yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].ps).sym); ;}
    break;

  case 9:
#line 196 "camp.y"
    { (yyval.run) = (yyvsp[(1) - (1)].d); ;}
    break;

  case 10:
#line 197 "camp.y"
    { (yyval.run) = (yyvsp[(1) - (1)].s); ;}
    break;

  case 11:
#line 199 "camp.y"
    { (yyval.run) = new modifiedRunnable((yyvsp[(1) - (2)].ml)->getPos(), (yyvsp[(1) - (2)].ml), (yyvsp[(2) - (2)].d)); ;}
    break;

  case 12:
#line 201 "camp.y"
    { (yyval.run) = new modifiedRunnable((yyvsp[(1) - (2)].ml)->getPos(), (yyvsp[(1) - (2)].ml), (yyvsp[(2) - (2)].s)); ;}
    break;

  case 13:
#line 205 "camp.y"
    { (yyval.ml) = new modifierList((yyvsp[(1) - (1)].mod).pos); (yyval.ml)->add((yyvsp[(1) - (1)].mod).val); ;}
    break;

  case 14:
#line 206 "camp.y"
    { (yyval.ml) = new modifierList((yyvsp[(1) - (1)].perm).pos); (yyval.ml)->add((yyvsp[(1) - (1)].perm).val); ;}
    break;

  case 15:
#line 208 "camp.y"
    { (yyval.ml) = (yyvsp[(1) - (2)].ml); (yyval.ml)->add((yyvsp[(2) - (2)].mod).val); ;}
    break;

  case 16:
#line 210 "camp.y"
    { (yyval.ml) = (yyvsp[(1) - (2)].ml); (yyval.ml)->add((yyvsp[(2) - (2)].perm).val); ;}
    break;

  case 17:
#line 214 "camp.y"
    { (yyval.d) = (yyvsp[(1) - (1)].vd); ;}
    break;

  case 18:
#line 215 "camp.y"
    { (yyval.d) = (yyvsp[(1) - (1)].d); ;}
    break;

  case 19:
#line 216 "camp.y"
    { (yyval.d) = (yyvsp[(1) - (1)].d); ;}
    break;

  case 20:
#line 218 "camp.y"
    { (yyval.d) = new accessdec((yyvsp[(1) - (3)].pos), (yyvsp[(2) - (3)].ipl)); ;}
    break;

  case 21:
#line 220 "camp.y"
    { (yyval.d) = new unraveldec((yyvsp[(1) - (5)].pos), (yyvsp[(2) - (5)].n), (yyvsp[(4) - (5)].ipl)); ;}
    break;

  case 22:
#line 222 "camp.y"
    { (yyval.d) = new unraveldec((yyvsp[(1) - (5)].pos), (yyvsp[(2) - (5)].n), WILDCARD); ;}
    break;

  case 23:
#line 223 "camp.y"
    { (yyval.d) = new unraveldec((yyvsp[(1) - (3)].pos), (yyvsp[(2) - (3)].n), WILDCARD); ;}
    break;

  case 24:
#line 225 "camp.y"
    { (yyval.d) = new fromaccessdec((yyvsp[(1) - (5)].pos), (yyvsp[(2) - (5)].ps).sym, (yyvsp[(4) - (5)].ipl)); ;}
    break;

  case 25:
#line 227 "camp.y"
    { (yyval.d) = new fromaccessdec((yyvsp[(1) - (5)].pos), (yyvsp[(2) - (5)].ps).sym, WILDCARD); ;}
    break;

  case 26:
#line 229 "camp.y"
    { (yyval.d) = new importdec((yyvsp[(1) - (3)].pos), (yyvsp[(2) - (3)].ip)); ;}
    break;

  case 27:
#line 230 "camp.y"
    { (yyval.d) = new includedec((yyvsp[(1) - (3)].pos), (yyvsp[(2) - (3)].ps).sym); ;}
    break;

  case 28:
#line 232 "camp.y"
    { (yyval.d) = new includedec((yyvsp[(1) - (3)].pos), (string)*(yyvsp[(2) - (3)].ps).sym); ;}
    break;

  case 29:
#line 236 "camp.y"
    { (yyval.ip) = new idpair((yyvsp[(1) - (1)].ps).pos, (yyvsp[(1) - (1)].ps).sym); ;}
    break;

  case 30:
#line 238 "camp.y"
    { (yyval.ip) = new idpair((yyvsp[(1) - (3)].ps).pos, (yyvsp[(1) - (3)].ps).sym, (yyvsp[(2) - (3)].ps).sym , (yyvsp[(3) - (3)].ps).sym); ;}
    break;

  case 31:
#line 242 "camp.y"
    { (yyval.ipl) = new idpairlist(); (yyval.ipl)->add((yyvsp[(1) - (1)].ip)); ;}
    break;

  case 32:
#line 244 "camp.y"
    { (yyval.ipl) = (yyvsp[(1) - (3)].ipl); (yyval.ipl)->add((yyvsp[(3) - (3)].ip)); ;}
    break;

  case 33:
#line 248 "camp.y"
    { (yyval.ps) = (yyvsp[(1) - (1)].ps); ;}
    break;

  case 34:
#line 249 "camp.y"
    { (yyval.ps) = (yyvsp[(1) - (1)].ps); ;}
    break;

  case 35:
#line 253 "camp.y"
    { (yyval.ip) = new idpair((yyvsp[(1) - (1)].ps).pos, (yyvsp[(1) - (1)].ps).sym); ;}
    break;

  case 36:
#line 255 "camp.y"
    { (yyval.ip) = new idpair((yyvsp[(1) - (3)].ps).pos, (yyvsp[(1) - (3)].ps).sym, (yyvsp[(2) - (3)].ps).sym , (yyvsp[(3) - (3)].ps).sym); ;}
    break;

  case 37:
#line 259 "camp.y"
    { (yyval.ipl) = new idpairlist(); (yyval.ipl)->add((yyvsp[(1) - (1)].ip)); ;}
    break;

  case 38:
#line 261 "camp.y"
    { (yyval.ipl) = (yyvsp[(1) - (3)].ipl); (yyval.ipl)->add((yyvsp[(3) - (3)].ip)); ;}
    break;

  case 39:
#line 265 "camp.y"
    { (yyval.vd) = (yyvsp[(1) - (2)].vd); ;}
    break;

  case 40:
#line 269 "camp.y"
    { (yyval.vd) = new vardec((yyvsp[(1) - (2)].t)->getPos(), (yyvsp[(1) - (2)].t), (yyvsp[(2) - (2)].dil)); ;}
    break;

  case 41:
#line 273 "camp.y"
    { (yyval.t) = (yyvsp[(1) - (1)].t); ;}
    break;

  case 42:
#line 274 "camp.y"
    { (yyval.t) = new arrayTy((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].dim)); ;}
    break;

  case 43:
#line 278 "camp.y"
    { (yyval.t) = new nameTy((yyvsp[(1) - (1)].n)); ;}
    break;

  case 44:
#line 282 "camp.y"
    { (yyval.dim) = new dimensions((yyvsp[(1) - (2)].pos)); ;}
    break;

  case 45:
#line 283 "camp.y"
    { (yyval.dim) = (yyvsp[(1) - (3)].dim); (yyval.dim)->increase(); ;}
    break;

  case 46:
#line 287 "camp.y"
    { (yyval.elist) = new explist((yyvsp[(1) - (3)].pos)); (yyval.elist)->add((yyvsp[(2) - (3)].e)); ;}
    break;

  case 47:
#line 289 "camp.y"
    { (yyval.elist) = (yyvsp[(1) - (4)].elist); (yyval.elist)->add((yyvsp[(3) - (4)].e)); ;}
    break;

  case 48:
#line 293 "camp.y"
    { (yyval.dil) = new decidlist((yyvsp[(1) - (1)].di)->getPos()); (yyval.dil)->add((yyvsp[(1) - (1)].di)); ;}
    break;

  case 49:
#line 295 "camp.y"
    { (yyval.dil) = (yyvsp[(1) - (3)].dil); (yyval.dil)->add((yyvsp[(3) - (3)].di)); ;}
    break;

  case 50:
#line 299 "camp.y"
    { (yyval.di) = new decid((yyvsp[(1) - (1)].dis)->getPos(), (yyvsp[(1) - (1)].dis)); ;}
    break;

  case 51:
#line 301 "camp.y"
    { (yyval.di) = new decid((yyvsp[(1) - (3)].dis)->getPos(), (yyvsp[(1) - (3)].dis), (yyvsp[(3) - (3)].vi)); ;}
    break;

  case 52:
#line 305 "camp.y"
    { (yyval.dis) = new decidstart((yyvsp[(1) - (1)].ps).pos, (yyvsp[(1) - (1)].ps).sym); ;}
    break;

  case 53:
#line 306 "camp.y"
    { (yyval.dis) = new decidstart((yyvsp[(1) - (2)].ps).pos, (yyvsp[(1) - (2)].ps).sym, (yyvsp[(2) - (2)].dim)); ;}
    break;

  case 54:
#line 307 "camp.y"
    { (yyval.dis) = new fundecidstart((yyvsp[(1) - (3)].ps).pos, (yyvsp[(1) - (3)].ps).sym, 0,
                                            new formals((yyvsp[(2) - (3)].pos))); ;}
    break;

  case 55:
#line 310 "camp.y"
    { (yyval.dis) = new fundecidstart((yyvsp[(1) - (4)].ps).pos, (yyvsp[(1) - (4)].ps).sym, 0, (yyvsp[(3) - (4)].fls)); ;}
    break;

  case 56:
#line 314 "camp.y"
    { (yyval.vi) = (yyvsp[(1) - (1)].e); ;}
    break;

  case 57:
#line 315 "camp.y"
    { (yyval.vi) = (yyvsp[(1) - (1)].ai); ;}
    break;

  case 58:
#line 320 "camp.y"
    { (yyval.b) = (yyvsp[(2) - (3)].b); ;}
    break;

  case 59:
#line 324 "camp.y"
    { (yyval.ai) = new arrayinit((yyvsp[(1) - (2)].pos)); ;}
    break;

  case 60:
#line 326 "camp.y"
    { (yyval.ai) = new arrayinit((yyvsp[(1) - (4)].pos)); (yyval.ai)->addRest((yyvsp[(3) - (4)].vi)); ;}
    break;

  case 61:
#line 328 "camp.y"
    { (yyval.ai) = (yyvsp[(2) - (3)].ai); ;}
    break;

  case 62:
#line 330 "camp.y"
    { (yyval.ai) = (yyvsp[(2) - (5)].ai); (yyval.ai)->addRest((yyvsp[(4) - (5)].vi)); ;}
    break;

  case 63:
#line 334 "camp.y"
    { (yyval.ai) = new arrayinit((yyvsp[(1) - (1)].pos)); ;}
    break;

  case 64:
#line 335 "camp.y"
    { (yyval.ai) = (yyvsp[(1) - (1)].ai); ;}
    break;

  case 65:
#line 336 "camp.y"
    { (yyval.ai) = (yyvsp[(1) - (2)].ai); ;}
    break;

  case 66:
#line 340 "camp.y"
    { (yyval.ai) = new arrayinit((yyvsp[(1) - (1)].vi)->getPos());
		     (yyval.ai)->add((yyvsp[(1) - (1)].vi));;}
    break;

  case 67:
#line 343 "camp.y"
    { (yyval.ai) = (yyvsp[(1) - (3)].ai); (yyval.ai)->add((yyvsp[(3) - (3)].vi)); ;}
    break;

  case 68:
#line 347 "camp.y"
    { (yyval.fls) = (yyvsp[(1) - (1)].fls); ;}
    break;

  case 69:
#line 349 "camp.y"
    { (yyval.fls) = (yyvsp[(1) - (3)].fls); (yyval.fls)->addRest((yyvsp[(3) - (3)].fl)); ;}
    break;

  case 70:
#line 350 "camp.y"
    { (yyval.fls) = new formals((yyvsp[(1) - (2)].pos)); (yyval.fls)->addRest((yyvsp[(2) - (2)].fl)); ;}
    break;

  case 71:
#line 354 "camp.y"
    { (yyval.fls) = new formals((yyvsp[(1) - (1)].fl)->getPos()); (yyval.fls)->add((yyvsp[(1) - (1)].fl)); ;}
    break;

  case 72:
#line 356 "camp.y"
    { (yyval.fls) = (yyvsp[(1) - (3)].fls); (yyval.fls)->add((yyvsp[(3) - (3)].fl)); ;}
    break;

  case 73:
#line 360 "camp.y"
    { (yyval.boo) = true; ;}
    break;

  case 74:
#line 361 "camp.y"
    { (yyval.boo) = false; ;}
    break;

  case 75:
#line 366 "camp.y"
    { (yyval.fl) = new formal((yyvsp[(2) - (2)].t)->getPos(), (yyvsp[(2) - (2)].t), 0, 0, (yyvsp[(1) - (2)].boo)); ;}
    break;

  case 76:
#line 368 "camp.y"
    { (yyval.fl) = new formal((yyvsp[(2) - (3)].t)->getPos(), (yyvsp[(2) - (3)].t), (yyvsp[(3) - (3)].dis), 0, (yyvsp[(1) - (3)].boo)); ;}
    break;

  case 77:
#line 370 "camp.y"
    { (yyval.fl) = new formal((yyvsp[(2) - (5)].t)->getPos(), (yyvsp[(2) - (5)].t), (yyvsp[(3) - (5)].dis), (yyvsp[(5) - (5)].vi), (yyvsp[(1) - (5)].boo)); ;}
    break;

  case 78:
#line 375 "camp.y"
    { (yyval.d) = new fundec((yyvsp[(3) - (5)].pos), (yyvsp[(1) - (5)].t), (yyvsp[(2) - (5)].ps).sym, new formals((yyvsp[(3) - (5)].pos)), (yyvsp[(5) - (5)].s)); ;}
    break;

  case 79:
#line 377 "camp.y"
    { (yyval.d) = new fundec((yyvsp[(3) - (6)].pos), (yyvsp[(1) - (6)].t), (yyvsp[(2) - (6)].ps).sym, (yyvsp[(4) - (6)].fls), (yyvsp[(6) - (6)].s)); ;}
    break;

  case 80:
#line 381 "camp.y"
    { (yyval.d) = new recorddec((yyvsp[(1) - (3)].pos), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].b)); ;}
    break;

  case 81:
#line 382 "camp.y"
    { (yyval.d) = new typedec((yyvsp[(1) - (2)].pos), (yyvsp[(2) - (2)].vd)); ;}
    break;

  case 82:
#line 387 "camp.y"
    { (yyval.e) = new fieldExp((yyvsp[(2) - (3)].pos), (yyvsp[(1) - (3)].e), (yyvsp[(3) - (3)].ps).sym); ;}
    break;

  case 83:
#line 388 "camp.y"
    { (yyval.e) = new subscriptExp((yyvsp[(2) - (4)].pos),
                              new nameExp((yyvsp[(1) - (4)].n)->getPos(), (yyvsp[(1) - (4)].n)), (yyvsp[(3) - (4)].e)); ;}
    break;

  case 84:
#line 390 "camp.y"
    { (yyval.e) = new subscriptExp((yyvsp[(2) - (4)].pos), (yyvsp[(1) - (4)].e), (yyvsp[(3) - (4)].e)); ;}
    break;

  case 85:
#line 391 "camp.y"
    { (yyval.e) = new callExp((yyvsp[(2) - (3)].pos),
                                      new nameExp((yyvsp[(1) - (3)].n)->getPos(), (yyvsp[(1) - (3)].n)),
                                      new arglist()); ;}
    break;

  case 86:
#line 395 "camp.y"
    { (yyval.e) = new callExp((yyvsp[(2) - (4)].pos), 
                                      new nameExp((yyvsp[(1) - (4)].n)->getPos(), (yyvsp[(1) - (4)].n)),
                                      (yyvsp[(3) - (4)].alist)); ;}
    break;

  case 87:
#line 398 "camp.y"
    { (yyval.e) = new callExp((yyvsp[(2) - (3)].pos), (yyvsp[(1) - (3)].e), new arglist()); ;}
    break;

  case 88:
#line 400 "camp.y"
    { (yyval.e) = new callExp((yyvsp[(2) - (4)].pos), (yyvsp[(1) - (4)].e), (yyvsp[(3) - (4)].alist)); ;}
    break;

  case 89:
#line 402 "camp.y"
    { (yyval.e) = (yyvsp[(2) - (3)].e); ;}
    break;

  case 90:
#line 404 "camp.y"
    { (yyval.e) = new nameExp((yyvsp[(2) - (3)].n)->getPos(), (yyvsp[(2) - (3)].n)); ;}
    break;

  case 91:
#line 405 "camp.y"
    { (yyval.e) = new thisExp((yyvsp[(1) - (1)].pos)); ;}
    break;

  case 92:
#line 409 "camp.y"
    { (yyval.arg).name=0;      (yyval.arg).val=(yyvsp[(1) - (1)].e); ;}
    break;

  case 93:
#line 410 "camp.y"
    { (yyval.arg).name=(yyvsp[(1) - (3)].ps).sym; (yyval.arg).val=(yyvsp[(3) - (3)].e); ;}
    break;

  case 94:
#line 414 "camp.y"
    { (yyval.alist) = (yyvsp[(1) - (1)].alist); ;}
    break;

  case 95:
#line 416 "camp.y"
    { (yyval.alist) = (yyvsp[(1) - (3)].alist); (yyval.alist)->rest = (yyvsp[(3) - (3)].arg); ;}
    break;

  case 96:
#line 417 "camp.y"
    { (yyval.alist) = new arglist(); (yyval.alist)->rest = (yyvsp[(2) - (2)].arg); ;}
    break;

  case 97:
#line 421 "camp.y"
    { (yyval.alist) = new arglist(); (yyval.alist)->add((yyvsp[(1) - (1)].arg)); ;}
    break;

  case 98:
#line 423 "camp.y"
    { (yyval.alist) = (yyvsp[(1) - (3)].alist); (yyval.alist)->add((yyvsp[(3) - (3)].arg)); ;}
    break;

  case 99:
#line 428 "camp.y"
    { (yyval.e) = new nameExp((yyvsp[(1) - (1)].n)->getPos(), (yyvsp[(1) - (1)].n)); ;}
    break;

  case 100:
#line 429 "camp.y"
    { (yyval.e) = (yyvsp[(1) - (1)].e); ;}
    break;

  case 101:
#line 430 "camp.y"
    { (yyval.e) = (yyvsp[(1) - (1)].e); ;}
    break;

  case 102:
#line 431 "camp.y"
    { (yyval.e) = new stringExp((yyvsp[(1) - (1)].ps).pos, *(yyvsp[(1) - (1)].ps).sym); ;}
    break;

  case 103:
#line 433 "camp.y"
    { (yyval.e) = new scaleExp((yyvsp[(1) - (2)].e)->getPos(), (yyvsp[(1) - (2)].e), (yyvsp[(2) - (2)].e)); ;}
    break;

  case 104:
#line 435 "camp.y"
    { (yyval.e) = new castExp((yyvsp[(2) - (4)].n)->getPos(), new nameTy((yyvsp[(2) - (4)].n)), (yyvsp[(4) - (4)].e)); ;}
    break;

  case 105:
#line 437 "camp.y"
    { (yyval.e) = new castExp((yyvsp[(2) - (5)].n)->getPos(), new arrayTy((yyvsp[(2) - (5)].n), (yyvsp[(3) - (5)].dim)), (yyvsp[(5) - (5)].e)); ;}
    break;

  case 106:
#line 439 "camp.y"
    { (yyval.e) = new unaryExp((yyvsp[(1) - (2)].ps).pos, (yyvsp[(2) - (2)].e), (yyvsp[(1) - (2)].ps).sym); ;}
    break;

  case 107:
#line 441 "camp.y"
    { (yyval.e) = new unaryExp((yyvsp[(1) - (2)].ps).pos, (yyvsp[(2) - (2)].e), (yyvsp[(1) - (2)].ps).sym); ;}
    break;

  case 108:
#line 442 "camp.y"
    { (yyval.e) = new unaryExp((yyvsp[(1) - (2)].ps).pos, (yyvsp[(2) - (2)].e), (yyvsp[(1) - (2)].ps).sym); ;}
    break;

  case 109:
#line 443 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 110:
#line 444 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 111:
#line 445 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 112:
#line 446 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 113:
#line 447 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 114:
#line 448 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 115:
#line 449 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 116:
#line 450 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 117:
#line 451 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 118:
#line 452 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 119:
#line 453 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 120:
#line 454 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 121:
#line 455 "camp.y"
    { (yyval.e) = new andExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 122:
#line 456 "camp.y"
    { (yyval.e) = new orExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 123:
#line 457 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 124:
#line 458 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 125:
#line 459 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 126:
#line 460 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 127:
#line 461 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 128:
#line 463 "camp.y"
    { (yyval.e) = new newRecordExp((yyvsp[(1) - (2)].pos), (yyvsp[(2) - (2)].t)); ;}
    break;

  case 129:
#line 465 "camp.y"
    { (yyval.e) = new newArrayExp((yyvsp[(1) - (3)].pos), (yyvsp[(2) - (3)].t), (yyvsp[(3) - (3)].elist), 0, 0); ;}
    break;

  case 130:
#line 467 "camp.y"
    { (yyval.e) = new newArrayExp((yyvsp[(1) - (4)].pos), (yyvsp[(2) - (4)].t), (yyvsp[(3) - (4)].elist), (yyvsp[(4) - (4)].dim), 0); ;}
    break;

  case 131:
#line 469 "camp.y"
    { (yyval.e) = new newArrayExp((yyvsp[(1) - (3)].pos), (yyvsp[(2) - (3)].t), 0, (yyvsp[(3) - (3)].dim), 0); ;}
    break;

  case 132:
#line 471 "camp.y"
    { (yyval.e) = new newArrayExp((yyvsp[(1) - (4)].pos), (yyvsp[(2) - (4)].t), 0, (yyvsp[(3) - (4)].dim), (yyvsp[(4) - (4)].ai)); ;}
    break;

  case 133:
#line 473 "camp.y"
    { (yyval.e) = new newFunctionExp((yyvsp[(1) - (5)].pos), (yyvsp[(2) - (5)].t), new formals((yyvsp[(3) - (5)].pos)), (yyvsp[(5) - (5)].s)); ;}
    break;

  case 134:
#line 475 "camp.y"
    { (yyval.e) = new newFunctionExp((yyvsp[(1) - (6)].pos),
                                             new arrayTy((yyvsp[(2) - (6)].t)->getPos(), (yyvsp[(2) - (6)].t), (yyvsp[(3) - (6)].dim)),
                                             new formals((yyvsp[(4) - (6)].pos)),
                                             (yyvsp[(6) - (6)].s)); ;}
    break;

  case 135:
#line 480 "camp.y"
    { (yyval.e) = new newFunctionExp((yyvsp[(1) - (6)].pos), (yyvsp[(2) - (6)].t), (yyvsp[(4) - (6)].fls), (yyvsp[(6) - (6)].s)); ;}
    break;

  case 136:
#line 482 "camp.y"
    { (yyval.e) = new newFunctionExp((yyvsp[(1) - (7)].pos),
                                             new arrayTy((yyvsp[(2) - (7)].t)->getPos(), (yyvsp[(2) - (7)].t), (yyvsp[(3) - (7)].dim)),
                                             (yyvsp[(5) - (7)].fls),
                                             (yyvsp[(7) - (7)].s)); ;}
    break;

  case 137:
#line 487 "camp.y"
    { (yyval.e) = new conditionalExp((yyvsp[(2) - (5)].pos), (yyvsp[(1) - (5)].e), (yyvsp[(3) - (5)].e), (yyvsp[(5) - (5)].e)); ;}
    break;

  case 138:
#line 488 "camp.y"
    { (yyval.e) = new assignExp((yyvsp[(2) - (3)].pos), (yyvsp[(1) - (3)].e), (yyvsp[(3) - (3)].e)); ;}
    break;

  case 139:
#line 491 "camp.y"
    { (yyval.e) = new pairExp((yyvsp[(1) - (5)].pos), (yyvsp[(2) - (5)].e), (yyvsp[(4) - (5)].e)); ;}
    break;

  case 140:
#line 493 "camp.y"
    { (yyval.e) = new tripleExp((yyvsp[(1) - (7)].pos), (yyvsp[(2) - (7)].e), (yyvsp[(4) - (7)].e), (yyvsp[(6) - (7)].e)); ;}
    break;

  case 141:
#line 495 "camp.y"
    { (yyval.e) = new transformExp((yyvsp[(1) - (13)].pos), (yyvsp[(2) - (13)].e), (yyvsp[(4) - (13)].e), (yyvsp[(6) - (13)].e), (yyvsp[(8) - (13)].e), (yyvsp[(10) - (13)].e), (yyvsp[(12) - (13)].e)); ;}
    break;

  case 142:
#line 497 "camp.y"
    { (yyvsp[(2) - (3)].j)->pushFront((yyvsp[(1) - (3)].e)); (yyvsp[(2) - (3)].j)->pushBack((yyvsp[(3) - (3)].e)); (yyval.e) = (yyvsp[(2) - (3)].j); ;}
    break;

  case 143:
#line 499 "camp.y"
    { (yyvsp[(2) - (2)].se)->setSide(camp::OUT);
                     joinExp *jexp =
                         new joinExp((yyvsp[(2) - (2)].se)->getPos(), symbol::trans(".."));
                     (yyval.e)=jexp;
                     jexp->pushBack((yyvsp[(1) - (2)].e)); jexp->pushBack((yyvsp[(2) - (2)].se)); ;}
    break;

  case 144:
#line 505 "camp.y"
    { (yyval.e) = new prefixExp((yyvsp[(1) - (2)].ps).pos, (yyvsp[(2) - (2)].e), symbol::trans("+")); ;}
    break;

  case 145:
#line 507 "camp.y"
    { (yyval.e) = new prefixExp((yyvsp[(1) - (2)].ps).pos, (yyvsp[(2) - (2)].e), symbol::trans("-")); ;}
    break;

  case 146:
#line 510 "camp.y"
    { (yyval.e) = new postfixExp((yyvsp[(2) - (2)].ps).pos, (yyvsp[(1) - (2)].e), symbol::trans("+")); ;}
    break;

  case 147:
#line 511 "camp.y"
    { (yyval.e) = new selfExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 148:
#line 513 "camp.y"
    { (yyval.e) = new selfExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 149:
#line 514 "camp.y"
    { (yyval.e) = new selfExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 150:
#line 515 "camp.y"
    { (yyval.e) = new selfExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 151:
#line 516 "camp.y"
    { (yyval.e) = new selfExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 152:
#line 518 "camp.y"
    { (yyval.e) = new selfExp((yyvsp[(2) - (3)].ps).pos, (yyvsp[(1) - (3)].e), (yyvsp[(2) - (3)].ps).sym, (yyvsp[(3) - (3)].e)); ;}
    break;

  case 153:
#line 520 "camp.y"
    { (yyval.e) = new quoteExp((yyvsp[(1) - (4)].pos), (yyvsp[(3) - (4)].b)); ;}
    break;

  case 154:
#line 526 "camp.y"
    { (yyval.j) = new joinExp((yyvsp[(1) - (1)].ps).pos,(yyvsp[(1) - (1)].ps).sym); ;}
    break;

  case 155:
#line 528 "camp.y"
    { (yyval.j) = (yyvsp[(1) - (1)].j); ;}
    break;

  case 156:
#line 530 "camp.y"
    { (yyvsp[(1) - (2)].se)->setSide(camp::OUT);
                     (yyval.j) = (yyvsp[(2) - (2)].j); (yyval.j)->pushFront((yyvsp[(1) - (2)].se)); ;}
    break;

  case 157:
#line 533 "camp.y"
    { (yyvsp[(2) - (2)].se)->setSide(camp::IN);
                     (yyval.j) = (yyvsp[(1) - (2)].j); (yyval.j)->pushBack((yyvsp[(2) - (2)].se)); ;}
    break;

  case 158:
#line 536 "camp.y"
    { (yyvsp[(1) - (3)].se)->setSide(camp::OUT); (yyvsp[(3) - (3)].se)->setSide(camp::IN);
                     (yyval.j) = (yyvsp[(2) - (3)].j); (yyval.j)->pushFront((yyvsp[(1) - (3)].se)); (yyval.j)->pushBack((yyvsp[(3) - (3)].se)); ;}
    break;

  case 159:
#line 541 "camp.y"
    { (yyval.se) = new specExp((yyvsp[(2) - (4)].ps).pos, (yyvsp[(2) - (4)].ps).sym, (yyvsp[(3) - (4)].e)); ;}
    break;

  case 160:
#line 542 "camp.y"
    { (yyval.se) = new specExp((yyvsp[(1) - (3)].pos), symbol::opTrans("spec"), (yyvsp[(2) - (3)].e)); ;}
    break;

  case 161:
#line 544 "camp.y"
    { (yyval.se) = new specExp((yyvsp[(1) - (5)].pos), symbol::opTrans("spec"),
				      new pairExp((yyvsp[(3) - (5)].pos), (yyvsp[(2) - (5)].e), (yyvsp[(4) - (5)].e))); ;}
    break;

  case 162:
#line 547 "camp.y"
    { (yyval.se) = new specExp((yyvsp[(1) - (7)].pos), symbol::opTrans("spec"),
				      new tripleExp((yyvsp[(3) - (7)].pos), (yyvsp[(2) - (7)].e), (yyvsp[(4) - (7)].e), (yyvsp[(6) - (7)].e))); ;}
    break;

  case 163:
#line 552 "camp.y"
    { (yyval.j) = new joinExp((yyvsp[(1) - (1)].ps).pos, (yyvsp[(1) - (1)].ps).sym); ;}
    break;

  case 164:
#line 554 "camp.y"
    { (yyval.j) = new joinExp((yyvsp[(1) - (3)].ps).pos, (yyvsp[(1) - (3)].ps).sym); (yyval.j)->pushBack((yyvsp[(2) - (3)].e)); ;}
    break;

  case 165:
#line 556 "camp.y"
    { (yyval.j) = new joinExp((yyvsp[(1) - (3)].ps).pos, (yyvsp[(1) - (3)].ps).sym); (yyval.j)->pushBack((yyvsp[(2) - (3)].e)); ;}
    break;

  case 166:
#line 557 "camp.y"
    { (yyval.j) = new joinExp((yyvsp[(1) - (1)].ps).pos, (yyvsp[(1) - (1)].ps).sym); ;}
    break;

  case 167:
#line 558 "camp.y"
    { (yyval.j) = new joinExp((yyvsp[(1) - (1)].ps).pos, (yyvsp[(1) - (1)].ps).sym); ;}
    break;

  case 168:
#line 562 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(1) - (2)].ps).pos, (yyvsp[(2) - (2)].e), (yyvsp[(1) - (2)].ps).sym,
                              new booleanExp((yyvsp[(1) - (2)].ps).pos, false)); ;}
    break;

  case 169:
#line 565 "camp.y"
    { (yyval.e) = new ternaryExp((yyvsp[(1) - (4)].ps).pos, (yyvsp[(2) - (4)].e), (yyvsp[(1) - (4)].ps).sym, (yyvsp[(4) - (4)].e),
                              new booleanExp((yyvsp[(1) - (4)].ps).pos, false)); ;}
    break;

  case 170:
#line 568 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(1) - (3)].ps).pos, (yyvsp[(3) - (3)].e), (yyvsp[(1) - (3)].ps).sym,
                              new booleanExp((yyvsp[(2) - (3)].ps).pos, true)); ;}
    break;

  case 171:
#line 571 "camp.y"
    { (yyval.e) = new ternaryExp((yyvsp[(1) - (5)].ps).pos, (yyvsp[(3) - (5)].e), (yyvsp[(1) - (5)].ps).sym, (yyvsp[(5) - (5)].e),
                              new booleanExp((yyvsp[(2) - (5)].ps).pos, true)); ;}
    break;

  case 172:
#line 576 "camp.y"
    { (yyval.e) = new unaryExp((yyvsp[(1) - (2)].ps).pos, (yyvsp[(2) - (2)].e), (yyvsp[(1) - (2)].ps).sym); ;}
    break;

  case 173:
#line 578 "camp.y"
    { (yyval.e) = new binaryExp((yyvsp[(1) - (4)].ps).pos, (yyvsp[(2) - (4)].e), (yyvsp[(1) - (4)].ps).sym, (yyvsp[(4) - (4)].e)); ;}
    break;

  case 174:
#line 582 "camp.y"
    { (yyval.s) = new emptyStm((yyvsp[(1) - (1)].pos)); ;}
    break;

  case 175:
#line 583 "camp.y"
    { (yyval.s) = (yyvsp[(1) - (1)].s); ;}
    break;

  case 176:
#line 584 "camp.y"
    { (yyval.s) = (yyvsp[(1) - (2)].s); ;}
    break;

  case 177:
#line 586 "camp.y"
    { (yyval.s) = new ifStm((yyvsp[(1) - (5)].pos), (yyvsp[(3) - (5)].e), (yyvsp[(5) - (5)].s)); ;}
    break;

  case 178:
#line 588 "camp.y"
    { (yyval.s) = new ifStm((yyvsp[(1) - (7)].pos), (yyvsp[(3) - (7)].e), (yyvsp[(5) - (7)].s), (yyvsp[(7) - (7)].s)); ;}
    break;

  case 179:
#line 590 "camp.y"
    { (yyval.s) = new whileStm((yyvsp[(1) - (5)].pos), (yyvsp[(3) - (5)].e), (yyvsp[(5) - (5)].s)); ;}
    break;

  case 180:
#line 592 "camp.y"
    { (yyval.s) = new doStm((yyvsp[(1) - (7)].pos), (yyvsp[(2) - (7)].s), (yyvsp[(5) - (7)].e)); ;}
    break;

  case 181:
#line 594 "camp.y"
    { (yyval.s) = new forStm((yyvsp[(1) - (9)].pos), (yyvsp[(3) - (9)].run), (yyvsp[(5) - (9)].e), (yyvsp[(7) - (9)].sel), (yyvsp[(9) - (9)].s)); ;}
    break;

  case 182:
#line 596 "camp.y"
    { (yyval.s) = new extendedForStm((yyvsp[(1) - (8)].pos), (yyvsp[(3) - (8)].t), (yyvsp[(4) - (8)].ps).sym, (yyvsp[(6) - (8)].e), (yyvsp[(8) - (8)].s)); ;}
    break;

  case 183:
#line 597 "camp.y"
    { (yyval.s) = new breakStm((yyvsp[(1) - (2)].pos)); ;}
    break;

  case 184:
#line 598 "camp.y"
    { (yyval.s) = new continueStm((yyvsp[(1) - (2)].pos)); ;}
    break;

  case 185:
#line 599 "camp.y"
    { (yyval.s) = new returnStm((yyvsp[(1) - (2)].pos)); ;}
    break;

  case 186:
#line 600 "camp.y"
    { (yyval.s) = new returnStm((yyvsp[(1) - (3)].pos), (yyvsp[(2) - (3)].e)); ;}
    break;

  case 187:
#line 604 "camp.y"
    { (yyval.s) = new expStm((yyvsp[(1) - (1)].e)->getPos(), (yyvsp[(1) - (1)].e)); ;}
    break;

  case 188:
#line 608 "camp.y"
    { (yyval.s) = new blockStm((yyvsp[(1) - (1)].b)->getPos(), (yyvsp[(1) - (1)].b)); ;}
    break;

  case 189:
#line 612 "camp.y"
    { (yyval.run) = 0; ;}
    break;

  case 190:
#line 613 "camp.y"
    { (yyval.run) = (yyvsp[(1) - (1)].sel); ;}
    break;

  case 191:
#line 614 "camp.y"
    { (yyval.run) = (yyvsp[(1) - (1)].vd); ;}
    break;

  case 192:
#line 618 "camp.y"
    { (yyval.e) = 0; ;}
    break;

  case 193:
#line 619 "camp.y"
    { (yyval.e) = (yyvsp[(1) - (1)].e); ;}
    break;

  case 194:
#line 623 "camp.y"
    { (yyval.sel) = 0; ;}
    break;

  case 195:
#line 624 "camp.y"
    { (yyval.sel) = (yyvsp[(1) - (1)].sel); ;}
    break;

  case 196:
#line 628 "camp.y"
    { (yyval.sel) = new stmExpList((yyvsp[(1) - (1)].s)->getPos()); (yyval.sel)->add((yyvsp[(1) - (1)].s)); ;}
    break;

  case 197:
#line 630 "camp.y"
    { (yyval.sel) = (yyvsp[(1) - (3)].sel); (yyval.sel)->add((yyvsp[(3) - (3)].s)); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3248 "camp.tab.c"
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



