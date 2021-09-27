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
    crc8( 0x00, &temp_crc_1 );
    crc8( 0x00, &temp_crc_1 );

    TEST_ASSERT_EQUAL_HEX( 0x00, temp_crc_1 );

}


void test_lens_announcement_first(void)
{
    uint8_t payload[] = {
        0x4c, 0x52, 0x31, 0x30, 0x36, 0x41, 0x00, 0x00, 0x46, 0x53, 0x53, 0x4e, 0x57, 0x30, 0x30, 0x36,
        0x47, 0x46, 0x34, 0x35, 0x6d, 0x6d, 0x46, 0x32, 0x2e, 0x38, 0x20, 0x52, 0x20, 0x57, 0x52, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x32, 0x34, 0x30, 0x33, 0x33, 0x38, 0x36, 0x36, 0x30, 0x35, 0x01, 0x56, 0x01, 0x00, 0x01, 0x00,
        0x01, 0x00, 0x01, 0x00, 0xc8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    crc8( 0x00, &temp_crc_1 );
    crc8( 0x00, &temp_crc_1 );

    for( uint16_t i = 0; i < sizeof(payload); i++ )
    {
        crc8( payload[i], &temp_crc_1 );
    }

    TEST_ASSERT_EQUAL_HEX( 0xAF, temp_crc_1 );

}

void test_lens_announcement_second(void)
{
    uint8_t payload[] = {
        0x4c, 0x52, 0x31, 0x30, 0x36, 0x41, 0x00, 0x00, 0x46, 0x53, 0x53, 0x4e, 0x57, 0x30, 0x30, 0x36,
        0x47, 0x46, 0x34, 0x35, 0x6d, 0x6d, 0x46, 0x32, 0x2e, 0x38, 0x20, 0x52, 0x20, 0x57, 0x52, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x32, 0x34, 0x30, 0x33, 0x33, 0x38, 0x36, 0x36, 0x30, 0x35, 0x01, 0x56, 0x01, 0x00, 0x01, 0x00,
        0x01, 0x00, 0x01, 0x00, 0xc8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    crc8( 0xFF, &temp_crc_1 );
    crc8( 0xFF, &temp_crc_1 );

    for( uint16_t i = 0; i < sizeof(payload); i++ )
    {
        crc8( payload[i], &temp_crc_1 );
    }

    TEST_ASSERT_EQUAL_HEX( 0xAD, temp_crc_1 );
}