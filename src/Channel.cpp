
#include "../include/Channel.hpp"

Channel::Channel(const std::string& name,  User& userCreator, Server &serv)
{
	_name = name;
	_key = "";
	_topic = "";
	_userList.push_back(&userCreator);
	_serv = &serv;
}

std::string Channel::getName()
{
	return _name;
}
