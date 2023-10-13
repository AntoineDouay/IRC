

#include "../include/Server.hpp"

Server::Server(int port, std::string pssw) : _password(pssw), _port(port)
{
}

void	Server::init()
{
	int opt = 1;

	if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		return ;

	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		std::cout << "pas cool\n";
		return ;
	}

	struct sockaddr_in	address;
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(_port);

	if (bind(_server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
		return ;

	if (listen(_server_fd, 10) < 0)
		return ;
	
	_p_fds.push_back(pollfd());
	_p_fds.back().fd = _server_fd;
	_p_fds.back().events = POLLIN;

	std::cout << "socket server listening \n";

	return ;
}

void	Server::run()
{
	while (42)
	{
		if (poll(&_p_fds[0], _p_fds.size(), 6000) == -1)
		return;

		if (_p_fds[0].revents == POLLIN)
			acceptUser();
		else
		{
			for (std::vector<pollfd>::iterator it = _p_fds.begin(); it != _p_fds.end(); ++it)
				if((*it).revents == POLLIN)
				{
					receive(_users[(*it).fd]);
				}

			std::vector<User *> v_users = getUsers();
			for (std::vector<User *>::iterator it = v_users.begin(); it != v_users.end(); it++)
				if ((*it)->getStatus() == DELETE)
					delUser(*it);

		}
	}
}

void	Server::acceptUser()
{
	int 					user_fd;
	socklen_t				len;
	struct sockaddr_in		address;

	if ((user_fd = accept(_p_fds[0].fd, (struct sockaddr *)&address, &len)) == -1)
		return ;
	
	_users[user_fd] = new User(user_fd, address, this);

	_p_fds.push_back(pollfd());
	_p_fds.back().fd = user_fd;
	_p_fds.back().events = POLLIN;

	std::cout << "new client add \n";
}


void	Server::delUser(User * user)
{
	std::map<int, User *>::iterator it = _users.find(user->getFD());

	if (it != _users.end())
	{
		_users.erase(it);
		close(user->getFD());
	}

	for (std::vector<pollfd>::iterator it = _p_fds.begin(); it != _p_fds.end(); it++)
	{
		if (it->fd == user->getFD())
		{
			_p_fds.erase(it);
			break ;
		}
	}
	close(user->getFD());

	delete user;
}

void	Server::receive(User * user)
{
	char buffer[1024];


	int n = recv(user->getFD(), buffer, sizeof(buffer), 0);

	if (n < 0)
		return ; //error to manage

	// if (!n)
	// {
	// 	user->setStatus(3); // normal shutdown of ending socket -> status = DELETE
	// 	return ;
	// }

	buffer[n] = '\0';
	std::string buf = buffer;
	std::string delimiter("\n");
	size_t pos;

	while ((pos = buf.find(delimiter)) != std::string::npos)
	{
		std::string str = buf.substr(0, pos);
		std::cout << str << std::endl;
		Commands cmd(str, this, user);
		cmd.execute();
		buf.erase(0 , pos + delimiter.size());
	}
}

std::string	Server::getPassword()
{
	return _password;
}

std::vector<User *>	Server::getUsers()
{
	std::vector<User *>	cli;

	std::map<int, User *>::iterator it = _users.begin();

	for (; it != _users.end(); it++)
		cli.push_back(it->second);

	return (cli);
}

void Server::createChannel(const std::string &name, const User &who, std::string *key) {
	_channels.push_back(new Channel(name, who, key));
}

Channel *Server::findChannel(std::string target, std::vector<Channel *> list) const {
	vector<Channel *>::iterator it = list.begin();
	for (int i = 0; it != list.end(); it++) {
		if (target == list[i]->getName())
			return list[i];
	}
	return NULL;
}

std::vector<Channel *> Server::getChannel() const {
	return _channels;
}
