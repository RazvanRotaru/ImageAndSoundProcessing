#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <utility>

#include "../utils/Visitor.h"
#include "../utils/DataContainer.h"
#include "../utils/Helper.h"

using namespace std;

class FrequencyContainer {
public:
    void computeFrequencies(DataContainer* dataContainer) {
        map<string, float> values = dataContainer->getValues();
        vector<string> types = dataContainer->getTypes();

        float sum = getArraySum(types, values);
        sum += 1;
        TERMINATOR = 1.0f / sum;

        for (string type : types) 
            values[type] /= sum;

        dataContainer->setValues(values);
        retrieveFrequencies(dataContainer);
        writeFrequencies(dataContainer->getFilename());
    }

    map<string, pair<float, float> > getFrequencies() {
        return freq;
    }

    void accept(Visitor<FrequencyContainer>* v) {
        v->visit(this);
    }

    string getTERMINATOR() {
        return "TERMINATOR";
    }

private:
    float TERMINATOR;
    map<string, pair<float, float> > freq;
    vector<string> types;

    void retrieveFrequencies(DataContainer* dataContainer) {
        map<string, float> values = dataContainer->getValues();
        vector<string> types = dataContainer->getTypes();
        
        float prevMargin = 0.0f;
        for (string type : types) {
            this->types.push_back(type);
            freq[type] = make_pair(prevMargin, prevMargin + values[type]);

            prevMargin += values[type];
        }
        freq["TERMINATOR"] = make_pair(1-TERMINATOR, 1);
    }

    void writeFrequencies(string filename) {
        size_t lastIndex = filename.find_last_of(".");
		string outFilename = filename.substr(0, lastIndex) + "_freq.csv";

        ofstream outputFile;
        outputFile.open(outFilename);
        
        outputFile << "Simbol,Frecventa,Interval de probabilitate" << endl;
		for (string type : types)
            outputFile << type << "," << freq[type].second - freq[type].first 
                            << "," << freq[type].first << "-" << freq[type].second << endl;

        outputFile << "TERMINATOR" << "," << TERMINATOR << "," << 1-TERMINATOR << "-1" << endl;
        outputFile.close();
    }
};