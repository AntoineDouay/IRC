
#include "../include/Commands.hpp"


Commands::Commands(std::string cmd, Server * serv, User * client)
{
	_serv = serv;
	_user = client;
	parse_cmd(cmd);
	init_func_map();
}

void	Commands::init_func_map()
{
	_func.insert(std::make_pair("JOIN", &Commands::JOIN));
	_func.insert(std::make_pair("KICK", &Commands::KICK));
	_func.insert(std::make_pair("PASS", &Commands::PASS));
	_func.insert(std::make_pair("USER", &Commands::USER));
	_func.insert(std::make_pair("NICK", &Commands::NICK));
	_func.insert(std::make_pair("JOIN", &Commands::JOIN));
	_func.insert(std::make_pair("PING", &Commands::PING));
	_func.insert(std::make_pair("PONG", &Commands::PONG));
	_func.insert(std::make_pair("WHOIS", &Commands::WHOIS));
	_func.insert(std::make_pair("OPER", &Commands::OPER));
	_func.insert(std::make_pair("PRIVMSG", &Commands::PRIVMSG));
	_func.insert(std::make_pair("MODE", &Commands::MODE));
	_func.insert(std::make_pair("INVITE", &Commands::INVITE));
	_func.insert(std::make_pair("TOPIC", &Commands::TOPIC));
	_func.insert(std::make_pair("QUIT", &Commands::QUIT));
}

void	Commands::parse_cmd(const std::string &instruction)
{
	std::string	value;
	std::string	trailing;
	size_t		trailingPos;
	bool		flag;

	trailingPos = instruction.find(":");
	if (trailingPos != std::string::npos)
	{
		value = instruction.substr(0, trailingPos - 1);
		trailing = instruction.substr(trailingPos + 1, instruction.size() - trailingPos - 2);
	}
	else
		value = instruction.substr(0, instruction.size());
	std::stringstream	ss(value);
	std::string			str;
	flag = false;
	while (ss >> str)
	{
		if (!flag)
		{
			_command = str;
			flag = true;
		}
		else
			_parameters.push_back(str);
	}
	if (trailing.size() > 0)
		_parameters.push_back(trailing);
	// std::cout << "Parsing test --------------------------------";
	// for (size_t i = 0; i < _parameters.size(); i++)
	// {
	// 	std::cout << _parameters[i] << std::endl;
	// 	for (size_t m = 0; m < _parameters[i].size(); m++)
	// 	{
	// 		if (_parameters[i][m] == '\n')
	// 			std::cout << "\\n" << std::endl;
	// 		else if (_parameters[i][m] == '\r')
	// 			std::cout << "\\r" << std::endl;
	// 		else
	// 			std::cout << _parameters[i][m] << std::endl;
	// 	}
	// 	std::cout << std::endl;
	// }
}

bool	Commands::hasCrlf(const std::string &instruction)
{
	if (instruction.size() >= 2)
	{
		if (instruction[instruction.size() - 1] != '\n')
			return (false);
		if (instruction[instruction.size() - 2] != '\r')
			return (false);
		return (true);
	}
	return (false);
}

void	Commands::execute()
{
	std::string cmd = _command;

	if (cmd != "PASS" && _user->getStatus() == NO_PASSWORD)
		return ;
	if (_func.find(cmd) != _func.end())
		(this->*_func[cmd])();
}

void	Commands::reply(std::string str, ...)
{
	va_list		vl;

	std::string nick(_user->getNickname());

	if (nick == "")
		nick = "*";

	std::string	_reply(":" + _serv->getName() + " " + str.substr(0, 4) + nick + " ");

	int i = 4;

	va_start(vl, str);

	while(str[i])
	{
		if (str[i] != '<')
			_reply += str[i];
		else
		{
			while (str[i] != '>')
				i++;
			_reply += va_arg(vl, char *);
		}
		i++;
	}
//	cout << "|" << _reply << "|" << endl; // TODO only for test
	send(_user->getFD(), _reply.c_str(), _reply.size(), 0);
}

void Commands::reply(std::vector<User> userList, std::string str, ...) {
	va_list		vl;
	va_start(vl, str);

	std::string _reply;
	int i = 1;
	_reply.append(":");

	while(str[i])
	{
		if (str[i] != '<')
			_reply += str[i];
		else
		{
			while (str[i] != '>')
				i++;
			_reply += va_arg(vl, char *);
		}
		i++;
	}
//	_reply.append("\n");
//	cout << "|" << _reply << "|" << endl; // TODO only for test
	vector<User>::iterator it = userList.begin();

	for (; it != userList.end(); it++) {
		cout << "it: " << it->getNickname() << " fd: " << it->getFD() << endl;
		send(it->getFD(), _reply.c_str(), _reply.size(), 0);
	}
}

// void	Commands::PASS()
// {
// 	if (_parameters.size() == 0)
// 		return reply (ERR_NEEDMOREPARAMS, _command.c_str());
// 	if (_user->getStatus() != NO_PASSWORD)
// 		return reply (ERR_ALREADYREGISTERED);
// 	// std::cout << _parameters[0] << std::endl;
// 	// std::cout << _serv->getPassword() << std::endl;

// 	if (_parameters[0] == _serv->getPassword())
// 		_user->setStatus(1);

// 	return ;
// }

// void	Commands::USER()
// {
// 	if (_parameters.size() == 0)
// 		return reply (ERR_NEEDMOREPARAMS);
// 	if (_user->getStatus() != REGISTER)
// 		return reply (ERR_ALREADYREGISTERED);

// 	_user->setUsername(_parameters[0]);
// 	if (_user->getNickname() != "" && _user->getStatus() != NO_PASSWORD)
// 	{
// 		reply(RPL_WELCOME, _user->getNickname().c_str(), _user->getUsername().c_str(), _user->getHostName().c_str());
// 		//send welcome rply
// 	}
// }

// void	Commands::NICK()
// {
// 	if (_parameters.size() == 0)
// 		return reply (ERR_NONICKNAMEGIVEN);

// 	std::vector<User *> u = _serv->getUsers();

// 	for (size_t i = 0; i < u.size(); i++)
// 		if (_parameters[0] == u[i]->getNickname())
// 			return reply (ERR_NICKNAMEINUSE, _parameters[0].c_str());

// 	_user->setNickname(_parameters[0]);
// 	if (_user->getUsername() != "" && _user->getStatus() != NO_PASSWORD)
// 	{
// 		reply(RPL_WELCOME, _user->getNickname().c_str(), _user->getUsername().c_str(), _user->getHostName().c_str());
// 		//send welcome rply

// 	}
// }

void	Commands::QUIT()
{
	std::string str(_user->getNickname() + ": QUIT ");

	if (_parameters.size() > 0)
		str += _parameters[0];
	_user->setStatus(3);
	send (_user->getFD(), str.c_str(), str.size(), 0); //nul
}

// void	Commands::PASS()
// {
// 	std::vector<std::string> &parameters = _command.getParameters();
// 	if (parameters.size() != 1)
// 		return ;
// 	if (parameters[0] != _serv->getPassword())
// 		return ;
// 	_user->setStatus(1);
// }
// void	Commands::USER()
// {
// 	std::vector<std::string> &parameters = _command.getParameters();

// 	if (parameters.size() < 1)
// 		return ;
// 	_client->setUsername(parameters[0]);
// 	if (_client->getNickname() != "" && _client->getStatus() != NO_PASSWORD)
// 	{
// 		send (_client->getFD(), RPL_WELCOME, 80, 0);
// 		//send welcome rply
// 	}
// }
// void	Commands::NICK()
// {
// 	std::vector<std::string> &parameters = _command.getParameters();

// 	if (parameters.size() != 1)
// 		return ;
// 	_client->setNickname(parameters[0]);
// 	if (_client->getUsername() != "" && _client->getStatus() != NO_PASSWORD)
// 	{
// 		send (_client->getFD(), RPL_WELCOME, 80, 0);
// 		//send welcome rply
// 	}
// }

