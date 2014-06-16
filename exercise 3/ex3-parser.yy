/***********************
 * Example of C++ in Bison (yacc)
 * Compare Bison Manual, Section 10.1.6 A Complete C++ Example
 * https://www.gnu.org/software/bison/manual/html_node/A-Complete-C_002b_002b-Example.html
 * The Makefile has been simplified radically, but otherwise
 * everything here comes from the Bison source code (see also).
 * (This comment added by Prof. R. C. Moore, fbi.h-da.de)
 *
 * This is the yacc (bison) file, i.e. grammar file.
 * See also ex3-scanner.ll for the lexical scanner 
 * (flex input).
 *
 ***********************/
%{
#include <string>
#include <vector>


std::vector<std::string> vId;
std::vector<double> vVal;

%}
%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "2.5"
%defines
%define parser_class_name "ex3xx_parser"

%code requires {
#include "BinaryExprAST.h"
#include "NumberExprAST.h"
#include "Root.h"
class ex3xx_driver;
}

// The parsing context.
%parse-param { ex3xx_driver& driver }
%lex-param   { ex3xx_driver& driver }

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
  int           ival;
  double	dval;
  bool		bval;
  std::string *sval;
  ExprAST *exp;
  BinaryExprAST *bExp;
  NumberExprAST *nExp;
  Root* root;
};

%code {
# include "ex3-driver.hh"
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
%token		RETURN			"return"
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
%type		<nExp>	Const
%type		<nExp>	Value
//%type		<sval>	Id_List
//%type		<dval>	Value_List
%type		<exp>	Exp
//%type		<ival>	Assignment
//%type		<sval>	Param_List
//%type		<sval>	Param
%type		<root> Program


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

/*Program :	  FUNC ID LEFTBRACKET Param_List  
				{ 
				
				for(int i = 0; i < vId.size(); i++){
					if(i < vVal.size())
						driver.variables[vId[i]] = vVal[i];
					else
						driver.variables[vId[i]];
				}
				vId.clear();
				vVal.clear();
				
				} 	
				RIGHTBRACKET TYPE Block Main 
			| Main ;
			
Main:	FUNC MAIN LEFTBRACKET RIGHTBRACKET Block ;

Param_List:	  Param { $$ = $1; vId.push_back(*$1); } 
			| Param COMMA { vId.push_back(*$1); } Param_List ;
			
Param:	  ID TYPE ;

Block :   LEFTCURLY Statement RIGHTCURLY 
		| LEFTCURLY Statement_Func RIGHTCURLY;
		
Statement:	  Var_Block
			| If_Statement 
			| Var_Block Statement 
			| If_Statement Statement 
			| Assignment
			| Assignment Statement
			| For_Statement ;
			
Statement_Func:	  Statement RETURN Exp 
				| RETURN Exp ;
			
Var_Block :	  VAR Id_List TYPE
			| VAR Id_List TYPE ASSIGN2 Value_List { 
				for(int i = 0; i < vId.size(); i++){
					if(i < vVal.size())
						driver.variables[vId[i]] = vVal[i];
					else
						driver.variables[vId[i]];
				}
				vId.clear();
				vVal.clear();
			};
	
If_Statement: 	  IF LEFTBRACKET Exp RIGHTBRACKET Block ELSE Block
				| IF LEFTBRACKET Exp RIGHTBRACKET Block ;
				
For_Statement: FOR Assignment SEMICOLON IDProgram RELOP Value SEMICOLON ID INCR Block ;
		
Id_List:	  ID { $$ = $1; vId.push_back(*$1); }
			| ID COMMA { vId.push_back(*$1); } Id_List ;
			
Value_List:	  Exp { $$ = $1; vVal.push_back($1); }
			| Exp COMMA { vVal.push_back($1); } Value_List ;
	*/

Program: Exp { Root* root = new Root(); root->setLHS($1); root->print(); $$ = root; };

Exp:  Exp '+' Exp { /*$$ = $1 + $3;*/ $$ = new BinaryExprAST("+", $1, $3); }
	| Exp '-' Exp { $$ = new BinaryExprAST("-", $1, $3); }
	| Exp '*' Exp { $$ = new BinaryExprAST("*", $1, $3); }
	| Exp '/' Exp { $$ = new BinaryExprAST("/", $1, $3); }
	//| Exp RELOP Exp
	//| LEFTBRACKET Exp RIGHTBRACKET { $$ = $2; }
	| Value { $$ = $1; }
	
Value:	//ID { $$ = driver.variables[*$1]; delete $1; }
	Const ;
	    
Const: NUMBER { $$ = new NumberExprAST($1); } ;
       | DOUBLE { /*$$ = $1;*/ $$ = new NumberExprAST($1); };

//Assignment:	ID ASSIGN Exp { driver.variables[*$1] = $3; $$ = $3;} ;
 
%%

void
yy::ex3xx_parser::error (const yy::ex3xx_parser::location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
