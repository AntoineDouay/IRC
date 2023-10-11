
#ifndef SERVER_HPP

# define SERVER_HPP

#include "main.hpp"

class User;
class Commands;
class Channel;

class Server{

	private :

	std::vector<pollfd>		_p_fds;

	std::map<int, User *> 	_users;
	std::vector<Channel *>	_channels;

	std::string	_password;
	int			_port;

	int			_server_fd;

	public :

	Server(int port, std::string pssw);

	void	init();
	void	run();

	void	acceptUser();
	void	delUser(User * User);
	void	receive(User * User);

	std::string				getPassword();
	std::vector<User *>		getUsers();

	void createChannel(std::string const &name, User const &who, std::string *key);
};

#endif
