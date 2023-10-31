
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
	std::vector<User *> userList = chan->getUserList();
	for (std::vector<User *>::iterator it = userList.begin(); it != userList.end(); it++)
		if ((*it)->getNickname() == _user->getNickname())
			userOnChan = true;

	if (!userOnChan)
		return reply(ERR_NOTONCHANNEL, chan->getName().c_str(), "is not in the channel");

	std::vector<User *> operList = chan->getAdmin();
	for (std::vector<User *>::iterator it = operList.begin(); it != operList.end(); it++)
		if ((*it)->getNickname() == _user->getNickname())
			userIsOper = true;

	// std::cout << "pass err user is oper chan\n";
	// std::cout << "|" << chan->getName() << "|" << "\n";
	// std::cout << "|" << _parameters[0] << "|" << "\n";

	if (chan->getTopicRestrictionOn())
		if (!userIsOper)
			return reply(ERR_CHANOPRIVSNEEDED, _parameters[0].c_str(), "need operator rights");

	if (_parameters.size() > 1)
		chan->setTopic(*_user, _parameters[1]);

	if (chan->getTopic().empty())
		return reply(RPL_NOTOPIC, chan->getName().c_str(), "no topic");

	reply(RPL_TOPIC, chan->getName().c_str(), chan->getTopic().c_str());
	//send msg to all user of the channel (not numeric replies)
	reply(chan->getUserList(), false, TOPIC_CHANGE, _user->getNickname().c_str(), _user->getUsername().c_str(),
		_serv->getName().c_str(), chan->getName().c_str(), chan->getTopic().c_str());
}
