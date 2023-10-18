#include "../../include/Commands.hpp"


void	handleSinglePrivMSG(Server *server, std::string &preMessage,
	const std::string &message,
	const std::string &nick, const std::string &username,
	const std::string &hostname)
{
	std::vector<User *>	users = server->getUsers();
	User 				*user = 0;

	for (size_t i = 0; i < users.size(); i++)
	{
		if (nick.size() > 0 && nick != users[i]->getNickname())
			continue ;
		if (username.size() > 0 && username != users[i]->getUsername())
			continue ;
		if (hostname.size() > 0 && hostname != users[i]->getHostName())
			continue ;
		user = users[i];
	}
	if (user)
	{
		std::cout << "USER is found" << std::endl;
		preMessage += nick + " :" + message + "\r\n";
		std::cout << preMessage;
		send(user->getFD(), message.c_str(), message.size(), 0);
	}
	else
		Commands::reply(ERR_NORECIPIENT, _command.c_str());
}

void	Commands::PRIVMSG()
{
	bool		isChannel	= false;
	bool		isRegex		= false;
	std::string recipent;
	std::string	channel		= "";
	std::string	nick		= "";
	std::string	username	= "";
	std::string	hostname	= "";
	std::string	servername	= "";
	std::string preMessage		= "";
	std::size_t	found;

	if (_parameters.size() == 0)
	{
		Commands::reply(ERR_NORECIPIENT, _command.c_str());
		return ;
	}
	if (_parameters.size() == 1)
	{
		Commands::reply(ERR_NOTEXTTOSEND);
		return ;
	}
	recipent = _parameters[0];
	if (recipent.size() == 0)
		return ;
	//check if it's channel
	found = recipent.find("*");

	if (recipent.size() > 0 && recipent[0] == '#'
		&& found == std::string::npos)
	{
		isChannel = true;
		channel = recipent.substr(1, recipent.size() - 1);
		//Handle channel here
	}
	if ((recipent[0] == '#' || recipent[0] == '$')
		&& found != std::string::npos)
	{
		isRegex = true;
		//Handle regex here
	}
	if (!isChannel && !isRegex)
	{
		//nickname parse
		found = recipent.find("!");
		if (found != std::string::npos)
			nick = recipent.substr(0, found);
		else if (recipent.find("!") == std::string::npos
			&& recipent.find("@") == std::string::npos
			&& recipent.find("%") == std::string::npos)
			nick = recipent;
		//username parse
		if (recipent.find("@") != std::string::npos
			|| recipent.find("%") != std::string::npos)
		{
			found = recipent.find("!");
			if (found != std::string::npos)
				username = recipent.substr(found + 1, \
					std::min(recipent.find("%"), \
					recipent.find("@")) - found - 1);
			else
				username = recipent.substr(0, std::min(recipent.find("%"), recipent.find("@")));
		}
		//hostname parse
		found = recipent.find("@");
		if (found != std::string::npos)
			hostname = recipent.substr(found + 1);
		//servername parse
		found = recipent.find("%");
		if (found != std::string::npos)
		{
			std::size_t foundHost = recipent.find("@");
			if (foundHost != std::string::npos)
				servername = recipent.substr(found + 1, foundHost - found);
			else
				servername = recipent.substr(found + 1);
		}
		preMessage = ":" + _user->getNickname() + " PRIVMSG ";
		handleSinglePrivMSG(_serv, preMessage, _parameters[1], nick, username, hostname);
	}
}
