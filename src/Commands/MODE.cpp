
#include "../../include/Commands.hpp"


// NEED GETNAME FOR CHANNEL

void	Commands::MODE()
{
	int sign = -1; // 0 - 1 +;

	if (_parameters.size() < 2)
		return reply (ERR_NEEDMOREPARAMS);

	// if (_parameters[0] !=_user->getNickname())
	// 	return reply (ERR_USERSDONTMATCH, "the nickname is not yours"); 

	std::vector<Channel *> chan = _serv->getChannel();

	for (size_t i = 0; i < chan.size(); i++)
		if (_parameters[0] == chan[i]->getName())
			break ;

	if (i == chan.size()) //pas trouver l'err
		return ;

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
			//if (sign == 0)
			// 	chan[i].setMode();
			if (sign == 1)
				chan[i].setInviteMod();
			break;
		}
		case 't':
		{
			//if (sign == 0)
			 //	chan[i].setMode();
			if (sign == 1)
				chan[i].setTopicRestricton();
			break;
		}
		case 'k':
		{
			if (sign == 0)
				chan[i].removePassword();
			if (sign == 1)
				chan[i].setChannelPassword();
			break;
		}
		case 'o':
		{
			//if (sign == 0)
			//	chan[i].setMode();
			if (sign == 1)
				chan[i].setOperator();
			break;
		}
		case 'l':
		{
			//if (sign == 0)
			 //	chan[i].setMode();
			if (sign == 1)
				chan[i].setMaxUsers();
			break;
		};
		default:
			return reply (ERR_UNKNOWNMODE, _parameters[1].at(2), "unknow mode");
	}
}