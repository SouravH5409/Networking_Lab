#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

// Function to generate simple chatbot responses
void chatbot_response(char *client_msg, char *response) {
    if (strstr(client_msg, "hello") != NULL) {
        strcpy(response, "Hi there! How can I help you?");
    } else if (strstr(client_msg, "how are you") != NULL) {
        strcpy(response, "I'm just a chatbot, but I'm doing great! How about you?");
    } else if (strstr(client_msg, "bye") != NULL) {
        strcpy(response, "Goodbye! Have a great day!");
    } else {
        strcpy(response, "I'm not sure how to respond to that. Can you ask something else?");
    }
}

int main() {
    int sock_desc, temp_sock_desc, len;
    struct sockaddr_in servaddr, client;
    char client_msg[1024], response[1024];

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
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
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
    printf("Server is listening on port 3002...\n");

    len = sizeof(client);
    temp_sock_desc = accept(sock_desc, (struct sockaddr *)&client, &len);
    if (temp_sock_desc < 0) {
        printf("Error in accepting connection\n");
        exit(1);
    }
    printf("Client connected.\n");

    while (1) {
        memset(client_msg, 0, sizeof(client_msg));
        memset(response, 0, sizeof(response));

        // Receive client message
        recv(temp_sock_desc, client_msg, sizeof(client_msg), 0);
        printf("Client: %s\n", client_msg);

        // Check if client wants to exit
        if (strcmp(client_msg, "bye") == 0) {
            strcpy(response, "Goodbye! Chat ended.");
            send(temp_sock_desc, response, strlen(response), 0);
            break;
        }

        // Generate chatbot response
        chatbot_response(client_msg, response);
        send(temp_sock_desc, response, strlen(response), 0);
    }

    close(temp_sock_desc);
    close(sock_desc);
    return 0;
}

