#include "communication.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>

Communication::Communication(Data &theData)
    : m_thePort(8430)
    , m_theSocketServer(-1)
    , m_theSocketClient(-1)
    , m_theData(theData)
    , m_theController(m_theData)
{

}

Communication::~Communication()
{
    std::cout << "Communication::~Communication" << std::endl;
}

bool Communication::init()
{
    ConfigData cfData = m_theData.getConfig();
    m_thePort=cfData->getPort();
    string ip = cfData->getIP();
    m_theSocketServer = socket(AF_INET, SOCK_STREAM, 0);
    m_theSocketAddressServer.sin_family = AF_INET;
    m_theSocketAddressServer.sin_port = htons(m_thePort);
    m_theSocketAddressServer.sin_addr.s_addr = INADDR_ANY;
    if (bind(m_theSocketServer, (struct sockaddr*) &m_theSocketAddressServer,
             sizeof(m_theSocketAddressServer)) < 0) {
        std::cout << "Bind failed." << std::endl;
        return false;

    }
    if (listen(m_theSocketServer, 10) < 0) {
        std::cout << "Listen failed." << std::endl;
        return false;

    }
    printf("Waiting for connection ...\n");
    return true;
}

void Communication::run()
{
    while (m_theSocketClient = accept(m_theSocketServer,
                                      (struct sockaddr*) &m_theSocketAddressClient,
                                      &m_conLen))
    {
        int recBytes = recv(m_theSocketClient, m_recBuffer, SIZE_OF_BUFFER, 0);
        std::string str(m_recBuffer);
        std::cout << "Communication::run() Message: " << str << std::endl;

        m_theData.setReceiveData(str);

        m_theController.move();
        // setServo via Controller
        // set value to sendData
        // send sendData
        
        string strAnswer = "";
        strAnswer=m_theData.getSendData();
        m_theData.setSendData(strAnswer);

        write(m_theSocketClient,strAnswer.c_str(),strAnswer.length());
        //close(m_theSocketClient);
    }
}
