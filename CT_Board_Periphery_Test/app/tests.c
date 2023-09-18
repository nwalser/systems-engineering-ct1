/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Implementation of module tests.
 * 
 *  $Id$
 * ------------------------------------------------------------------------- */


/* Standard includes */
#include <stdint.h>

/* User includes */
#include "tests.h"
#include "utilities.h"
#include "hal_adc.h"
#include "hal_gpio.h"
#include "reg_ctboard.h"


/* -- Public function definitions
 * ------------------------------------------------------------------------- */

void test_DIPSW_LED(void)
{
    #define DIPSW_PATTERN_START_L   (0x01)
    #define DIPSW_PATTERN_START_R   (0x80)
    #define DIPSW_PATTERN_STOP_L    (0x80)
    #define DIPSW_PATTERN_STOP_R    (0x01)
    
    static uint8_t value_led_left = DIPSW_PATTERN_START_L;
    static uint8_t value_led_right = DIPSW_PATTERN_START_R;
    
    REG16(CT_ADDR_LED, 0u) = ((uint16_t)(value_led_left << 8u) | value_led_left) ^ REG16(CT_ADDR_DIPSW, 0u);
    REG16(CT_ADDR_LED, 2u) = ((uint16_t)(value_led_right << 8u) | value_led_right) ^ REG16(CT_ADDR_DIPSW, 2u);  
            
    value_led_left = (value_led_left == DIPSW_PATTERN_STOP_L) ? DIPSW_PATTERN_START_L : (uint8_t)(value_led_left << 1u);
    value_led_right = (value_led_right == DIPSW_PATTERN_STOP_R) ? DIPSW_PATTERN_START_R : (value_led_right >> 1u);  
}

    
void test_7SEGMENT(void)
{
    #define SEG7_PATTERN_START_L    (0x01)
    #define SEG7_PATTERN_START_R    (0x20)
    #define SEG7_PATTERN_STOP_L     (0x20)
    #define SEG7_PATTERN_STOP_R     (0x01)
    
    static uint8_t value_hex_left = SEG7_PATTERN_START_L;
    static uint8_t value_hex_right = SEG7_PATTERN_START_L;
    
    REG8(CT_ADDR_7SEG, 0u) = ~(value_hex_left);
    REG8(CT_ADDR_7SEG, 1u) = ~(value_hex_right);
    REG8(CT_ADDR_7SEG, 2u) = ~(value_hex_left);
    REG8(CT_ADDR_7SEG, 3u) = ~(value_hex_right);
            
    value_hex_left = (value_hex_left == SEG7_PATTERN_STOP_L) ? SEG7_PATTERN_START_L : (uint8_t)(value_hex_left << 1u);
    value_hex_right = (value_hex_right == SEG7_PATTERN_STOP_R) ? SEG7_PATTERN_START_R : (value_hex_right >> 1u);
}


void test_BUTTON(void) 
{
    switch (REG8(CT_ADDR_BUTTON, 0u) & 0x0f) {
        case 0x01:
            REG8(CT_ADDR_7SEG, 0u) = 0x00;
            break;
                
        case 0x02:
            REG8(CT_ADDR_7SEG, 1u) = 0x00;
            break;
                
        case 0x04:
            REG8(CT_ADDR_7SEG, 2u) = 0x00;
            break;
                
        case 0x08:
            REG8(CT_ADDR_7SEG, 3u) = 0x00;
            break;
                
        default:
            break;
    }
}


void test_POTI(void)
{
    #define POTI_OFFSET             (31u)
    #define POTI_SYMBOL             (0xdb)
    
    uint8_t value_poti, offset;
    
    hal_adc_start(ADC3);
    
    // Wait till conversion is finished
    while((!ADC3->SR) & 0x00000002);
    
    value_poti = (uint8_t)((255u - ADC3->DR) * 9 / 255u);
    
    // Display the converted data
    for(offset = 0u; offset <= 9u; offset++) {
        if (offset <= value_poti) {
            REG8(CT_LCD_ASCII, (POTI_OFFSET + offset)) = POTI_SYMBOL;
        } else {
            REG8(CT_LCD_ASCII, (POTI_OFFSET + offset)) = ' ';
        }
    }
}


void test_PWM(void)
{
    #define PWM_START               (0x1000)
    #define PWM_STEP                (0x1000)
    
    static uint16_t value_pwm = PWM_START;
    static uint8_t pwm_state = 0u;
            
    switch (pwm_state) {
        default:
        case 0u:
            REG16(CT_LCD_PWM, 0u) = value_pwm;
            if (value_pwm == 0u) {
                pwm_state = 1u;
            }
            break;
                    
        case 1u:
            REG16(CT_LCD_PWM, 2u) = value_pwm;
            if (value_pwm == 0u) {
                pwm_state = 2u;
            }
            break;
                    
        case 2u:
            REG16(CT_LCD_PWM, 4u) = value_pwm;
            if (value_pwm == 0u) {
                pwm_state = 0u;
            }
            break;
    }
            
    value_pwm -= PWM_STEP;
}


void test_HEXSW(void)
{
    uint8_t value_hexsw = REG8(CT_ADDR_HEXSW, 0u) & 0x0f;
    REG8(CT_LCD_BIN, 4u) = value_hexsw;
}


void test_GPIO(void)
{
    #define GPIO_NOTHING            ('o')
    #define GPIO_FAIL               ('x')
    #define GPIO_SUCCESS            (254u)
    
    #define GPIO_POS_P1             ( 2u)
    #define GPIO_POS_P2             ( 6u)
    #define GPIO_POS_P3             (10u)
    #define GPIO_POS_P4             (14u)
    
    uint8_t value_gpio, i;
    uint8_t fails = 0u;
    uint8_t output = 1u;
    
    uint32_t offset_lcd = 0;
    uint32_t offset_gpio = 0;
    
    REG8(CT_LCD_ASCII, GPIO_POS_P1) = GPIO_NOTHING;
    REG8(CT_LCD_ASCII, GPIO_POS_P2) = GPIO_NOTHING;
    REG8(CT_LCD_ASCII, GPIO_POS_P3) = GPIO_NOTHING;
    REG8(CT_LCD_ASCII, GPIO_POS_P4) = GPIO_NOTHING;
    
    switch (REG8(CT_ADDR_BUTTON, 0u) & 0x0f) {
        case 0x08:
            offset_lcd = GPIO_POS_P1;
            offset_gpio = 0u;
            break;
                
        case 0x04:
            offset_lcd = GPIO_POS_P2;
            offset_gpio = 1u;
            break;
                
        case 0x02:
            offset_lcd = GPIO_POS_P3;
            offset_gpio = 2u;
            break;
                
        case 0x01:
            offset_lcd = GPIO_POS_P4;
            offset_gpio = 3u;
            break;
                
        default:
            output = 0u;
            break;
    }
    
    if (output) {
        for (i = 0u; i < 8u; i++) {
            value_gpio = (uint8_t)(0x1 << i);
            REG8(CT_GPIO_OUT, offset_gpio) = value_gpio;
            if (REG8(CT_GPIO_IN, offset_gpio) != value_gpio) {
                fails++;
            }
        }
        if (fails) {
            REG8(CT_LCD_ASCII, offset_lcd) = GPIO_FAIL;
        } else {
            REG8(CT_LCD_ASCII, offset_lcd) = GPIO_SUCCESS;
        }
    }
}


void test_DIRECT_GPIO(void)
{
    #define TEST_VALUE              0xaf5
    #define TEST_MASK               0x0fff
    #define GPIO_NOTHING            ('o')
    #define GPIO_FAIL               ('x')
    #define GPIO_SUCCESS            (254u)
    #define OFFSET_LCD              19
    
    uint16_t read_value;
    
    hal_gpio_output_write(GPIOA, TEST_VALUE);
    read_value = hal_gpio_input_read(GPIOB);
    
    if((read_value & TEST_MASK) == (TEST_VALUE & TEST_MASK)){
        REG8(CT_LCD_ASCII, OFFSET_LCD) = GPIO_SUCCESS;
    }else{
        REG8(CT_LCD_ASCII, OFFSET_LCD) = GPIO_FAIL;
    }
}

