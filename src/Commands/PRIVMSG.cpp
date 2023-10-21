#include "../../include/Commands.hpp"

// void sendFileViaDCC(int userSocket, const std::string &filename) {

//     // Read the file and send it
//     std::ifstream file;
//     file.open(filename.c_str(), std::ios::binary); // Open the file in binary mode
//     if (!file.is_open()) {
//         std::cerr << "Failed to open file." << std::endl;
//         return;
//     }

//     char buffer[1024] = {0};
//     while (file) {
//         file.read(buffer, sizeof(buffer));
//         send(userSocket, buffer, file.gcount(), 0);
//     }
// }

void	Commands::handleSinglePrivMSG(Server *server, std::string &preMessage,
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
		preMessage += nick + " :" + message + "\r\n";
		send(user->getFD(), preMessage.c_str(), preMessage.size(), 0);

		// if (message.find("DCC SEND") != std::string::npos) {
		// 	std::istringstream iss(message);
		// 	std::vector<std::string> tokens;
		// 	std::istream_iterator<std::string> iter(iss);
		// 	std::istream_iterator<std::string> end;
		// 	while (iter != end) {
		// 		tokens.push_back(*iter);
		// 		std::cout << "Token: " << *iter << std::endl;
		// 		++iter;
		// 	}
		// 	if (tokens.size() >= 6) {
		// 		std::string filename = tokens[2];
		// 		std::string ip = tokens[3];
		// 		std::string port = tokens[4];
		// 		std::string filesize = tokens[5];

		// 		sendFileViaDCC(user->getFD(), filename);
		// 		return;
		// 	}
		// }
	}
	else
		Commands::reply(ERR_NORECIPIENT, "PRIVMSG");
}

void	Commands::handleChannelMSG(Server *server, User *user,
			const std::string &name, std::string &message)
{
	std::vector<Channel *>	channels = server->getChannel();

	for (size_t i = 0; i < channels.size(); i++)
	{
		std::cout << channels[i]->getName() << std::endl;
		if (channels[i]->getName() == name)
		{
			bool					isMyChan = false;
			const std::vector<User> users = channels[i]->getUserList();
			for (size_t d = 0; d < users.size(); d++)
			{
				if (user->getNickname() == users[d].getNickname())
					isMyChan = true;
			}
			for (size_t d = 0; isMyChan && d < users.size(); d++)
			{
				if (user->getNickname() != users[d].getNickname())
				{
					std::string finalMessage = ":" + user->getNickname()
						+ "!" + user->getUsername() + "@" + user->getHostName()
						+ " PRIVMSG " + name + " :" + message + "\r\n";
					send(users[d].getFD(), finalMessage.c_str(), finalMessage.size(), 0);
				}
			}
			if (!isMyChan)
				Commands::reply(ERR_CANNOTSENDTOCHAN, name.c_str());
			return ;
		}
	}
	Commands::reply(ERR_NORECIPIENT, "PRIVMSG");
}

// void handleDCC(Server *server, const std::string &nickname, const std::string &filename, const std::string &ip, const std::string &port, const std::string &filesize) {
//     // Your DCC handling logic here
//     // Example: print the received information
// 	(void) server;
//     std::cout << "Received DCC SEND command:" << std::endl;
//     std::cout << "Nickname: " << nickname << std::endl;
//     std::cout << "Filename: " << filename << std::endl;
//     std::cout << "IP: " << ip << std::endl;
//     std::cout << "Port: " << port << std::endl;
//     std::cout << "Filesize: " << filesize << std::endl;
// }

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
	std::string preMessage	= "";
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
		handleChannelMSG(_serv, _user, recipent, _parameters[1]);
		return ;
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

/*

CAP LS
PASS aaa
NICK migi
USER migi migi localhost :Migi Dali
*/
