#ifndef CLIENT_HPP

#define CLIENT_HPP

#include "main.hpp"

enum Status{

	NO_PASSWORD,
	REGISTER,
	ONLINE,
	DELETE

};

class Server;

class Client{

	private :

	int					_fd;
	struct sockaddr_in	_address;

	std::string			_nickname;
	std::string			_username;

	Status				_status;

	Server				*_serv;

	public :

	Client(int fd, struct sockaddr_in adress, Server * serv);

	int			getFD();
	Status		getStatus();
	std::string	getUsername();
	std::string	getNickname();

	void	setStatus(int status);
	void	setUsername(std::string str);
	void	setNickname(std::string str);
};

#endif