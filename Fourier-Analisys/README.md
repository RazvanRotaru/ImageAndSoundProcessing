## Usage:
  * Makefile rules allow you to either:
      * **make sinusoidal_signal** - makes two sinusoidal mono wave files, sin1.wav and sin2.wav both having a 8KHz sampling rate, 16b/sample, and 1024 samples
        * [argument] (default value)
        * frequency1 (400Hz)
        * frequency2 (1KHz)
        * amplitude1 (15.000)
        * amplitude2 (10.000)     
      * **make combine_signals** - combines the result of *sinusoidal_signal* rule
      * **make frequency_charts** - plots the frequency magnitudes of all files created by *combine_signals* and its dependencies
      * **analyze_frequency** - analyzes sin3.wav's frequencies and compares them to two references
        * [argument] (default value)
        * frequency1 (400Hz)
        * frequency2 (1KHz)
      * **two_way_fourier** - applies both direct and inverse Fourier transforms to sin3.wav and saves the processed values to i_sin3.wav
      * **clean**

## Output:
  * The output *csv* magnitude files will be found in **/output**
  * The *png* with the chart will also be found in **/output**
  * The created audio files will be found in **/audio**

## Implementation details:
  * A custom structure for complex numbers can be found in **complex.h**
  * Fourier transform implementation can be found in **fourier.h**
