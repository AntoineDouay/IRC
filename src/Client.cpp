
#include "../include/Client.hpp"

Client::Client(int fd, struct sockaddr_in adress, Server * serv) : _fd(fd), _address(adress), _serv(serv)
{
	(void)_fd;
	(void)_address;
	_nickname = "";
	_username = "";
	(void)_serv;
}

int Client::getFD()
{
	return _fd;
}

void	Client::setStatus(int status)
{
	_status = static_cast<Status>(status);
}