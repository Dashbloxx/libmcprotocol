#pragma once

int encode_varint(unsigned char * buffer, int value);
int decode_varint(const unsigned char * buffer, int *value);
int count_varint(unsigned char * buffer);

#define VARINT_BUFFER_SIZE 5