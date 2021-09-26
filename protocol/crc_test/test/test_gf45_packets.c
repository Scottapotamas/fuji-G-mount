#include "unity.h"
#include <stdlib.h>

// MODULE UNDER TEST
#include "crc.h"
 
// DEFINITIONS 
#define CRC_DIVISOR 0xFF

// PRIVATE TYPES
 
// PRIVATE DATA
uint8_t temp_crc_1 = 0;

// PRIVATE FUNCTIONS
 
// SETUP, TEARDOWN
 
void setUp(void)
{
    temp_crc_1 = 0;
}
 
void tearDown(void)
{

}
 
// TESTS
 
void test_basic(void)
{
    crc8( 0x00, &temp_crc_1 );
    TEST_ASSERT_EQUAL_HEX( 0xE1F0, temp_crc_1 );

    temp_crc_1 = CRC_DIVISOR;
    crc8( 0x0A, &temp_crc_1 );
    TEST_ASSERT_EQUAL_HEX( 0x40BA, temp_crc_1 );

    temp_crc_1 = CRC_DIVISOR;
    crc8( 0xFF, &temp_crc_1 );
    TEST_ASSERT_EQUAL_HEX( 0xFF00, temp_crc_1 );

    temp_crc_1 = CRC_DIVISOR;
    crc8( 0xFF, &temp_crc_1 );
    crc8( 0x0A, &temp_crc_1 );
    TEST_ASSERT_EQUAL_HEX( 0xBFBA, temp_crc_1 );

    //run 00 to 0F sequentially 
    temp_crc_1 = CRC_DIVISOR;
    for(uint8_t i = 0x00; i < 16; i++)
    {
        crc8( i, &temp_crc_1 );
    }
    TEST_ASSERT_EQUAL_HEX( 0x3B37, temp_crc_1 );
}