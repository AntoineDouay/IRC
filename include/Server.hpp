
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
	std::string	_server_name;
  
	public :

	Server(int port, std::string pssw);

	void	init();
	void	run();

	void	acceptUser();
	void	delUser(User * User);
	void	receive(User * User);

	std::string				getPassword();
	std::string				getName();
	std::vector<User *>		getUsers();

	std::vector<Channel *>		getChannel() const;

	void createChannel(std::string const &name, User const &who, std::string key);
	Channel *findChannel(std::string target, std::vector<Channel *> list) const;
};

#endif
