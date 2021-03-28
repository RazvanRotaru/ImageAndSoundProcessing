#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "wave.h"
#include "complex.h"
#include "fourier.h"
#include "utils.h"

using namespace std;


int main(int argc, char* argv[]) {
    wave_hdr waveHeader;

    string filename;
    float *refFrequencies;
    int frequenciesNo;

    if (argc <= 2) {
        string input;
        
        cout << "Input filename: ";
        getline(cin, input);
        stringstream(input) >> filename;

        cout << "Input number of reference frequencies: ";
        getline(cin, input);
        stringstream(input) >> frequenciesNo;

        refFrequencies = new float[frequenciesNo];
        for (int i = 0; i < frequenciesNo; i++) {
            cout << "Input reference frequency " << i+1 << ": " << flush;
            getline(cin, input);
            stringstream(input) >> refFrequencies[i];
        }
    }
    else {
        filename = argv[1];
        frequenciesNo = argc - 2;
        refFrequencies = new float[frequenciesNo]; 
        for (int i = 2; i < argc; i++) {
            refFrequencies[i - 2] = atoi(argv[i]);
        }
    }
    string filepath = "audio/"; filepath += filename;

    if (!readHeader(waveHeader, filepath.c_str()))
        return 1;

    float time = getTotalTime(waveHeader);
    float fNyquist = getNyquistFrequnecy(waveHeader);
    float refNyquist = waveHeader.SampleRate / 2;

    int16_t* samples;
    int samplesNo = readData(&samples, waveHeader, filepath.c_str());
    if (samplesNo == 0) 
        return 1;
    
    complex* complexSamples = makeComplexArray(samples, samplesNo);
    complex* complexSamples_frequency = fourier(complexSamples, samplesNo);
    int* spikes = extractSpikes(complexSamples_frequency, samplesNo);

    printf("Reference frequencies: ");
    for (int i = 0; i < frequenciesNo; i++)
        printf("%.2fHz ", refFrequencies[i]);
    printf("\nReference Nyquist frequency: %.2fHz\n", refNyquist);

    printf("\n\nAnalysing file %s of length %.3fms...\n\n", filename.c_str(), time * 1'000);
    printf("Identified frequencies: \n");
    for (int i = 0; i < frequenciesNo; i++) {
        float frequency = (float)spikes[i] / time;
        printf("%s\n", compare(frequency, refFrequencies[i], "Hz"));
    }
    printf("Identified Nyquist frequency:\n");
    printf("%s\n", compare(fNyquist, refNyquist, "Hz"));

    delete[] complexSamples_frequency;
    delete[] refFrequencies;
    delete[] spikes;
    return 0;
}