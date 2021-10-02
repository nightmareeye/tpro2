//
// Created by alex on 08.09.2021.
//

#ifndef MESSENGERSERVER_SERVER_H
#define MESSENGERSERVER_SERVER_H
#include <map>
#include <iostream>
#include "Client.h"
class Server {
private:
    static Server *_instance ;
    std::map<std::string, Client*> Clients;

protected:
    Server() {

    }

public:
    static Server *Instance() {
        if (_instance == nullptr) // Был ли ранее создан экземпляр класса
        {
            // если нет, то создать единственный экземпляр и вернуть его.
            _instance = new Server();
        }
        return _instance;
    }

    ~Server() {
        delete _instance;
    }

    void AddClient(std::string id, Client &Client) {
        Clients[id] = &Client;
    }

    Client *GetConnectionByID(std::string id) {
        auto it = Clients.find(id);
        return it->second;
    }

    void RemoveConnectionByID(std::string id) {
        auto it = this->Clients.find(id);
        if(it->first != "")
            this->Clients.erase(it);
    }

    std::map<std::string, Client*>* GetClients(){
        return &this->Clients;
    }

};

#endif MESSENGERSERVER_SERVER_H
