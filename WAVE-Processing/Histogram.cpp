#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>

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
    cout << "Getting histogram for " << filename << "..." << endl << endl;

    if (!readHeader(waveHeader, filename))
        return 1;

    int16_t* samples;
    int NumSamples = readData(&samples, waveHeader, filename);
    if (NumSamples == 0) 
        return 1; 

    map<int16_t, int> histogram;
    for (int i = 0; i < NumSamples; i++) {
        histogram[samples[i]] += 1;
    }

    outFile = fopen("output/histogram_values.csv", "w");
    for (map<int16_t, int>::iterator it = histogram.begin(); it != histogram.end(); it++)
        fprintf(outFile, "%d,%d\n", it->first, it->second);
    fclose(outFile);

    delete[] samples;
    return 0;
}