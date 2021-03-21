#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
#include <cmath>

#include "wave.h"

using namespace std;

float d(float normalizedSample) {
    float x = abs(normalizedSample);
    int mu = 255;
    float sign = normalizedSample / x;
    
    return sign * ((powf(mu + 1, x) -1) / mu);
}

int16_t i_muLaw(float normalizedSample) {
    float maxVal = 1 << (sizeof(int16_t) * 8 - 1);
    return floor(maxVal * (float)d(normalizedSample));
}

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

    if (!readHeader(waveHeader, filename))
        return 1;

    int16_t* samples;
    int NumSamples = readData(&samples, waveHeader, filename);
    if (NumSamples == 0) 
        return 1; 

    /* Compute the muLaw decoded data */
    int16_t* data = new int16_t[NumSamples];
    for (int i = 0; i < NumSamples; i++)
        data[i] = i_muLaw(normalize((int8_t)(samples[i] - 128)));

    /* Adjust header to new bits per sample */
    waveHeader.ByteRate *= 2;
    waveHeader.BlockAlign *= 2;
    waveHeader.BitsPerSample *= 2;
    waveHeader.Subchunk2Size *= 2;
    waveHeader.ChunkSize = waveHeader.Subchunk2Size + 36;
    waveHeader.AudioFormat = 1; // PCM format

    if (!writeHeader(waveHeader, "audio/beep2.wav"))
        return 1;
    if (!writeData(data, waveHeader, "audio/beep2.wav"))
        return 1;

    delete[] data;
    delete[] samples;
    return 0;
}