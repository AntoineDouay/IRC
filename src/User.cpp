
#include "../include/User.hpp"

User::User(int fd, std::string hostname, Server * serv) : _fd(fd), _serv(serv)
{
	(void)_fd;
	_nickname = "";
	_username = "";
	_hostname = hostname;
	_status = NO_PASSWORD;
	_last_ping = time(NULL);
	_last_time_active = time(NULL);
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
	return _hostname;
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

time_t	User::getLastActivity() const
{
	return _last_time_active;
}

time_t	User::getLastPing() const
{
	return _last_ping;
}

void 	User::setLastActivity()
{
	_last_time_active = time(NULL);
}

void 	User::setLastPing()
{
	_last_ping = time(NULL);
}
