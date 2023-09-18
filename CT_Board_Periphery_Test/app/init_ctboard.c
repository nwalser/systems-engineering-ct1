/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Implementation of module init_ctboard.
 * 
 *  $Id$
 * ------------------------------------------------------------------------- */


/* Standard includes */
#include <stdint.h>

/* User includes */
#include "init_ctboard.h"
#include "reg_stm32f4xx.h"
#include "reg_ctboard.h"
#include "init_ctboard.h"
#include "utilities.h"

#include "hal_gpio.h"
#include "hal_fmc.h"
#include "hal_adc.h"
#include "hal_rcc.h"


/* -- Macros (FMC)
 * ------------------------------------------------------------------------- */

#define FMC_PORTD_PINMASK               0xfffb
#define FMC_PORTE_PINMASK               0xffff
#define FMC_PORTF_PINMASK               0xf03f
#define FMC_PORTG_PINMASK               0x363f
#define GPIO_DIRECT_PINMASK             0x0fff


/* -- Local function declarations
 * ------------------------------------------------------------------------- */
 
static void init_ADC(void);
static void init_FMC(void);
static void init_LCD(void);
static void init_GPIO(void);

static void wait(uint32_t value);


/* -- Public function definitions
 * ------------------------------------------------------------------------- */

/*
 * See header file
 */
void init_CT_BOARD(void)
{
    init_ADC();
    init_FMC();
    init_GPIO();
    
    wait(0x1ffff);
    
    init_LCD();
}


/* -- Local function definitions
 * ------------------------------------------------------------------------- */

/** 
 *  \brief  Waits.
 */
static void wait(uint32_t value)
{
    for(; value > 0; value--) {}
}

static void init_ADC(void)
{
    // Clock configuration
    RCC->APB2ENR |= 0x00000400;
    RCC->AHB1ENR |= 0x00000020;
    
    // Analog pin configuration
    GPIOF->MODER |= 0x00003000;
 
    // ADC configuration
    ADC3->CR1 |= 0x02000000;                    // Resolution -> 8 Bit, scan mode -> disabled
//    REG_ADCx_CR2(ADC3_BASE) |= 0x00000000;    // Data alignment -> right, ext. trigger conv. -> T1_CC1, ext. trigger edge -> none
//    REG_ADCx_CR2(ADC3_BASE) |= 0x00000000;    // Ext. trigger conv. -> T1_CC1, ext. trigger edge -> none
    ADC3->CR2 |= 0x00000002;                    // Continous conversion mode -> enabled
//    REG_ADCx_SQR1(ADC3_BASE) |= 0x00000000;   // Number of conv. -> 1
    
    // Enable ADC conversion
    ADC3->CR2 |= 0x00000001;                    // ADC3 enable
    
    // Select the channel to be read from
    ADC3->SMPR2 |= 0x00006000;                // Channel 4 sampling time -> 144 cycles
    ADC3->SQR3 |= 0x00000004;                 // Channel 4 rank -> 1 (?)
}


/** 
 *  \brief  Initializes FMC.
 */
static void init_FMC(void)
{
    hal_gpio_output_t gpio_init;
    hal_fmc_sram_init_t sram_init;
    hal_fmc_sram_timing_t sram_timing;
    
    /* Enable used peripherals */
    GPIOD_ENABLE();
    GPIOE_ENABLE();
    GPIOF_ENABLE();
    GPIOG_ENABLE();
    FMC_ENABLE();
    
    /* Configure the involved GPIO pins to AF12 (FMC) */
    gpio_init.pupd = HAL_GPIO_PUPD_NOPULL;
    gpio_init.out_speed = HAL_GPIO_OUT_SPEED_50MHZ;
    gpio_init.out_type = HAL_GPIO_OUT_TYPE_PP;
    
    /* GPIOD configuration (pins: 0,1,3-15) */
    gpio_init.pins = FMC_PORTD_PINMASK;
    hal_gpio_init_alternate(GPIOD, HAL_GPIO_AF_FMC, gpio_init);
    
    /* GPIOE configuration (pins: 0-15) */
    gpio_init.pins = FMC_PORTE_PINMASK;
    hal_gpio_init_alternate(GPIOE, HAL_GPIO_AF_FMC, gpio_init);
    
    /* GPIOF configuration (pins: 0-5,12-15) */
    gpio_init.pins = FMC_PORTF_PINMASK;
    hal_gpio_init_alternate(GPIOF, HAL_GPIO_AF_FMC, gpio_init);
    
    /* GPIOG configuration (pins: 1-5, 9, 10, 12, 13) */
    gpio_init.pins = FMC_PORTG_PINMASK;
    hal_gpio_init_alternate(GPIOG, HAL_GPIO_AF_FMC, gpio_init);
    
    
    /* Initialize the synchronous PSRAM on bank 1 */
    sram_init.address_mux = DISABLE;
    sram_init.type = HAL_FMC_TYPE_PSRAM;
    sram_init.width = HAL_FMC_WIDTH_16B;
    sram_init.read_burst = ENABLE;
    sram_init.write_enable = ENABLE;
    sram_init.write_burst = ENABLE;
    sram_init.continous_clock = ENABLE;
    
    sram_timing.bus_turnaround = 1u;
    sram_timing.clk_divider = 15u;
    sram_timing.data_latency = 2u;
    
    hal_fmc_init_sram(HAL_FMC_SRAM_BANK1, sram_init, sram_timing);   
    
    
    /* Initialize the asynchronous SRAM on bank 2 */
    sram_init.address_mux = DISABLE;
    sram_init.type = HAL_FMC_TYPE_SRAM;
    sram_init.width = HAL_FMC_WIDTH_16B;
    sram_init.read_burst = DISABLE;
    sram_init.write_enable = DISABLE;
    sram_init.write_burst = DISABLE;
    sram_init.continous_clock = DISABLE;
    
    sram_timing.bus_turnaround = 1u;
    sram_timing.address_setup = 11u;
    sram_timing.address_hold = 5u;
    sram_timing.data_setup = 11u;
    sram_timing.mode = HAL_FMC_ACCESS_MODE_A;
    
    hal_fmc_init_sram(HAL_FMC_SRAM_BANK2, sram_init, sram_timing);
}


/** 
 *  \brief  Initializes static content of LCD.
 */
static void init_LCD(void)
{    
    // GPIO
    REG8(CT_LCD_ASCII,  0u) = 'P';
    REG8(CT_LCD_ASCII,  1u) = '1';
    
    REG8(CT_LCD_ASCII,  4u) = 'P';
    REG8(CT_LCD_ASCII,  5u) = '2';
    
    REG8(CT_LCD_ASCII, 8u) = 'P';
    REG8(CT_LCD_ASCII, 9u) = '3';
    
    REG8(CT_LCD_ASCII, 12u) = 'P';
    REG8(CT_LCD_ASCII, 13u) = '4';
    
    REG8(CT_LCD_ASCII, 16u) = 'P';
    REG8(CT_LCD_ASCII, 17u) = '5';
    REG8(CT_LCD_ASCII, 18u) = '6';
    
    // HEXSW    
    REG8(CT_LCD_ASCII, 20u) = 'H';
    REG8(CT_LCD_ASCII, 21u) = 'E';
    REG8(CT_LCD_ASCII, 22u) = 'X';
    REG8(CT_LCD_ASCII, 23u) = 'S';
    REG8(CT_LCD_ASCII, 24u) = 'W';
}

static void init_GPIO(void)
{
    hal_gpio_output_t gpio_init_a;
    hal_gpio_input_t gpio_init_b;
    
    GPIOA_ENABLE();
    GPIOB_ENABLE();
    
    gpio_init_a.pins = GPIO_DIRECT_PINMASK;
    gpio_init_a.pupd = HAL_GPIO_PUPD_NOPULL;
    gpio_init_a.out_speed = HAL_GPIO_OUT_SPEED_50MHZ;
    gpio_init_a.out_type = HAL_GPIO_OUT_TYPE_PP;
    
    gpio_init_b.pins = GPIO_DIRECT_PINMASK;
    gpio_init_b.pupd = HAL_GPIO_PUPD_DOWN;
    
    hal_gpio_init_output(GPIOA, gpio_init_a);
    hal_gpio_init_input(GPIOB, gpio_init_b);
}
