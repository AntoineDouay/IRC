#include "../include/main.hpp"

int main (int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "usage is : ./ircserv [port] [password]\n";
		return 1;
	}
	std::string psswrd(argv[2]);
	if (!psswrd.size())
	{
		std::cout << "need a password\n";
		return 1;
	}

	int port = atoi(argv[1]);
	Server serv(port, argv[2]);
	if (serv.init())
	{
		std::cout << "Error : problem in the init of the tcp serv\n";
		return 1;
	}
	serv.run();
	return 0;
}