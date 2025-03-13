#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>  // For inet_addr()
#include <unistd.h>     // For close()

int main() {
    char buff[100];
    int k;
    struct sockaddr_in server;
    int sock_desc;

    // Create socket
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1) {
        printf("Error in socket creation\n");
        return 1;
    }

    // Set up server address
    server.sin_family = AF_INET;
    server.sin_port = 3003;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  // Change this to the server's IP address if needed

    // Connect to the server
    k = connect(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k == -1) {
        printf("Error in connecting to server!\n");
        return 1;
    }

    // Prompt for data to send
    printf("Enter data to be sent: ");
    fgets(buff, sizeof(buff), stdin);

    // Remove the newline character if it exists
    buff[strcspn(buff, "\n")] = 0;

    // Send data to server
    k = send(sock_desc, buff, strlen(buff), 0);
    if (k == -1) {
        printf("Error in sending data!\n");
        return 1;
    }

    // Close the socket
    close(sock_desc);
    return 0;
}

