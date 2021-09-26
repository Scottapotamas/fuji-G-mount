#include "crc.h"

void crc8(uint8_t data, uint8_t *crc)
{
    *crc ^= data;
}