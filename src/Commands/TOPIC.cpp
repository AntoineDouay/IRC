
#include "../../include/Commands.hpp"

void	Commands::TOPIC()
{
	if (_parameters.size() == 0)
		return reply(ERR_NEEDMOREPARAMS, "TOPIC");

	std::vector<Channel *> channels = _serv->getChannel();
	Channel *chan = NULL;
	bool userOnChan = false;
	bool userIsOper = false;
	for (std::vector<Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if ((*it)->getName() == _parameters[0])
			chan = *it;
	}
	if (chan == NULL)
		return ; 

	std::vector<User> userList = chan->getUserList();
	for (std::vector<User>::iterator it = userList.begin(); it != userList.end(); it++)
		if (it->getNickname() == _user->getNickname())
			userOnChan = true;

	if (!userOnChan)
		return reply(ERR_NOTONCHANNEL, chan->getName().c_str(), "is not in the channel");

	std::vector<User> operList = chan->getAdmin();
	for (std::vector<User>::iterator it = operList.begin(); it != operList.end(); it++)
		if (it->getNickname() == _user->getNickname())
			userIsOper = true;

	if (chan->getTopicRestrictionOn())
		if (!userIsOper)
			return reply(ERR_CHANOPRIVSNEEDED, chan->getName().c_str(), "need operator rights");

	if (_parameters.size() < 2)
		return reply (RPL_NOTOPIC, chan->getName().c_str(), chan->getTopic().c_str());
	else
		{
			chan->setTopic(*_user, _parameters[1]);
			return reply (RPL_TOPIC, chan->getName().c_str(), chan->getTopic().c_str());
		}

}		

//         ERR_NOCHANMODES