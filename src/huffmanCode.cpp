#include "huffmanCode.h"

int huffmanCode::GetFileByPath(const std::string& path)
{
    std::ifstream file(path, std::ios_base::binary);
    if (file.is_open()) {
        if (file.good()) {
            probabilities.clear();
            container.clear();
            char symbol;
            while (file.get(symbol)) {
                {
                    int flag = 0;
                    for (unsigned long i = 0; i < container.size(); ++i) {
                        if ((int)(unsigned char)symbol == container[i]) {
                            probabilities[i] += 1;
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag) {
                        container.push_back((int)(unsigned char)symbol);
                        probabilities.push_back(1);
                    }
                }
            }
            double sumOfProbabilities = 0;
            for (double& probability : probabilities) {
                sumOfProbabilities += probability;
            }
            for (double& probability : probabilities) {
                probability /= sumOfProbabilities;
            }
            filePath = path;
            return 1;
        }
    }
    std::cout << "Could not open file\n";
    return 0;
}

void huffmanCode::QuickSort(int L, size_t R)
{
    int i = L;
    int j = R;
    double temp = probabilities[(i + j) / 2];

    while (i <= j) {
        while (probabilities[i] > temp) {
            i++;
        }
        while (probabilities[j] < temp) {
            j--;
        }
        if (i <= j) {
            std::swap(probabilities[i], probabilities[j]);
            std::swap(container[i], container[j]);
            i++;
            j--;
        }
    }
    if (L < j) {
        QuickSort(L, j);
    }
    if (i < (int)R) {
        QuickSort(i, R);
    }
}

huffmanCode::~huffmanCode()
{
    probabilities.clear();
    probabilitiesTmp.clear();
    container.clear();
    matrixCode.clear();
}

int huffmanCode::Up(int n, double q)
{
    int j;
    for (int i = n - 1; i >= 0; i--) {
        if (i > 0 && probabilitiesTmp[i - 1] < q) {
            probabilitiesTmp[i] = probabilitiesTmp[i - 1];
            j = i;
        } else {
            j = i;
            break;
        }
    }
    probabilitiesTmp[j] = q;
    return j;
}

void huffmanCode::Down(int n, int j)
{
    std::vector<int> s(matrixCode[j].size());
    s = matrixCode[j];
    for (int i = j; i < n - 1; i++) {
        matrixCode[i] = matrixCode[i + 1];
    }
    matrixCode[n - 1] = s;
    matrixCode[n] = s;
    matrixCode[n - 1].push_back(0);
    matrixCode[n].push_back(1);
}

void huffmanCode::Huffman(int n)
{
    double q;
    int j;
    if (n == 1) {
        matrixCode[0].push_back(0);
        matrixCode[1].push_back(1);
    } else {
        q = probabilitiesTmp[n - 1] + probabilitiesTmp[n];
        j = Up(n, q);
        Huffman(n - 1);
        Down(n, j);
    }
}

void huffmanCode::Encode()
{
    if (!probabilities.empty()) {
        matrixCode.resize(probabilities.size());
        QuickSort(0, probabilities.size() - 1);
        for (double& probability : probabilities) {
            probabilitiesTmp.push_back(probability);
        }
        Huffman(probabilities.size() - 1);
    }
}

void huffmanCode::ShowTable()
{
    using namespace std;
    if (!probabilities.empty()) {
        int widthProp = 0;
        for (double probability : probabilities) {
            if (widthProp < (int)to_string(probability).length()) {
                widthProp = to_string(probability).length();
            }
        }
        for (unsigned long i = 0; i < probabilities.size(); ++i) {
            cout << setw(3) << container[i] << "|";
            cout << setw(widthProp) << to_string(probabilities[i]) + "|";
            cout << setw(3) << to_string(matrixCode[i].size()) << "|";
            for (unsigned long j = 0; j < matrixCode[i].size(); ++j) {
                cout << matrixCode[i][j];
            }
            cout << "\n";
        }
        double avrLen = 0;
        double entropy = 0;
        for (unsigned long i = 0; i < matrixCode.size(); ++i) {
            avrLen += matrixCode[i].size() * probabilities[i];
            entropy -= probabilities[i] * log2(probabilities[i]);
        }
        cout << "Entropy: " << entropy << endl;
        cout << "Average length: " << avrLen << endl;
    }
}
void huffmanCode::WriteInFile()
{
    std::ifstream input(filePath, std::ios::in | std::ios::binary);
    if (input.is_open()) {
        if (input.good()) {
            int countByte = 0;
            int countNewByte = 0;
            int countBit = 0;
            int thisByte = 0;
            char symbol;
            std::ofstream outputBase(
                    "./encodedBase.dat", std::ios::out | std::ios::binary);
            while (input.get(symbol)) {
                countByte++;
                auto bytePos = std::find(
                        container.begin(),
                        container.end(),
                        ((int)(unsigned char)symbol));
                for (unsigned long j = 0,
                                   thisElement
                     = std::distance(container.begin(), bytePos);
                     j < matrixCode[thisElement].size();
                     ++j) {
                    if (countBit == 8) {
                        countNewByte++;
                        int value = 0;
                        int i = 0;
                        while (thisByte != 0) {
                            i++;
                            value += thisByte % 10 * (int)pow(2, i);
                            thisByte /= 10;
                        }
                        outputBase << (char)value;
                        countBit = 0;
                    }
                    ++countBit;
                    thisByte *= 10;
                    thisByte += matrixCode[thisElement][j];
                }
            }
            if (countBit > 0) {
                countNewByte++;
                int value = 0;
                int i = 0;
                while (thisByte != 0) {
                    i++;
                    value += thisByte % 10 * (int)pow(2, i);
                    thisByte /= 10;
                }
                outputBase << (char)value;
                countBit = 0;
            }
            outputBase.close();
            std::ofstream outputTable("./encodeTable.txt", std::ios::out);
            for (size_t i = 0; i < container.size(); ++i) {
                outputTable << container[i] << "\t";
                for (unsigned long j = 0; j < matrixCode[i].size(); ++j) {
                    outputTable << matrixCode[i][j];
                }
                outputTable << "\n";
            }
            std::cout << "Data compression ratio: "
                      << (double)(countNewByte) / (countByte)*100 << "%\n";
        }
    }
}