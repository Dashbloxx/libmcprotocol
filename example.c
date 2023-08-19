#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <mcprotocol/packet.h>

static void printh(void * data, size_t size)
{
    const unsigned char * bytes = (const unsigned char *)data;
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", bytes[i]);
    }
    printf("\n");
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        fprintf(stderr, "error: failed to create socket.\n");
        return 1;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(25565);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1)
    {
        fprintf(stderr, "error: connection failed.\n");
        close(sockfd);
        return 1;
    }

    current_state = STATE_LOGIN;

    __packet_handshake(sockfd, 763, "127.0.0.1", 25565, 2);
    __packet_login_start(sockfd, "Reapiu", "d224acff-702b-4d70-8abb-4c1e46a87c4a");
    __handle_clientbound_packet(sockfd);

    close(sockfd);

    return 0;
}
