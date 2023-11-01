
#include "../../include/Commands.hpp"

void	Commands::PASS()
{
	if (_parameters.size() == 0)
		return reply (ERR_NEEDMOREPARAMS, _command.c_str());
	if (_user->getStatus() != NO_PASSWORD)
		return reply (ERR_ALREADYREGISTERED);
	// std::cout << _parameters[0] << std::endl;
	// std::cout << _serv->getPassword() << std::endl;

	if (_parameters[0] == _serv->getPassword())
		_user->setStatus(1);
	else
		_user->setStatus(3);
	
	return ;
}