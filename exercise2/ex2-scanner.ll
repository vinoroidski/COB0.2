/***********************
 * Example of C++ in Bison (yacc) 
 * Compare Bison Manual, Section 10.1.6 A Complete C++ Example
 * https://www.gnu.org/software/bison/manual/html_node/A-Complete-C_002b_002b-Example.html
 * The Makefile has been simplified radically, but otherwise
 * everything here comes from the Bison source code (see also).
 * (This comment added by Prof. R. C. Moore, fbi.h-da.de)
 *
 * This is the (f)lex file, i.e. token definitions
 * See also ex2-parser.yy for the parser (grammar)
 * (yacc/bison input).
 *
 ***********************/

%{ /* -*- C++ -*- */
# include <cstdlib>
# include <cerrno>
# include <climits>
# include <string>
# include "ex2-driver.hh"
# include "ex2-parser.hh"

/* Work around an incompatibility in flex (at least versions
   2.5.31 through 2.5.33): it generates code that does
   not conform to C89.  See Debian bug 333231
   <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.  */
# undef yywrap
# define yywrap() 1

/* By default yylex returns int, we use token_type.
   Unfortunately yyterminate by default returns 0, which is
   not of token_type.  */
#define yyterminate() return token::END
%}

%option noyywrap nounput batch debug

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
double [0-9]+(".")+[0-9]+
blank [ \t]


%{
# define YY_USER_ACTION  yylloc->columns (yyleng);
%}

%%
%{
  yylloc->step ();
%}
{blank}+   yylloc->step ();
[\n]+      yylloc->lines (yyleng); yylloc->step ();

%{
  typedef yy::ex2xx_parser::token token;
%}
	/* Convert ints to the actual type of tokens.  */

	/* Operators! First, single character operators +, -, * and /
         * Then one operator with two characters := (assignment)
         */
[-+*/]   return yy::ex2xx_parser::token_type (yytext[0]);


":="     return token::ASSIGN;
"{"     return token::LEFTCURLY;



	/* Numbers */
{int}    {
           errno = 0;
           long n = strtol (yytext, NULL, 10);
           if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
             driver.error (*yylloc, "integer is out of range");
           yylval->ival = n;
           return token::NUMBER;
         }


	/* Id's (Names) */
{id}     {
           yylval->sval = new std::string (yytext);
           return token::ID;
         }


	/* Errors (fall through, default) */
.        driver.error (*yylloc, "invalid character");
%%


void
ex2xx_driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      error (std::string ("cannot open ") + file);
      exit (1);
    }
}



void
ex2xx_driver::scan_end ()
{
  fclose (yyin);
}

