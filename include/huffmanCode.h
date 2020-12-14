#ifndef ENCODE_H
#define ENCODE_H
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

class huffmanCode {
protected:
    std::vector<int> container;
    std::vector<double> probabilities;
    std::vector<double> probabilitiesTmp;
    std::vector<std::vector<int>> matrixCode;
    std::string filePath;

    void QuickSort(int L, size_t R);
    int Up(int n, double q);
    void Down(int n, int j);
    void Huffman(int n);

public:
    int GetFileByPath(const std::string& path);
    ~huffmanCode();
    void Encode();
    void ShowTable();
    void WriteInFile();
};

#endif
