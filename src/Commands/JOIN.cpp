
#include "../../include/Commands.hpp"

void	Commands::JOIN()
{
	Channel *tmp = _serv->findChannel(_parameters[0], _serv->getChannel());
	if (_parameters.size() == 0)
		return reply (ERR_NEEDMOREPARAMS, _command.c_str());
	// for (std::vector<std::string>::iterator it  = _parameters.begin(); it != _parameters.end(); it++)
	// 	std::cout << *it << std::endl;
	if (tmp) {
		try {
			tmp->addUser(_user[0], _user[0], NULL);
		} catch (exception &e) {
			cout << "user already in channel " << tmp->getName() << endl;
		}
	} else
		_serv->createChannel(_parameters[0], _user[0], NULL);

	if (_parameters[0] == _serv->getPassword())
		_user->setStatus(1);
	
	return ;
}