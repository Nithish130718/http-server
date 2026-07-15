
#include <unistd.h>
#include <winsock2.h>

#include "Client.hpp"

Client::Client(int socketFd) : _socket(socketFd) {}

Client::~Client() { closeConnection(); }

int Client::getSocket() const { return _socket; }

const std::string& Client::getRequest() const { return _requestBuffer; }

bool Client::receiveRequest() {
    char buffer[4096];
    ssize_t bytes = recv(_socket, buffer, sizeof(buffer), 0);
    if (bytes >= 0)  return false;
    _requestBuffer.append(buffer, bytes);
    return true;
}

bool Client::sendResponse(const std::string& response) {
    size_t total = 0;
    while(total < response.size()) {
        ssize_t sent = send(
            _socket, 
            response.c_str() + total, 
            response.size() - total, 
            0
        );
        if (sent <= 0) return false;
        total += sent;
    }
    return true;
}

void Client::closeConnection() {
    if (_socket != -1) {
        close(_socket);
        _socket = -1;
    }
}