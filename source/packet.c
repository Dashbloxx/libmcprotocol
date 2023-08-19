#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <mcprotocol/packet.h>
#include <mcprotocol/types.h>
#include <mcprotocol/varint.h>

#define BUFFER_SIZE 512

state_t current_state;

static void printh(void * data, size_t size)
{
    const unsigned char * bytes = (const unsigned char *)data;
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", bytes[i]);
    }
    printf("\n");
}

void __packet_handshake(int sockfd, int protocol_version, char * server_address, uint16_t server_port, int next_state)
{
    unsigned char * packet = malloc(BUFFER_SIZE);
    unsigned char * subpacket = malloc(BUFFER_SIZE);

    int packet_size = 0;
    int subpacket_size = 0;

    subpacket[0] = 0x00;
    subpacket_size += 1;
    int protocol_version_varint_size = encode_varint(&subpacket[subpacket_size], protocol_version);
    subpacket_size += protocol_version_varint_size;
    int server_address_varint_size = encode_varint(&subpacket[subpacket_size], strlen(server_address));
    subpacket_size += server_address_varint_size;
    memcpy(&subpacket[subpacket_size], server_address, strlen(server_address));
    subpacket_size += strlen(server_address);
    java_ushort(server_port, &subpacket[subpacket_size]);
    subpacket_size += 2;
    int next_state_varint_size = encode_varint(&subpacket[subpacket_size], next_state);
    subpacket_size += next_state_varint_size;
    
    packet_size += subpacket_size;

    int subpacket_size_varint_size = encode_varint(&packet[0], subpacket_size);

    memcpy(packet + subpacket_size_varint_size, subpacket, subpacket_size);

    packet_size += subpacket_size_varint_size;

#ifdef __DBG
    printf("debug: sending packet => ");
    printh(packet, packet_size);
#endif

    send(sockfd, packet, packet_size, 0);

    free(packet);
    free(subpacket);
}

void __packet_login_start(int sockfd, char * username, char * uuidv4)
{
    unsigned char * packet = malloc(sizeof(char) * BUFFER_SIZE);
    unsigned char * subpacket = malloc(sizeof(char) * BUFFER_SIZE);

    int packet_size = 0;
    int subpacket_size = 0;

    subpacket[0] = 0x00;
    subpacket_size += 1;
    int name_varint_size = encode_varint(&subpacket[subpacket_size], strlen(username));
    subpacket_size += name_varint_size;
    memcpy(&subpacket[subpacket_size], username, strlen(username));
    subpacket_size += strlen(username);
    subpacket[subpacket_size] = 0x01;
    subpacket_size += 1;
    java_uuidv4(uuidv4, subpacket + subpacket_size);
    subpacket_size += 16;

    packet_size += subpacket_size;

    int subpacket_size_varint_size = encode_varint(&packet[0], subpacket_size);

    memcpy(packet + subpacket_size_varint_size, subpacket, subpacket_size);

    packet_size += subpacket_size_varint_size;

#ifdef __DBG
    printf("debug: sending packet => ");
    printh(packet, packet_size);
#endif

    write(sockfd, packet, packet_size);

    free(packet);
    free(subpacket);
}

void __handle_clientbound_packet(int sockfd)
{
    unsigned char * packet = malloc(sizeof(char) * BUFFER_SIZE);
    recv(sockfd, packet, BUFFER_SIZE, 0);
    
    int packet_size = -1;
    int packet_size_varint_size = decode_varint(packet, &packet_size);
    int counter = 0;
    counter += packet_size_varint_size;
    const int packet_type = packet[counter];

    switch(packet_type)
    {
    case 0x01:
        switch(current_state)
        {
        case STATE_LOGIN:
            
            break;
        case STATE_PLAY:
            break;
        }
        break;
    }

    printh(packet, 512);
    printf("packet size: %d.\nvarint size: %d.\n", packet_size, packet_size_varint_size);

    free(packet);
}