#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

class TCPMessage {
public:
    uint8_t data[64];
    uint8_t length;

    TCPMessage() { }

    TCPMessage(uint8_t length): length(length) { }

    TCPMessage(uint8_t *data, uint8_t length) : length(length) {
        for(int i = 0; i < length; i++)
            this->data[i] = data[i];
    }

    void init(uint8_t *data, uint8_t length) {
        this -> length = length;
        for(int i = 0; i < length; i++)
            this->data[i] = data[i];
    }
};

class TCPServer {
private:
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    uint8_t buffer[1024] = { 0 };

public:
    TCPServer(uint16_t port){
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
    
        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        if (listen(server_fd, 3) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
    }

    bool ReadMessage(TCPMessage* message){
        valread = read(new_socket, buffer, 1024);
        message->init(buffer, valread);
    }

    int WriteMessage(TCPMessage* message){
        return send(new_socket,(const char*) message->data, message->length, 0);
    }

    void close_socket(){
        close(new_socket);
        shutdown(server_fd, SHUT_RDWR);
    }

};