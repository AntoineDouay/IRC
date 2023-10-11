
#include "../../include/Commands.hpp"

void	Commands::JOIN()
{
	if (_parameters.size() == 0)
		return reply (ERR_NEEDMOREPARAMS, _command.c_str());
	for (std::vector<std::string>::iterator it  = _parameters.begin(); it != _parameters.end(); it++)
		std::cout << *it << std::endl;
	_serv->createChannel(_parameters[0], _user[0], NULL);

	if (_parameters[0] == _serv->getPassword())
		_user->setStatus(1);
	
	return ;
}