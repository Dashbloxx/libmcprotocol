#pragma once

enum
{
    PACKET_LOGIN,
    PACKET_HANDSHAKE
};

void __packet_handshake(int sockfd, int protocol_version, char * server_address, uint16_t server_port, int next_state);
void __packet_login_start(int sockfd, char * username, char * uuidv4);