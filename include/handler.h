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
    inhabitedLocality records[4000] = {0};
    inhabitedLocality* indexRecords[4000] = {nullptr};

public:
    handle();
    void show();
};