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
#include <stdlib.h>
#include <stdarg.h>

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <map>
#include <ctime>
#include <climits>
#include <fstream>


#include "Server.hpp"
#include "User.hpp"
#include "Commands.hpp"
#include "Channel.hpp"
#include "reply.hpp"

#endif
