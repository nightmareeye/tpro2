//
// Created by alex on 08.09.2021.
//

#ifndef MESSENGER_NETWORKMANAGER_H
#define MESSENGER_NETWORKMANAGER_H

#endif //MESSENGER_NETWORKMANAGER_H

#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerParams.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/Socket.h"
#include <nlohmann/json.hpp>

#include <iostream>
#include "queue"
#include "map"
#include <thread>
#include "Message.h"
class NetworkManager{
private:
    std::string name;
    std::string id;

    Poco::Timespan* timeSpan;
    bool status = true;
    //ip-адресс сервера
    std::string ip_addr;
    //порт сервера
    int port;
    //сокет, который будет пытаться подключиться к серверу
    Poco::Net::StreamSocket streamSocket;

    std::thread thread_server;

    std::thread thread_client;

    std::queue<Message> message_to_server;

    std::map<std::string,std::function<void(std::string)>> message_to_client;

    bool Connect(){
        try{
            this->streamSocket.connect(Poco::Net::SocketAddress( this->ip_addr,this->port));
            return true;
        }
        catch (Poco::Exception exception){
            std::cout << exception.displayText() << std::endl << std::flush;
            this->streamSocket.close();
        }
        return false;
    }

    void SendMessage(Message message){
        std::string str_message = message.GetJsonMessage().dump();
        try{
            this->streamSocket.sendBytes(str_message.data(),str_message.length()+1);
        }
        catch (Poco::Exception exception){
            std::cout << exception.message() << std::endl << std::flush;
            this->message_to_server.push(message);
        }
    }

    void serverThread(int reconnectCount) {
        char incommingBuffer[1000];
        while (status) {
            if (streamSocket.poll(*timeSpan, Poco::Net::Socket::SELECT_READ) == false) {

            } else {
                int nBytes = -1;

                try {
                    nBytes = streamSocket.receiveBytes(incommingBuffer, sizeof(incommingBuffer));
                }
                catch (Poco::Exception &exc) {
                    //Handle your network errors.
                    std::cerr << "Network error: " << exc.displayText() << std::endl;

                }

                if (nBytes == 0) {
                    std::cout << "Client closes connection!" << std::endl << std::flush;
                    std::cout << "Start reconnect" << std::endl << std::flush;
                    int count = 0;
                    while(count < reconnectCount){
                        if(this->Connect()) {
                            std::cout << "Reconnect success" <<std::endl << std::flush;
                            std::function<void(std::string)> callback = [](std::string request){
                                nlohmann::json j_message = nlohmann::json::parse(request);
                                std::cout << j_message["text"].dump() << std::endl << std::flush;
                            };
                            nlohmann::json j_msg;
                            AddMessageToServer(*MessageToServer("server","auth","hello server",j_msg,callback));
                            break;
                        }
                        else {
                            count ++;
                            using namespace std::chrono_literals;
                            std::this_thread::sleep_for(2000ms);
                        }
                        if(count == reconnectCount)
                            status = false;
                    }
                } else {
                    std::string request(incommingBuffer);
                    nlohmann::json json = nlohmann::json::parse(request);
                    if(json["command"] == "response")
                        (message_to_client[json["user_message_id"]])(request);
                    else if(json["command"] == "new_message"){
                        std::cout << json << std::endl <<std::flush;
                    }
                    else if(json["command"] == "exception"){
                        std::cout << json["exception"] << std::endl << std::flush;
                    }
                }
            }
        }

        std::cout << "Server thread stop" << std::endl << std::flush;
    }

    void clientThread(){
        while(status){
            if(!message_to_server.empty()){
                try {
                    Message message = message_to_server.front();
                    message_to_server.pop();
                    this->message_to_client[message.GetID()] = message.GetCallbackFunc();
                    this->SendMessage(message);
                }catch(std::exception ex) {
                    std::cout << ex.what() << std::endl << std::flush;
                }
            }
        }
        std::cout << "Client thread stop" << std::endl << std::flush;
    }

public:
    NetworkManager(const std::string& ip_addr, int port, std::string uid,std::string name){
        this->ip_addr = ip_addr;
        this->port = port;
        this->id = uid;
        this->name = name;
    }

    void Start(int reconnectCount){
            this->timeSpan = new Poco::Timespan(10,0);
            if(this->Connect())
            {
                thread_server = std::thread(&NetworkManager::serverThread,this,reconnectCount);
                thread_client = std::thread(&NetworkManager::clientThread,this);
            }
    }

    void AddMessageToServer(Message& message){
        this->message_to_server.push(message);
    }

    Message* MessageToServer(std::string from,std::string command, std::string msg, nlohmann::json j_message,std::function<void(std::string)> callback){
        j_message["clientID"] = id;
        j_message["name"] = name;
        j_message["message"] = msg;
        Message *message = new Message(from,j_message,command,callback);
        return message;
    }

};