#include "handler.h"
#include <iostream>
#define ESC "\033"

using namespace std;

void SelectionMenu()
{
    handle body;
    char key[255];
    body.ShowDB();
    printf(ESC "c");
    cout << "Press any key to continue...\n";
    getchar();
    getchar();
    body.HeapSort();
    printf(ESC "c");
    cout << "Now database been sorted.\n";
    cout << "Press any key to continue...\n";
    getchar();
    body.ShowDB();
    cout << "Write the search key 3 symbols: ";
    cin >> key;
    body.FindKey(key);
    body.PrintList();
    cout << "Press any key to continue...\n";
    getchar();
    getchar();
    printf(ESC "c");
    body.MoveToTree();
    cout << "Tree: \n";
    body.LeftToRight(body.ReturnVertexRoot());
    cout << "Press any key to continue...\n";
    getchar();
    printf(ESC "c");
    cout << "Write the search key 3 symbols: ";
    cin >> key;
    body.FindKeyTree(key);
    getchar();
    getchar();
}