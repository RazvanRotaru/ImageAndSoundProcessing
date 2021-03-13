#pragma once

#include <map>
#include <vector>
#include <string>

#include "FrequencyContainer.h"

using namespace std;

class ArithmeticEncoder : public Visitor<FrequencyContainer> {
public:

    ArithmeticEncoder(string s, char delim) {
        stringstream ss(s.c_str());
        string symbol;

        while (getline(ss, symbol, delim))
            symbols.push_back(symbol);
    }

    void visit(FrequencyContainer* dataContainer) {
        float low = 0.0f;
        float high = 1.0f;

        symbols.push_back(dataContainer->getTERMINATOR());
        map<string, pair<float, float> > freq = dataContainer->getFrequencies();

        int size = symbols.size();
        for (int i = 0; i < size; i++) {
            float range = high - low;
            high = low + range * freq[symbols[i]].second;
            low = low + range * freq[symbols[i]].first;
        }

        code = (high + low) / 2;
    }

    float getCode() {
        return code;
    }

    void printCode() {
        cout << "The encoded code is: " << code << endl;
    }

private:
    float code;
    vector<string> symbols;
};