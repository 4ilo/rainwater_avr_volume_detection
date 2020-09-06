#include <avr/io.h>

#include "adc.h"

void adc_init(void)
{
    // Select Vref = AVcc
    ADMUX |= (1 << REFS0);

    // Set prescaler to 16 and enable ADC
    // Adc clock should be between 50kHz and 200kHz
    ADCSRA |= (1 << ADPS2) | (1 << ADEN);
}

uint16_t adc_read(uint8_t channel)
{
    // Select ADC channel with safety mask
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // Single conversion
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));

    return ADC;
}
