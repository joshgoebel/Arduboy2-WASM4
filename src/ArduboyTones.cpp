#include "ArduboyTones.h"
#include "wasm4.h"

static bool (*outputEnabled)();


ArduboyTones::ArduboyTones()
{
//   outputEnabled = outEn;

}

void ArduboyTones::tone(uint16_t freq, uint16_t dur) {
    ::tone(freq, dur, 0,0);
}