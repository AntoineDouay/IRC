#include "../include/Channel.hpp"
#include <cstdio>
#include <exception>

/*
Channel::Channel(const std::string& name,  User& userCreator, Server &serv)
{
	_name = name;
	_key = "";
	_topic = "";
	_userList.push_back(&userCreator);
	_serv = &serv;
}
*/

//Channel::Channel(void) {
//
//}

Channel::Channel(const string& name, const User& userCreator, string key):
		_name(name),
		_key(key),
		_maxUser(UINT_MAX),
		_inviteRestrictionOn(false),
		_topicRestrictionOn(false)
{
	// cout << "Channel constructor called" << endl; // TODO Only for test
	/* Channels names are strings (beginning with a '&', '#', '+' or '!'
	   character) of length up to fifty (50) characters. RFC2812-1.3 */
	if ( _name.length() <= 0 && 51 <= _name.length() ){
		throw std::exception();
	}
	switch (_name[0]) {
		case '&':
			break;
		case '#':
			break;
		case '+':
			break;
		case '!':
			break;
		default:
			throw exception();
	}
	_userList.push_back(userCreator);
	_operatorList.push_back(userCreator);

	(void)_id;
	(void)_key;
	(void)_serv;
}

//Channel::Channel(Channel const &src) {
//
//}

Channel::~Channel(void) {

}

//Channel &Channel::operator=(Channel const &rhs) {
//
//}

string Channel::getName(void) const {
	return _name;
}

const vector<User> &Channel::getAdmin(void) const {
	return _operatorList;
}

const vector<User> &Channel::getUserList(void) const {
	return _userList;
}

string 	Channel::getKey(void) const
{}
unsigned int Channel::getMaxUser(void) const
{}
bool Channel::getinviteRestrictionOn(void) const
{}
bool Channel::gettopicRestrictionOn(void) const
{}
	

bool Channel::userIsOper(User &target)
{
	vector<User>::iterator it = _operatorList.begin();
	for (; it != _operatorList.end(); it++)
		if (it->getNickname() == target.getNickname())
			return true;
	return false;
}

void Channel::addUser(const User& who, const User& newUser, string key) {
	// cout << "Channel::addUser called for user: " << newUser.getNickname() << endl; //TODO it's only for test
	if (_key != "" && key != _key)
		throw CustomErrorMessage("Bad key");
	if (_maxUser <= _userList.size())
		throw CustomErrorMessage(_name + " channel is full"); // channel is full
	for (vector<User>::iterator it = _userList.begin(); it != _userList.end(); it++){
		if (it->getNickname() == newUser.getNickname()){
			throw CustomErrorMessage("User already exist");
		}
	}
	_userList.push_back(newUser);
	(void)who; // TODO remove
}

vector<User>::iterator Channel::findUser(const User& user) {
	vector<User>::iterator it;
	for (it = _userList.begin(); it != _userList.end(); it++){
		if (user.getUsername() == it->getUsername())
			return it;
	}
	return it;
}

void Channel::deleteUser(User who, User targetUser) {
	_userList.erase(findUser(targetUser));
	(void)who; // TODO remove
}

void Channel::setTopic(User who, string newTopic) {
	if (userIsOper(who) || !_topicRestrictionOn)
		_topic = newTopic;
}

const string Channel::getTopic(void) const {
	return _topic;
}

void Channel::setChannelPassword(User who, string password)
{
	if (userIsOper(who))
		_key = password;
}

void Channel::removeChannelPassword(User who)
{
	if (userIsOper(who))
		_key = "";
}

void Channel::setInviteRestriction(User who) {
	if (userIsOper(who))
	{
		if (_inviteRestrictionOn == false)
			_inviteRestrictionOn = true;
		else 
			throw CustomErrorMessage("channel already have invite restriction on");
	}
	else 
			throw CustomErrorMessage("user is not operator");
}

void Channel::removeInviteRestriction(User who) {
		if (userIsOper(who))
	{
		if (_inviteRestrictionOn == true)
			_inviteRestrictionOn = false;
		else 
			throw CustomErrorMessage("channel already have invite restriction off");
	}
	else 
			throw CustomErrorMessage("user is not operator");
}

void Channel::setTopicRestriction(User who) {
		if (userIsOper(who))
	{
		if (_topicRestrictionOn == false)
			_topicRestrictionOn = true;
		else 
			throw CustomErrorMessage("channel already have topic restriction on");
	}
	else 
			throw CustomErrorMessage("user is not operator");
}

void Channel::removeTopicRestriction(User who) {
		if (userIsOper(who))
	{
		if (_topicRestrictionOn == true)
			_topicRestrictionOn = false;
		else 
			throw CustomErrorMessage("channel already have topic restriction off");
	}
	else 
			throw CustomErrorMessage("user is not operator");
}

void Channel::setOperator(User &who, User &target) {

	if (userIsOper(who)) {
		for (vector<User>::iterator it = _userList.begin(); it != _userList.end(); it++){
			if (it->getNickname() == target.getNickname()){
				_operatorList.push_back(target);
				return;
			}
		}
		throw CustomErrorMessage("Error: user is not in the channel");
	}
	throw CustomErrorMessage(who.getNickname() + " is not a channel operator");
}

void Channel::removeOperator(User &who, User &target) {

	if (userIsOper(who)) {
		for (vector<User>::iterator it = _operatorList.begin(); it != _operatorList.end(); it++){
			if (it->getNickname() == target.getNickname()){
				_operatorList.erase(it);
				return;
			}
		}
		throw CustomErrorMessage("Error: user is already not a operator in the channel");
	}
	throw CustomErrorMessage(who.getNickname() + " is not a channel operator");
}

void Channel::setMaxUsers(User who, unsigned int sizeMax) {
	if (userIsOper(who))
		_maxUser = sizeMax;
}

void Channel::removeMaxUsersRestriction(User who)
{
	if (userIsOper(who))
		_maxUser = UINT_MAX;
}

// ---------------------------------------------------- //
// -------------------- EXCEPTIONS -------------------- //
// ---------------------------------------------------- //

Channel::CustomErrorMessage::CustomErrorMessage(string msg):
_msg("Error: " + msg)
{}

Channel::CustomErrorMessage::~CustomErrorMessage() throw() {}

const char *Channel::CustomErrorMessage::what() const throw() {
	return _msg.c_str();
}

// ---------------------------------------------------- //
// -------------------- OVERLOAD << ------------------- //
// ---------------------------------------------------- //

std::ostream & operator<<(std::ostream &o, const Channel &rhs) {
	vector<User> userList = rhs.getUserList();
	vector<User> operList = rhs.getAdmin();
	o << "Chanel name: " << rhs.getName() << endl;
	for (vector<User>::iterator it = operList.begin(); it != userList.end(); it++) {
		o << it->getNickname() << ", ";
	}
	o << "Topic: " << rhs.getTopic() << endl;
	o << "Users: ";
	for (vector<User>::iterator it = userList.begin(); it != userList.end(); it++) {
		o << it->getNickname() << ", ";
	}
	return o;
}