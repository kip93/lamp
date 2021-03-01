/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \
* Implementation of a fire-like effect.                                        *
*                                                                              *
* Author:   Kip (https://github.com/kip93/).                                   *
* Source:   https://github.com/kip93/lamp/                                     *
* License:  BSD 3-Clause                                                       *
\ * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef FIRE_H_
#define FIRE_H_

#include "effect.h"  // Abstract effect structure.


/**
 * Fire effect implementation intended for a circular cylindrical LED matrix.
 */
class Fire : public Effect {

    public:  ///////////////////////////////////////////////////////////////////////

        /**
         * Destructor. Free up resources.
         */
        ~Fire() {
            delete callback;
        }

        /**
         * Update the contents of the LED matrix.
         */
        void update() {
            fill(callback);
            show(30);  // Show changes and keep the code to ~30 FPS.
            callback -> update();
        }

    private:  //////////////////////////////////////////////////////////////////////

        /**
         * The fire-ish colour palette.
         */
        static const ColourPalette palette PROGMEM;

        /**
         * Get a colour from the palette.
         */
        static CRGB get_colour(uint8_t index) {
            return interpolate_colour(palette, index);
        }

        /**
         * Effect callback that will compute and show the fire.
         */
        class Callback : public FillCallback {

            public:

                /**
                 * Callback function. Shows the fire animation.
                 *
                 * @param i The row index.
                 * @param j The column index.
                 *
                 * @returns An RGB colour to be set at the given coordinates.
                 */
                CRGB call(uint8_t i, uint8_t j) {
                    return get_colour(fire[index(i, j)]);
                }

                /**
                 * Create the next frame of the fire-like animation.
                 */
                void update() {
                    // Shift all rows up and "decay" the colours.
                    for(uint8_t i = rows - 1; i > 0;--i) {
                        for(uint8_t j = 0; j < cols; ++j) {
                            fire[index(i, j)] = qadd8(fire[index(i - 1, j)], 0x1F) - 0x0F;
                        }
                    }

                    // Create a new random bottom row.
                    for(uint8_t j = 0; j < cols; ++j) {
                        fire[index(0, j)] = random8(0x20, 0x90);
                    }
                }

            private:

                /**
                 * An array with the info to be shown. Contents are indices to be used with the
                 * colour palette.
                 */
                uint8_t fire[num_leds] = {  // Initialise to a dark background.
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
                 };

                /**
                 * Compute the linear coordinate of a pixel in the array based on its real
                 * position.
                 *
                 * @param i The row coordinate of the pixel.
                 * @param j The column coordinate of the pixel.
                 *
                 * @warning This will not validate the inputs, and using invalid coordinates
                 *          results in undefined behaviour.
                 */
                static uint16_t index(uint8_t i, uint8_t j) {
                    return ((uint16_t) i) + ((uint16_t) j) * ((uint16_t) rows);
                }
        };

        /**
         * The callback instance to be sent to the parent class.
         */
        Callback * const callback = new Callback();
};

// Populate the contents of the colour palette.
const ColourPalette Fire::palette PROGMEM = {
    0xFFD033, 0xFFBE33, 0xFEAE01, 0xFE9A01,
    0xFE8F01, 0xFA7D01, 0xEF7101, 0xD86001,
    0xAF4A01, 0x923701, 0x651802, 0x470202,
    0x2E0001, 0x140101, 0x070101, 0x050000,
};

#endif  // FIRE_H_
