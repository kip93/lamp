/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \
* Implementation of a matrix-like effect.                                      *
*                                                                              *
* Author:   Kip (https://github.com/kip93/).                                   *
* Source:   https://github.com/kip93/lamp/                                     *
* License:  BSD 3-Clause                                                       *
\ * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "effect.h"  // Abstract effect structure.


/**
 * Matrix effect implementation.
 */
class Matrix : public Effect {

    public:  ///////////////////////////////////////////////////////////////////////

        /**
         * Destructor. Free up resources.
         */
        ~Matrix() {
            delete callback;
        }

        /**
         * Update the contents of the LED matrix.
         */
        void update() {
            fill(callback);
            show(10);  // Show changes and keep the code to ~10 FPS.
            callback -> update();
        }

    private:  //////////////////////////////////////////////////////////////////////

        /**
         * Effect callback that will compute and show the matrix effect.
         */
        class Callback : public FillCallback {

            public:

                /**
                 * Constructor. Initialised the random dots around the matrix.
                 */
                Callback() {
                    for(uint16_t i = 0; i < num_leds; ++i) {
                        dots[i] = random8(8) == 0;
                    }
                }

                /**
                 * Callback function. Shows the matrix animation.
                 *
                 * @param i The row index.
                 * @param j The column index.
                 *
                 * @returns An RGB colour to be set at the given coordinates.
                 */
                CRGB call(uint8_t i, uint8_t j) {
                    return (((uint32_t) 0x20) * rain[index(i, j)] / 0xFF << 16) +  // Red.
                           (((uint32_t) 0xC4) * rain[index(i, j)] / 0xFF << 8)  +  // Green.
                            ((uint32_t) 0x20) * rain[index(i, j)] / 0xFF;          // Blue.
                }

                /**
                 * Create the next frame of the matrix-like animation.
                 */
                void update() {
                    // Move up to 24 dots around randomly.
                    for(uint8_t i = 0; i < 24; ++i) {
                        uint16_t rand1 = random16(num_leds);
                        uint16_t rand2 = random16(num_leds);
                        if((dots[rand1] == true) && (dots[rand2] == false)) {
                            dots[rand1] = false;
                            dots[rand2] = true;
                        }
                    }

                    // Fade.
                    for(uint8_t i = 0; i < rows; ++i) {
                        for(uint8_t j = 0; j < cols; ++j) {
                            rain[index(i, j)] = qsub8(rain[index(i, j)], 0x30);
                        }
                    }

                    // Shift down.
                    for(uint8_t j = 0; j < cols; ++j) {
                        uint8_t foo = dots[index(0, j)];
                        for(uint8_t i = 1; i < rows; ++i) {
                            dots[index(i - 1, j)] = dots[index(i, j)];
                        }
                        dots[index(rows - 1, j)] = foo;
                    }

                    // Show new spots.
                    for(uint8_t i = 0; i < rows; ++i) {
                        for(uint8_t j = 0; j < cols; ++j) {
                            if(dots[index(i, j)]) {
                                rain[index(i, j)] = 0xFF;
                            }
                        }
                    }
                }

            private:

                /**
                 * An array containing the heads for the falling columns.
                 */
                bool dots[num_leds] = { };
                /**
                 * An array with the info to be shown. Contents define the intensity of each
                 * pixel.
                 */
                uint8_t rain[num_leds] = { };

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

#endif  // MATRIX_H_
