
#include "../../include/Commands.hpp"

void	Commands::INVITE()
{
	if (_parameters.size() < 2)
		return reply(ERR_NEEDMOREPARAMS, "Invite");
	
	std::vector<Channel *> channels = _serv->getChannel();
	Channel *chan = NULL;
	bool	targetOnChan = false;
	bool	userOnChan = false;
	bool	userIsOper = false;

	for (std::vector<Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if ((*it)->getName() == _parameters[1])
			chan = *it;
	}
	if (chan == NULL)
		return ;

	std::vector<User *> users = _serv->getUsers();
	std::vector<User *>::iterator itt = users.begin();
	User * target = NULL;
	for (; itt != users.end(); itt++)
		if ((*itt)->getNickname() == _parameters[0])
		{
			target = *itt;
			break ;
		}

	if (itt == users.end())
		return reply(ERR_NOSUCHNICK, _parameters[0].c_str(), "this nickname is not in use");

	std::vector<User *> userList = chan->getUserList();
	for (std::vector<User* >::iterator it = userList.begin(); it != userList.end(); it++)
		if ((*it)->getNickname() == _user->getNickname())
			userOnChan = true;

	if (!userOnChan)
		return reply(ERR_NOTONCHANNEL, chan->getName().c_str(), "cannot invite if your not in the channel");

	for (std::vector<User *>::iterator it = userList.begin(); it != userList.end(); it++)
		if ((*it)->getNickname() == _parameters[0])
			targetOnChan = true;

	if (targetOnChan)
		return reply(ERR_USERONCHANNEL, _parameters[0].c_str(), chan->getName().c_str(), "already on the channel");

	std::vector<User *> operList = chan->getAdmin();
	for (std::vector<User *>::iterator it = operList.begin(); it != operList.end(); it++)
		if ((*it)->getNickname() == _user->getNickname())
			userIsOper = true;

	if (chan->getInviteRestrictionOn())
		if (!userIsOper)
			return reply(ERR_CHANOPRIVSNEEDED, chan->getName().c_str(), "need operator rights");

	reply(RPL_INVITING, _parameters[0].c_str(), _parameters[1].c_str());
	std::string msg(_user->getNickname() + " has invited you on " + chan->getName() + "!\n");
	chan->addInvitedUser(target);
	send(target->getFD(), msg.c_str(), msg.size(), 0);
}	