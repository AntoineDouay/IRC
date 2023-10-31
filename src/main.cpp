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
		std::cerr << "usage is : ./ircserv [port] [password]" << std::endl;
		return (1);
	}
  	std::string psswrd(argv[2]);
	if (!psswrd.size())
	{
		std::cerr << "need a password" << std::endl;
		return (1);
	}

	std::signal(SIGINT, &signalHandler);
	int port = atoi(argv[1]);
	Server serv(port, argv[2]);
	try {
		serv.init();
		while (!gShutdown)
			serv.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	serv.clean();
	return 0;
}
