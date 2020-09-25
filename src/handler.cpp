#include "handler.h"
#include <iostream>
#define ESC "\033"

handle::handle()
{
    FILE* file;
    file = fopen("testBase4.dat", "rb");
    fread((inhabitedLocality*)records, sizeof(inhabitedLocality), 4000, file);
    for (int i = 0; i < 4000; i++) {
        indexRecords[i] = &records[i];
    }
}

void handle::show()
{
    using namespace std;
    int multiplier = 1;
    do {
        printf(ESC "c");
        cout << "Hello, dear User, enter from 1 to 20 to view pages\n"
             << "To exit view write '-1'\n";
        cout << "Number page: ";
        cin >> multiplier;
    } while (!(
            ((multiplier <= 200) && (multiplier >= 1)) || (multiplier == -1)));
    while (true) {
        printf(ESC "c");
        if (multiplier == -1) {
            break;
        }
        for (int i = 20 * (multiplier - 1); i < multiplier * 20; i++) {
            cout << handle::indexRecords[i]->fullName << endl
                 << handle::indexRecords[i]->streetName << endl
                 << handle::indexRecords[i]->house << endl
                 << handle::indexRecords[i]->apartment << endl
                 << handle::indexRecords[i]->date << endl
                 << endl;
        }
        do {
            cout << "Number page: ";
            cin >> multiplier;
        } while (
                !(((multiplier <= 200) && (multiplier >= 1))
                  || (multiplier == -1)));
    }
}