
#ifndef COMMANDS_HPP

#define COMMANDS_HPP

#include "main.hpp"

class Commands{

	private :

	static std::map<std::string, void (Commands::*)()> _func;

	public :

	Commands(std::string full_cmd);

	void	PASS();
	void	AWAY();
	void	NICK();
	void	USER();
	void	WHOIS();
	void	WHO();
	void	MODE();
	void	PING();
	void	PONG();
	void	JOIN();
	void	KICK();
	void	KILL();
	void	PART();
	void	TOPIC();
	void	INVITE();
	void	NAMES();
	void	NOTICE();
	void	LIST();
	void	PRIVMSG();
	void	WALLOPS();
	void	OPER();
	void	QUIT();

	void	init_func_map();

};

#endif