
#include "../../include/Commands.hpp"

void	Commands::PING()
{
    // if (_parameters.size() == 0)
    //     return reply (ERR_NOORIGIN, "need server_name as parameter");

    std::string msg = ":";
    if (_parameters.size() == 0)
        msg += _user->getNickname() + " PONG :\r\n";
    else
        msg += _user->getNickname() + " PONG :" + _parameters[0] + "\r\n";

    send(_user->getFD(), msg.c_str(), msg.size(), 0);
    return;
}
