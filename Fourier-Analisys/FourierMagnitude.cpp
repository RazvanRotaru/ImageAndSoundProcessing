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

    string outFilename = "output/magnitudes_" + removeExtension(filename) + ".csv";
    FILE* outfile = fopen(outFilename.c_str(), "w");
    for (int i = 0; i < samplesNo; i++)
        fprintf(outfile, "%d,%f\n", i, magnitude(complexSamples_frequency[i]));
    fclose(outfile);

    delete[] complexSamples_frequency;
    return 0;
}