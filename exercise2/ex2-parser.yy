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
%{
#include <string.h>
%}
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
  bool			bval;
  std::string *sval;
};

%code {
# include "ex2-driver.hh"
}

%token		END	0 "end of file"
%token		ASSIGN			":="
%token		ASSIGN2			"="
%token		COMMA			","
%token		SEMICOLON		";"
%token		FUNC			"func"
%token		MAIN			"main"
%token		VAR				"var"
%token		TYPE			"int"
%token		RELOP			"<"
%token		INCR			"++"
%token		LEFTBRACKET		"("
%token		RIGHTBRACKET	")"
%token		LEFTCURLY		"{"
%token		RIGHTCURLY		"}"
%token		IF				"if"
%token		ELSE			"else"
%token		FOR				"for"
%token		<sval>	ID 		"identifier"
%token		<ival>	NUMBER  "number"
%token		<dval>	DOUBLE	"Double"
%type		<dval>	Const
%type		<dval>	Value
%type		<dval>	Exp
%type		<ival>	Assignment

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

%left RELOP;
%left '+' '-';
%left '*' '/';
%start Program ;

Program : FUNC MAIN LEFTBRACKET RIGHTBRACKET Block ;

Block :   LEFTCURLY Statement RIGHTCURLY ;
		
Statement:	  Var_Block
			| If_Statement 
			| Var_Block Statement 
			| If_Statement Statement 
			| Assignment
			| Assignment Statement
			| For_Statement ;
			
Var_Block :	  VAR Id_List TYPE
			| VAR Id_List TYPE ASSIGN2 Value_List ;
	
If_Statement: 	  IF LEFTBRACKET Exp RIGHTBRACKET Block ELSE Block
				| IF LEFTBRACKET Exp RIGHTBRACKET Block ;
				
For_Statement: FOR Assignment SEMICOLON ID RELOP Value SEMICOLON ID INCR Block ;
		
Id_List:	  ID
			| ID COMMA Id_List ;
			
Value_List:	  Exp
			| Exp COMMA Value_List ;
	
Exp:  Exp '+' Exp { $$ = $1 + $3; }
	| Exp '-' Exp { $$ = $1 + $3; }
	| Exp '*' Exp { $$ = $1 + $3; }
	| Exp '/' Exp { $$ = $1 + $3; }
	| Exp RELOP Exp
	| LEFTBRACKET Exp RIGHTBRACKET { $$ = $2; }
	| Value { $$ = $1; };
	
Value:	ID { $$ = driver.variables[*$1]; delete $1; }
	  | Const ;
	    
Const: NUMBER { $$ = $1; }
	 | DOUBLE { $$ = $1; } ;

Assignment:	ID ASSIGN Exp { driver.variables[*$1] = $3; $$ = $3;} ;

%%

void
yy::ex2xx_parser::error (const yy::ex2xx_parser::location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
