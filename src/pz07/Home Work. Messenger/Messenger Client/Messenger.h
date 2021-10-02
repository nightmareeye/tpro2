//
// Created by alex on 08.09.2021.
//

#ifndef MESSENGER_MESSENGER_H
#define MESSENGER_MESSENGER_H

#include "Message.h"
#include "NetworkManager.h"
#include <nlohmann/json.hpp>

class Messenger {
private:
    std::string name;
    std::string my_id;
    NetworkManager *networkManager;

    std::string uniqueName() {
        srand(time(0));
        auto randchar = []() -> char
        {
            const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        std::string str(10,0);
        std::generate_n( str.begin(), 10, randchar );
        return str;
    }
public:
    void PrintMenu(){
        std::cout << "1. Connect to Chat" << std::endl << std::flush;
        std::cout << "2. Send Message to Client" << std::endl << std::flush;
        std::cout << "3. Get Client {Name : ID}" << std::endl << std::flush;
    }

    void ConnectToServer(std::string &ip_addr,int port,int reconnectCount){
        my_id = uniqueName();
        this->networkManager = new NetworkManager(ip_addr,port,my_id,name);
        networkManager->Start(reconnectCount);
        std::function<void(std::string)> callback = [](std::string request){
            nlohmann::json j_message = nlohmann::json::parse(request);
            std::cout << j_message["text"] << std::endl << std::flush;
        };
        nlohmann::json j_msg;
        networkManager->AddMessageToServer(*networkManager->MessageToServer("server","auth","hello server",j_msg,callback));
    }

    void Start(){
        while(true) {
            this->PrintMenu();
            int command;
            std::cin >> command;
            switch (command) {
                case 1: {
                    std::string ip;
                    int port;
                    int count;
                    std::cout << "Input server IP_ADDRESS: " << std::flush;
                    std::cin >> ip;
                    std::cout << "Input Server PORT: " << std::flush;
                    std::cin >> port;
                    std::cin.ignore(32767, '\n');
                    std::cout << "Input your NAME: " << std::flush;
                    std::getline(std::cin,name);
                    std::cout << "Input reconnect count:" << std::flush;
                    std::cin >> count;
                    this->ConnectToServer(ip, port,count);
                    break;
                }
                case 2: {
                    std::string user_id;
                    std::cout << "Input user ID: "<< std::flush;
                    std::cin >>user_id;
                    std::cin.ignore(32767, '\n');
                    std::cout << "Input text message: " << std::flush;
                    std::string message;
                    std::getline (std::cin, message);//необходимо заменить на getline
                    nlohmann::json j_message;
                    j_message["online_userID"] = user_id;
                    std::function<void(std::string)> callback = [](std::string request){
                        return;
                    };
                    networkManager->AddMessageToServer(*networkManager->MessageToServer("client","new_message",message,j_message,callback));
                     break;
                }
                case 3: {
                    nlohmann::json j_message;
                    std::function<void(std::string)> callback = [](std::string request){
                        nlohmann::json j_message = nlohmann::json::parse(request);
                        for(auto it: j_message["users"]){
                            std::cout << "Name: " + it["name"].dump() + " : " + "ClientID: " + it["clientID"].dump() << std::endl;
                        }

                        return;
                    };
                    networkManager->AddMessageToServer(*networkManager->MessageToServer("server","get_online_user","",j_message,callback));
                    break;
                }
            }
        }
    }
};


#endif //MESSENGER_MESSENGER_H
