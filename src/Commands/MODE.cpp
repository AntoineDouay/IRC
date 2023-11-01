
#include "../../include/Commands.hpp"

void	mode_i(Server &serv, Commands &cmd, User &user, std::vector<std::string> &parameters, Channel &chan, int sign)
{
	(void)cmd;
	(void)parameters;
	if (sign)
		chan.setInviteRestriction();
	else
		chan.removeInviteRestriction();
	cmd.reply(RPL_CHANNELMODEIS, chan.getName().c_str(), parameters[1].c_str(), "");
	cmd.reply(chan.getUserList(), false, MODE_CHANGE, user.getNickname().c_str(), user.getUsername().c_str(),
				  serv.getName().c_str(), chan.getName().c_str(), parameters[1].c_str());
}

void	mode_te(Server &serv, Commands &cmd,  User &user, std::vector<std::string> &parameters, Channel &chan, int sign)
{
	(void)cmd;
	(void)parameters;

	if (sign)
		chan.setTopicRestriction();
	else
		chan.removeTopicRestriction();
	cmd.reply(RPL_CHANNELMODEIS, chan.getName().c_str(), parameters[1].c_str(), "");	
	cmd.reply(chan.getUserList(), false, MODE_CHANGE, user.getNickname().c_str(), user.getUsername().c_str(),
				  serv.getName().c_str(), chan.getName().c_str(), parameters[1].c_str());
	//std::cout << chan.getTopicRestrictionOn() << std::endl;
}

void	mode_l(Server &serv, Commands &cmd, User &user, std::vector<std::string> &parameters, Channel &chan, int sign)
{
	if (!sign)
	{
		chan.removeMaxUsersRestriction();
		cmd.reply(RPL_CHANNELMODEIS, chan.getName().c_str(), parameters[1].c_str(), "");
		cmd.reply(chan.getUserList(), false, MODE_CHANGE, user.getNickname().c_str(), user.getUsername().c_str(),
				serv.getName().c_str(), chan.getName().c_str(), parameters[1].c_str());
	//	std::cout << chan.getMaxUser() << std::endl;
		return ;
	}
	if (parameters.size() < 3)
		return;

	std::istringstream ss(parameters[2]);
	unsigned int n;

	ss >> n;

	if(ss.fail())
	{
		// std::cout << "maxuser parameters is not a unsigned int\n";
		return ;
	}
	if (sign)
		chan.setMaxUsers(n);
	cmd.reply(RPL_CHANNELMODEIS, chan.getName().c_str(), parameters[1].c_str(), parameters[2].c_str());
	cmd.reply(chan.getUserList(), false, MODE_CHANGE, user.getNickname().c_str(), user.getUsername().c_str(),
				serv.getName().c_str(), chan.getName().c_str(), parameters[1].c_str());
	//std::cout << chan.getMaxUser() << std::endl;
}

void	mode_k(Server &serv, Commands &cmd, User &user, std::vector<std::string> &parameters, Channel &chan, int sign)
{
	if (parameters.size() < 3)
		return ;

	if (sign)
	{
		chan.setChannelPassword(parameters[2]);
		cmd.reply(RPL_CHANNELMODEIS, chan.getName().c_str(), parameters[1].c_str(), "");
		cmd.reply(chan.getUserList(), false, MODE_CHANGE2, user.getNickname().c_str(), user.getUsername().c_str(),
				serv.getName().c_str(), chan.getName().c_str(), parameters[1].c_str(), parameters[2].c_str());
		return;
	}
	else if (!sign && parameters[2] == chan.getKey())
	{
		chan.removeChannelPassword();
		cmd.reply(RPL_CHANNELMODEIS, chan.getName().c_str(), parameters[1].c_str(), "");
		cmd.reply(chan.getUserList(), false, MODE_CHANGE2, user.getNickname().c_str(), user.getUsername().c_str(),
				serv.getName().c_str(), chan.getName().c_str(), parameters[1].c_str(), parameters[2].c_str());
		return;
	}

	
	//std::cout << chan.getKey() << std::endl;
}

void	mode_o(Server &serv, Commands &cmd, User &user, std::vector<std::string> &parameters, Channel &chan, int sign)
{
	(void)cmd;
	(void)parameters;

	if (parameters.size() < 3)
		return;
	User *target = serv.getOneUser(parameters[2]);

	if (!chan.isInChannel(parameters[2]))
		return cmd.reply(ERR_USERNOTINCHANNEL, parameters[2].c_str(), chan.getName().c_str(), "not in the channel");

	if (target == NULL)
		return ;

	if (sign)
		chan.setOperator(target);
	else
		chan.removeOperator(target);
	cmd.reply(RPL_CHANNELMODEIS, chan.getName().c_str(), parameters[1].c_str(), "");
	cmd.reply(chan.getUserList(), false, MODE_CHANGE2, user.getNickname().c_str(), user.getUsername().c_str(),
				serv.getName().c_str(), chan.getName().c_str(), parameters[1].c_str(), parameters[2].c_str());
	// std::vector<User> operList = chan.getAdmin();
	// std::vector<User>::iterator it = operList.begin();
	// for (; it != operList.end(); it++)
	// 	std::cout << "ope : " <<  it->getNickname() << std::endl;
}

void	Commands::MODE()
{
	int sign = -1; // 0 - | 1 +;

	if (_parameters.size() < 2)
		return reply(ERR_NEEDMOREPARAMS, _command.c_str());

	std::vector<Channel *> chan = _serv->getChannel();

	size_t i = 0;

	for (; i < chan.size(); i++)
		if (_parameters[0] == chan[i]->getName())
			break ;

	if (i == chan.size())
		return ;

	if (!chan[i]->userIsOper(*_user))
		return reply(ERR_CHANOPRIVSNEEDED, chan[i]->getName().c_str(), "you need op rights");


	if (_parameters[1].size() != 0 && (_parameters[1].at(0) != '+' && _parameters[1].at(0) != '-'))
		return ; //same

	if (_parameters[1].at(0) == '+')
		sign = 1;
	if (_parameters[1].at(0) == '-')
		sign = 0;

	if (_parameters[1].size() < 2)
		return ; //...
	
	if (_parameters[1].size() > 2){
		std::cout << "error unknow mode\n";
		return reply (ERR_UNKNOWNMODE, _parameters[1].c_str(), "unknow mode");
	}
	
	switch (_parameters[1].at(1))
	{
		case 'i':
		{
			mode_i(*_serv, *this, *_user, _parameters, *(chan[i]), sign);
			break;
		}
		case 't':
		{
			mode_te(*_serv, *this, *_user, _parameters, *(chan[i]), sign);
			break;
		}
		case 'k':
		{
			mode_k(*_serv, *this, *_user, _parameters, *(chan[i]), sign);
			break;
		}
		case 'o':
		{
			mode_o(*_serv, *this, *_user, _parameters, *(chan[i]), sign);
			break;
		}
		case 'l':
		{
			mode_l(*_serv, *this, *_user, _parameters, *(chan[i]), sign);
			break;
		};
		default:
			std::cout << "error unknow mode\n";
			return reply (ERR_UNKNOWNMODE, _parameters[1].c_str(), "unknow mode");
	}
}