#include "ArduboyTones.h"
#include "wasm4.h"

static bool (*outputEnabled)();


ArduboyTones::ArduboyTones(boolean (*outEn)())
{
  outputEnabled = outEn;
}

void ArduboyTones::tone(uint16_t freq, uint16_t dur) {
    if (outputEnabled) {
        ::tone(freq, dur / 16, 100,TONE_PULSE1 | TONE_MODE1);
    }
}