
#include "../../include/Commands.hpp"

void	Commands::NICK()
{
	if (_parameters.size() == 0)
		return reply (ERR_NONICKNAMEGIVEN);

	std::vector<User *> u = _serv->getUsers();

	for (size_t i = 0; i < u.size(); i++)
		if (_parameters[0] == u[i]->getNickname())
			return reply (ERR_NICKNAMEINUSE, _parameters[0].c_str());

	_user->setNickname(_parameters[0]);
	if (_user->getUsername() != "" && _user->getStatus() != NO_PASSWORD)
	{
		reply(RPL_WELCOME, _user->getNickname().c_str(), _user->getUsername().c_str(), _user->getHostName().c_str());
		//send welcome rply

	}
}