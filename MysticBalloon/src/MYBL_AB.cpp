/*
  Mystic Balloon: http://www.team-arg.org/mybl-manual.html

  Arduboy version 1.7.2:  http://www.team-arg.org/mybl-downloads.html

  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

  2016-2018 - GAVENO - CastPixel - JO3RI - Martian220

  Game License: MIT : https://opensource.org/licenses/MIT

*/

//determine the game
#define GAME_ID 34

#include <Arduino.h>
#include "wasm4.h"
#include "globals.h"
#include "menu.h"
#include "game.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"
#include "levels.h"


typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM  mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuHelp,
  stateMenuPlaySelect,
  stateMenuInfo,
  stateMenuSoundfx,
  stateGameNextLevel,
  stateGamePlaying,
  stateGamePause,
  stateGameOver,
  stateMenuPlayContinue,
  stateMenuPlayNew,
};

void start()
{
  // arduboy.boot();                                           // begin with the boot logo en setting up the device to work
  // arduboy.audio.begin();
  // arduboy.bootLogoSpritesSelfMasked();
  // arduboy.setFrameRate(60);                                 // set the frame rate of the game at 60 fps
  EEPROM.boot();
  loadSetEEPROM();
}



unsigned int bootTicks = 0;
uint8_t bootMode = 0;
void wasm4Logo() {
  bootTicks++;

  const uint8_t logo[1024] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x2a,0xaa,0xaa,0xa8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2a,0xaa,0xaa,0xa8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2a,0xaa,0xaa,0xa8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,0xaa,0xaa,0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,0xaa,0xaa,0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xaa,0xaa,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xaa,0xaa,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x15,0x55,0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0x55,0x40,0x00,0x00,0x00,0x00,0x01,0x55,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0x55,0x40,0x00,0x00,0x00,0x00,0x01,0x55,0x40,0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x55,0x50,0x00,0x00,0x00,0x00,0x01,0x55,0x40,0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x55,0x50,0x00,0x00,0x00,0x00,0x01,0x55,0x40,0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x55,0x50,0x00,0x00,0x00,0x00,0x01,0x55,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0x55,0x40,0x00,0x00,0x00,0x00,0x01,0x55,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0x55,0x40,0x00,0x00,0x00,0x55,0x55,0x55,0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x15,0x55,0x00,0x00,0x00,0x00,0x55,0x55,0x55,0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x01,0x50,0x00,0x00,0x00,0x00,0x55,0x55,0x55,0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0x55,0x55,0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0x55,0x55,0x55,0x55,0x00,0x00,0x00,0x15,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0x55,0x55,0x55,0x55,0x00,0x00,0x01,0x55,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x40,0x00,0x00,0x00,0x05,0x55,0x54,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x40,0x00,0x00,0x00,0x05,0x55,0x54,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x40,0x00,0x00,0x00,0x15,0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x40,0x00,0x00,0x00,0x15,0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x40,0x00,0x00,0x00,0x15,0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x40,0x00,0x00,0x00,0x05,0x55,0x54,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x40,0x00,0x00,0x00,0x05,0x55,0x54,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x55,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x15,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

  PALETTE[0] = 0x000;
  PALETTE[1] = 0x668f31;
  PALETTE[2] = 0xd3e6bb;
  PALETTE[3] = 0xff0000;
  *DRAW_COLORS = 0x1032;
  blit(logo, 48, 48, 64, 64, BLIT_2BPP);
  if (bootTicks>100)
    bootMode++;
}

void jgLogo() {
  bootTicks++;

  *DRAW_COLORS = 0x11;
  rect(0,0,159,159);

  *DRAW_COLORS = 2;
  text("Hello from C! How are oyu? xxxx", 10, 10);

  if (bootTicks>200)
      bootMode++;
}

const int BOOT_MODE_COUNT = 2;
const FunctionPointer bootModes[2] = {
  wasm4Logo,
  jgLogo
};


void update() {

  // arduboy.bootLogoSpritesSelfMasked();
  if (bootMode < BOOT_MODE_COUNT) {
    bootModes[bootMode]();
    return;
  }


  // if (!(arduboy.nextFrame())) return;
  if (gameState < STATE_GAME_NEXT_LEVEL && arduboy.everyXFrames(10))sparkleFrames = (++sparkleFrames) % 5;
  arduboy.pollButtons();
  arduboy.clear();
  // gameState = ;
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();

  PALETTE[0] = 0x000000;
  PALETTE[1] = 0xffff99;
  *DRAW_COLORS = 1;

  // memset(FRAMEBUFFER,0xFF,3200);
  arduboy.display();
  arduboy.frameCount++;


    // uint8_t gamepad = *GAMEPAD1;
    // if (gamepad & BUTTON_1) {
    //     *DRAW_COLORS = 4;
    // }

    // blit(smiley, 76, 76, 8, 8, BLIT_1BPP);
    // text("Press X to blink", 16, 90);
}
