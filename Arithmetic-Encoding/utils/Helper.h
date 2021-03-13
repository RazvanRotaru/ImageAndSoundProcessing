#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void printMatrix(std::vector < std::vector<bool> > mat) {
    int rows = mat.size();

    for (int i = 0; i < rows; i++) {
        int cols = mat[i].size();

        for (int j = 0; j < cols; j++)
            std::cout << mat[i][j] << " ";
        std::cout << std::endl;
    }
}

float getArraySum(std::vector<std::string> array, std::map<std::string, float> value)	{
    float arrSum = 0;

    for (string type : array)
        arrSum += value[type];
    return arrSum;
}

float getMaxSum(std::vector < std::vector<bool> > mat) {
    int typesNo = mat.size();
    int desiredSum = mat[0].size();
    float maxSum = 0;

    for (int j = desiredSum; j > 0; j--)
        if (mat[typesNo-1][j]) {
            maxSum = j;
            break;
        }

    return maxSum;
}

std::vector<std::string> getDifference(std::vector<std::string> v1, std::vector<std::string> v2) {
    int sz1 = v1.size();
    int sz2 = v2.size();
    for (int i = 0; i < sz2; i++)
        for (int j = 0; j < sz1; j++)
            if (v2[i] == v1[j]) {
                v1.erase(v1.begin() + j);
                break;
            }

    return v1;
}