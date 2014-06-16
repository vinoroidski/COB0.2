
#ifndef EX3XX_DRIVER_HH
# define EX3XX_DRIVER_HH
# include <string>
# include <map>
# include <vector>
# include <list>
# include "ex3-parser.hh"
# include "ExprAST.h"

// Tell Flex the lexer's prototype ...
# define YY_DECL                                        \
  yy::ex3xx_parser::token_type                         \
  yylex (yy::ex3xx_parser::semantic_type* yylval,      \
         yy::ex3xx_parser::location_type* yylloc,      \
         ex3xx_driver& driver)
// ... and declare it for the parser's sake.
YY_DECL;

// Conducting the whole scanning and parsing of ex3.
class ex3xx_driver
{
public:
  ex3xx_driver ();
  virtual ~ex3xx_driver ();

  std::map<std::string, double> variables;
  
  
 // std::list<ExprAST*> elements;

  int result;

  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;

  // Run the parser on file F.
  // Return 0 on success.
  int parse (const std::string& f);
  // The name of the file being parsed.
  // Used later to pass the file name to the location tracker.
  std::string file;
  // Whether parser traces should be generated.
  bool trace_parsing;

  // Error handling.
  void error (const yy::location& l, const std::string& m);
  void error (const std::string& m);
};
#endif // ! EX3XX_DRIVER_HH
