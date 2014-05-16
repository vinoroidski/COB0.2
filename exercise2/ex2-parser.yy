/***********************
 * Example of C++ in Bison (yacc)
 * Compare Bison Manual, Section 10.1.6 A Complete C++ Example
 * https://www.gnu.org/software/bison/manual/html_node/A-Complete-C_002b_002b-Example.html
 * The Makefile has been simplified radically, but otherwise
 * everything here comes from the Bison source code (see also).
 * (This comment added by Prof. R. C. Moore, fbi.h-da.de)
 *
 * This is the yacc (bison) file, i.e. grammar file.
 * See also ex2-scanner.ll for the lexical scanner 
 * (flex input).
 *
 ***********************/

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "2.5"
%defines
%define parser_class_name "ex2xx_parser"

%code requires {
# include <string>
class ex2xx_driver;
}

// The parsing context.
%parse-param { ex2xx_driver& driver }
%lex-param   { ex2xx_driver& driver }

%locations
%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &driver.file;
};

%debug
%error-verbose

// Symbols.
// 
// Compare Bison Manual
// Section 3.8.4 The Collection of Value Types
// https://www.gnu.org/software/bison/manual/html_node/Union-Decl.html
%union
{
  int          ival;
  double		dval;
  std::string *sval;
};

%code {
# include "ex2-driver.hh"
}

%token		END	0 "end of file"
%token		ASSIGN	":="
//%token		SUBADD	'+' '-'	// NEW
//%token		MULDIV	'*' '/'	// NEW
%token	<sval>	ID "identifier"
%token	<ival>	NUMBER     "number"
%token	<dval>	DOUBLE     "Double"
%type	<ival>	assignment
%type	<dval>	exp
%type	<dval>	Const
%type	<dval>	Value
%token		LEFTBRACKET	"("
%token		RIGHTBRACKET	")"
%token		LEFTCURLY	"{"
%token		RIGHTCURLY	"}"

// Printer Macro is used for tracing the parser,
// Compare Bison Manual
// Section 3.8.8 Printing Semantic Values
%printer    { debug_stream () << *$$; } "identifier"

// Destructor Macro is used with error recovery
// Compare Bison Manual
// Section 3.8.7 Freeing Discarded Symbols
%destructor { delete $$; } "identifier"

%printer    { debug_stream () << $$; } <ival>

%%
%start unit;
unit: assignment { driver.result = $1; } ;


%left '+' '-';
%left '*' '/';
%left '(' ')';
assignment:	ID ASSIGN exp { driver.variables[*$1] = $3; 
// The problem was here, we didnt return the value of $3 to assignment
$$ = $3;};
// *******************************************************************

exp:  exp '+' exp { $$ = $1 + $3; }
	| exp '-' exp { $$ = $1 - $3; }
	| exp '*' exp { $$ = $1 * $3; }
	| exp '/' exp { $$ = $1 / $3; }
	| Value
	| LEFTBRACKET exp { $$ = $2; }
	| Value RIGHTBRACKET { $$ = $1; }
	| Value RIGHTBRACKET RIGHTBRACKET;
	| Value RIGHTBRACKET '+' exp;
	| Value RIGHTBRACKET '-' exp;
	| Value RIGHTBRACKET '*' exp;
	| Value RIGHTBRACKET '/' exp;
	| RIGHTBRACKET;

Value:	ID { $$ = driver.variables[*$1]; delete $1; }
	  | Const ;
	  
Const: NUMBER { $$ = $1; }
	 | DOUBLE { $$ = $1; } ;
   
%%

void
yy::ex2xx_parser::error (const yy::ex2xx_parser::location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
