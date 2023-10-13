

/*  ----RPLY----- */

# define RPL_WELCOME "001 :Welcome to the Internet Relay Network <nick>!<user>@<host>\r\n"

/*  ---- ERR ----- */

# define ERR_NEEDMOREPARAMS	 "461 <command> : Not enough parameters\r\n"
# define ERR_ALREADYREGISTERED "462 : Unusable command : already registered\r\n"

# define ERR_NONICKNAMEGIVEN "431 : Need a nickname parameter\r\n"
# define ERR_NICKNAMEINUSE	 "433 <nick> : already in use\r\n"

# define ERR_NOORIGIN "409 :<reason>\r\n" //ping

# define RPL_WHOISUSER "311 <nick> <user> <host> * :<real_name>\r\n" //whois

# define RPL_YOUREOPER "381 :<info>\r\n"
# define ERR_PASSWDMISMATCH	"464 :<reason>\r\n" 

# define ERR_UNKNOWNMODE "472 <char> :<reason>\r\n"
# define ERR_USERNOTINCHANNEL "<nick> <channel> :<reason>\r\n"
# define ERR_USERSDONTMATCH " 502 :<reason>\r\n" // MODE