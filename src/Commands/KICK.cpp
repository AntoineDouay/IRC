#include "../../include/Commands.hpp"
#include <ostream>

void Commands::KICK() {
	for (std::vector<std::string>::iterator it  = _parameters.begin(); it != _parameters.end(); it++) // TODO only for test
		std::cout << "1: " << *it << std::endl;
	if (_parameters.size() == 3) {
		if (_parameters[2].at(0) == ':')
			_parameters[2].erase(0, 1);
	} else {
		_parameters.push_back("");
	}

	Channel *channelTarget = _serv->findChannel(_parameters[0], _serv->getChannel());

	if (!channelTarget->isInChannel(_parameters[1])) {
		reply(ERR_USERNOTINCHANNEL, _parameters[1].c_str(), _parameters[1].c_str(),"not in the channel");
		return;
	}

	reply(channelTarget->getUserList(), KICK_REPLY,
		  _parameters[0].c_str(), _parameters[1].c_str(), _parameters[2].c_str());
	channelTarget->deleteUser(_parameters[1]);
	User * u = _serv->getOneUser(_parameters[1]);
	u->removeChannel(channelTarget);
}
