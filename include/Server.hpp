
#ifndef SERVER_HPP

# define SERVER_HPP

#include "main.hpp"

class User;
class Commands;
class Channel;

# define TIME_OUT	300000
# define SERV_PING		30 // ping every seconds

class Server{

	private :

	std::vector<pollfd>		_p_fds;

	std::map<int, User *> 	_users;
	std::vector<Channel *>	_channels;

	std::string	_password;
	int			_port;

	int			_server_fd;
	std::string	_server_name;

	public :

	Server(int port, std::string pssw);

	void	init();
	void	run();
	void	clean();

	void	acceptUser();
	void	delUser(User * User);
	void	receive(User * User);
	void	pingUser();

	std::string				getPassword();
	std::string				getName();
	std::vector<User *>		getUsers();
	int						getFD();

	User 					*getOneUser(std::string nickname);
	User *					findUser(const std::string& targetUser, std::vector<User *> userList);

	std::vector<Channel *>		getChannel() const;
	void						delChannel(Channel * chan);

	void	createChannel(std::string const &name, User * who, std::string key);
	Channel *findChannel(std::string target, std::vector<Channel *> list) const;
	void	delChannel(Channel * chan, User * user);
};

#endif
