#include "../../include/Commands.hpp"


void escapeSpecialChars(std::string &input)
{
	std::string output;
	for (size_t i = 0; i < input.size(); i++)
	{
		char c = input[i];
		switch (c)
		{
			case '\"':
				break;
			case '\\':
				break;
			case '\b':
				break;
			case '\f':
				break;
			case '\n':
				break;
			case '\r':
				break;
			case '\t':
				break;
			default:
				output += c;
				break;
		}
	}
	input = output;
}

// Callback function to write the result to a string
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s)
{
	size_t newLength = size * nmemb;
	try
	{
		s->append((char *)contents, newLength);
	}
	catch (std::bad_alloc &e)
	{
		return 0;
	}
	return newLength;
}

void Commands::handleBot(const std::string &message)
{
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(4000); // Port where your Node.js server is running
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error connecting to the server");
    }

    send(clientSocket, message.c_str(), strlen(message.c_str()), 0);

    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);

    std::cout << "Server response: " << buffer << std::endl;
	std::string jfdk314(":novel PRIVMSG " + _user->getNickname() + " :" + buffer);
	escapeSpecialChars(jfdk314);
	jfdk314 += "\r\n";
	send(_user->getFD(), jfdk314.c_str(), jfdk314.size(), 0);
    close(clientSocket);
}


void Commands::handleSinglePrivMSG(Server *server, std::string &preMessage,
								   const std::string &message,
								   const std::string &nick, const std::string &username,
								   const std::string &hostname)
{
	std::vector<User *> users = server->getUsers();
	User *user = 0;

	for (size_t i = 0; i < users.size(); i++)
	{
		if (nick.size() > 0 && nick != users[i]->getNickname())
			continue;
		if (username.size() > 0 && username != users[i]->getUsername())
			continue;
		if (hostname.size() > 0 && hostname != users[i]->getHostName())
			continue;
		user = users[i];
	}
	if (user)
	{
		preMessage += nick + " :" + message + "\r\n";
		send(user->getFD(), preMessage.c_str(), preMessage.size(), 0);
	}
	else
		Commands::reply(ERR_NORECIPIENT, "PRIVMSG");
}

void Commands::handleChannelMSG(Server *server, User *user,
								const std::string &name, std::string &message)
{
	std::vector<Channel *> channels = server->getChannel();

	for (size_t i = 0; i < channels.size(); i++)
	{
		std::cout << channels[i]->getName() << std::endl;
		if (channels[i]->getName() == name)
		{
			bool isMyChan = false;
			const std::vector<User *> users = channels[i]->getUserList();
			for (size_t d = 0; d < users.size(); d++)
			{
				if (user->getNickname() == users[d]->getNickname())
					isMyChan = true;
			}
			for (size_t d = 0; isMyChan && d < users.size(); d++)
			{
				if (user->getNickname() != users[d]->getNickname())
				{
					std::string finalMessage = ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostName() + " PRIVMSG " + name + " :" + message + "\r\n";
					send(users[d]->getFD(), finalMessage.c_str(), finalMessage.size(), 0);
				}
			}
			if (!isMyChan)
				Commands::reply(ERR_CANNOTSENDTOCHAN, name.c_str());
			return;
		}
	}
	Commands::reply(ERR_NORECIPIENT, "PRIVMSG");
}

void Commands::PRIVMSG()
{
	bool isChannel = false;
	bool isRegex = false;
	std::string recipent;
	std::string channel = "";
	std::string nick = "";
	std::string username = "";
	std::string hostname = "";
	std::string servername = "";
	std::string preMessage = "";
	std::size_t found;

	if (_parameters.size() == 0)
	{
		Commands::reply(ERR_NORECIPIENT, _command.c_str());
		return;
	}
	if (_parameters.size() == 1)
	{
		Commands::reply(ERR_NOTEXTTOSEND);
		return;
	}
	recipent = _parameters[0];
	if (recipent.size() == 0)
		return;
	// check if it's channel
	found = recipent.find("*");

	if (recipent.size() > 0 && recipent[0] == '#' && found == std::string::npos)
	{
		isChannel = true;
		handleChannelMSG(_serv, _user, recipent, _parameters[1]);
		return;
	}
	if ((recipent[0] == '#' || recipent[0] == '$') && found != std::string::npos)
	{
		isRegex = true;
		// Handle regex here
	}
	if (!isChannel && !isRegex)
	{
		// nickname parse
		found = recipent.find("!");
		if (found != std::string::npos)
			nick = recipent.substr(0, found);
		else if (recipent.find("!") == std::string::npos && recipent.find("@") == std::string::npos && recipent.find("%") == std::string::npos)
			nick = recipent;
		// username parse
		if (recipent.find("@") != std::string::npos || recipent.find("%") != std::string::npos)
		{
			found = recipent.find("!");
			if (found != std::string::npos)
				username = recipent.substr(found + 1,
										   std::min(recipent.find("%"),
													recipent.find("@")) -
											   found - 1);
			else
				username = recipent.substr(0, std::min(recipent.find("%"), recipent.find("@")));
		}
		// hostname parse
		found = recipent.find("@");
		if (found != std::string::npos)
			hostname = recipent.substr(found + 1);
		// servername parse
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
		if (nick == "novel")
			handleBot(_parameters[1]);
		else
			handleSinglePrivMSG(_serv, preMessage, _parameters[1], nick, username, hostname);
	}
}

