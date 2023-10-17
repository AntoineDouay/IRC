
#include "../../include/Commands.hpp"

void	Commands::USER()
{
	if (_parameters.size() == 0)
		return reply (ERR_NEEDMOREPARAMS);
	if (_user->getStatus() != REGISTER)
		return reply (ERR_ALREADYREGISTERED);
	
	_user->setUsername(_parameters[0]);
	if (_user->getNickname() != "" && _user->getStatus() != NO_PASSWORD && _user->getStatus() != ONLINE)
	{
		reply(RPL_WELCOME, _user->getNickname().c_str(), _user->getUsername().c_str(), _user->getHostName().c_str());
		_user->setStatus(2);
	}
}