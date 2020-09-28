#pragma once
#include <fstream>

class handle {
private:
    typedef struct {
        char fullName[32] = "\0";
        char streetName[18] = "\0";
        short int house = 0;
        short int apartment = 0;
        char date[10] = "\0";
    } inhabitedLocality;
    inhabitedLocality records[4000];
    inhabitedLocality** indexRecords;

    struct list {
        handle::inhabitedLocality* data = nullptr;
        struct list* next = nullptr;
    };

    list* root = nullptr;

public:
    handle();
    void ShowDB();
    void heapify(inhabitedLocality** arr, int n, int i);
    void HeapSort();
    void FindKey(char key[]);

    // list function

    void AddToList(inhabitedLocality* locality);
    void PrintList();
};