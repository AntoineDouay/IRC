

/*  ----RPLY----- */

# define RPL_WELCOME "001 :Welcome to the Internet Relay Network <nick>!<user>@<host>\r\n"
# define KICK_REPLY "KICK <channel> <target> <reason>"

/*  ---- ERR ----- */

# define ERR_NEEDMOREPARAMS	 "461 <command> : Not enough parameters\r\n"
# define ERR_ALREADYREGISTERED "462 : Unusable command : already registered\r\n"

# define ERR_NONICKNAMEGIVEN "431 : Need a nickname parameter\r\n"
# define ERR_NICKNAMEINUSE	 "433 <nick> : already in use\r\n"

# define ERR_BADCHANNELKEY "475 <channel> :Bad channel key\r\n"

// For kick command error
# define ERR_NOSUCHNICK "401 <nick> :<reason>\r\n"
# define ERR_NOSUCHCHANNEL "403 <channel> :<reason>\r\n"
# define ERR_USERNOTINCHANNEL "441 <nick> <channel> :<reason>\r\n"
# define ERR_NOTONCHANNEL "442 <channel> :<reason>\r\n"
# define ERR_BADCHANMASK "476 <channel> :<reason>\r\n"
# define ERR_CHANOPRIVSNEEDED "482 <channel> :<reason>\r\n"