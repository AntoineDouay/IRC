#include "../../include/Commands.hpp"
#include <ostream>

void Commands::KICK() {
	for (std::vector<std::string>::iterator it  = _parameters.begin(); it != _parameters.end(); it++) // TODO only for test
		std::cout << "1: " << *it << std::endl;
	_parameters[2].erase(0, 1);

	kick_reply(_serv->getName(), _parameters[0], _parameters[1], _parameters[2]);
}

void Commands::kick_reply(std::string serverName, std::string channel, std::string target, std::string reason) {
	string output = ":";

	output.append(serverName + " KICK " + channel + " " + target + " :" + reason + "\r\n");

//	cout << "|" << output << "|" << endl; // TODO only for test
	vector<User> userList = _serv->getChannel()[0]->getUserList();
	vector<User>::iterator it = userList.begin();

	for (; it != userList.end(); it++) {
		cout << "it: " << it->getNickname() << "fd: " << it->getFD() << endl;
		send(it->getFD(), output.c_str(), output.size(), 0);
	}
}
