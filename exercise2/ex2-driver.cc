#include "ex2-driver.hh"
#include "ex2-parser.hh"

ex2xx_driver::ex2xx_driver ()
  : trace_scanning (false), trace_parsing (false)
{
  //variables["one"] = 1;
  //variables["two"] = 2;
}

ex2xx_driver::~ex2xx_driver ()
{
}

int
ex2xx_driver::parse (const std::string &f)
{
  file = f;
  scan_begin ();
  yy::ex2xx_parser parser (*this);
  parser.set_debug_level (trace_parsing);
  int res = parser.parse ();
  scan_end ();
  return res;
}

void
ex2xx_driver::error (const yy::location& l, const std::string& m)
{
  std::cerr << l << ": " << m << std::endl;
}

void
ex2xx_driver::error (const std::string& m)
{
  std::cerr << m << std::endl;
}
