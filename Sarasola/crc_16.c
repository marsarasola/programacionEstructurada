#include "crc_16.h"

// returns 16-bit checksum. If done for a packet with checksum appended, should return 0
// length is in bytes!
// be careful this function is not reentrant
void calculate_checksum_ptr(uint8_t input[], uint16_t length, uint16_t *result)
{
    static int16_t CRCPoly = 0xA001;
    static uint16_t i = 0;
    static uint8_t j = 0;
    static uint8_t data = 0;
    static uint8_t result_bit = 0;
    static uint8_t data_bit = 0;

    // for every byte
    for (i = 0; i < length; i++) {
        data = input[i];
        // for every bit
        for (j = 0; j < 8; j++) {
            result_bit = *result & 0x1;    // get LSbit
            *result = *result >> 1;        // shift down
            data_bit = data & 0x1;        // get LSbit
            data = data >> 1;            // shift down
            if (result_bit != data_bit) {
                *result = *result ^ CRCPoly;
            }
        }
    }
}

uint16_t calculate_checksum(uint8_t input[], uint16_t length)
{
    uint16_t checksum = 0;

    calculate_checksum_ptr(input, length, &checksum);

    return checksum;
}
