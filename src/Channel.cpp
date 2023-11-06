#include "../include/Channel.hpp"
#include <cstdio>
#include <exception>

Channel::Channel(const string& name, User * userCreator, string key):
		_name(name),
		_key(key),
		_maxUser(UINT_MAX),
		_inviteRestrictionOn(false),
		_topicRestrictionOn(false)
{
	if ( name.length() <= 0 || 51 <= name.length() ){
		throw std::exception();
	}
	switch (_name[0]) {
		case '#':
			break;
		default:
			throw exception();
	}
	_userList.push_back(userCreator);
	_operatorList.push_back(userCreator);
	userCreator->addChannel(this);
	(void)_id;
	(void)_serv;
}


Channel::~Channel(void) {

}

string Channel::getName(void) const {
	return _name;
}

const vector<User *> Channel::getAdmin(void) const {
	return _operatorList;
}

const vector<User *> Channel::getUserList(void) const {
	return _userList;
}

string 	Channel::getKey(void) const
{
	return _key;
}
unsigned int Channel::getMaxUser(void) const
{
	return _maxUser;
}
bool Channel::getInviteRestrictionOn(void) const
{
	return _inviteRestrictionOn;
}
bool Channel::getTopicRestrictionOn(void) const
{
	return _topicRestrictionOn;
}
	
bool Channel::userIsOper(User &target)
{
	vector<User *>::iterator it = _operatorList.begin();
	for (; it != _operatorList.end(); it++)
		if ((*it)->getNickname() == target.getNickname())
			return true;
	return false;
}

int Channel::addUser(User * newUser, string key) {

	if (_key != "" && key != _key)
		return 0;

	if (_maxUser <= _userList.size())
		return 1;

	for (vector<User *>::iterator it = _userList.begin(); it != _userList.end(); it++){
		if ((*it)->getNickname() == newUser->getNickname()){
			return 2;
		}
	}
	_userList.push_back(newUser);
	return -1;
}

void	Channel::addInvitedUser(User *invited)
{
	_invitedUserList.push_back(invited);
}

bool	Channel::isInvited(User *target)
{
	for(std::vector<User *>::iterator it = _invitedUserList.begin(); it != _invitedUserList.end(); it++)
		if ((*it)->getNickname() == target->getNickname())
			return true;
	return false;
}

vector<User *>::iterator Channel::findUser(User * user) {
	vector<User *>::iterator it;
	for (it = _userList.begin(); it != _userList.end(); it++){
		if (user->getUsername() == (*it)->getUsername())
			return it;
	}
	return it;
}

void Channel::deleteUser(User * targetUser) {
	_userList.erase(findUser(targetUser));
}

void Channel::setTopic(User who, string newTopic) {
	if (userIsOper(who) || !_topicRestrictionOn)
		_topic = newTopic;
}

const string Channel::getTopic(void) const {
	return _topic;
}

void Channel::setChannelPassword(std::string password)
{
	_key = password;
}

void Channel::removeChannelPassword()
{
	_key = "";
}

void Channel::setInviteRestriction() {
	if (_inviteRestrictionOn == false)
		_inviteRestrictionOn = true;
}

void Channel::removeInviteRestriction() {

	if (_inviteRestrictionOn == true)
	{
		_inviteRestrictionOn = false;
		_invitedUserList.clear();
	}
}

void Channel::setTopicRestriction() {
	if (_topicRestrictionOn == false)
		_topicRestrictionOn = true;
}

void Channel::removeTopicRestriction() {
	if (_topicRestrictionOn == true)
		_topicRestrictionOn = false;
}

void Channel::setOperator(User * target) {

	for (vector<User *>::iterator it = _userList.begin(); it != _userList.end(); it++){
		if ((*it)->getNickname() == target->getNickname()){
			_operatorList.push_back(target);
			return;
		}
	}
}

void Channel::removeOperator(User * target) {
	for (vector<User *>::iterator it = _operatorList.begin(); it != _operatorList.end(); it++){
		if ((*it)->getNickname() == target->getNickname()){
			_operatorList.erase(it);
			return;
		}
	}
}

void Channel::setMaxUsers(unsigned int sizeMax) {
	_maxUser = sizeMax;
}

void Channel::removeMaxUsersRestriction()
{
	_maxUser = UINT_MAX;
}

bool Channel::isInChannel(const string &target) {
	vector<User *>::iterator it = _userList.begin();
	for (; it != _userList.end(); it++) {
		if ((*it)->getNickname() == target) {
			return true;
		}
	}
	return false;
}

void Channel::deleteUser(const string& nickTarget) {
	vector<User *>::iterator user = findUser(nickTarget);
	_userList.erase(user);
}

vector<User *>::iterator Channel::findUser(const string &user) {
	vector<User *>::iterator it = _userList.begin();
	for (; it != _userList.end(); it++) {
		if ((*it)->getNickname() == user) {
			return it;
		}
	}
	return _userList.end();
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
	vector<User *> userList = rhs.getUserList();
	vector<User *> operList = rhs.getAdmin();
	o << "Chanel name: " << rhs.getName() << endl;
	for (vector<User *>::iterator it = operList.begin(); it != userList.end(); it++) {
		o << (*it)->getNickname() << ", ";
	}
	o << "Topic: " << rhs.getTopic() << endl;
	o << "Users: ";
	for (vector<User *>::iterator it = userList.begin(); it != userList.end(); it++) {
		o << (*it)->getNickname() << ", ";
	}
	return o;
}