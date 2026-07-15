
#pragma once 

#include <string>
#include <vector>

class Client{
    private:
        int _socket;
        std::string _requestBuffer;
    
    public:
        explicit Client(int socketFd);
        ~Client();
        int getSocket() const;
        const std::string& getRequest() const;
        bool receiveRequest();
        bool sendResponse(const std::string& response);
        void closeConnection();
};