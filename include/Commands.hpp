
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
	void	MODE();
	void	PING();
	void	PONG();
	void	JOIN();
	void	KICK();
	void	TOPIC();
	void	INVITE();
	void	PRIVMSG();
	void	QUIT();

	void	init_func_map();
	void	parse_cmd(const std::string &instruction);
	static bool hasCrlf(const std::string &instruction);

	void	execute();
	void	reply(std::string str, ...);
	void	reply(std::vector<User *> userList, bool sendToMe, std::string str, ...);
	void	kick_reply(std::string serverName, std::string channel, std::string target, std::string reason);

	// Private msg helpers
	void	handleSinglePrivMSG(Server *server, std::string &preMessage,
				const std::string &message,
				const std::string &nick, const std::string &username,
				const std::string &hostname);
	void	handleChannelMSG(Server *server, User *user,
				const std::string &name, std::string &message);
	void	handleBot(const std::string &message);


};

#endif
