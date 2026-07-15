
#pragma once 

class Server {
    private:
        int _port;
        int _server_fd;
        bool _running;
        void setupSocket();
        void acceptClient();
    
    public:
        explicit Server (int port);
        ~Server();
        void start();
        void stop();
};