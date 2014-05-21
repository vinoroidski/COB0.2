
#ifndef EX2XX_DRIVER_HH
# define EX2XX_DRIVER_HH
# include <string>
# include <map>
# include <vector>
# include "ex2-parser.hh"

// Tell Flex the lexer's prototype ...
# define YY_DECL                                        \
  yy::ex2xx_parser::token_type                         \
  yylex (yy::ex2xx_parser::semantic_type* yylval,      \
         yy::ex2xx_parser::location_type* yylloc,      \
         ex2xx_driver& driver)
// ... and declare it for the parser's sake.
YY_DECL;

// Conducting the whole scanning and parsing of ex2.
class ex2xx_driver
{
public:
  ex2xx_driver ();
  virtual ~ex2xx_driver ();

  std::map<std::string, int> variables;

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
#endif // ! EX2XX_DRIVER_HH
