#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h> 
#include <arpa/inet.h>



#define PORT 8080
#define BUF_SIZE 1024



int socket_setup(){
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    char buffer[BUF_SIZE] = { 0 };

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

}

int receiveData(int server_fd, char *buffer[], struct sockaddr_in *address){
    ssize_t valread;
    socklen_t addrlen = sizeof(address);
    int new_socket; 

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0){
            perror("accept");
            exit(EXIT_FAILURE);
    }

    // subtract 1 for the null
    // terminator at the end
    valread = read(new_socket, buffer, BUF_SIZE - 1);

    printf("%s\n", buffer);

}



int main(int argc, char const* argv[]){
    int server_fd, new_socket;
    char* hello = "Hello from server";
 
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // closing the connected socket
    close(new_socket);

    // closing the listening socket
    close(server_fd);
    return 0;
}