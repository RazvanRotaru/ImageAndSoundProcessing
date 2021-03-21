#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

#include "wave.h"

using namespace std;

int main(int argc, char* argv[]) {
    wave_hdr waveHeader;
    FILE *inFile, *outFile; 

    char* filename;
    if (argc <= 1) {
        cout << "Input file name:" << endl;
        cin.get(filename, 256);
    }
    else 
        filename = argv[1];
    cout << "Parsing " << filename << "..." << endl << endl;

    if (!readHeader(waveHeader, filename))
        return 1;

    cout << "File size: " << getFileSize(&waveHeader) << endl;
    cout << "File format: " << convertToText(&(waveHeader.Format), sizeof(waveHeader.Format)) << endl;
    cout << "Audio format: " << waveHeader.AudioFormat << endl;
    cout << "Channels no: " << waveHeader.NumChannels << endl;
    cout << "Sample rate: " << waveHeader.SampleRate << endl;
    cout << "Bits per sample: " << waveHeader.BitsPerSample << endl;
    cout << "Samples value: [";

    int16_t* samples;
    int NumSamples = readData(&samples, waveHeader, filename);
    if (NumSamples == 0) 
        return 1; 

    outFile = fopen("output/sample_values.csv", "w");
    for (int i = 0; i < NumSamples; i++) {
        fprintf(outFile, "%d,%d\n", i, samples[i]);
        if (i <= 10)
            cout << samples[i] << ", ";
    }
    cout << "...]" << endl;
    fclose(outFile);

    outFile = fopen("output/normalized_sample_values.txt", "w");
    for (int i = 0; i < NumSamples; i++)
        fprintf(outFile, "%.5f\n", normalize(samples[i]));
    fclose(outFile);

    delete[] samples;
    return 0;
}