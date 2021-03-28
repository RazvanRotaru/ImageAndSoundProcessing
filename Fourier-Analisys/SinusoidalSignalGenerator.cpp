#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>

#include "wave.h"

using namespace std;

#define samplingRate 8'000
#define bitsPerSample 16
#define channelsNo 1
#define samplesNo 1024

int main(int argc, char* argv[]) {
    wave_hdr waveHeader;
    
    int A, frequency;
    char *filename;
    if (argc <= 3) {
        cout << "Input filename:" << endl;                  cin >> filename;
        cout << "Input signal frequency:" << endl;          cin >> frequency;
        cout << "Input signal maximum amplitude:" << endl;  cin >> A;
    }
    else {
        filename = argv[1];
        frequency = atoi(argv[2]);
        A = atoi(argv[3]);
    }
    string filepath = "audio/"; filepath += filename;
    
    waveHeader = createHeader(samplingRate, bitsPerSample, channelsNo, samplesNo);
    if (!writeHeader(waveHeader, filepath.c_str()))
        return 1;
        
    int16_t* data = new int16_t[samplesNo];
    for (int i = 0; i < samplesNo; i++)
        data[i] = A * sin((float)((float)i / samplingRate *
                                            2 * M_PI * frequency));

    if (!writeData(data, waveHeader, filepath.c_str()))
        return 1;

    delete[] data;
    return 0;
}