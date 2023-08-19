#include <mcprotocol/varint.h>

int encode_varint(unsigned char * buffer, int value)
{
    int index = 0;
    do
    {
        unsigned char temp = value & 0x7F;
        value >>= 7;
        if (value != 0)
        {
            temp |= 0x80;
        }
        buffer[index++] = temp;
    } while (value != 0);
    return index;
}

int decode_varint(const unsigned char * buffer, int *value)
{
    *value = 0;
    int shift = 0;
    int index = 0;
    unsigned char byte;
    do
    {
        byte = buffer[index++];
        *value |= (byte & 0x7F) << shift;
        shift += 7;
    } while (byte & 0x80);
    return index;
}

int count_varint(unsigned char * buffer)
{
    int size = 0;
    while (*buffer & 0x80)
    {
        buffer++;
        size++;
    }
    size++;
    return size;
}