//
// Created by alex on 08.09.2021.
//

#ifndef MESSENGER_MESSAGE_H
#define MESSENGER_MESSAGE_H

#include <iostream>
#include <nlohmann/json.hpp>
#include <iomanip>
class Message {
private:
    std::string user_id;
    std::string id;
    std::string create_time;
    nlohmann::json str_message;
    std::function<void(std::string)> callback;
    std::string command;

    std::string GetCurrentTime(){
        std::time_t time = std::time(0);
        std::tm* local = std::localtime(&time);
        return "";
    }

    std::string CreateIdMessage(){
        srand(time(0));
        auto randchar = []() -> char
        {
            const char charset[] = "0123456789";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        std::string str(20,0);
        std::generate_n( str.begin(), 20, randchar );
        return str;
    }
public:
    Message(std::string user_id, nlohmann::json j_message,std::string cmd,std::function<void(std::string)> &func){
        this->user_id = user_id;
        this->str_message = j_message;
        this->callback = func;
        this->create_time = GetCurrentTime();
        this->id = CreateIdMessage();
        this->command = cmd;
    }

    std::string GetTextMessage(){
        return this->str_message;
    }

    std::string GetID(){
        return this->id;
    }

    nlohmann::json GetJsonMessage(){
        nlohmann::json j_message;
        j_message["from"] = this->user_id;
        j_message["text"] = this->str_message;
        j_message["time"] = this->create_time;
        j_message["message_id"] = this->id;
        j_message["command"] = this->command;
        return j_message;
    }

    std::function<void(std::string)> GetCallbackFunc(){
        return this->callback;
    }
};


#endif //MESSENGER_MESSAGE_H
