
#ifndef COMMANDS_HPP

# define COMMANDS_HPP

# include "main.hpp"

class Server;
class User;

class Commands{

	private :

	std::map<std::string, void (Commands::*)()>	_func;

	std::string					_command;
	std::vector<std::string>	_parameters;

	Server	*_serv;
	User	*_user;

	public :

	Commands(std::string cmd, Server * serv, User * client);

	void	PASS();
	void	USER();
	void	NICK();
	// void	AWAY();
	void	WHOIS();
	// void	WHO();

	void	MODE();
	void	PING();
	//void	PONG();
	void	JOIN();

	void	KICK();

	// void	KILL();
	// void	PART();
	// void	TOPIC();
	// void	INVITE();
	// void	NAMES();
	// void	NOTICE();
	// void	LIST();
	void	PRIVMSG();
	// void	WALLOPS();
	void	OPER();
	void	QUIT();

	void	init_func_map();
	void	parse_cmd(const std::string &instruction);
	static bool hasCrlf(const std::string &instruction);

	void	execute();
	void	reply(std::string str, ...);
	void	kick_reply(std::string serverName, std::string channel, std::string target, std::string reason);

	// Private msg helpers
	void	handleSinglePrivMSG(Server *server, std::string &preMessage,
				const std::string &message,
				const std::string &nick, const std::string &username,
				const std::string &hostname);
	void	handleChannelMSG(Server *server, User *user,
				const std::string &name, std::string &message);


};

/*
message    =  [ ":" prefix SPACE ] command [ params ] crlf
prefix     =  servername / ( nickname [ [ "!" user ] "@" host ] )
command    =  1*letter / 3digit
params     =  *14( SPACE middle ) [ SPACE ":" trailing ]
			=/ 14( SPACE middle ) [ SPACE [ ":" ] trailing ]

nospcrlfcl =  %x01-09 / %x0B-0C / %x0E-1F / %x21-39 / %x3B-FF
				; any octet except NUL, CR, LF, " " and ":"
middle     =  nospcrlfcl *( ":" / nospcrlfcl )
trailing   =  *( ":" / " " / nospcrlfcl )

SPACE      =  %x20        ; space character
crlf       =  %x0D %x0A   ; "carriage return" "linefeed"

After extracting the parameter list, all parameters are equal
whether matched by <middle> or <trailing>. <trailing> is just a
syntactic trick to allow SPACE within the parameter.

Commands to parse:
	- NICK <nickname>
*/

/*
Description:
- Gets string and constructs object from it.
Fallback:
- If there is no crlf _command member would be empty string("")
*/

#endif
