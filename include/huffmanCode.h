#ifndef ENCODE_H
#define ENCODE_H
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>

class huffmanCode {
protected:
    std::vector<int> container;
    std::vector<double> probabilities;
    std::vector<double> probabilitiesTmp;
    std::vector<std::vector<int>> matrixCode;

    void QuickSort(int L, size_t R);
    int Up(int n, double q);
    void Down(int n, int j);
    void Huffman(int n);

public:
    int GetFileByPath(const std::string& path);
    ~huffmanCode();
    void Encode();
    void ShowTable();
};

#endif
