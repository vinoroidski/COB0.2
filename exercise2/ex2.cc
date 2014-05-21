
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
		//std::cout <<"RESULT: "<< driver.result << std::endl;
		
		std::map<std::string, int>::iterator it;
		std::cout<<"---VARIABLES---"<<std::endl;
		
		for(it = driver.variables.begin(); it != driver.variables.end(); ++it){
			std::cout<<it->first;
			std::cout<<"		";
			std::cout<<it->second<<std::endl;
			}
     }
}

