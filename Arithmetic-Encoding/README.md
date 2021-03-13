## Usage:
  * Compile Arithmetic-Encoder.cpp
  * Pass a input file with symbol frequencies and a string of symbols **as text**


## Implementation details:
  * A DataContainer is firt initialized from the file
  * A FrequencyContainer is initialized based on the DataContainer
  * An ArithmeticEncoder passes the FrequencyContainer and computes a code for the input string of symbols
  * An ArithmeticDecoder passes the FrequencyContainer and re-computes the input string from the code
