#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    char filename[BUFFER_SIZE], buffer[BUFFER_SIZE];
    FILE *file;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("Socket"); exit(1); }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);
    printf("Server listening on port %d...\n", PORT);

    client_fd = accept(server_fd, (struct sockaddr*)&addr, &addr_len);
    if (client_fd < 0) { perror("Accept"); exit(1); }

    recv(client_fd, filename, BUFFER_SIZE, 0);

    file = fopen(filename, "r");
    if (!file) {
        send(client_fd, "File not found", 14, 0);
    } else {
        while (fgets(buffer, BUFFER_SIZE, file))
            send(client_fd, buffer, strlen(buffer), 0);
        fclose(file);
    }

    close(client_fd);
    close(server_fd);
    return 0;
}
