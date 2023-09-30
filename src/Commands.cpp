
#include "../include/Commands.hpp"

# define RPL_WELCOME ":irc_43 001 adouay :Welcome to the Internet Relay Network <nick>!<user>@<host>\r\n"

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
}

void	Commands::parse_cmd(std::string cmd)
{
	std::stringstream	ss(cmd);
	std::string			token;

	while (ss >> token)
	{
		_tokens.push_back(token);
	}
}

void	Commands::execute()
{
	std::string cmd = _tokens[0];

	if (cmd != "PASS" && _client->getStatus() == NO_PASSWORD)
		return ;
	if (_func.find(cmd) != _func.end())
		(this->*_func[cmd])();
}

void	Commands::PASS()
{
	if (_tokens.size() != 2)
		return ;
	if (_tokens[1] != _serv->getPassword())
		return ;
	_client->setStatus(1);
}
void	Commands::USER()
{
	if (_tokens.size() < 2)
		return ;
	_client->setUsername(_tokens[1]);
	if (_client->getNickname() != "" && _client->getStatus() != NO_PASSWORD)
	{
		send (_client->getFD(), RPL_WELCOME, 80, 0);
		//send welcome rply
	}
}
void	Commands::NICK()
{
	if (_tokens.size() != 2)
		return ;
	_client->setNickname(_tokens[1]);
	if (_client->getUsername() != "" && _client->getStatus() != NO_PASSWORD)
	{
		send (_client->getFD(), RPL_WELCOME, 80, 0);
		//send welcome rply
	}
}

