#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock_desc;
    struct sockaddr_in servaddr;
    char buffer[1024];
    socklen_t len;

    // Create UDP socket
    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_desc < 0) {
        printf("Error in socket creation\n");
        exit(1);
    }
    printf("Socket created successfully.\n");

    // Configure server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(3004);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(servaddr);

    // Send "time" request to server
    strcpy(buffer, "time");
    sendto(sock_desc, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, len);
    printf("Request sent to server for current time.\n");

    // Receive server response
    memset(buffer, 0, sizeof(buffer));
    recvfrom(sock_desc, buffer, sizeof(buffer), 0, (struct sockaddr *)&servaddr, &len);

    // Print the current time received from server
    printf("Server Response: Current Time - %s\n", buffer);

    close(sock_desc);
    return 0;
}

