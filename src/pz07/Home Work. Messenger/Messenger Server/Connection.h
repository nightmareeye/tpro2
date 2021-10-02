//
// Created by alex on 08.09.2021.
//

#include <Poco/Net/TCPServerConnection.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <regex>
#ifndef MESSENGERSERVER_CONNECTION_H
#define MESSENGERSERVER_CONNECTION_H

#include "Server.h"
#include "Client.h"
using namespace std;
Server* Server::_instance = nullptr;

class newConnection : public Poco::Net::TCPServerConnection {
private:
    std::string id;
    std::string name;
public:
    newConnection(const Poco::Net::StreamSocket &s) :
            Poco::Net::TCPServerConnection(s) {
    }

    nlohmann::json GetListOnlineUser(Server &server){
        nlohmann::json online_user;
        for(auto it : *server.GetClients()){
            nlohmann::json user;
            user["clientID"] = it.first;
            user["name"] = it.second->GetName();
            online_user.push_back(user);
        }
        return online_user;
    }

    void run() {
        cout << "New connection from: " << socket().peerAddress().host().toString() << endl << flush;
        bool isOpen = true;
        Poco::Timespan timeOut(10, 0);
        char incommingBuffer[1000];
        while (isOpen) {

            if (socket().poll(timeOut, Poco::Net::Socket::SELECT_READ) == false) {
                cout << "TIMEOUT!" << endl << flush;
            } else {
                cout << "RX EVENT!!! ---> " << flush;
                int nBytes = -1;

                try {
                    nBytes = socket().receiveBytes(incommingBuffer, sizeof(incommingBuffer));
                }
                catch (Poco::Exception &exc) {
                    //Handle your network errors.
                    cerr << "Network error: " << exc.displayText() << endl;
                    isOpen = false;
                }

                if (nBytes == 0) {
                    cout << "Client closes connection!" << endl << flush;
                    isOpen = false;
                    auto server = Server::Instance();
                    server->RemoveConnectionByID(this->id);
                } else {
                    std::string message(incommingBuffer);
                    std::cout << message << std::endl << std::flush;
                    nlohmann::json j_message = nlohmann::json::parse(message);
                    auto server = Server::Instance();
                    if (j_message["from"] == "server") {
                        Client *client;
                        nlohmann::json message_to_client;
                        if(j_message["command"] == "auth"){
                            std::string client_id = j_message["text"]["clientID"].dump();
                            server->RemoveConnectionByID(id);
                            client = new Client(regex_replace(j_message["text"]["name"].dump(),regex("\""),""), &socket());
                            this->id = regex_replace(client_id,regex("\""),"");
                            server->AddClient(this->id, *client);
                            message_to_client["text"] = "Hello, " + client->GetName() + " You join to chat";
                        }
                        else if(j_message["command"] == "get_online_user"){
                            client = server->GetConnectionByID(this->id);
                            nlohmann::json online_user = this->GetListOnlineUser(*server);
                            message_to_client["users"] = online_user;
                        }
                        message_to_client["command"] = "response";
                        message_to_client["user_message_id"] = j_message["message_id"];
                        std::cout << message_to_client.dump() << std::endl << std::flush;
                        while(!client->SendMessage(message_to_client));
                    }
                    else if(j_message["from"] == "client"){
                        std::string user_id = j_message["text"]["online_userID"];
                        user_id = regex_replace(user_id,regex("\""),"");
                        auto client = server->GetConnectionByID(user_id);
                        if(client == NULL){
                            nlohmann::json j_exception;
                            j_exception["command"] = "exception";
                            j_exception["exception"] = "Client close connection or you input not valid ID";
                            std::cout << j_exception.dump() << std::endl << std::flush;
                            socket().sendBytes(j_exception.dump().data(),j_exception.dump().length()+1);
                        }
                        else {
                            nlohmann::json message;
                            message["from"] = "client";
                            message["command"] = "new_message";
                            message["text"] = j_message["text"];
                            std::cout << message.dump() << std::endl << std::flush;
                            client->SendMessage(message);
                        }
                    }
                }
            }
        }
        cout << "Connection finished!" << endl << flush;
    }
};
#endif MESSENGERSERVER_CONNECTION_H
