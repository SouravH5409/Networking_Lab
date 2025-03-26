#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

// Function to check if a number is prime
int is_prime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;
    }
    return 1;
}

int main() {
    int sock_desc;
    struct sockaddr_in servaddr, clientaddr;
    char buffer[1024];
    int num;
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
    servaddr.sin_port = htons(3003);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the address and port
    if (bind(sock_desc, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        printf("Error in binding\n");
        exit(1);
    }
    printf("Server is listening on port 3003...\n");

    len = sizeof(clientaddr);

    while (1) {
        // Receive number from client
        memset(buffer, 0, sizeof(buffer));
        recvfrom(sock_desc, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientaddr, &len);
        num = atoi(buffer);
        printf("Received number: %d\n", num);

        // Check if the number is prime
        char result[50];
        if (is_prime(num)) {
            strcpy(result, "Prime");
        } else {
            strcpy(result, "Not Prime");
        }

        // Send the result back to client
        sendto(sock_desc, result, strlen(result), 0, (struct sockaddr *)&clientaddr, len);
    }

    close(sock_desc);
    return 0;
}
