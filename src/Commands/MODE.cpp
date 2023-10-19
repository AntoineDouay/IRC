
#include "../../include/Commands.hpp"

void	mode_i(User &user, Channel &chan, int sign)
{
	try {
		if (sign)
			chan.setInviteRestriction(user);
		else
			chan.removeInviteRestriction(user);
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	//std::cout << chan.getInviteRestrictionOn() << std::endl;
}

void	mode_te(User &user, Channel &chan, int sign)
{
	try {
		if (sign)
			chan.setTopicRestriction(user);
		else
			chan.removeTopicRestriction(user);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}		

	//std::cout << chan.getTopicRestrictionOn() << std::endl;
}

void	mode_l(User &user, std::vector<std::string> &parameters, Channel &chan, int sign)
{
	if (parameters[2].size() == 0)
		return;

	if (!sign)
	{
		chan.removeMaxUsersRestriction(user);
	//	std::cout << chan.getMaxUser() << std::endl;
		return ;
	}
	if (parameters.size() < 3)
		return; //err management

	std::istringstream ss(parameters[2]);
	unsigned int n;

	ss >> n;

	if(ss.fail())
	{
		std::cout << "maxuser parameters is not a unsigned int\n";
		return ;
	}

	if (sign)
		chan.setMaxUsers(user, n);

	//std::cout << chan.getMaxUser() << std::endl;
}

void	mode_k(User &user, std::vector<std::string> &parameters, Channel &chan, int sign)
{
	if (parameters.size() < 3)
		return; //err management
	if (parameters[2].size() == 0)
		return;

	if (sign)
		chan.setChannelPassword(user, parameters[2]);
	else
		chan.removeChannelPassword(user);

	//std::cout << chan.getKey() << std::endl;
}

void	mode_o(User &user, Server &serv, std::vector<std::string> &parameters, Channel &chan, int sign)
{
	if (parameters.size() < 3)
		return; //err management
	User *target = serv.getOneUser(parameters[2]);

	if (target == NULL) // bloque une execption
		return ;

	try {
		if (sign)
			chan.setOperator(user, *target);
		else
			chan.removeOperator(user, *target);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	// std::vector<User> operList = chan.getAdmin();
	// std::vector<User>::iterator it = operList.begin();
	// for (; it != operList.end(); it++)
	// 	std::cout << "ope : " <<  it->getNickname() << std::endl;
}

void	Commands::MODE()
{
	int sign = -1; // 0 - 1 +;

	if (_parameters.size() < 2)
		return reply (ERR_NEEDMOREPARAMS);

	// if (_parameters[0] !=_user->getNickname())
	// 	return reply (ERR_USERSDONTMATCH, "the nickname is not yours"); 

	std::vector<Channel *> chan = _serv->getChannel();

	size_t i = 0;
	for (; i < chan.size(); i++)
		if (_parameters[0] == chan[i]->getName())
			break ;

	if (i == chan.size()) //pas trouver l'err
		return ;
	//makestd::cout << "chan name " << chan[i]->getName() << std::endl;

	if (_parameters[1].size() != 0 && (_parameters[1].at(0) != '+' && _parameters[1].at(0) != '-'))
		return ; //same

	if (_parameters[1].at(0) == '+')
		sign = 1;
	if (_parameters[1].at(0) == '-')
		sign = 0;

	if (_parameters[1].size() < 2)
		return ; //...

	switch (_parameters[1].at(1))
	{
		case 'i':
		{
			mode_i(*_user, *(chan[i]), sign);
			break;
		}
		case 't':
		{
			mode_te(*_user, *(chan[i]), sign);
			break;
		}
		case 'k':
		{
			mode_k(*_user, _parameters, *(chan[i]), sign);
			break;
		}
		case 'o':
		{
			mode_o(*_user, *_serv, _parameters, *(chan[i]), sign);
			break;
		
		}
		case 'l':
		{
			mode_l(*_user, _parameters, *(chan[i]), sign);
			break;
		};
		default:
			return reply (ERR_UNKNOWNMODE, _parameters[1].at(2), "unknow mode");
	}
}

//maybe replace exception with reply in the client ?