#ifndef CHANNEL_H
# define CHANNEL_H

# include "main.hpp"
//# include "Commands.hpp"
#include <exception>

using namespace std;

class Server;
class User;

class Channel {

public :
	Channel(const string& name, User * userCreator, string key);
	~Channel(void);

	string getName(void) const;
	string getKey(void) const;
	unsigned int getMaxUser(void) const;
	bool getInviteRestrictionOn(void) const;
	bool getTopicRestrictionOn(void) const;
	
	const vector<User *> getAdmin(void) const;
	const vector<User *> getUserList(void) const;
	const string getTopic(void) const;

	bool userIsOper(User &target);

	int addUser(User * newUser, string key);
	void deleteUser(User * targetUser);

	void addInvitedUser (User* invited);
	bool isInvited (User *target);
  
	void deleteUser(const string& nickTarget);

	void setTopic(User who, string newTopic);

	void setInviteRestriction(); // function for +i
	void removeInviteRestriction(); // function for -i

	void setTopicRestriction(); // function for +t
	void removeTopicRestriction(); // function for -t

	void setChannelPassword(string password); // function for -k
	void removeChannelPassword(); // function for -k

	void setOperator(User * target); // function for +o
	void removeOperator(User * target); // function -o

	void setMaxUsers(unsigned int sizeMax); // function for +l
	void removeMaxUsersRestriction(); // function for -l

	bool isInChannel(const string &target);

	class CustomErrorMessage : public exception {
	public:
		CustomErrorMessage(string msg);
		~CustomErrorMessage() throw();
		const char *what() const throw();
	private:
		string _msg;	
	};


private:
	int _id;
	string _name;
	string _key;
	string _topic;
	vector<User *> _operatorList;
	unsigned int _maxUser;
	vector<User *> _userList;
	vector<User *> _invitedUserList;

	bool _inviteRestrictionOn;
	bool _topicRestrictionOn;

	vector<User *>::iterator findUser(User * user);
	vector<User *>::iterator findUser(const string& user);
	Server				*_serv;
};

#endif