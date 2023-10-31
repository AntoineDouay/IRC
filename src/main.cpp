#include "../include/main.hpp"

bool	gShutdown = false;

static void	signalHandler(int signal)
{
	(void) signal;
	gShutdown = true;
}

int main (int argc, char **argv)
{
	// struct sigaction sigIntHandler;
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

	std::signal(SIGINT, &signalHandler);
	int port = atoi(argv[1]);
	Server serv(port, argv[2]);
	if (serv.init())
	{
		std::cout << "Error : problem in the init of the tcp serv\n";
		return 1;
	}
	while (!gShutdown) {
		serv.run();
	}
	serv.clean();
	return 0;
}
