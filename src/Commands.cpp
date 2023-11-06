
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
	send(_user->getFD(), _reply.c_str(), _reply.size(), 0);
}

void Commands::reply(std::vector<User *> userList, bool sendToMe, std::string str, ...) {
	
	va_list		vl;
	
	std::string	_reply;
	
	int i = 1;

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

	vector<User *>::iterator it = userList.begin();

	for (; it != userList.end(); it++) {
		if ((*it)->getFD() != _user->getFD() || sendToMe)
			send((*it)->getFD(), _reply.c_str(), _reply.size(), 0);
	}
}

void	Commands::QUIT()
{
	std::string str(_user->getNickname() + ": QUIT ");

	if (_parameters.size() > 0)
		str += _parameters[0];
	_user->setStatus(3);

	// std::vector<Channel *>chan = _user->getChannel();
	// std::vector<Channel *>empty;
	// for(std::vector<Channel *>::iterator it = chan.begin(); it != chan.end(); it++)
	// {
	// 	(*it)->deleteUser(_user->getNickname());
	// 	try {
	// 		if ((*it)->getUserList().size() == 0)
	// 			empty.push_back(*it);
	// 	} catch (std::exception &e) {
	// 		cout << e.what() << endl;
	// 	}
	// }
	
	// for (vector<Channel *>::iterator it = empty.end()-1; it != empty.begin()-1; it--){
	// 	_serv->delChannel(*it, _user);
	// }
}
