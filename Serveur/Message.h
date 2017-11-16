#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

class Message {
public:
	Message();
    Message(std::string user, std::string adress, std::string time, std::string message);

    friend std::ostream & operator<<(std::ostream &os, Message message);

	std::string getUser();
	std::string getAddress();
	std::string getTime();
	std::string getMessage();

private:
    std::string user_;
    std::string address_;
    std::string time_;
	std::string message_;
};

#endif /* end of include guard: MESSAGE_H */
