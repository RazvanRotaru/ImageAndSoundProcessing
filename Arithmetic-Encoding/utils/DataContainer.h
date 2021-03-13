#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <map>
#include <vector>
#include <utility> 

#include "Visitor.h"

using namespace std;

class DataContainer {
public:
	DataContainer(string filename) {
		this->filename = filename;

		openFiles();
		readFile();
	}

	~DataContainer()
	{
		inputFile.close();
		outputFile.close();
	}

	map<string, float> getValues() {
		return value;
	}

	void setValues(map<string, float> values) {
		value = values;
	}

	vector<string> getTypes() {
		return types;
	}

	string getFilename() {
		return filename;
	}

    void accept(Visitor<DataContainer>* v) {
        v->visit(this);
    }

    void writeOutput(map<string, string> codes) {
		outputFile << "Simbol,Frecventa,Cod" << endl;
		for (string type: types)
			outputFile << type << "," << value[type] << "," << codes[type] << endl;
	}

    void printResult(map<string, string> codes) {
		int ans = 0;

		for (string type : types)
			ans += value[type] * codes[type].length();
		
		cout << ans << " bits needed to encode the file" << endl;
	}

private:
	string filename;

	ifstream inputFile;
	ofstream outputFile;

	map<string, float> value;
	vector<string> types;

	void readFile() {
		string inType, line;
		int inVal;
		
		inputFile >> line;
		while (inputFile >> line) {
			stringstream  ss(line);
			string field;
			inType = "";

			while (getline(ss, field, ',')) {
				if(ss.peek() == ',') 
					ss.ignore();

				if (inType == "")
					inType = field;
				else
					inVal = stoi(field);
			}
			value[inType] = inVal;
			types.push_back(inType);
		}
	}

	void openFiles() {
		inputFile.open(filename);

		size_t lastIndex = filename.find_last_of(".");
		string outFilename = filename.substr(0, lastIndex) + "_out.csv";
		outputFile.open(outFilename);
	}
};