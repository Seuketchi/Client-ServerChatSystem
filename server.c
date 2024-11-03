#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024 // Define a buffer size for messages

int main()
{

    // create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        printf("Socket Creation Failed");
        exit(1);
    }

    // define server address
    struct sockaddr_in serverAddress;           // creates serverAddress entity
    serverAddress.sin_family = AF_INET;         // setting address family/type of address == IPv4
    serverAddress.sin_addr.s_addr = INADDR_ANY; // accept any message from any address
    serverAddress.sin_port = htons(8000);       // htons convert port number format that suitable for network communication

    // bind socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("Bind Failed");
        exit(1);
    }

    // listen connections
    if (listen(serverSocket, 5) < 0)
    { // 5 : maximum connections
        perror("Listen failed");
        exit(1);
    }

    // accepts connections
    struct sockaddr_in clientAddress;
    socklen_t clientLen = sizeof(clientAddress);
    int clientSocket;
    char buffer[BUFFER_SIZE];

    while (1)
    {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientLen);
        if (clientSocket < 0)
        {
            perror("Accept failed");
            continue; // if failed, continue to next iteration
        }
        printf("Client connected!\n");

        while (1)
        {
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesReceived > 0)
            {
                buffer[bytesReceived] = '\0';
                printf("Client: %s\n", buffer);
            }
        }

        close(clientSocket);
    }

    close(serverSocket);
    return 0;
}