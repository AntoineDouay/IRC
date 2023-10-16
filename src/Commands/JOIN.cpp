
#include "../../include/Commands.hpp"

void	Commands::JOIN()
{
	Channel *tmp = _serv->findChannel(_parameters[0], _serv->getChannel());
	string	tmp_key;
	if (_parameters.size() == 0)
		return reply (ERR_NEEDMOREPARAMS, _command.c_str());
	if (_parameters.size() >= 2)
		tmp_key = _parameters[1];
	else
	 	tmp_key = "";
	// for (std::vector<std::string>::iterator it  = _parameters.begin(); it != _parameters.end(); it++) // TODO only for test
	// 	std::cout << *it << std::endl;
	if (tmp) {
		try {
			tmp->addUser(_user[0], _user[0], tmp_key);
		} catch (exception &e) {
			reply(ERR_BADCHANNELKEY, _parameters[0].c_str());
			cout << e.what() << endl;
		}
	} else
		_serv->createChannel(_parameters[0], _user[0], tmp_key);

	if (_parameters[0] == _serv->getPassword())
		_user->setStatus(1);
	
	return ;
}