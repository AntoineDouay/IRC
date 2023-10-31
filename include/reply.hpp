

/*  ----RPLY----- */

# define RPL_WELCOME "001 :Welcome to the Internet Relay Network <nick>!<user>@<host>\r\n"
# define RPL_YOURHOST "002 :Your host is <servername>, running version <version>\r\n"
# define RPL_CREATED "003 :This server was created <date>\r\n"
# define RPL_MYINFO	"004 <server_name> <version> <user_modes> <chan_modes>\r\n"

//global channel msg

# define KICK_REPLY "::<nickname>!<username>@:<hostname> KICK <channel> <target> <reason>\n"
# define JOIN_WELCOME "::<nickname>!<username>@:<hostname> JOIN <channel>\n"
# define TOPIC_CHANGE "::<nickname>!<username>@:<hostname> TOPIC <channel> <topic>\n"
# define MODE_CHANGE "::<nickname>!<username>@:<hostname> MODE <channel> <mode>\n"
# define MODE_CHANGE2 "::<nickname>!<username>@:<hostname> MODE <channel> <mode> <param>\n"
# define NICK_CHANGE "::<nickname>!<username>@:<hostname> NICK <nick>\n" 
# define PART_CHANGE "::<nickname>!<username>@:<hostname> PART <channel>\n" 

/*  ---- ERR ----- */

# define ERR_NEEDMOREPARAMS	 "461 <command> : Not enough parameters\r\n"
# define ERR_ALREADYREGISTERED "462 : Unusable command : already registered\r\n"

# define ERR_NONICKNAMEGIVEN "431 : Need a nickname parameter\r\n"
# define ERR_NICKNAMEINUSE	 "433 <nick> : already in use\r\n"

# define ERR_NOORIGIN "409 :<reason>\r\n" //ping

# define RPL_WHOISUSER "311 <nick> <user> <host> * :<real_name>\r\n" //whois

# define RPL_YOUREOPER "381 :<info>\r\n"
# define ERR_PASSWDMISMATCH	"464 :<reason>\r\n"

# define ERR_CHANNELISFULL "471 <channel> channel full\r\n"

//FOR MODE
# define ERR_UNKNOWNMODE "472 <char> :<reason>\r\n"
# define ERR_USERSDONTMATCH "502 :<reason>\r\n" 

# define RPL_CHANNELMODEIS	"324 <channel> <mode> <mode_params>\r\n"
# define RPL_INVITELIST "346 <channel> <invitemask>\r\n"

# define ERR_BADCHANNELKEY "475 <channel> :Bad channel key\r\n"

// For kick command error
# define ERR_NOSUCHNICK "401 <nick> :<reason>\r\n"
# define ERR_NOSUCHCHANNEL "403 <channel> :<reason>\r\n"
# define ERR_USERNOTINCHANNEL "441 <nick> <channel> :<reason>\r\n"
# define ERR_NOTONCHANNEL "442 <channel> :<reason>\r\n"
# define ERR_CHANOPRIVSNEEDED "482 <channel> :<reason>\r\n"

//For private msg
# define ERR_NORECIPIENT "411 :No recipient given <command>\r\n"
# define ERR_NOTEXTTOSEND "412 :No text to send\r\n"
# define ERR_CANNOTSENDTOCHAN "404 <channel name> :Cannot send to channel\r\n"
# define ERR_TOOMANYTARGETS "407 <target> :<error code> recipents. <abort message>\r\n"

// for join
# define ERR_INVITEONLYCHAN "473 <channel> :<reason>\r\n"

// for invite
# define ERR_NOSUCHNICK "401 <nick> :<reason>\r\n"
# define ERR_NOTONCHANNEL "442 <channel> :<reason>\r\n"
# define ERR_USERONCHANNEL "443 <nick> <channel> :<reason>\r\n"
# define ERR_NOPRIVILEGES "481 :<reason>\r\n"
# define RPL_INVITING "341 <nick> <channel>\r\n"

//topic
# define RPL_NOTOPIC "331 <channel> :<info>\r\n"
# define RPL_TOPIC "332 <channel> :<topic>\n"
