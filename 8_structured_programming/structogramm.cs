while(true){
    // read adc value -> store to register
    // The function call BL adc_get_value will return the ADC-value in the 32-bit register R0. 
    int adcValue = adcGetValue();

    if(buttonT0Pressed)
    {
        setLCDColor(green);
        displayADCValue(adcValue);

        // display scaled value on led bar
        int scaledValue = adcValue / 8;
        int ledMask = 0;
        for(int i = scaledValue; i > 0; i--){
            ledMask |= 0x01;
            ledMask <<= 1;
        }
        displayOnLed31to0(ledMask);
    } 
    else 
    {
        var dipSwitchValueS7toS0 = readDipSwitchValues();
        var newAdcValue = dipSwitchValueS7toS0 - adcValue;

        if(newAdcValue >= 0)
        {
            setLCDColor(blue);
        }
        else
        {
            setLCDColor(red);
        }

        displayADCValue(newAdcValue);
    }
}


/*
constrolling of seven segment displays
ADDR_SEG7_BIN   EQU      0x60000114

                LDR      r0, =ADDR_SEG7_BIN
                STRB     r1, [r0, #0]                     ; Write byte of binary data to DS1..0.
                STRH     r1, [r0, #0]                     ; Write half word of binary data to all displays.
*/

