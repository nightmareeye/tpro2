#include <iostream>
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerParams.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/Socket.h"
#include <nlohmann/json.hpp>
#include "Connection.h"
using namespace std;


int main(int argc, char** argv) {

    //Create a server socket to listen.
    Poco::Net::ServerSocket svs(1234);

    //Configure some server params.
    Poco::Net::TCPServerParams* pParams = new Poco::Net::TCPServerParams();
    pParams->setMaxThreads(4);
    pParams->setMaxQueued(4);
    pParams->setThreadIdleTime(100);

    //Create your server
    Poco::Net::TCPServer myServer(new Poco::Net::TCPServerConnectionFactoryImpl<newConnection>(), svs, pParams);
    myServer.start();

    while(true);

    return 0;
}