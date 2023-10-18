#include "../../include/Commands.hpp"
#include <ostream>

void Commands::KICK() {
	for (std::vector<std::string>::iterator it  = _parameters.begin(); it != _parameters.end(); it++) // TODO only for test
		std::cout << "1: " << *it << std::endl;
	if (_parameters[2].at(0) == ':')
		_parameters[2].erase(0, 1);

	Channel *channelTarget = _serv->findChannel(_parameters[0], _serv->getChannel());

	reply(channelTarget->getUserList(), KICK_REPLY, _user->getNickname().c_str(),
		  _parameters[0].c_str(), _parameters[1].c_str(), _parameters[2].c_str());
}
