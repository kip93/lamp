/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \
* Implementation of a simple shifting solid colour effect.                     *
*                                                                              *
* Author:   Kip (https://github.com/kip93/).                                   *
* Source:   https://github.com/kip93/lamp/                                     *
* License:  BSD 3-Clause                                                       *
\ * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef RAINBOW_H_
#define RAINBOW_H_

#include "effect.h"  // Abstract effect structure.


/**
 * Effect implementation that shows a slowly changing solid colour.
 */
class Rainbow : public Effect {

    public:  ///////////////////////////////////////////////////////////////////////

        /**
         * Destructor. Free up resources.
         */
        ~Rainbow() {
            delete callback;
        }

        /**
         * Update the contents of the LED matrix.
         */
        void update() {
            fill(callback);
            show(2);  // Show changes and keep the code to ~2 FPS.
            callback -> update();
        }

    private:  //////////////////////////////////////////////////////////////////////

        /**
         * Effect callback that will compute and show the correct colour.
         */
        class Callback : public FillCallback {

            public:

                /**
                 * Callback function. Shows the current colour.
                 *
                 * @param i The row index.
                 * @param j The column index.
                 *
                 * @returns An RGB colour to be set at the given coordinates.
                 */
                CRGB call(uint8_t i, uint8_t j) {
                    return interpolate_colour(RainbowColors_p, index);
                }

                /**
                 * Shift to the next colour.
                 */
                void update() {
                    index += 1;
                }

            private:

                /**
                 * The current colour to be shown.
                 */
                uint8_t index = 0;
        };

        /**
         * The callback instance to be sent to the parent class.
         */
        Callback * const callback = new Callback();
};

#endif  // RAINBOW_H_
