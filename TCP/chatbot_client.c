#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock_desc;
    struct sockaddr_in servaddr;
    char msg[1024], response[1024];

    // Create socket
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc < 0) {
        printf("Error in socket creation\n");
        exit(1);
    }
    printf("Socket created successfully.\n");

    // Configure server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(3002);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(sock_desc, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        printf("Connection failed.\n");
        exit(1);
    }
    printf("Connected to the chatbot server.\n");

    while (1) {
        memset(msg, 0, sizeof(msg));
        memset(response, 0, sizeof(response));

        // Get input from the user
        printf("You: ");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = 0; // Remove newline character

        // Send message to server
        send(sock_desc, msg, strlen(msg), 0);

        // Check if user wants to exit
        if (strcmp(msg, "bye") == 0) {
            printf("Chat ended.\n");
            break;
        }

        // Receive response from server
        recv(sock_desc, response, sizeof(response), 0);
        printf("Chatbot: %s\n", response);
    }

    close(sock_desc);
    return 0;
}

