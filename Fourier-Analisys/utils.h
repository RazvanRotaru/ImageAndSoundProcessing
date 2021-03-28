#pragma once

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string removeExtension(const char* filename) {
    string fullname(filename);
    size_t lastindex = fullname.find_last_of("."); 
    return fullname.substr(0, lastindex); 
}

template <class T>
const char* compare(T x, T y, const char *unit) {
    char *line;
    float difference = abs(x - y);
    float percent = difference * 100 / y;
    sprintf(line, "\t- %.2f%s\t- error of %.2f%% (difference %.2f%s)", x, unit, percent, difference, unit);

    return line;
}