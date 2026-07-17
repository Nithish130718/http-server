
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <ws2tcpip.h>
#include <winsock2.h>

#include "Server.hpp"
#include "Client.hpp"

Server::Server(int port) 
    : _port(port), 
      _server_fd(-1),
      _running(false)
{}

Server::~Server() { stop(); }

void Server::setupSocket() {
    _server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_fd < 0)  throw std::runtime_error("socket failed!");
    int opt = 1;
    setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
    sockaddr_in address;
    std::memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(_port);
    if (bind(_server_fd, 
             (sockaddr*) &address, 
             sizeof(address)) < 0)
             throw std::runtime_error("bind failed");
    if (listen(_server_fd, SOMAXCONN) < 0)  throw std::runtime_error("listen failed");
}

void Server::acceptClient() {
    sockaddr_in clientAddr;
    socklen_t len = sizeof(clientAddr);
    int clientFd = ::accept(
        _server_fd, 
        (sockaddr*) &clientAddr,
        &len
    );
    if (clientFd < 0)  return;
    Client client(clientFd);
    if (!client.receiveRequest())  return;
    std::string response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 5\r\n"
        "\r\n"
        "Hello";
    client.sendResponse(response);
}

void Server::start() {
    setupSocket();
    _running = true;
    while(_running)  acceptClient();
}

void Server::stop() {
    if (_server_fd != -1) {
        close(_server_fd);
        _server_fd = -1;
    }
    _running = false;
}



