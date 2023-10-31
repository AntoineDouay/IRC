
#include "../../include/Commands.hpp"

void	Commands::PART()
{
	// std::vector<User *> list;
	// list.push_back(_user);

	if (_parameters.size() < 1)
		return;

	std::vector<Channel *> chan = _serv->getChannel();

	size_t i = 0;
	for (; i < chan.size(); i++)
		if (_parameters[0] == chan[i]->getName())
			break ;

	if (i == chan.size())
		return ;

	std::vector<User *> users = chan[i]->getUserList();
	reply(users, true, PART_CHANGE, _user->getNickname().c_str(), _user->getUsername().c_str(),
		_user->getHostName().c_str(), _parameters[0].c_str());
	
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++)
		if (_user->getNickname() == (*it)->getNickname())
		{
			users.erase(it);
			break;
		}
	std::vector<Channel *> user_channels = _user->getChannel();
	for (std::vector<Channel *>::iterator it = user_channels.begin(); it != user_channels.end(); it++)
		if ((*it)->getName() == _parameters[0])
		{
			user_channels.erase(it);
			break;
		}
}	