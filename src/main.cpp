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
    // sigIntHandler.sa_handler = signalHandler;
    // sigemptyset(&sigIntHandler.sa_mask);
    // sigIntHandler.sa_flags = 0;
    // sigaction(SIGINT, &sigIntHandler, 0);
	std::signal(SIGINT, &signalHandler);
	int port = atoi(argv[1]);
	Server serv(port, argv[2]);
	serv.init();
	while (!gShutdown) {
		serv.run();
	}
	serv.clean();
	return 0;
}
