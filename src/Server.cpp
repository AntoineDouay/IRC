

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
			acceptClient();
		else
		{
			for (std::vector<pollfd>::iterator it = _p_fds.begin(); it != _p_fds.end(); ++it)
				if((*it).revents == POLLIN)
				{
					receive(_clients[(*it).fd]);
				}

			std::vector<Client *> v_clients = getClients();
			for (std::vector<Client *>::iterator it = v_clients.begin(); it != v_clients.end(); it++)
				if ((*it)->getStatus() == DELETE)
					delClient(*it);

		}
	}
}

void	Server::acceptClient()
{
	int 					client_fd;
	socklen_t				len;
	struct sockaddr_in		address;

	if ((client_fd = accept(_p_fds[0].fd, (struct sockaddr *)&address, &len)) == -1)
		return ;
	
	_clients[client_fd] = new Client(client_fd, address, this);

	_p_fds.push_back(pollfd());
	_p_fds.back().fd = client_fd;
	_p_fds.back().events = POLLIN;

	std::cout << "new client add \n";
}


void	Server::delClient(Client * client)
{
	std::map<int, Client *>::iterator it = _clients.find(client->getFD());

	if (it != _clients.end())
	{
		_clients.erase(it);
		close(client->getFD());
	}

	for (std::vector<pollfd>::iterator it = _p_fds.begin(); it != _p_fds.end(); it++)
	{
		if (it->fd == client->getFD())
		{
			_p_fds.erase(it);
			break ;
		}
	}
	close(client->getFD());

	delete client;
}

void	Server::receive(Client * client)
{
	char buffer[1024];


	int n = recv(client->getFD(), buffer, sizeof(buffer), 0);

	if (n < 0)
		return ; //error to manage

	// if (!n)
	// {
	// 	client->setStatus(3); // normal shutdown of ending socket -> status = DELETE
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
		Commands cmd(str, this, client);
		cmd.execute();
		buf.erase(0 , pos + delimiter.size());
	}
}

std::string	Server::getPassword()
{
	return _password;
}

std::vector<Client *>	Server::getClients()
{
	std::vector<Client *>	cli;

	std::map<int, Client *>::iterator it = _clients.begin();

	for (; it != _clients.end(); it++)
		cli.push_back(it->second);

	return (cli);
}