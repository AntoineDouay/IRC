
#include "../include/User.hpp"

User::User(int fd, struct sockaddr_in adress, Server * serv) : _fd(fd), _address(adress), _serv(serv)
{
	(void)_fd;
	(void)_address;
	_nickname = "";
	_username = "";
	(void)_serv;
}

int User::getFD() const
{
	return _fd;
}

Status	User::getStatus() const
{
	return _status;
}

std::string	User::getNickname() const
{
	return _nickname;
}
std::string	User::getUsername() const
{
	return _username;
}
std::string	User::getHostName() const
{
	return inet_ntoa(_address.sin_addr);
}


void	User::setStatus(int status)
{
	_status = static_cast<Status>(status);
}

void	User::setNickname(std::string str)
{
	_nickname = str;
}
void	User::setUsername(std::string str)
{
	_username = str;

}