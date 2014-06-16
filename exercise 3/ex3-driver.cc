#include "ex3-driver.hh"
#include "ex3-parser.hh"

ex3xx_driver::ex3xx_driver ()
  : trace_scanning (false), trace_parsing (false)
{
  //variables["one"] = 1;
  //variables["two"] = 2;
}

ex3xx_driver::~ex3xx_driver ()
{
}

int
ex3xx_driver::parse (const std::string &f)
{
  file = f;
  scan_begin ();
  yy::ex3xx_parser parser (*this);
  parser.set_debug_level (trace_parsing);
  int res = parser.parse ();
  scan_end ();
  return res;
}

void
ex3xx_driver::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void
ex3xx_driver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}
