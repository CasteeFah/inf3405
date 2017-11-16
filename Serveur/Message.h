#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>

class Message {
public:
    Message(std::string user, std::string adress, std::string time, std::string message);

    friend std::ostream & operator<<(std::ostream &os, Message message);

private:
    std::string user_;
    std::string address_;
    std::string time_;
	std::string message_;
};

#endif /* end of include guard: MESSAGE_H */
