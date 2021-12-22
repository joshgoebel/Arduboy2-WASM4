This is a port of the Arduboy2 library to WASM-4.

At a very high level:

- rips out all the legit hardware stuff (ports, I/O interfaces, sleep, etc)
- maps `Arduboy2::display` to the center of the WASM-4 screen
- maps the WASM-4 controller #1 to `Arduboy2Core::buttonsState()`
- bundles (for now) `ArduboyTones` and maps it's `tone([one note])` function to `w4.tone` channel 1
- adds some scaffolding for `<Arduino.h>` and friends to make porting most things easier
- 1024 buffer is still needs for the screen since all the native functions are still drawing to that buffer, only in `display` is that translated to the native WASM-4 display

### Example

<img src="https://aws1.discourse-cdn.com/standard14/uploads/arduboy/original/3X/6/1/6187b9adbd70ef1658b8162b59b07a8c2b3d3e4d.png" width="600" />

### TODO

- [ ] Restore sound in `Arduboy2Beep.cpp`
- [ ] more cleanups of the built-in functions
- [ ] random does nothing
- [ ] randomSeed does nothing
- [ ] does not support `Print` or `print` yet