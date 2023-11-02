

#include "../include/Server.hpp"

Server::Server(int port, std::string pssw) : _password(pssw), _port(port)
{
	_server_name = "ft_irc43";
}

void	Server::init()
{
	int opt = 1;

	if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		throw std::runtime_error("Socket error");

	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
		throw std::runtime_error("setsockopt error");

	fcntl(_server_fd, F_SETFL, O_NONBLOCK);

	struct sockaddr_in	address;
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(_port);
	memset(&(address.sin_zero), '\0', 8);

	if (bind(_server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
		throw std::runtime_error("bind error");

	if (listen(_server_fd, address.sin_port) < 0)
		throw std::runtime_error("port error");

	_p_fds.push_back(pollfd());
	_p_fds.back().fd = _server_fd;
	_p_fds.back().events = POLLIN;

	std::cout << "socket server listening \n";
}

void	Server::run()
{
	if (poll(&_p_fds[0], _p_fds.size(), 600) == -1)
	{
		gShutdown = true;
		return ;
	}
	for (size_t i = 0; i < _p_fds.size(); i++)
	{
		if (_p_fds[i].revents & POLLIN) {
			if (_p_fds[i].fd == _server_fd){
				std::cout << "accept\n";
				acceptUser();
			}else{
				std::cout << "receive\n";
				receive(_users[_p_fds[i].fd]);
			}
		}
	}

	pingUser();

	std::vector<User *> v_users = getUsers();
	for (std::vector<User *>::iterator it = v_users.begin(); it != v_users.end(); it++)
		if ((*it)->getStatus() == DELETE)
			delUser(*it);

}

void	Server::acceptUser()
{
	int 					user_fd;
	socklen_t				len = 0;
	struct sockaddr_in		address;


	len = sizeof(address);

	address.sin_family = 0;
	address.sin_port = 0;
	address.sin_port = 0;
	memset(&(address.sin_zero), '\0', 8);


	if ((user_fd = accept(_p_fds[0].fd, (struct sockaddr *)&address, &len)) == -1)
		return ;

	_users[user_fd] = new User(user_fd, inet_ntoa(address.sin_addr), this);

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
		std::string msg(_server_name + ": you have been disconnected for inactivity\r\n");
		send(user->getFD(), msg.c_str(), msg.size(), 0);
		close(user->getFD());
	}

	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		std::vector<User *> channelMembers = (*it)->getUserList();
		for (std::vector<User *>::iterator uIt = channelMembers.begin(); uIt != channelMembers.end(); uIt++)
		{
			if (user == (*uIt))
			{
				std::cout << "I'm removed from " << (*it)->getName() << std::endl;
				(*it)->deleteUser(user);
				std::cout << "New size " << (*it)->getUserList().size();
			}
		}
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
	// printUserList();
}

void	Server::receive(User * user)
{
	char buffer[1024];


	int n = recv(user->getFD(), buffer, sizeof(buffer), 0);

	if (n < 0)
	{
		std::cout << "signal received\n";
		return ; // what to do ??
	}

	if (!n)
	{
		std::cout << "sig 2\n";
		user->setStatus(3);
		return ;
	}
	user->setLastActivity();
	user->setLastPing();
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

void    Server::pingUser()
{
    std::vector<User *> users = getUsers();

    for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++)
    {
        if (time(NULL) - (*it)->getLastActivity() >= TIME_OUT)
            (*it)->setStatus(3);
        else if (time(NULL) - (*it)->getLastPing() >= SERV_PING)
        {
            std::string msg("PING :" + _server_name + "\r\n");
            send((*it)->getFD(), msg.c_str(), msg.size(), 0);
            (*it)->setLastPing();
        }
    }
}

void	Server::printUserList()
{
	std::map<int, User *>::iterator it = _users.begin();
	std::cout << "--- User List ---\n";
	for (;it != _users.end(); it++)
	{
		std::cout << it->second->getNickname() << std::endl;
	}
	std::cout << "-----------------\n";
}

std::string	Server::getPassword()
{
	return _password;
}

std::string	Server::getName()
{
	return _server_name;;
}

std::vector<User *>	Server::getUsers()
{
	std::vector<User *>	cli;

	std::map<int, User *>::iterator it = _users.begin();

	for (; it != _users.end(); it++)
		cli.push_back(it->second);

	return (cli);
}

User *Server::getOneUser(std::string nickname)
{
	std::vector<User *>	cli = getUsers();

	std::vector<User *>::iterator it = cli.begin();
	for(; it != cli.end(); it++)
		if ((*it)->getNickname() == nickname)
			return *it;
	return (NULL);
}

void Server::createChannel(const std::string &name, User * who, std::string key) {
	_channels.push_back(new Channel(name, who, key));
}

void Server::delChannel(Channel * chan, User * user)
{
	std::vector<Channel *>::iterator it = _channels.begin();
	user->removeChannel(chan);
	for(;it != _channels.end(); it++)
		if ((*it) == chan)
		{
			_channels.erase(it);
			break ;
		}
	delete chan;
}

Channel *Server::findChannel(std::string target, std::vector<Channel *> list) const {
	vector<Channel *>::iterator it = list.begin();
	for (; it != list.end(); it++) {
		if (target == it[0]->getName())
			return it[0];
	}
	return NULL;
}

std::vector<Channel *> Server::getChannel() const {
	return _channels;
}

User *Server::findUser(const string& targetUser, vector<User *> userList) {
	vector<User *>::iterator it = userList.begin();

	for (;it != userList.end(); it++) {
		if (it[0]->getNickname() == targetUser)
			return *it;
	}
	return NULL;
}

int	Server::getFD()
{
	return _server_fd;
}

void	Server::clean()
{
	std::cout << "Cleaning the server" << std::endl;
	std::vector<User *> v_users = getUsers();
	for (std::vector<User *>::iterator it = v_users.begin(); it != v_users.end(); it++)
		delUser(*it);
	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
		delete (*it);
	close(_server_fd);
}

void Server::delChannel(Channel * chan)
{
    std::vector<Channel *>::iterator it = _channels.begin();
    for(;it != _channels.end(); it++)
        if ((*it) == chan)
        {
            _channels.erase(it);
            break ;
        }
    delete chan;
}
