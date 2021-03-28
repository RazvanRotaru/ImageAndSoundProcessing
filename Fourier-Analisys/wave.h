#pragma once

#include <string>
#include <limits>
#include <math.h>

using namespace std;

typedef struct WAVE_HEADER {
    /* RIFF Header */
    uint8_t     ChunkID[4];
    uint32_t    ChunkSize;
    uint8_t     Format[4];

    /* "fmt" Subchunk */
    uint8_t     Subchunk1ID[4];
    uint32_t    Subchunk1Size;
    uint16_t    AudioFormat;
    uint16_t    NumChannels;
    uint32_t    SampleRate;
    uint32_t    ByteRate;
    uint16_t    BlockAlign;
    uint16_t    BitsPerSample;

    /* "data" Subchunk */
    uint8_t     Subchunk2ID[4];
    uint32_t    Subchunk2Size;
} wave_hdr;

int getFileSize(wave_hdr* waveHeader) {
    if (waveHeader == nullptr)
        return 0;
    return waveHeader->ChunkSize 
            + sizeof(waveHeader->ChunkSize) 
                + sizeof(waveHeader->ChunkID);
}

int getSamplesNo(wave_hdr waveHeader) {
    return waveHeader.Subchunk2Size / (waveHeader.NumChannels * waveHeader.BitsPerSample / 8);
}

string convertToText(void* data, int size) {
    string s((char*)data);
    return s.substr(0, size);
}

int readHeader(wave_hdr& waveHeader, const char* filename) {
    FILE* inFile = fopen(filename, "rb");
    if (!inFile) {
        cerr << "FILE NOT FOUND" << endl;
        fclose(inFile);
        return 0;
    }

    size_t bytesRead = fread((char*)&waveHeader, sizeof(wave_hdr), 1, inFile);
    if (bytesRead == 0) {
        cerr << "HEADER READ FAILED" << endl;
        fclose(inFile);
        return 0;
    }

    fclose(inFile);
    return 1;
}

int writeHeader(wave_hdr waveHeader, const char* filename) {
    FILE* wavFile = fopen(filename, "wb");
    if (!wavFile) {
        cerr << "CAN'T OPEN FILE" << endl;
        fclose(wavFile);
        return 0;
    }

    size_t bytesWritten = fwrite(&waveHeader, sizeof(wave_hdr), 1, wavFile);
    if (bytesWritten == 0) {
        cerr << "CAN'T WRITE HEADER" << endl;
        fclose(wavFile);
        return 0;
    }

    fclose(wavFile);
    return 1;
}

template <class T>
int readSamples(T** samples, wave_hdr waveHeader, const char* filename) {
    FILE* inFile = fopen(filename, "rb");
    if (!inFile) {
        cerr << "FILE NOT FOUND" << endl;
        fclose(inFile);
        return 0;
    }
    fseek(inFile, sizeof(wave_hdr), SEEK_SET);

    int NumSamples = getSamplesNo(waveHeader);
    *samples = new T[NumSamples]; 

    size_t bytesRead = fread(*samples, sizeof(**samples), NumSamples, inFile);
    if (bytesRead == 0) {
        cerr << "SAMPLES READ FAILED" << endl;
        delete[] *samples;
        fclose(inFile);
        return 0;
    }

    fclose(inFile);
    return NumSamples;
}

int readData(int16_t** samples, wave_hdr waveHeader, const char* filename) {
    switch (waveHeader.BitsPerSample) {
        case 16:
            return readSamples(samples, waveHeader, filename);
        case 8:
            uint8_t *data;
            int sampleNo = readSamples(&data, waveHeader, filename);
            *samples = new int16_t[sampleNo];
            for (int i = 0; i < sampleNo; i++)
                (*samples)[i] = data[i];
            delete[] data;
            return sampleNo;
    }
    return 0;
}

template <class T>
int writeSamples(T* data, int chunks, const char* filename) {
    FILE* wavFile = fopen(filename, "ab");
    if (!wavFile) {
        cerr << "CAN'T OPEN FILE" << endl;
        fclose(wavFile);
        return 0;
    }
    fseek(wavFile, sizeof(wave_hdr), SEEK_SET);
    
    size_t bytesWritten = fwrite(data, sizeof(*data), chunks, wavFile);
    if (bytesWritten == 0) {
        cerr << "CAN'T WRITE DATA" << endl;
        fclose(wavFile);
        return 0;
    }

    fclose(wavFile);
    return 1;
}

int writeData(int16_t* data, wave_hdr waveHeader, const char* filename) {
    int NumSamples = getSamplesNo(waveHeader);
    
    switch (waveHeader.BitsPerSample) {
        case 16:
            return writeSamples(data, NumSamples, filename);
        case 8:
            uint8_t *samples = new uint8_t[NumSamples];
            for (int i = 0; i < NumSamples; i++)
                samples[i] = (uint8_t)data[i];
            int code = writeSamples(samples, NumSamples, filename);
            delete[] samples;
            return code;
    }
    return 0;
}

template <class T>
float normalize(T sample) {
    int maxSampleValue = max(abs(numeric_limits<T>::min()),
                            abs(numeric_limits<T>::max()));
    return round((float)sample/maxSampleValue * 100000) / 100000;
}

wave_hdr createHeader(int samplingRate, int bitsPerSample, int channelsNo, int samplesNo) {
    int blockAlign = channelsNo * bitsPerSample / 8;
    int byteRate = samplingRate * blockAlign;
    int subchunk2Size = samplesNo * channelsNo * bitsPerSample / 8;
    int fileSize = sizeof(wave_hdr) + subchunk2Size; 

    return {
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
}

wave_hdr combineHeaders(wave_hdr wavHeader1, wave_hdr wavHeader2) {
    int samplesNo1 = getSamplesNo(wavHeader1);
    int samplesNo2 = getSamplesNo(wavHeader2);

    int samplesNo = max(samplesNo1, samplesNo2);
    int sampleRate = min(wavHeader1.SampleRate, wavHeader2.SampleRate);
    int bitsPerSample = max(wavHeader1.BitsPerSample, wavHeader2.BitsPerSample);
    int channelsNo = min(wavHeader1.NumChannels, wavHeader2.NumChannels);

    return createHeader(sampleRate, bitsPerSample, channelsNo, samplesNo);
}

int16_t* combineData(int16_t* samples1, int sampleNo1, int16_t* samples2, int sampleNo2) {
    int16_t* data;
    int maxSize = max(sampleNo1, sampleNo2);

    data = new int16_t[maxSize];
    for (int i = 0; i < maxSize; i++) 
        data[i] = 0;
    
    for (int i = 0; i < sampleNo1; i++) 
        data[i] += samples1[i];
    
    for (int i = 0; i < sampleNo2; i++)
        data[i] += samples2[i];
    
    delete[] samples1;
    delete[] samples2;
    return data;
}

double getNyquistFrequnecy(const wave_hdr waveHeader) {
    int f = waveHeader.SampleRate;
    int N = getSamplesNo(waveHeader);
    float tau = 1.0 / f;
    float t = tau * (N - 1);

    return N / (2 * t);
}

double getTotalTime(const wave_hdr waveHeader) {
    int f = waveHeader.SampleRate;
    int N = getSamplesNo(waveHeader);
    float tau = 1.0 / f;

    return tau * (N - 1);
}