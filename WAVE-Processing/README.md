## Usage:
  * Makefile rules allow you to either:
      * Parse and export a file data - **make extract file=#FILENAME**
      * Compare the exported data to an Audacity export (*save Audacity export in /ref*) - **make compare_extracted**
      * Create a mono wav file of a given duration at a frequency of 400Hz sampled at 8000Hz with a word-length of 16 bits - **make create duration=#DURATION_IN_SEC**
      * Encode a given wav file using the muLaw function - **make encode file=#FILENAME**
      * Decode a given wav file using the inverse muLaw function - **make decode file=#FILENAME**
      * Plot the histogram of a given wav file - **make histogram file=#FILENAME** 


## Output:
  * The output data files (for data extraction and histogram) will be found in /output
  * The png with the histogram will also be found in /output
  * The created audio files will be found in /audio. The encoded file will be called beep1.wav, the decoded will be called beep2.wav and the created mono wav file will be called my_beep.wav

## Implementation details:
  * Currently only PCM format is accepted because of the header structure that does not need an additional "fact" block
  * Reads and writes to files are general, files of any bits per sample will be accepted and correctly processed
