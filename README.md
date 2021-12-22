This is a port of the Arduboy2 library to WASM-4.

At a very high level:

- rips out all the legit hardware stuff (ports, I/O interfaces, sleep, etc)
- maps `Arduboy2::display` to the center of the WASM-4 screen
- maps the WASM-4 controller #1 to `Arduboy2Core::buttonsState()`
- bundles (for now) `ArduboyTones` and maps it's `tone([one note])` function to `w4.tone` channel 1
- adds some scaffolding for `<Arduino.h>` and friends to make porting most things easier
- 1024 buffer is still needs for the screen since all the native functions are still drawing to that buffer, only in `display` is that translated to the native WASM-4 display

### Porting checklist

- You can't use tight loops waiting for input, since WASM-4 is event driven and `update` is called at 60 FPS
- You're stuck with 60 FPS (or an even multiple, 30, 15, etc.)

### Example

<img src="https://aws1.discourse-cdn.com/standard14/uploads/arduboy/original/3X/6/1/6187b9adbd70ef1658b8162b59b07a8c2b3d3e4d.png" width="600" />

To play it online:

<https://ajoshguy.itch.io/mystic-balloons-w4>

### Requirements

- A working C/C++ toolchain on your local machine for compiling
- Working Make tooks, since you'll need `make` to build
- The WASM-4 `w4` console utility for running or bundling your cartridges

### TODO

- [ ] Restore sound in `Arduboy2Beep.cpp`
- [ ] more cleanups of the built-in functions
- [ ] random does nothing
- [ ] randomSeed does nothing
- [ ] does not support `Print` or `print` yet
- [ ] Move palette setup and such things into the library
- [ ] Is there some way to hide `EEPROM.boot()`?


### Porting Mystic Balloons

Pretty much all the work was in the main sketch file:

Before:

```c++
void setup()
{
  arduboy.boot();
  arduboy.audio.begin();
  arduboy.bootLogoSpritesSelfMasked();
  arduboy.setFrameRate(60);
  loadSetEEPROM();
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  if (gameState < STATE_GAME_NEXT_LEVEL && arduboy.everyXFrames(10))sparkleFrames = (++sparkleFrames) % 5;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}
```

After:

Make sure you notice the functions have been renamed to `start` and `update`.

```c++
void start()
{
  arduboy.boot();
  // we MUST set aside 1024 of RAM to allow us to easily
  // persist the entire EEPROM to disk correctly
  EEPROM.boot();
  // does nothing currently, we're really always 60 FPS
  // but perhaps we can make it work with 15 or 30 in the future
  arduboy.setFrameRate(60);
  arduboy.audio.begin();
  loadSetEEPROM();
}

void update() {
  if (stillBooting()) {
    return;
  }

  // set our "black and white" pallette
  PALETTE[0] = 0x000000;
  PALETTE[1] = 0xffff99;

  if (!(arduboy.nextFrame())) return;
  if (gameState < STATE_GAME_NEXT_LEVEL && arduboy.everyXFrames(10))sparkleFrames = (++sparkleFrames) % 5;
  arduboy.pollButtons();
  arduboy.clear();
  // this can be simplified since we have no PROGMEM on WASM-4
  mainGameLoop[gameState]();
  arduboy.display();
}
```

Update is only called when the next frame is needed so essentially `nextFrame()` is almost a NOP, but it still does useful things with regard to frame counting, etc. so it's best to leave it.