
#include "../include/Commands.hpp"


Commands::Commands(std::string cmd, Server * serv, Client * client) 
{
	_serv = serv;
	_client = client;
	parse_cmd(cmd);
	init_func_map();
}

void	Commands::init_func_map()
{
	_func.insert(std::make_pair("PASS", &Commands::PASS));
	_func.insert(std::make_pair("USER", &Commands::USER));
	_func.insert(std::make_pair("NICK", &Commands::NICK));
	//
	_func.insert(std::make_pair("QUIT", &Commands::QUIT));
}

void	Commands::parse_cmd(const std::string &instruction)
{
	// std::string	value;
	// std::string	trailing;
	// size_t		trailingPos;
	// std::string	s;
	bool		flag;

	// if (hasCrlf(instruction))
	// {
	// 	trailingPos = instruction.find(":");
	// 	if (trailingPos != std::string::npos)
	// 	{
	// 		value = instruction.substr(0, trailingPos - 1);
	// 		trailing = instruction.substr(trailingPos + 1, instruction.size() - trailingPos - 2);
	// 	}
	// 	else
	// 		value = instruction.substr(0, instruction.size() - 2);
		std::stringstream	ss(instruction);
		std::string			str;
		flag = false;
		while (ss >> str) // std::getline(ss, s, ' ')
		{
			if (!flag)
			{
				_command = str;
				flag = true;
			}
			else
				_parameters.push_back(str);
		}
	// 	}
	// 	if (trailing.size() > 0)
	// 		_parameters.push_back(trailing);
	// }
	// else
	// 	_command = "";

	//std::cout << _command << std::endl;
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

	if (cmd != "PASS" && _client->getStatus() == NO_PASSWORD)
		return ;
	if (_func.find(cmd) != _func.end())
		(this->*_func[cmd])();
}

void	Commands::reply(std::string str, ...)
{
	va_list		vl;

	std::string nick(_client->getNickname());

	if (nick == "")
		nick = "*";

	std::string	_reply(":server_name " + str.substr(0, 4) + nick + " ");

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
	send(_client->getFD(), _reply.c_str(), _reply.size(), 0);
}

void	Commands::PASS()
{
	if (_parameters.size() == 0)
		return reply (ERR_NEEDMOREPARAMS, _command.c_str());
	if (_client->getStatus() != NO_PASSWORD)
		return reply (ERR_ALREADYREGISTERED);
	// std::cout << _parameters[0] << std::endl;
	// std::cout << _serv->getPassword() << std::endl;

	if (_parameters[0] == _serv->getPassword())
		_client->setStatus(1);
	
	return ;
}

void	Commands::USER()
{
	if (_parameters.size() == 0)
		return reply (ERR_NEEDMOREPARAMS);
	if (_client->getStatus() != REGISTER)
		return reply (ERR_ALREADYREGISTERED);
	
	_client->setUsername(_parameters[0]);
	if (_client->getNickname() != "" && _client->getStatus() != NO_PASSWORD)
	{
		reply(RPL_WELCOME, _client->getNickname().c_str(), _client->getUsername().c_str(), _client->getHostName().c_str());
		//send welcome rply
	}
}

void	Commands::NICK()
{
	if (_parameters.size() == 0)
		return reply (ERR_NONICKNAMEGIVEN);

	std::vector<Client *> cli = _serv->getClients();

	for (size_t i = 0; i < cli.size(); i++)
		if (_parameters[0] == cli[i]->getNickname())
			return reply (ERR_NICKNAMEINUSE, _parameters[0].c_str());

	_client->setNickname(_parameters[0]);
	if (_client->getUsername() != "" && _client->getStatus() != NO_PASSWORD)
	{
		reply(RPL_WELCOME, _client->getNickname().c_str(), _client->getUsername().c_str(), _client->getHostName().c_str());
		//send welcome rply

	}
}

void	Commands::QUIT()
{
	std::string str(_client->getNickname() + ": QUIT ");

	if (_parameters.size() > 0)
		str += _parameters[0];
	_client->setStatus(3);
	send (_client->getFD(), str.c_str(), str.size(), 0); //nul
}

// void	Commands::PASS()
// {
// 	std::vector<std::string> &parameters = _command.getParameters();
// 	if (parameters.size() != 1)
// 		return ;
// 	if (parameters[0] != _serv->getPassword())
// 		return ;
// 	_client->setStatus(1);
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

