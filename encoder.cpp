#include <stdio.h>
#include "pico/stdlib.h"
#include "encoder.h"
#include "quadrature_encoder.pio.h" // This file only allows consecutive pins

Encoder::Encoder(int pinA, int pinB, int ppr) {
    const uint PIN_AB = 10;

    stdio_init_all();

    PIO pio = pio0;
    const uint sm = 0;

    uint offset = pio_add_program(pio, &quadrature_encoder_program);
    quadrature_encoder_program_init(pio, sm, offset, PIN_AB, 0);
};

