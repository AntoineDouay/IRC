#ifndef CHANNEL_H
# define CHANNEL_H

# include "main.hpp"

class Server;
class User;

class Channel {

public :
    //Channel(void);
    Channel(const std::string& name, User& userCreator, Server &serv);
    //Channel(Channel const &src);
    ~Channel(void);

    //Channel &operator=(Channel const &rhs);

    std::string getName(void) const;
    std::string getAdmin(void) const;
    const std::vector<User> &getUserList(void) const;

    void addUser(User who, User newUser);
    void deleteUser(User who, User targetUser);
    void inviteUser(User who, User targetUser);
    void kickUser(User who, User targetUser);
    void setTopic(User who, std::string newTopic);

    void setInviteMod(User who, User target); // function for -i
    void setTopicRestricton(User who, bool isOperatorOnly); // function for -t
    void setChannelPassword(User who, std::string password); // function for +k
    void setOperator(User who, User target, bool isOperator); // function for -o
    void setMaxUsers(User who, int sizeMax); // function for -l

	void	removePassword(); // -k

	std::string getName();

private:
    int _id;
    std::string 		_name;
    std::string 		_key;
    std::string 		_topic;
    //std::string 		_operatorName;
    std::vector<User *> _userList;

	Server				*_serv;

};

//std::ostream & operator<<(std::ostream &o, Channel const &rhs);

#endif