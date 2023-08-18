#pragma once

#include <stdint.h>

void java_ushort(uint16_t value, unsigned char * buffer);
void java_sshort(int16_t value, unsigned char * buffer);
void java_uint(uint32_t value, unsigned char * buffer);
void java_sint(int32_t value, unsigned char * buffer);
void java_ulong(uint64_t value, unsigned char * buffer);
void java_slong(int64_t value, unsigned char * buffer);
void java_uuidv4(char * input, uint8_t * output);