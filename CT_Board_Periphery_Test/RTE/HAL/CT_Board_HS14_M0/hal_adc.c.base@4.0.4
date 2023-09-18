/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Implementation of module hal_adc.
 *
 *  The hardware abstraction layer for the analog to digital converter.
 *
 *  $Id$
 * ------------------------------------------------------------------------- */

/* User includes */
#include "hal_adc.h"


/* -- Public function definitions
 * ------------------------------------------------------------------------- */

/*
 * See header file
 */
void hal_adc_reset(reg_adc_t *adc)
{
    adc->CR1 = 0u;
    adc->CR2 = 0u;
    adc->SQR1 = 0u;
}


/*
 * See header file
 */
void hal_adc_init_base(reg_adc_t *adc, hal_adc_init_t init)
{
    uint32_t reg;

    /* process resolution and scan mode */
    reg = ((uint32_t) init.scan_mode << 8u) |
          ((uint32_t) init.resolution << 24u);
    adc->CR1 = reg;

    /* process others */
    reg = ((uint32_t) init.alignment << 11u) |
          ((uint32_t) init.trigger << 24u) |
          ((uint32_t) init.polarity << 28u) |
          ((uint32_t) init.continuous_mode << 1u);
    adc->CR2 = reg;

    /* process nr_conversions */
    if (init.nr_conversions == 0) {
        reg = (0u << 20u);
    } else {
        reg = ((uint32_t) (init.nr_conversions - 1u) << 20u);
    }
    adc->SQR1 &= ~(0xfu << 20u);
    adc->SQR1 |= reg;
    
    /* enable */
    adc->CR2 |= (0x1u << 0u);
}


/*
 * See header file
 */
void hal_adc_init_channel(reg_adc_t *adc, 
                          hal_adc_channel_t channel,
                          hal_adc_ch_init_t init)
{
    uint32_t reg, clear_reg;
    uint8_t shift_reg;
    
    /* check rank */
    if (init.rank < 1u || 
        init.rank > 16u) {
        return;
    }
        
    /* process sampling rank */
    clear_reg = 0x1fu;
    reg = channel;
    if (init.rank >= 13u) {
        /* rank 13..16 -> SQR1 */
        shift_reg = (init.rank - 13u) * 5u;
        clear_reg <<= shift_reg;
        reg <<= shift_reg;
        adc->SQR1 &= clear_reg;
        adc->SQR1 |= reg;
    } else if (init.rank >= 7u) {
        /* rank 7..12 -> SQR2 */
        shift_reg = (init.rank - 7u) * 5u;
        clear_reg <<= shift_reg;
        reg <<= shift_reg;
        adc->SQR2 &= clear_reg;
        adc->SQR2 |= reg;
    } else if (init.rank >= 1u) {
        /* rank 1..6 -> SQR3 */
        shift_reg = (init.rank - 1u) * 5u;
        clear_reg <<= shift_reg;
        reg <<= shift_reg;
        adc->SQR3 &= clear_reg;
        adc->SQR3 |= reg;
    }
        
    /* process sampling cycles */
    clear_reg = 0x7u;
    reg = init.cycles;
    if (channel >= HAL_ADC_CH10) {
        /* rank 10..15 -> SMPR1 */
        shift_reg = (uint8_t) (channel - HAL_ADC_CH10) * 3;
        clear_reg <<= shift_reg;
        reg <<= shift_reg;
        adc->SMPR1 &= clear_reg;
        adc->SMPR1 |= reg;
    } else {//if (channel >= HAL_ADC_CH0) {
        /* rank 0..9 -> SMPR2 */
        shift_reg = (uint8_t) (channel - HAL_ADC_CH0) * 3u;
        clear_reg <<= shift_reg;
        reg <<= shift_reg;
        adc->SMPR2 &= clear_reg;
        adc->SMPR2 |= reg;
    }
}


/*
 * See header file
 */
void hal_adc_start(reg_adc_t *adc)
{
    adc->CR2 |= (0x1u << 30u);
}


/*
 * See header file
 */
void hal_adc_stop(reg_adc_t *adc)
{
    adc->CR2 &= ~(0x1u << 30u);
}


/*
 * See header file
 */
void hal_adc_set_dma(reg_adc_t *adc,
                     hal_bool_t status)
{
    if (status == DISABLE) {
        adc->CR2 &= ~((1u << 8u) |
                      (1u << 9u));
    } else {
        adc->CR2 |= (1u << 8u) |
                    (1u << 9u);
    }
}
