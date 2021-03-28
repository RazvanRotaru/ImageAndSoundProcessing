#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>

#include "wave.h"

using namespace std;

#define samplingRate 8'000
#define bitsPerSample 16
#define channelsNo 1
#define frequency 400
#define A 15'000

int main(int argc, char* argv[]) {
    wave_hdr waveHeader;
    FILE* wavFile;

    int duration;
    if (argc <= 1) {
        cout << "Input signal duration:" << endl;
        cin >> duration;
    }
    else
        duration = atoi(argv[1]);
    
    int samplesNum = duration * samplingRate;
    int blockAlign = channelsNo * bitsPerSample / 8;
    int byteRate = samplingRate * blockAlign;
    int subchunk2Size = samplesNum * channelsNo * bitsPerSample / 8;
    int fileSize = sizeof(wave_hdr) + subchunk2Size; 

    waveHeader = {
        /* RIFF Header */
        {0x52, 0x49, 0x46, 0x46},   // "RIFF" in big-endian
        (uint32_t)(fileSize - 8),
        {0x57, 0x41, 0x56, 0x45},   // "WAVE" in big-endian

        /* "fmt" Subchunk */
        {0x66, 0x6d, 0x74, 0x20},   // "fmt " in big-endian
        (uint32_t)16,
        (uint16_t)1,                // PCM format
        (uint16_t)channelsNo,
        (uint32_t)samplingRate,
        (uint32_t)byteRate,
        (uint16_t)blockAlign,
        (uint16_t)bitsPerSample,

        /* "data" Subchunk */
        {0x64, 0x61, 0x74, 0x61},   // "data" in big-endian
        (uint32_t)subchunk2Size
    };

    if (!writeHeader(waveHeader, "audio/my_beep.wav"))
        return 1;
        
    int16_t* data = new int16_t[samplesNum];
    for (int i = 0; i < samplesNum; i++)
        data[i] = A * sin((float)((float)i / samplesNum *
                             2 * M_PI * frequency * duration));

    if (!writeData(data, waveHeader, "audio/my_beep.wav"))
        return 1;

    delete[] data;
    return 0;
}
