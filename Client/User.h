#pragma once
#include <string>

class User
{
public:
	User();
	~User();
	bool validateUser(User user);
	std::string getUserId();
	std::string getPassword();

private:
	std::string userId;
	std::string password;
};

