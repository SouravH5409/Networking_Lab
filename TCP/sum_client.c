#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock_desc;
    struct sockaddr_in servaddr;
    int num1, num2, sum;

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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Connect to localhost

    // Connect to server
    if (connect(sock_desc, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        printf("Connection failed.\n");
        exit(1);
    }
    printf("Connected to server.\n");

    // Input two numbers
    printf("Enter the first number: ");
    scanf("%d", &num1);
    printf("Enter the second number: ");
    scanf("%d", &num2);

    // Send numbers to server
    send(sock_desc, &num1, sizeof(num1), 0);
    send(sock_desc, &num2, sizeof(num2), 0);
    printf("Numbers sent to server.\n");

    // Receive sum from server
    recv(sock_desc, &sum, sizeof(sum), 0);
    printf("Received sum from server: %d\n", sum);

    // Close socket
    close(sock_desc);
    return 0;
}

