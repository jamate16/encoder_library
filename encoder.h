/**
 * @file encoder.h
 * @author Jamate
 * @brief This is the declaration of an encoder class interface for embedded systems
 * @version 0.1
 * @date 2023-03-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "quadrature_encoder.pio.h" /// \todo Change structure so that the the encoder pins are not consecutive

#define _PI  3.14159265359f
#define _2PI 6.28318530718f

class Encoder {
public: // Public variables
    uint8_t pinA; /// Encoder channel A hardware pin
    uint8_t pinB; /// Encoder channel B hardware pin

    float cpr;
    volatile int32_t enc_count;
    volatile int32_t last_enc_count;

    PIO pio;
    uint sm;
    uint pio_inst_offset;   

private: // Private variables
    double position_zero;
    double position;
    double velocity;

public: // Public methods
    Encoder(int _pinA, int _pinB, int ppr, PIO _pio);
    void init();

    void calculateStates();
    double getPosition();
    double getVelocity();

    void setHome();

private: // Private methods
    void calculatePosition();
    void calculateVelocity(int64_t delta_time_us, int32_t delta_enc_count);
};
