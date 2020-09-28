#include "handler.h"
#include <iostream>
#include <string.h>
#define ESC "\033"

handle::handle()
{
    indexRecords = new inhabitedLocality*[4000];
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

void handle::heapify(inhabitedLocality** arr, int n, int i)
{
    int head = i;
    inhabitedLocality* buff;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && strcmp(arr[l]->streetName, arr[head]->streetName) == 0) {
        if (strcmp(arr[l]->fullName, arr[head]->fullName) > 0) {
            head = l;
        }
    } else {
        if (l < n && strcmp(arr[l]->streetName, arr[head]->streetName) > 0) {
            head = l;
        }
    }

    if (r < n && strcmp(arr[r]->streetName, arr[head]->streetName) == 0) {
        if (strcmp(arr[r]->fullName, arr[head]->fullName) > 0) {
            head = r;
        }
    } else {
        if (r < n && strcmp(arr[r]->streetName, arr[head]->streetName) > 0) {
            head = r;
        }
    }

    if (head != i) {
        buff = arr[i];
        arr[i] = arr[head];
        arr[head] = buff;

        heapify(arr, n, head);
    }
}

void handle::HeapSort()
{
    int n = 4000;
    inhabitedLocality* buff;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(handle::indexRecords, n, i);

    for (int i = n - 1; i >= 0; i--) {
        buff = indexRecords[0];
        indexRecords[0] = indexRecords[i];
        indexRecords[i] = buff;

        heapify(handle::indexRecords, i, 0);
    }
}