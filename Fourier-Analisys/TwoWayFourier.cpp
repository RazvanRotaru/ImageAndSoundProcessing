#include <iostream>
#include <fstream>

#include "wave.h"
#include "complex.h"
#include "fourier.h"
#include "utils.h"

using namespace std;

int main(int argc, char* argv[]) {
    wave_hdr waveHeader;

    char *filename;
    if (argc <= 1) {
        cout << "Input filename:" << endl;  cin >> filename;
    }
    else 
        filename = argv[1];
    string filepath = "audio/"; filepath += filename;

    if (!readHeader(waveHeader, filepath.c_str()))
        return 1;
    int16_t* samples;
    int samplesNo = readData(&samples, waveHeader, filepath.c_str());
    if (samplesNo == 0) 
        return 1;
    
    complex* complexSamples = makeComplexArray(samples, samplesNo);
    complex* complexSamples_frequency = fourier(complexSamples, samplesNo);
    complex* complexSamples_time = inverse_fourier(complexSamples_frequency, samplesNo);
    int16_t* data = makeRealArray(complexSamples_time, samplesNo);
    
    string outfilepath = "audio/i_"; outfilepath += filename;
    if (!writeHeader(waveHeader, outfilepath.c_str()))
        return 1;
    if (!writeData(data, waveHeader, outfilepath.c_str()))
        return 1;

    delete[] data;
    return 0;
}