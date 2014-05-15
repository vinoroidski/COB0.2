
#include <iostream>
#include "ex2-driver.hh"


int
main (int argc, char *argv[])
{
  ex2xx_driver driver;
  for (int i = 1; i < argc; ++i)
    if (argv[i] == std::string ("-p"))
      driver.trace_parsing = true;
    else if (argv[i] == std::string ("-s"))
      driver.trace_scanning = true;
    else if (!driver.parse (argv[i])){
		std::cout <<"RESULT: "<< driver.result << std::endl;
     }
}

