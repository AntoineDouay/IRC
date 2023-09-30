
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

Status	Client::getStatus()
{
	return _status;
}

std::string	Client::getNickname()
{
	return _nickname;
}
std::string	Client::getUsername()
{
	return _username;

}

void	Client::setStatus(int status)
{
	_status = static_cast<Status>(status);
}

void	Client::setNickname(std::string str)
{
	_nickname = str;
}
void	Client::setUsername(std::string str)
{
	_username = str;

}