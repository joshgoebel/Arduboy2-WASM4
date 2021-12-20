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
#include <abw4lib.h>
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







void update() {

  // arduboy.bootLogoSpritesSelfMasked();
  if (stillBooting()) {
    return;
  }

  if (!(arduboy.nextFrame())) return;
  if (gameState < STATE_GAME_NEXT_LEVEL && arduboy.everyXFrames(10))sparkleFrames = (++sparkleFrames) % 5;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();

  PALETTE[0] = 0x000000;
  PALETTE[1] = 0xffff99;
  *DRAW_COLORS = 1;

  memset(FRAMEBUFFER,0xFF,3200);
  arduboy.display();
}
