//
// Created by alex on 08.09.2021.
//

#ifndef MESSENGERSERVER_CLIENT_H
#define MESSENGERSERVER_CLIENT_H


#include <Poco/Net/StreamSocket.h>
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>
class Client {
private:
    std::string name;
    Poco::Net::StreamSocket *streamSocket;
public:
    Client(std::string name, Poco::Net::StreamSocket* ss){
        this->name = name;
        this->streamSocket = ss;
    }

    bool SendMessage(nlohmann::json &json){
        std::string message = json.dump();
        try{
            this->streamSocket->sendBytes(message.data(),message.length() + 1);
            return true;
        }
        catch(Poco::Exception exception) {
            std::cout << exception.displayText() << std::endl << std::flush;
        }
        return false;
    }

    std::string GetName(){
        return this->name;
    }



};


#endif //MESSENGERSERVER_CLIENT_H
