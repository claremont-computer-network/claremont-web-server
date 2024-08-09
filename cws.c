#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 80
#define BUFFER_SIZE 1024

void handle_client(int client_socket);

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to the IP address and port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Bind to all available interfaces
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 10) == -1) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d\n", PORT);

    // Main loop to accept connections
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Client connection failed");
            continue;
        }
        handle_client(client_socket);
        close(client_socket);
    }

    close(server_socket);
    return 0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    // Read the client's request
    bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
        perror("Read failed");
        return;
    }

    buffer[bytes_read] = '\0';

    // Simple domain check (parsing HTTP headers for the Host field)
    if (strstr(buffer, "Host: ourplaceprod.com") != NULL) {
        // Serve files from /var/www/ourplaceprod
        FILE *file = fopen("/var/www/ourplaceprod/index.html", "r");
        if (file != NULL) {
            while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
                write(client_socket, buffer, bytes_read);
            }
            fclose(file);
        } else {
            const char *response = "HTTP/1.1 404 Not Found\r\n\r\n";
            write(client_socket, response, strlen(response));
        }
    } else if (strstr(buffer, "Host: tesfaasmara.com") != NULL) {
        // Serve files from /var/www/tesfaasmara
        FILE *file = fopen("/var/www/tesfaasmara/index.html", "r");
        if (file != NULL) {
            while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
                write(client_socket, buffer, bytes_read);
            }
            fclose(file);
        } else {
            const char *response = "HTTP/1.1 404 Not Found\r\n\r\n";
            write(client_socket, response, strlen(response));
        }
    } else {
        // Default response for IP address or unmatched hosts
        FILE *file = fopen("/var/www/default/index.html", "r");
        if (file != NULL) {
            while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
                write(client_socket, buffer, bytes_read);
            }
            fclose(file);
        } else {
            const char *response = "HTTP/1.1 404 Not Found\r\n\r\n";
            write(client_socket, response, strlen(response));
        }
    }
}
