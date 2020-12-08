#include "handler.h"
#include <iostream>
#include <limits>
#define ESC "\033"

using namespace std;

void SelectionMenu()
{
    handle body;
    int choose = -1;
    while (true) {
        printf(ESC "c");
        cout << "1. Load into memory\n";
        cout << "2. Display database\n";
        cout << "3. Sort data\n";
        cout << "4. Quick search by key in list\n";
        cout << "5. Display the contents of the queue on the screen\n";
        cout << "6. Build a search tree by key\n";
        cout << "7. Display the contents of the tree\n";
        cout << "8. Quick search by key in tree\n";
        cout << "9. Encode by Huffman code\n";
        cout << "For exit write \"-1\"\n";
        cout << "Choose: ";
        cin >> choose;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choose) {
        case 1: {
            printf(ESC "c");
            cout << "The database has been loaded into memory.\n";

            break;
        }
        case 2: {
            printf(ESC "c");
            body.ShowDB();
            break;
        }
        case 3: {
            printf(ESC "c");
            cout << "Now database been sorted.\n";
            body.HeapSort();
            break;
        }
        case 4: {
            printf(ESC "c");
            body.DeleteList();
            cout << "Write the search key 3 symbols(Full name): ";
            char key[255];
            cin >> key;
            body.FindKey(key);
            getchar();
            break;
        }
        case 5: {
            printf(ESC "c");
            body.PrintList();
            break;
        }
        case 6: {
            printf(ESC "c");
            body.DeleteTree();
            cout << "The tree was built.\n";
            body.MoveToTree();
            break;
        }
        case 7: {
            printf(ESC "c");
            cout << "Tree: \n";
            body.LeftToRight(body.ReturnVertexRoot());
            break;
        }
        case 8: {
            printf(ESC "c");
            cout << "Write the search key(date): ";
            char key[255];
            cin >> key;
            body.FindKeyTree(key);
            getchar();
            break;
        }
        case 9: {
            printf(ESC "c");
            huffmanCode huffman;
            string path;
            cout << "Write the file path\n>";
            cin >> path;
            huffman.GetFileByPath(path);
            huffman.Encode();
            huffman.ShowTable();
            getchar();
            break;
        }
        }
        std::cout << "Press key to continue...\n";
        getchar();
        if (choose == -1) {
            break;
        }
    }
}