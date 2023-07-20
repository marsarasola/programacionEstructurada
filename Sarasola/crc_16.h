#ifndef CRC_16_H_INCLUDED
#define CRC_16_H_INCLUDED

#include <stdint.h>

// Se les da el .h y el .o
void calculate_checksum_ptr(uint8_t[], uint16_t, uint16_t*);
uint16_t calculate_checksum(uint8_t[], uint16_t);


#endif // CRC_16_H_INCLUDED
