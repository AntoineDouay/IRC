
#include "../include/Client.hpp"

Client::Client(int fd, struct sockaddr_in adress) : _fd(fd), _address(adress)
{
	(void)_fd;
	(void)_address;
	_nickname = "";
	_username = "";
}

