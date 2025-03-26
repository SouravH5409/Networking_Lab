#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>



int main() {
    int sock_desc;
    struct sockaddr_in servaddr, clientaddr;
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
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(sock_desc, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        printf("Error in binding\n");
        exit(1);
    }
    printf("Server is running and waiting for requests on port 3004...\n");

    len = sizeof(clientaddr);

    while (1) {
        // Receive request from client
        memset(buffer, 0, sizeof(buffer));
        recvfrom(sock_desc, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientaddr, &len);
        printf("Received request from client: %s\n", buffer);

        if (strcmp(buffer, "time") == 0) {
            // Get current system time
            time_t current_time;
            time(&current_time);
            char *time_str = ctime(&current_time);

            // Send current time to client
            sendto(sock_desc, time_str, strlen(time_str), 0, (struct sockaddr *)&clientaddr, len);
            printf("Sent time to client: %s", time_str);
        }
    }

    close(sock_desc);
    return 0;
}

