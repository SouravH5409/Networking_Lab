#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock_desc, temp_sock_desc, len, num1, num2, sum;
    struct sockaddr_in servaddr, client;

    // Create socket
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc < 0) {
        printf("Error in socket creation\n");
        exit(1);
    }
    printf("Socket created successfully.\n");

    // Server address configuration
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(3002); // Port 3002
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(sock_desc, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        printf("Error in binding\n");
        exit(1);
    }
    printf("Binding successful.\n");

    // Listen for connections
    if (listen(sock_desc, 5) < 0) {
        printf("Error in listening\n");
        exit(1);
    }
    printf("Server listening on port 3002...\n");

    len = sizeof(client);
    temp_sock_desc = accept(sock_desc, (struct sockaddr *)&client, &len);
    if (temp_sock_desc < 0) {
        printf("Error in accepting connection\n");
        exit(1);
    }
    printf("Client connected.\n");

    // Receive two integers from client
    recv(temp_sock_desc, &num1, sizeof(num1), 0);
    recv(temp_sock_desc, &num2, sizeof(num2), 0);
    printf("Received numbers: %d, %d\n", num1, num2);

    // Calculate sum
    sum = num1 + num2;
    printf("Calculated sum: %d\n", sum);

    // Send the sum back to client
    send(temp_sock_desc, &sum, sizeof(sum), 0);
    printf("Sum sent to client.\n");

    // Close sockets
    close(temp_sock_desc);
    close(sock_desc);
    return 0;
}

