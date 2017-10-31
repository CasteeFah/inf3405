#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>

class Message {
public:
    Message(std::string user, std::string adress, std::string time, char message[200]);

    friend std::ostream & operator<<(std::ostream &os, Message message);

private:
    std::string user_;
    std::string adress_;
    std::string time_;
    char message_[200];
};

#endif /* end of include guard: MESSAGE_H */
