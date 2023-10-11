#include "../include/Channel.hpp"

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

Channel::Channel(const string& name, const User& userCreator, string *key):
		_name(name),
		_key(key),
		_maxUser(UINT_MAX),
		_inviteRestrictionOn(false),
		_topicRestrictionOn(false)
{
	cout << "Channel constructor called" << endl; // TODO Only for test
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
	_operatorName = userCreator.getUsername();

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

string Channel::getAdmin(void) const {
	return _operatorName;
}

const vector<User> &Channel::getUserList(void) const {
	return _userList;
}

void Channel::addUser(const User& who, const User& newUser, string *key) {
	cout << "Channel::addUser called for user: " << newUser.getNickname() << endl;
	if (_maxUser <= _userList.size())
		throw exception(); // channel is full
	for (vector<User>::iterator it = _userList.begin(); it != _userList.end(); it++){
		if (it->getNickname() == newUser.getNickname()){
			throw std::exception();
		}
	}
	_userList.push_back(newUser);
	(void)who; // TODO remove
	(void)key; // TODO remove
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
	_topic = newTopic;
	(void)who; // TODO remove
}

const string Channel::getTopic(void) const {
	return _topic;
}

void Channel::setInviteRestriction(User who) {
	_inviteRestrictionOn = !_inviteRestrictionOn;
	(void)who; // TODO remove
}

void Channel::setTopicRestriction(User who) {
	_topicRestrictionOn = !_topicRestrictionOn;
	(void)who; // TODO remove
}

void Channel::setOperator(User who, User target) {
	(void)who; // TODO remove
	if (who.getUsername() == _operatorName) {
		for (vector<User>::iterator it = _userList.begin(); it != _userList.end(); it++){
			if (it->getUsername() == target.getUsername()){
				_operatorName = target.getUsername();
				return;
			}
		}
		throw exception(); // user is not in the channel
	}
	throw exception(); // who is not the channel operator
}

void Channel::setMaxUsers(User who, unsigned int sizeMax) {
	_maxUser = sizeMax;
	(void)who; // TODO remove
}

std::ostream & operator<<(std::ostream &o, const Channel &rhs) {
	vector<User> userList = rhs.getUserList();
	o << "Chanel name: " << rhs.getName() << endl;
	o << "Admin: " << rhs.getAdmin() << endl;
	o << "Topic: " << rhs.getTopic() << endl;
	o << "Users: ";
	for (vector<User>::iterator it = userList.begin(); it != userList.end(); it++) {
		o << it->getUsername() << ", ";
	}
	return o;
}