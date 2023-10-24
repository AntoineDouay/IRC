
#include "../../include/Commands.hpp"

void	Commands::PING()
{
	if (_parameters.size() == 0)
		return reply (ERR_NOORIGIN, "need server_name as parameter");

	std::string msg("PONG: " + _serv->getName() + "\r\n");

	send(_user->getFD(), msg.c_str(), msg.size(), 0);

	return;
}
