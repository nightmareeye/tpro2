#include <iostream>
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerParams.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/Socket.h"
#include <nlohmann/json.hpp>
#include <thread>

void ServerMessaging(Poco::Net::StreamSocket &ss){
    bool isOpen = true;
    Poco::Timespan timeOut(10,0);
    char incommingBuffer[1000];
    while(isOpen){
        if (ss.poll(timeOut,Poco::Net::Socket::SELECT_READ) == false){
            std::cout << "TIMEOUT!" << std::endl << std::flush;
        }
        else{
            std::cout << "RX EVENT!!! ---> "   << std::flush;
            int nBytes = -1;

            try {
                nBytes = ss.receiveBytes(incommingBuffer, sizeof(incommingBuffer));
            }
            catch (Poco::Exception& exc) {
                //Handle your network errors.
                std::cerr << "Network error: " << exc.displayText() << std::endl;
                isOpen = false;
            }

            if (nBytes==0){
                std::cout << "Client closes connection!" << std::endl << std::flush;
                isOpen = false;
            }
            else{
                std::string command(incommingBuffer);
            }
        }
    }
    std::cout << "Connection finished!" << std::endl << std::flush;
}


int main() {

    Poco::Net::StreamSocket ss;
    ss.connect(Poco::Net::SocketAddress("localhost",1234));

    std::thread startMessaging(ServerMessaging,std::ref(ss));

    while (true);

    return 0;
}
