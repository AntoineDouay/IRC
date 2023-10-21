#ifndef USER_HPP

#define USER_HPP

#include "main.hpp"

enum Status{

	NO_PASSWORD,
	REGISTER,
	ONLINE,
	DELETE

};

class Server;

class User{

	private :

	int					_fd;
	struct sockaddr_in	_address;

	std::string			_nickname;
	std::string			_username;

	time_t				_last_ping;
	time_t				_last_time_active;

	Status				_status;

	Server				*_serv;

	public :

	User(int fd, struct sockaddr_in adress, Server * serv);

	int			getFD() const;
	Status		getStatus() const;
	std::string	getUsername() const;
	std::string	getNickname() const;
	std::string	getHostName() const;
	time_t		getLastActivity() const;
	time_t		getLastPing() const;

	void	setLastPing();
	void	setLastActivity();
	void	setStatus(int status);
	void	setUsername(std::string str);
	void	setNickname(std::string str);
};

#endif