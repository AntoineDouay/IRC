
#include "../../include/Commands.hpp"

vector<string> getChanList(vector<string> channList, string param, unsigned long *end, unsigned long *start){
		unsigned long int len;

		len = *end - *start;
		std::string tmp = param.substr(*start, len);
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
	end = _parameters[0].find(',');

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
		if (tmp) 
		{
			if (tmp->getInviteRestrictionOn())
				if (!tmp->isInvited(_user))
					return reply (ERR_INVITEONLYCHAN, tmp->getName().c_str(), "has invite only restriction");

			errValue = tmp->addUser(_user, tmp_key);

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
					reply(tmp->getUserList(), true, JOIN_WELCOME, _user->getNickname().c_str(), _user->getUsername().c_str(),
					_serv->getName().c_str(), tmp->getName().c_str());
					break;
			}		
		}
		else {
			try {
				_serv->createChannel(*str, _user, tmp_key);
			} catch (exception &e) {
				reply(ERR_NOSUCHCHANNEL, _parameters[0].c_str(), "invalid channel name");
			}
		}
	}
}