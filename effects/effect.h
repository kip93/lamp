/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \
* Abstract representation of effects.                                          *
*                                                                              *
* Author:   Kip (https://github.com/kip93/).                                   *
* Source:   https://github.com/kip93/lamp/                                     *
* License:  BSD 3-Clause                                                       *
\ * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef EFFECT_H_
#define EFFECT_H_

#include <avr/pgmspace.h>  // Allow access to PROGMEM.
#include <FastLED.h>       // LED control library.


typedef TProgmemPalette16 ColourPalette;

/**
 * Abstract class for effects to be shown on the circular cylindrical LED
 * matrix.
 */
class Effect {

    public:  ///////////////////////////////////////////////////////////////////////

        /**
         * Define the shape of the matrix. Rows defines the height and cols the diameter.
         */
        static const uint8_t rows = 16, cols = 14;

        /**
         * The total amount of LEDs in the matrix.
         */
        static const uint16_t num_leds = rows * cols;

        /**
         * Abstract method. This updates the contents of the LED matrix.
         */
        virtual void update() = 0;

    protected:  ////////////////////////////////////////////////////////////////////

        /**
         * Constructor. Initialises the LED matrix through the FastLED library.
         */
        Effect() {
            FastLED.addLeds<WS2812, 13, GRB>(this -> buffer, num_leds).setCorrection(TypicalLEDStrip);

            FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);  // Max 5V, 2A.
            FastLED.setBrightness(0x18);
        }

        /**
         * Get a value from the frame buffer.
         *
         * @param i The row coordinate of the LED.
         * @param j The column coordinate of the LED.
         *
         * @returns The current RGB value.
         *
         * @warning This will not validate the inputs, and using invalid coordinates
         *          results in undefined behaviour.
         */
        CRGB get_led(uint8_t i, uint8_t j) {
            return buffer[index(i, j)];
        }

        /**
         * Set the value of an entry in the frame buffer.
         *
         * @param i The row coordinate of the LED.
         * @param j The column coordinate of the LED.
         * @param colour the colour to be set.
         *
         * @warning This will not validate the inputs, and using invalid coordinates
         *          results in undefined behaviour.
         */
        void set_led(uint8_t i, uint8_t j, CRGB colour) {
            buffer[index(i, j)] = colour;
        }

        /**
         * Set the value of an entry in the frame buffer.
         *
         * @param i The row coordinate of the LED.
         * @param j The column coordinate of the LED.
         * @param colour the colour to be set.
         *
         * @warning This will not validate the inputs, and using invalid coordinates
         *          results in undefined behaviour.
         */
        void set_led(uint8_t i, uint8_t j, uint16_t colour) {
            buffer[index(i, j)] = colour;
        }

        /**
         * Callback interface for the fill method.
         */
        class FillCallback {

            public:

                /**
                 * Callback function.
                 *
                 * @param i The row index.
                 * @param j The column index.
                 *
                 * @returns An RGB colour to be set at the given coordinates.
                 */
                virtual CRGB call(uint8_t i, uint8_t j) = 0;
        };

        /**
         * Helper method that iterates over the LEDs frame buffer and changes its
         * content.
         *
         * @param callback A function that receives the coordinates of an LED and returns
         *                 the colour to be set.
         */
        void fill(FillCallback *callback) {
            for(uint8_t i = 0; i < rows; ++i) {
                for(uint8_t j = 0; j < cols; ++j) {
                    set_led(i, j, callback -> call(i, j));
                }
            }
        }

        /**
         * Helper method that fills all of the frame buffer with a single colour.
         *
         * @param colour The colour to be used.
         */
        void fill(CRGB colour) {
            for(uint8_t i = 0; i < rows; ++i) {
                for(uint8_t j = 0; j < cols; ++j) {
                    set_led(i, j, colour);
                }
            }
        }

        /**
         * Take the current contents on the frame buffer and display it on the real LED
         * matrix.
         *
         * @param fps This defines the frequency at which the display will be updated by
         *            halting execution momentarily.
         */
        void show(uint8_t fps) {
            FastLED.show();
            FastLED.delay(1000 / fps);
        }

        /**
         * Use linear blending to interpolate 256 colours from a 16 colour palette.
         *
         * @param palette The colour palette to be interpolated.
         * @param index The virtual index for the colour to be computed.
         */
        static CRGB interpolate_colour(CRGBPalette16 palette, uint8_t index) {
            return ColorFromPalette(palette, index, 0xFF, LINEARBLEND);
        }

    private:  //////////////////////////////////////////////////////////////////////

        /**
         * The frame buffer which will hold the information to be shown on next update.
         */
        CRGB buffer[num_leds] = { };  // Initialise the buffer with black.

        /**
         * Compute the linear coordinate of an LED in the buffer based on its real
         * position.
         *
         * @param i The row coordinate of the LED.
         * @param j The column coordinate of the LED.
         *
         * @warning This will not validate the inputs, and using invalid coordinates
         *          results in undefined behaviour.
         */
        static uint16_t index(uint8_t i, uint8_t j) {
            return ((uint16_t) i) + ((uint16_t) j) * ((uint16_t) rows);
        }
};

#endif  // EFFECT_H_
