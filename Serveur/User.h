#pragma once
#include <string>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class User
{
public:
	User();
	User(std::string newUsername, std::string newPassword);
	~User();
	std::string getUsername();
	std::string getPassword();

private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & username;
		ar & password;
	}
	std::string username;
	std::string password;
};

