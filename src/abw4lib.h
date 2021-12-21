#ifndef ABW4LIB
#define ABW4LIB

typedef void (*FunctionPointer) ();

// uint8_t bootMode;
// unsigned int bootTicks;

void continueBooting();
bool stillBooting();
void wasm4Logo();
void jgLogo();
void arduboyLogo();

#endif