#include "../../include/Commands.hpp"
#include <ostream>

void Commands::KICK() {
	for (std::vector<std::string>::iterator it  = _parameters.begin(); it != _parameters.end(); it++) // TODO only for test
		std::cout << "1: " << *it << std::endl;
}