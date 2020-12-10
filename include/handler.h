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

    // queue

    struct list {
        handle::inhabitedLocality* data = nullptr;
        struct list* next = nullptr;
    };
    list* root = nullptr;
    int firtsIndex;

    // AVL tree

    struct vertex {
        handle::inhabitedLocality* data = nullptr;
        struct vertex* left = nullptr;
        struct vertex* right = nullptr;
        struct vertex* equal = nullptr;
        int balance = 0;
    };
    vertex* vertexRoot = nullptr;
    int increase = true;

public:
    ~handle();
    handle();
    int GetDataBase();
    void ShowDB();
    void heapify(inhabitedLocality** arr, int n, int i);
    void HeapSort();
    void FindKey(char key[]);

    // list function

    void AddToList(inhabitedLocality* locality);
    void PrintList();
    void DeleteList();

    // AVL function

    void MoveToTree();
    void LeftLeftRotation(vertex** head);
    void LeftRightRotation(vertex** head);
    void RightRightRotation(vertex** head);
    void RightLeftRotation(vertex** head);
    void AVLTree(vertex** head, inhabitedLocality* key);
    void LeftToRight(vertex* head);
    void AddToAVL(inhabitedLocality* key);
    vertex* ReturnVertexRoot();
    void FindKeyTree(char key[]);
    void DestroyRecursive(vertex*& leaf);
    void DeleteTree();
};