
#include "../../include/Commands.hpp"

void	Commands::OPER()
{
	if (_parameters.size() != 2)
		return reply (ERR_NEEDMOREPARAMS);
	
	if (_parameters[1] != _serv->getPassword())
		return reply (ERR_PASSWDMISMATCH, "password is incorrect");

	_user->setIsOper();
	return reply (RPL_YOUREOPER, "you are now an operator !");
}