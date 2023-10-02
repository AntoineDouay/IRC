#ifndef MAIN_HPP

# define MAIN_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <poll.h>
#include <fcntl.h>

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <ctime>

#include "Server.hpp"
#include "Client.hpp"
#include "Command.hpp"
#include "Commands.hpp"

#endif
