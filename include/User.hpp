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
class Channel;

class User{

	private :

	int					_fd;

	std::string			_nickname;
	std::string			_username;
	std::string			_hostname;

	time_t				_last_ping;
	time_t				_last_time_active;

	Status				_status;

	Server				*_serv;

	std::vector<Channel *>	_channels;
	public :

	User(int fd, std::string hostname, Server * serv);

	int			getFD() const;
	Status		getStatus() const;
	std::string	getUsername() const;
	std::string	getNickname() const;
	std::string	getHostName() const;
	time_t		getLastActivity() const;
	time_t		getLastPing() const;
	std::vector<Channel *>	getChannel() const; 

	void	addChannel(Channel * chan);
	void	removeChannel(Channel * chan);
	void	setLastPing();
	void	setLastActivity();
	void	setStatus(int status);
	void	setUsername(std::string str);
	void	setNickname(std::string str);
};

#endif