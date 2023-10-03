
#ifndef COMMANDS_HPP

# define COMMANDS_HPP

# include "main.hpp"
# include "Command.hpp"

class Command;
class Server;
class Client;

class Commands{

	private :

	std::map<std::string, void (Commands::*)()>	_func;
	std::vector<std::string>					_tokens;
	Command										_command;

	Server	*_serv;
	Client	*_client;

	public :

	Commands(std::string cmd, Server * serv, Client * client);

	void	PASS();
	void	USER();
	void	NICK();
	// void	AWAY();
	// void	WHOIS();
	// void	WHO();
	// void	MODE();
	// void	PING();
	// void	PONG();
	// void	JOIN();
	// void	KICK();
	// void	KILL();
	// void	PART();
	// void	TOPIC();
	// void	INVITE();
	// void	NAMES();
	// void	NOTICE();
	// void	LIST();
	// void	PRIVMSG();
	// void	WALLOPS();
	// void	OPER();
	// void	QUIT();

	void	init_func_map();
	void	parse_cmd(std::string cmd);

	void	execute();

};

#endif
