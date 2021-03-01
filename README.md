<!----------------------------------------------------------------------------->
<!-- Readme for GitHub repo.                                                 -->
<!--                                                                         -->
<!-- Author:   Kip (https://github.com/kip93/).                              -->
<!-- Source:   https://github.com/kip93/lamp/                                -->
<!-- License:  BSD 3-Clause                                                  -->
<!----------------------------------------------------------------------------->

# Arduino LED lamp

<!-- Mostly constant stuff. Cache of a year for the first 2, and an hour for the rest. -->
[![Written in C++ badge](https://img.shields.io/badge/Written%20in-C%2B%2B-B13959?style=flat&cacheSeconds=31556952)](https://github.com/kip93/lamp/search?l=c%2B%2B)
[![Made with love badge](https://img.shields.io/badge/Made%20with-%E2%99%A5-B13959?style=flat&cacheSeconds=31556952)](./LICENSE)
[![License badge](https://img.shields.io/github/license/kip93/lamp?style=flat&label=License&color=B13959&cacheSeconds=3600)](./LICENSE)
[![Code size badge](https://img.shields.io/github/languages/code-size/kip93/lamp?style=flatt&label=Size&color=B13959&cacheSeconds=3600)](https://github.com/kip93/lamp)

<!-- Let's be honest, no need to update these very often either. Cached for 15 minutes. -->
[![Contributors count badge](https://img.shields.io/github/contributors/kip93/lamp?style=flat&label=Contributors&color=42853D&cacheSeconds=900)](https://github.com/kip93/lamp/graphs/contributors)
[![Repo watchers badge](https://img.shields.io/github/watchers/kip93/lamp?style=flat&label=Watchers&color=42853D&cacheSeconds=900)](https://github.com/kip93/lamp/watchers)
[![Repo stars badge](https://img.shields.io/github/stars/kip93/lamp?style=flat&label=Stars&color=42853D&cacheSeconds=900)](https://github.com/kip93/lamp/stargazers)
[![Repo forks badge](https://img.shields.io/github/forks/kip93/lamp?style=flat&label=Forks&color=42853D&cacheSeconds=900)](https://github.com/kip93/lamp/network/members)

<!-- Relatively "volatile" badges. Cached for a minute. -->
[![Commit activity badge](https://img.shields.io/github/commit-activity/m/kip93/lamp?style=flat&label=Commit%20activity&color=067CC1&cacheSeconds=60)](https://github.com/kip93/lamp/graphs/commit-activity)
[![Last commit badge](https://img.shields.io/github/last-commit/kip93/lamp?style=flat&label=Last%20commit&color=067CC1&cacheSeconds=60)](https://github.com/kip93/lamp/commits/main)
[![Issues badge](https://img.shields.io/github/issues/kip93/lamp?style=flat&label=Issues&color=067CC1&cacheSeconds=60)](https://github.com/kip93/lamp/issues)
[![Pull requests badge](https://img.shields.io/github/issues-pr/kip93/lamp?style=flat&label=PRs&color=067CC1&cacheSeconds=60)](https://github.com/kip93/lamp/pulls)

An Arduino powered LED lamp based on WS2812 LEDs. It consists of a circular
cylindrical LED matrix encased in a glass jar with defusing material inside to
spread the light and give it a softer look.

## Usage

The given [`lamp.ino`](./lamp.ino) only loads one effect at a time. You need to
change which effect is imported in that file and recompile to change the shown
effect. Some effects are declared in the [effects folder](./effects/), but the
code is designed to make it easy to add your own effects.

The size of the matrix is defined in the
[effect definition](./effects/effect.h). The given file defines a matrix of
14x16 LEDs, because that was the size my lamp could fit, but all given effects
should scale pretty well to any reasonable size.

To compile and upload the code to the Arduino you need to:

 * Download and install the
   [Arduino IDE](https://www.arduino.cc/en/Main.Software).
 * Open the program and in `Tools > Manage Libraries...` install
   [FastLED](http://fastled.io/).
 * Open the [`lamp.ino`](./lamp.ino) file.
 * In `Tools > Board` and `Tools > Processor` select the correct Arduino model
   you are using.
 * In `Tools > Port` select the correct port where your device is connected to
   your computer.
 * Press the `Upload` button (the right pointing arrow).
 * C'est fini. As long as there was no error in the previous steps, the code
   should've been uploaded to your Arduino device.

## Wiring

Wiring should be relatively simple. From the Arduino Nano, pins `GND` and `VIN`
should be used to supply power to the device, and any data pin (in this example,
`D13`) should be connected to the `DIN` from the first LED in the strip. Then,
use the same power supply to connect to pins `VSS` and `VDD` of the strip (aka
`GND` and `VCC`/`VIN`/`5V`, respectively). For other Arduino models, refer to
[their pinouts](https://web.archive.org/web/20201029095458/https://arduino.pinout.guide/)
to know their correct connections (should be pretty much the same, but just in
case).

A detailed schematic is included in [lamp.sch](./lamp.sch)
(a [KiCAD](https://kicad.org/) schematic file), with the exact wiring for
everything.

### NOTE 1:

Depending on the size of the matrix, you might want to split the power input
into multiple parts to avoid problems. Otherwise this could cause, for example,
that the LEDs further down the line do not turn on because powers has dropped
too far, or decreased brightness at the end of the strip. This is accomplished
by instead of daisy chaining the power from one column to the next, to instead
connect new wires coming straight from the power supply (the data wire should
still be connected as usual).

### NOTE 2:

Do not use the power of the Arduino itself to drive the LEDs except for really
small cases (I'd say 20 LEDs tops, depending on brightness and RGB values),
since that could overload its circuits. Instead, use and power both the Arduino
and the LEDs that way (as detailed above).
