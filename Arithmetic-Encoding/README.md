## Usage:
  * Compile Arithmetic-Encoder.cpp
  * Pass a input file with symbol frequencies and a string of symbols **as text**


## Output:
  * For a file x.csv a file x_freq.csv will be created with the frequencies and probability intervals for each symbol
  * On consoll will be printed:
     * The encoded value representing the given string of symbols
     * The decoded symbols from the encoded value

## Implementation details:
  * A DataContainer is firt initialized from the file
  * A FrequencyContainer is initialized based on the DataContainer
  * An ArithmeticEncoder passes the FrequencyContainer and computes a code for the input string of symbols
  * An ArithmeticDecoder passes the FrequencyContainer and re-computes the input string from the code
