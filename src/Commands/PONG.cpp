

# include "../../include/Commands.hpp"

void    Commands::PONG()
{
    std::string msg;
    if (_parameters.size() == 0)
        msg = _user->getNickname() + " PING :\n";
    else
        msg = _user->getNickname() + " PING :" + _parameters[0] + "\n";

    send(_user->getFD(), msg.c_str(), msg.size(), 0);
    return;
}
