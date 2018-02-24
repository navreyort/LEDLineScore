# LED Line Score

A score-based approach to fade-control RGB colors on WS2801 driver chips. Requires [Adafruit-WS2801-Library](https://github.com/adafruit/Adafruit-WS2801-Library). 

### Scoring Mechanism

The score for the LED sequence can be specified in the main LEDLineScore.ino file. A complete score for one LED is specified as:

    #define kNumEvents1 5
    Color *color1[kNumEvents1] = {BLUE, BLACK, BLACK, GREEN, BLACK};
    uint16_t time1[kNumEvents1] = {4,2,4,6,2};

The `kNumEvents1` macro determines how many colors the system will go through for one LED.

The first part of the scoring system is to specify the color sequence as an array:

    Color *color1[kNumEvents1] = {BLUE, BLACK, BLACK, GREEN, BLACK};

The next step is to specify how many seconds (currently only integer multiples) the sequence needs to take to get to the next color. This time information is also specified using an array:

    uint16_t time1[kNumEvents1] = {4,2,4,6,2};
    
The two arrays in the above examples can then be interpreted as a sequence that takes 4 seconds to reach BLUE, 2 seconds to go to BLACK, stays on BLACK for 4 seconds, and so forth... 

Be sure to update the `kNumEvents1` macro to match the number of elements in the arrays when adding more color flows. Once a color sequence reaches the end, the system will automatically loop the sequence from the beginning.

### Adding New Colors

You can add new colors by creating new `Color` variables. For example:

    Color MAGENTA = new Color(255,0,255);
    
### Adding More LEDs

By default, the scoring system only defines 7 LEDs (`color1` ~ `color7`). You can add more LEDs by copy/pasting the existing color sequence definitions described above. Be sure to give a new name to the new definitions (e.g. `kNumEvents1` to `kNumEvents8`, `color1` to `color8`, and so forth...). 

In addition to creating new definitions, you will also need to instantiate the `ColorEnvelope` class that handles new LED sequence in the `setup()` function:

    envelopes[0] = new ColorEnvelope(color1,time1,kNumEvents1,0);

The first three parameters for the `ColorEnvelope` class is the definition of the LED color sequence described above. The last parameter defines the ID of the LED governed by WS2801 driver chips. The `ColorEnvelope` class needs to be stored in the array called `envelopes` for the entire system to properly function. An update to the `kNumLEDs` macro with an appropriate number is required when adding more LEDs.