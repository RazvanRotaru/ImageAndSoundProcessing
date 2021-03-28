#include <iostream>
#include <fstream>

#include "wave.h"

using namespace std;

int main(int argc, char* argv[]) {
    wave_hdr waveHeader1, waveHeader2;

    char *filename1, *filename2, *outfile;
    if (argc <= 3) {
        cout << "Input file 1:" << endl;        cin >> filename1;
        cout << "Input file 2:" << endl;        cin >> filename2;
        cout << "Input outputfile:" << endl;    cin >> outfile;
    }
    else {
        filename1 = argv[1];
        filename2 = argv[2];
        outfile = argv[3];
    }
    string path = "audio/";
    string filepath1 = path + filename1;
    string filepath2 = path + filename2;
    string outfilepath = path + outfile;

    /* read signal 1 */
    if (!readHeader(waveHeader1, filepath1.c_str()))
        return 1;
    int16_t* samples1;
    int samplesNo1 = readData(&samples1, waveHeader1, filepath1.c_str());
    if (samplesNo1 == 0) 
        return 1;

    /* read signal 2 */
    if (!readHeader(waveHeader2, filepath2.c_str()))
        return 1;
    int16_t* samples2;
    int samplesNo2 = readData(&samples2, waveHeader2, filepath2.c_str());
    if (samplesNo2 == 0) 
        return 1;


    /* combine signals */
    wave_hdr waveHeader = combineHeaders(waveHeader1, waveHeader2); 
    if (!writeHeader(waveHeader, outfilepath.c_str()))
        return 1;
    int16_t* data = combineData(samples1, samplesNo1, samples2, samplesNo2);
    if (!writeData(data, waveHeader, outfilepath.c_str()))
        return 1;

    delete[] data;
    return 0;
}