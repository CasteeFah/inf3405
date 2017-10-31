#pragma once
#include <string>

class User
{
public:
	User();
	~User();
	std::string getUsername();
	std::string getPassword();

private:
	std::string username;
	std::string password;
};
