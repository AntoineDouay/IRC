#ifndef CLIENT_HPP

#define CLIENT_HPP

#include "main.hpp"

enum Status{

	ONLINE,
	DELETE

};

class Client{

	private :

	int					_fd;
	struct sockaddr_in	_address;

	std::string			_nickname;
	std::string			_username;

	public :

	Client(int fd, struct sockaddr_in adress);
};

#endif