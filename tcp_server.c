#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>  // For additional Winsock functionality

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    int iResult;

    SOCKET server_fd = INVALID_SOCKET;
    SOCKET new_socket = INVALID_SOCKET;

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *response = "Hello from server!";

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("Socket creation failed: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  // Localhost
    address.sin_port = htons(PORT);                   // Set port to 8080

    iResult = bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    if (iResult == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Step 4: Listen for incoming connections
    iResult = listen(server_fd, 3);
    if (iResult == SOCKET_ERROR) {
        printf("Listen failed: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    printf("Server is running and listening on port %d...\n", PORT);

    while (1) {  // Infinite loop to keep accepting new connections
        // Step 5: Accept an incoming connection (Three-way handshake happens here)
        new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
        if (new_socket == INVALID_SOCKET) {
            printf("Accept failed: %d\n", WSAGetLastError());
            continue;
        }

        printf("Connection accepted.\n");

        // Step 6: Handle data transfer
        memset(buffer, 0, BUFFER_SIZE);
        iResult = recv(new_socket, buffer, BUFFER_SIZE, 0);  // Read data from client
        if (iResult > 0) {
            printf("Client message: %s\n", buffer);  // Print client's message

            // Respond to the client
            send(new_socket, response, strlen(response), 0);
            printf("Response sent to client.\n");
        } else if (iResult == 0) {
            printf("Connection closing...\n");
        } else {
            printf("Recv failed: %d\n", WSAGetLastError());
        }

        // Step 7: Close the client connection (Four-way handshake)
        closesocket(new_socket);
        printf("Connection closed.\n");
    }

    // Step 8: Close the server socket (this part will never be reached in the current loop)
    closesocket(server_fd);
    WSACleanup();

    return 0;
}
