#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <sys/socket.h>
#include <netinet/in.h>

#include "data.h"
#include "controller.h"

#define SIZE_OF_BUFFER 1024

class Communication
{
    public:
        Communication(Data &theData);
        ~Communication();

        bool init();

        void run();

    private:
        unsigned int m_thePort;
        char m_recBuffer[SIZE_OF_BUFFER];
        int m_theSocketServer;
        int m_theSocketClient;
        struct sockaddr_in m_theSocketAddressServer;
        struct sockaddr_in m_theSocketAddressClient;
        socklen_t m_conLen;

        Data &m_theData;
        Controller m_theController;
};

#endif // COMMUNICATION_H
