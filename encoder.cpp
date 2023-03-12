#include "Encoder.h"

Encoder::Encoder(int _pinA, int _pinB, int ppr, PIO _pio) {
    pinA = _pinA;
    pinB = _pinB;

    cpr = static_cast<float>(ppr) * 4;

    pio = _pio;
    sm = pio_claim_unused_sm(pio, true);
    pio_inst_offset = pio_add_program(pio, &quadrature_encoder_program);
};

void Encoder::init() {
    enc_count = 0;
    last_enc_count = 0;

    position_zero = 0.0;
    position = 0.0;
    velocity = 0.0;

    quadrature_encoder_program_init(pio, sm, pio_inst_offset, pinA, 0);
}

void Encoder::calculateStates() {
    static absolute_time_t last_time {get_absolute_time()};
    absolute_time_t current_time = get_absolute_time();
    int64_t delta_time_us = absolute_time_diff_us(last_time, current_time);

    enc_count = quadrature_encoder_get_count(pio, sm);
    int32_t delta_enc_count = enc_count - last_enc_count;

    calculatePosition();
    calculateVelocity(delta_time_us, delta_enc_count);

    last_enc_count = enc_count;
    last_time = current_time;
}

void Encoder::setHome() {
    position_zero = position;
}

void Encoder::calculatePosition() {
    position = static_cast<double>(enc_count) / (cpr / _2PI) - position_zero; // This calculation straight forward 
    // position += static_cast<double>(delta_enc_count) / (cpr / _2PI); // This also works fine, don't know if computationally they are the same though
}

void Encoder::calculateVelocity(int64_t delta_time_us, int32_t delta_enc_count) {
    double delta_angle_rad = static_cast<double>(delta_enc_count) / (cpr / _2PI);
    double delta_time = static_cast<double>(delta_time_us) * 1e-6f;

    velocity = delta_angle_rad / delta_time;
}

double Encoder::getPosition() { return position; }
double Encoder::getVelocity() { return velocity; }

