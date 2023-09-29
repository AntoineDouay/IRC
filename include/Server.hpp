
#ifndef SERVER_HPP

# define SERVER_HPP

#include "main.hpp"

class Client;

class Server{

	private :

	std::map<int, Client *> _clients;
	std::vector<pollfd>	_p_fds;

	std::string	_password;
	int			_port;

	int			_server_fd;

	public :

	Server(int port, std::string pssw);

	void	init();
	void	run();

	void	acceptClient();
};

#endif