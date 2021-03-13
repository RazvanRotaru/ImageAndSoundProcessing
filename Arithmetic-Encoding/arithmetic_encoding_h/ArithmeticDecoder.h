#pragma once

#include <map>
#include <vector>
#include <string>

#include "FrequencyContainer.h"

using namespace std;

class ArithmeticDecoder : public Visitor<FrequencyContainer> {
public:

    ArithmeticDecoder(float code) {
        this->code = code;
    }

    void visit(FrequencyContainer* dataContainer) {
        map<string, pair<float, float> > freq = dataContainer->getFrequencies();
        string currSymbol = "";

        float frequency = code;
        while (true) {
            currSymbol = getSymbolByFrequency(frequency, dataContainer);
            if (currSymbol.compare(dataContainer->getTERMINATOR()) == 0)
                break;
                
            symbols.push_back(currSymbol);

            float range = freq[currSymbol].second - freq[currSymbol].first;
            frequency = (frequency - freq[currSymbol].first) / range;
        }
    }

    void printSymbols() {
        cout << "The decoded symbols are: ";

        int size = symbols.size();
        for (int i = 0; i < size; i++) {
            cout << symbols[i];
            if (i != size - 1)
                cout << ", ";
        }
        cout << endl;
    }

private:
    float code;
    vector<string> symbols;

    string getSymbolByFrequency(float frequency, FrequencyContainer* dataContainer) {
        map<string, pair<float, float> > freq = dataContainer->getFrequencies();

        for (map<string, pair<float, float> >::const_iterator it = freq.begin(); 
			    it != freq.end(); it++) {
            if (frequency >= it->second.first && frequency <= it->second.second)
                return it->first;
        }

        return "";
    }
};