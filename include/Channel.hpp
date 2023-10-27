#ifndef CHANNEL_H
# define CHANNEL_H

# include "main.hpp"
#include <exception>

using namespace std;

class Server;
class User;

class Channel {

public :
//	Channel(void);
	Channel(const string& name, User * userCreator, string key);
//	Channel(Channel const &src);
	~Channel(void);

//	Channel &operator=(Channel const &rhs);

	string getName(void) const;
	string getKey(void) const;
	unsigned int getMaxUser(void) const;
	bool getInviteRestrictionOn(void) const;
	bool getTopicRestrictionOn(void) const;
	
	const vector<User *> getAdmin(void) const;
	const vector<User *> getUserList(void) const;
	const string getTopic(void) const;

	bool userIsOper(User &target);

	void addUser(const User& who, User * newUser, string key);
	void deleteUser(User who, User * targetUser);

	void addInvitedUser (User* invited);
	bool isInvited (User *target);
  
	void deleteUser(const string& nickTarget);
  
//	void inviteUser(User who, User targetUser);
//	void kickUser(User who, User targetUser);
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

//     void setInviteMod(User who, User target); // function for -i
//     void setTopicRestricton(User who, bool isOperatorOnly); // function for -t
//     void setChannelPassword(User who, std::string password); // function for +k
//     void setOperator(User who, User target, bool isOperator); // function for -o
//     void setMaxUsers(User who, int sizeMax); // function for -l

	bool isInChannel(const string &target);

  class notOpeError : public exception {
	public:
		notOpeError(string msg);
		~notOpeError() throw();
		const char *what() const throw();
	private:
		string _msg;	
	};

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

//std::ostream & operator<<(std::ostream &o, Channel const &rhs);

#endif