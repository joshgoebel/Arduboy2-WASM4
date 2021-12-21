/**
 * @file Arduboy2Core.cpp
 * \brief
 * The Arduboy2Core class for Arduboy hardware initilization and control.
 */

#include "Arduboy2Core.h"
#include "wasm4.h"

// #include <avr/wdt.h>


//========================================
//========== class Arduboy2Core ==========
//========================================

// Commands sent to the OLED display to initialize it
const PROGMEM uint8_t Arduboy2Core::lcdBootProgram[] = {
  // boot defaults are commented out but left here in case they
  // might prove useful for reference
  //
  // Further reading: https://www.adafruit.com/datasheets/SSD1306.pdf
  //
  // Display Off
  // 0xAE,

  // Set Display Clock Divisor v = 0xF0
  // default is 0x80
  0xD5, 0xF0,

  // Set Multiplex Ratio v = 0x3F
  // 0xA8, 0x3F,

  // Set Display Offset v = 0
  // 0xD3, 0x00,

  // Set Start Line (0)
  // 0x40,

  // Charge Pump Setting v = enable (0x14)
  // default is disabled
  0x8D, 0x14,

  // Set Segment Re-map (A0) | (b0001)
  // default is (b0000)
  0xA1,

  // Set COM Output Scan Direction
  0xC8,

  // Set COM Pins v
  // 0xDA, 0x12,

  // Set Contrast v = 0xCF
  0x81, 0xCF,

  // Set Precharge = 0xF1
  0xD9, 0xF1,

  // Set VCom Detect
  // 0xDB, 0x40,

  // Entire Display ON
  // 0xA4,

  // Set normal/inverse display
  // 0xA6,

  // Display On
  0xAF,

  // set display mode = horizontal addressing mode (0x00)
  0x20, 0x00,

  // set col address range
  // 0x21, 0x00, COLUMN_ADDRESS_END,

  // set page address range
  // 0x22, 0x00, PAGE_ADDRESS_END
};

void Arduboy2Core::boot()
{
  bootPins();
  bootSPI();
  bootOLED();
  bootPowerSaving();
}

// Pins are set to the proper modes and levels for the specific hardware.
// This routine must be modified if any pins are moved to a different port
void Arduboy2Core::bootPins()
{
}

void Arduboy2Core::bootOLED()
{
}

void Arduboy2Core::LCDDataMode()
{
}

void Arduboy2Core::LCDCommandMode()
{
}

// Initialize the SPI interface for the display
void Arduboy2Core::bootSPI()
{
}

void Arduboy2Core::safeMode()
{
}


/* Power Management */

void Arduboy2Core::idle()
{
}

void Arduboy2Core::bootPowerSaving()
{
}

// Shut down the display
void Arduboy2Core::displayOff()
{
  // TODO: reimplement in software?
}

// Restart the display after a displayOff()
void Arduboy2Core::displayOn()
{
  // TODO: reimplement in software?
}


/* Drawing */

void Arduboy2Core::paint8Pixels(uint8_t pixels)
{
  // TODO: reimplement in software?
}

void Arduboy2Core::paintScreen(const uint8_t *image)
{
  // TODO: reimplement in software?
}

// paint from a memory buffer, this should be FAST as it's likely what
// will be used by any buffer based subclass
//
// The following assembly code runs "open loop". It relies on instruction
// execution times to allow time for each byte of data to be clocked out.
// It is specifically tuned for a 16MHz CPU clock and SPI clocking at 8MHz.
void Arduboy2Core::paintScreen(uint8_t image[], bool clear)
{
  // TODO: reimplement in software?
}

void Arduboy2Core::blank()
{
  // TODO: reimplement in software?
}

void Arduboy2Core::sendLCDCommand(uint8_t command)
{
  // TODO: reimplement in software?
}

// invert the display or set to normal
// when inverted, a pixel set to 0 will be on
void Arduboy2Core::invert(bool inverse)
{
  sendLCDCommand(inverse ? OLED_PIXELS_INVERTED : OLED_PIXELS_NORMAL);
}

// turn all display pixels on, ignoring buffer contents
// or set to normal buffer display
void Arduboy2Core::allPixelsOn(bool on)
{
  sendLCDCommand(on ? OLED_ALL_PIXELS_ON : OLED_PIXELS_FROM_RAM);
}

// flip the display vertically or set to normal
void Arduboy2Core::flipVertical(bool flipped)
{
  sendLCDCommand(flipped ? OLED_VERTICAL_FLIPPED : OLED_VERTICAL_NORMAL);
}

// flip the display horizontally or set to normal
void Arduboy2Core::flipHorizontal(bool flipped)
{
  sendLCDCommand(flipped ? OLED_HORIZ_FLIPPED : OLED_HORIZ_NORMAL);
}

/* RGB LED */

void Arduboy2Core::setRGBled(uint8_t red, uint8_t green, uint8_t blue)
{
  // TODO: reimplement in software?
}

void Arduboy2Core::setRGBled(uint8_t color, uint8_t val)
{
  // TODO: reimplement in software?
}

void Arduboy2Core::freeRGBled()
{
}

void Arduboy2Core::digitalWriteRGB(uint8_t red, uint8_t green, uint8_t blue)
{
  // TODO: reimplement in software?
}

void Arduboy2Core::digitalWriteRGB(uint8_t color, uint8_t val)
{
  // TODO: reimplement in software?
}

/* Buttons */

uint8_t Arduboy2Core::buttonsState()
{
  uint8_t buttons = 0;

  if (*GAMEPAD1 & BUTTON_1) buttons |= A_BUTTON;
  if (*GAMEPAD1 & BUTTON_2) buttons |= B_BUTTON;
  if (*GAMEPAD1 & BUTTON_DOWN) buttons |= DOWN_BUTTON;
  if (*GAMEPAD1 & BUTTON_UP) buttons |= UP_BUTTON;
  if (*GAMEPAD1 & BUTTON_LEFT) buttons |= LEFT_BUTTON;
  if (*GAMEPAD1 & BUTTON_RIGHT) buttons |= RIGHT_BUTTON;

  return buttons;
}

unsigned long Arduboy2Core::generateRandomSeed()
{
  unsigned long seed;

  // TODO: reimplement in software?
  return 0;
}

// delay in ms with 16 bit duration
// void Arduboy2Core::delayShort(uint16_t ms)
// {
//   delay((unsigned long) ms);
// }

void Arduboy2Core::exitToBootloader()
{
  // TODO: what to do here, anything?
}


//=========================================
//========== class Arduboy2NoUSB ==========
//=========================================

void Arduboy2NoUSB::mainNoUSB()
{
}

