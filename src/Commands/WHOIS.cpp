
#include "../../include/Commands.hpp"

void	Commands::WHOIS()
{
	if (_parameters.size() == 0)
		return reply (ERR_NONICKNAMEGIVEN);

	return reply (RPL_WHOISUSER, _user->getNickname().c_str(), _user->getUsername().c_str(), _user->getHostName().c_str(), "idk_need_real_name_?");
}