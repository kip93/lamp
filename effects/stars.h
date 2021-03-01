/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \
* Implementation of a starry effect.                                           *
*                                                                              *
* Author:   Kip (https://github.com/kip93/).                                   *
* Source:   https://github.com/kip93/lamp/                                     *
* License:  BSD 3-Clause                                                       *
\ * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef STARS_H_
#define STARS_H_

#include "effect.h"  // Abstract effect structure.


/**
 * Stars effect implementation.
 */
class Stars : public Effect {

    public:  ///////////////////////////////////////////////////////////////////////

        /**
         * Destructor. Free up resources.
         */
        ~Stars() {
            delete callback;
        }

        /**
         * Update the contents of the LED matrix.
         */
        void update() {
            fill(callback);
            show(60);  // Show changes and keep the code to ~60 FPS.
            callback -> update();
        }

    private:  //////////////////////////////////////////////////////////////////////

        /**
         * Effect callback that will compute and show the starry effect.
         */
        class Callback : public FillCallback {

            public:

                /**
                 * Callback function. Shows the starry animation.
                 *
                 * @param i The row index.
                 * @param j The column index.
                 *
                 * @returns An RGB colour to be set at the given coordinates.
                 */
                CRGB call(uint8_t i, uint8_t j) {
                    return 0x010101 * stars[index(i, j)];
                }

                /**
                 * Create the next frame of the stars animation.
                 */
                void update() {
                    //  Generate random spots.
                    if(random8(0x04) == 0) {
                        stars[index(random8(rows), random8(cols))] = random8(0xA0, 0xFF);
                    }

                    // Fade.
                    for(uint8_t i = 0; i < rows; ++i) {
                        for(uint8_t j = 0; j < cols; ++j) {
                            stars[index(i, j)] = qsub8(stars[index(i, j)], 0x02);
                        }
                    }
                }

            private:

                /**
                 * An array with the info to be shown. Contents define the intensity of each
                 * pixel.
                 */
                uint8_t stars[num_leds] = { };

                /**
                 * Compute the linear coordinate of a star in the array based on its real
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

#endif  // STARS_H_
