#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <mcprotocol/packet.h>

#define BUFFER_SIZE 512

int send_packet(int sockfd, packet_t packet_type, ...)
{
    char * packet;
    char * subpacket;
    switch(packet_type)
    {
    case PACKET_HANDSHAKE:
        packet = malloc(BUFFER_SIZE);
        subpacket = malloc(BUFFER_SIZE);

        int packet_size = 0;
        int subpacket_size = 0;

        subpacket[0] = 0x00;
        subpacket_size += 1;
        int protocol_version_varint_size = encode_varint(&subpacket[subpacket_size], protocol_version);
        subpacket_size += protocol_version_varint_size;
        int server_address_varint_size = encode_varint(&subpacket[subpacket_size], strlen(server_address));
        subpacket_size += server_address_varint_size;
        strcpy(&subpacket[subpacket_size], server_address);
        subpacket_size += strlen(server_address);
        java_ushort(server_port, &subpacket[subpacket_size]);
        subpacket_size += 2;
        int next_state_varint_size = encode_varint(&subpacket[subpacket_size], next_state);
        subpacket_size += next_state_varint_size;
        
        packet_size += subpacket_size;

        int subpacket_size_varint_size = encode_varint(&packet[0], subpacket_size);

        memcpy(packet + subpacket_size_varint_size, subpacket, subpacket_size);

        packet_size += subpacket_size_varint_size;

        send(sockfd, packet, packet_size, 0);

        free(packet);
        free(subpacket);
    }
}