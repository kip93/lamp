/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \
* Entry point for Arduino code.                                                *
*                                                                              *
* Author:   Kip (https://github.com/kip93/).                                   *
* Source:   https://github.com/kip93/lamp/                                     *
* License:  BSD 3-Clause                                                       *
\ * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "effects/effect.h"  // The abstract effect representation.
#include "effects/fire.h"    // The desired effect implementation.

/**
 * Global variable to keep the effect to be shown.
 */
Effect *effect;

/**
 * Code to be run at start up.
 *
 * This waits for a second to avoid unexpected issues with the hardware when
 * booting, and then sets up the desired effect.
 */
void setup() {
    delay(1000);
    effect = new Fire();
}

/**
 * Code to be repeatedly run forever.
 *
 * This just calls the update method on the effect.
 */
void loop() {
    effect -> update();
}
