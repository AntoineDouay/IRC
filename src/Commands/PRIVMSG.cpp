#include "../../include/Commands.hpp"

void	Commands::PRIVMSG()
{
		std::vector<std::string> params;
	params.push_back("Mari");
	params.push_back("#lari");
	params.push_back("kalt%millennium.stealth.net");
	params.push_back("kalt%millennium.stealth.net@irc.stealth.net");
	params.push_back("kalt%millennium.stealth.net");
	params.push_back("Wiz!jto@tolsun.oulu.fi");
	params.push_back("$*.fi");
	params.push_back("#*.edu");

	for (size_t i = 0; i < params.size(); i++)
	{
		std::cout << "-----------------------------------" << std::endl;
		std::cout << params[i] << std::endl;
		bool		isChannel	= false;
		bool		isRegex		= false;
		std::string channel		= "";
		std::string nick		= "";
		std::string username	= "";
		std::string hostname	= "";
		std::string servername	= "";
		std::size_t found;

		if (params[i].size() == 0)
			return (0);
		//check if it's channel
		found = params[i].find("*");
		if (params[i].size() > 0 && params[i][0] == '#'
			&& found == std::string::npos)
		{
			isChannel = true;
			channel = params[i].substr(1, params[i].size() - 1);
			//Handle channel here
		}
		if ((params[i][0] == '#' || params[i][0] == '$')
			&& found != std::string::npos)
		{
			isRegex = true;
			//Handle regex here
		}
		if (!isChannel && !isRegex)
		{
			//nickname parse
			found = params[i].find("!");
			if (found != std::string::npos)
				nick = params[i].substr(0, found);
			else if (params[i].find("!") == std::string::npos
				&& params[i].find("@") == std::string::npos
				&& params[i].find("%") == std::string::npos)
				nick = params[i];
			//username parse
			if (params[i].find("@") != std::string::npos
				|| params[i].find("%") != std::string::npos)
			{
				found = params[i].find("!");
				if (found != std::string::npos)
					username = params[i].substr(found + 1, std::min(params[i].find("%"), params[i].find("@")) - found - 1);
				else
					username = params[i].substr(0, std::min(params[i].find("%"), params[i].find("@")));
			}
			//hostname parse
			found = params[i].find("@");
			if (found != std::string::npos)
				hostname = params[i].substr(found + 1);
			//servername parse
			found = params[i].find("%");
			if (found != std::string::npos)
			{
				std::size_t foundHost = params[i].find("@");
				if (foundHost != std::string::npos)
					servername = params[i].substr(found + 1, foundHost - found);
				else
					servername = params[i].substr(found + 1);
			}
			//Handle everything else
			std::cout << "User " << std::endl;
			std::cout << "Nick: " << nick << std::endl;
			std::cout << "Username: " << username << std::endl;
			std::cout << "Hostname: " << hostname << std::endl;
			std::cout << "Servername: " << servername << std::endl;
		}
	}
}
