#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <mcprotocol/types.h>

void java_ushort(uint16_t value, unsigned char * buffer)
{
    buffer[0] = (value >> 8) & 0xFF;
    buffer[1] = value & 0xFF;
}

void java_sshort(int16_t value, unsigned char * buffer)
{
    buffer[0] = (value >> 8) & 0xFF;
    buffer[1] = value & 0xFF;
}

void java_uint(uint32_t value, unsigned char * buffer)
{
    buffer[0] = (value >> 24) & 0xFF;
    buffer[1] = (value >> 16) & 0xFF;
    buffer[2] = (value >> 8) & 0xFF;
    buffer[3] = value & 0xFF;
}

void java_sint(int32_t value, unsigned char * buffer)
{
    buffer[0] = (value >> 24) & 0xFF;
    buffer[1] = (value >> 16) & 0xFF;
    buffer[2] = (value >> 8) & 0xFF;
    buffer[3] = value & 0xFF;
}

void java_ulong(uint64_t value, unsigned char * buffer)
{
    buffer[0] = (value >> 56) & 0xFF;
    buffer[1] = (value >> 48) & 0xFF;
    buffer[2] = (value >> 40) & 0xFF;
    buffer[3] = (value >> 32) & 0xFF;
    buffer[4] = (value >> 24) & 0xFF;
    buffer[5] = (value >> 16) & 0xFF;
    buffer[6] = (value >> 8) & 0xFF;
    buffer[7] = value & 0xFF;
}

void java_slong(int64_t value, unsigned char * buffer)
{
    buffer[0] = (value >> 56) & 0xFF;
    buffer[1] = (value >> 48) & 0xFF;
    buffer[2] = (value >> 40) & 0xFF;
    buffer[3] = (value >> 32) & 0xFF;
    buffer[4] = (value >> 24) & 0xFF;
    buffer[5] = (value >> 16) & 0xFF;
    buffer[6] = (value >> 8) & 0xFF;
    buffer[7] = value & 0xFF;
}

void java_uuidv4(char * input, uint8_t * output)
{
    char temp[3];
    temp[2] = '\0';

    int index = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] != '-')
        {
            temp[0] = input[i++];
            temp[1] = input[i];
            output[index++] = (uint8_t)strtol(temp, NULL, 16);
        }
    }
}