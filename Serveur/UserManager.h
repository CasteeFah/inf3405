#pragma once
#include <string>
#include "User.h"
#include <vector>
#include <memory>

class UserManager;
typedef std::shared_ptr<UserManager> Ptr_UserManager;

class UserManager
{
public:
	static Ptr_UserManager getInstance();
	UserManager();
	~UserManager();
	User getUser(int userId);
	int findUserId(std::string username);
	void addUser(User user);

private:

	std::vector<User> users;
	static Ptr_UserManager thisInstance;
};

