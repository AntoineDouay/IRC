#include "../include/main.hpp"

int main (int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "usage is : ./ircserv [port] [password]\n";
		return 1;
	}
	int port = atoi(argv[1]);
	Server serv(port, argv[2]);
	serv.init();
	serv.run();
	return 0;
}