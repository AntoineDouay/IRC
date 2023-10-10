
#include "../../include/Commands.hpp"

void	Commands::PASS()
{
	if (_parameters.size() == 0)
		return reply (ERR_NEEDMOREPARAMS, _command.c_str());
	for (std::vector<std::string>::iterator it  = _parameters.begin(); it != _parameters.end(); it++)
		std::cout << _parameters << std::endl;
	// std::cout << _parameters[0] << std::endl;
	// std::cout << _serv->getPassword() << std::endl;

	if (_parameters[0] == _serv->getPassword())
		_user->setStatus(1);
	
	return ;
}