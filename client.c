#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFFER_SIZE 1024 // Define a buffer size for messages

int main()
{

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        perror("Socket creation failed");
        exit(1);
    }

    // define server address
    struct sockaddr_in serverAddress;                       // creates serverAddress entity
    serverAddress.sin_family = AF_INET;                     // setting address family/type of address == IPv4
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // accept from 127.0.0.1 (local address)
    serverAddress.sin_port = htons(8000);                   // htons convert port number format that suitable for network communication

    // connect to server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("Connection Failed");
        exit(1);
    }

    // send message
    while (1)
    {
        char message[BUFFER_SIZE];

        printf("Message: ");
        fgets(message, BUFFER_SIZE, stdin);

        message[strcspn(message, "\n")] = 0;

        // exit loop
        if (strcmp(message, "exit") == 0)
        {
            break;
        }

        send(clientSocket, message, strlen(message), 0);
    }

    close(clientSocket);

    return 0;
}