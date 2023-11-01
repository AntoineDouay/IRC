
#include "../../include/Commands.hpp"

vector<string> getChanList(vector<string> channList, string param, unsigned long *end, unsigned long *start){
		unsigned long int len;

		len = *end - *start;
		std::string tmp = param.substr(*start, len);
		cout << "tmp: " << tmp << endl;
		*start = *end + 1;
		*end = param.find(',', *start);
		channList.push_back(tmp);
		return channList;
}

void	Commands::JOIN()
{
	vector<string> channelList;
	unsigned long int end;
	unsigned long int start = 0;
	// unsigned long int len;
	end = _parameters[0].find(',');
	// channelList = getChanList(channelList, _parameters[0], &end, &start);
	cout << "WHILE START\n";
	while (end != std::string::npos)
	{
		channelList = getChanList(channelList, _parameters[0], &end, &start);
		if (end == std::string::npos) {
			channelList = getChanList(channelList, _parameters[0], &end, &start);
			break;
		}
	
	}
	if (channelList.empty())
		channelList.push_back(_parameters[0]);
	// cout << "WHILE END\n";
	// for (unsigned long i = 0; i < channelList.size(); i++){
	// 	cout << channelList[i] << endl;
	// }
	// cout << "FOR END" << endl;

	vector<string>::iterator str = channelList.begin();
	for(; str != channelList.end(); str++) {
		Channel *tmp = _serv->findChannel(*str, _serv->getChannel());
		string	tmp_key;
		int errValue = -1;
		if (_parameters.size() == 0)
			return reply (ERR_NEEDMOREPARAMS, _command.c_str());

		if (_parameters.size() >= 2)
			tmp_key = _parameters[1];
		else
			tmp_key = "";
		// for (std::vector<std::string>::iterator it  = _parameters.begin(); it != _parameters.end(); it++) // TODO only for test
		// 	std::cout << *it << std::endl;
		if (tmp) {
			// try {
				if (tmp->getInviteRestrictionOn())
					if (!tmp->isInvited(_user))
						return reply (ERR_INVITEONLYCHAN, tmp->getName().c_str(), "has invite only restriction");

				errValue = tmp->addUser(_user[0], _user, tmp_key);
				switch (errValue)
				{
				case 0:
					reply(ERR_BADCHANNELKEY, (*str).c_str());
					break;
				case 1:
					reply(ERR_CHANNELISFULL, (*str).c_str());
					break;
				case 2:
					cerr << "User already in " << *str << " channel\n";
					break;
				default:
					_user->addChannel(tmp);
					// cout << "username: " << _user[0].getUsername() << " | nickname: " << _user[0].getNickname() << endl;
					reply(tmp->getUserList(), true, JOIN_WELCOME, _user->getNickname().c_str(), _user->getUsername().c_str(),
					_serv->getName().c_str(), tmp->getName().c_str());
					break;
				}		
			// } catch (exception &e) {
			// 	reply(ERR_BADCHANNELKEY, _parameters[0].c_str());
			// 	cout << e.what() << endl;
			// }
		} else
			_serv->createChannel(*str, _user, tmp_key);
		}
	// if (_parameters[0] == _serv->getPassword())
	// 	_user->setStatus(1);
}

// reply(JOIN_REPLY, _user->getNickname().c_str(), _user->getUsername().c_str(),
// 				  _user->getHostName().c_str(), tmp->getName().c_str());