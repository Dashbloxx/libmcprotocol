#pragma once

#include <stdint.h>

typedef enum
{
    STATE_LOGIN,
    STATE_PLAY
} state_t;

typedef struct
{
    char * server_id;
    int public_key_length;
    unsigned char * public_key;
    int verify_token_length;
    unsigned char * verify_token;
} encryption_request_t;

extern state_t current_state;

void __packet_handshake(int sockfd, int protocol_version, char * server_address, uint16_t server_port, int next_state);
void __packet_login_start(int sockfd, char * username, char * uuidv4);
void __handle_clientbound_packet(int sockfd);