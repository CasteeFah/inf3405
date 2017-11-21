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
    Message(std::string user, std::string adress, std::string port, tm time, std::string message);
	std::string timeToString(tm date);
	std::string messageToString();
    friend std::ostream & operator<<(std::ostream &os, Message message);

    std::string user_;
    std::string address_;
    std::string time_;
	std::string message_;
};

#endif /* end of include guard: MESSAGE_H */
