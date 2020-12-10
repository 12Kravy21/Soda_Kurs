#include "handler.h"
#include <cstring>
#include <iostream>
#define ESC "\033"

handle::handle()
{
    indexRecords = new inhabitedLocality*[4000];
}

int handle::GetDataBase()
{
    FILE* file;
    file = fopen("testBase4.dat", "rb");
    if (file != nullptr) {
        fread((inhabitedLocality*)records,
              sizeof(inhabitedLocality),
              4000,
              file);
        for (int i = 0; i < 4000; i++) {
            indexRecords[i] = &records[i];
        }
        return 1;
    } else {
        return 0;
    }
}

void handle::ShowDB()
{
    using namespace std;
    int multiplier = 1;
    do {
        printf(ESC "c");
        cout << "Hello, dear User, enter from 1 to 200 to view pages\n"
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
        cout << "Full Name";
        std::cout.width(40);
        cout << "Street";
        std::cout.width(17);
        cout << "House";
        std::cout.width(12);
        cout << "Apartment";
        std::cout.width(20);
        cout << "Date\n";
        for (int i = 20 * (multiplier - 1); i < multiplier * 20; i++) {
            std::cout << i + 1 << "." << handle::indexRecords[i]->fullName
                      << " ";
            std::cout.width(22);
            std::cout << handle::indexRecords[i]->streetName << " ";
            std::cout.width(6);
            std::cout << handle::indexRecords[i]->house << " ";
            std::cout.width(10);
            std::cout << handle::indexRecords[i]->apartment << " ";
            std::cout.width(22);
            std::cout << handle::indexRecords[i]->date << std::endl;
        }
        cout << "This page is >" << multiplier << "<\n";
        cout << "Write \"next\" for next page\n";
        cout << "Write \"prev\" for prev page\n";
        cout << "Or \"0\" for free choose\n";
        cout << ">";
        string chous;
        cin >> chous;
        if (chous == "0") {
            cout << "Number page: ";
            int tmpMlp = multiplier;
            cin >> multiplier;
            if (!(((multiplier <= 200) && (multiplier >= 1))
                  || (multiplier == -1))) {
                multiplier = tmpMlp;
            }
        }
        if (chous == "next" && multiplier < 200) {
            multiplier++;
        }
        if (chous == "prev" && multiplier > 1) {
            multiplier--;
        }
        if (chous == "-1") {
            multiplier = -1;
        }
    }
}

void handle::heapify(inhabitedLocality** arr, int n, int i)
{
    int head = i;
    inhabitedLocality* buff;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && strcmp(arr[l]->fullName, arr[head]->fullName) == 0) {
        if (strcmp(arr[l]->streetName, arr[head]->streetName) > 0) {
            head = l;
        }
    } else {
        if (l < n && strcmp(arr[l]->fullName, arr[head]->fullName) > 0) {
            head = l;
        }
    }

    if (r < n && strcmp(arr[r]->fullName, arr[head]->fullName) == 0) {
        if (strcmp(arr[r]->streetName, arr[head]->streetName) > 0) {
            head = r;
        }
    } else {
        if (r < n && strcmp(arr[r]->fullName, arr[head]->fullName) > 0) {
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

void handle::FindKey(char key[])
{
    int L = 0, R = 3999, sero;
    while (L < R) {
        sero = (L + R) / 2;
        if (strncmp(indexRecords[sero]->fullName, key, 3) < 0) {
            L = sero + 1;
        } else {
            R = sero;
        }
    }
    if (strncmp(indexRecords[R]->fullName, key, 3) == 0) {
        firtsIndex = R;
        while (strncmp(indexRecords[R]->fullName, key, 3) == 0 && R < 4000) {
            AddToList(indexRecords[R]);
            R++;
        }
    } else {
        std::cout << "Not found!";
    }
}

// list function

void handle::AddToList(inhabitedLocality* locality)
{
    if (handle::root != nullptr) {
        handle::list* head = handle::root;
        while (head->next) {
            head = head->next;
        }
        head->next = new handle::list;
        head = head->next;
        head->data = locality;
    } else {
        handle::root = new handle::list;
        handle::root->data = locality;
    }
}

void handle::PrintList()
{
    using namespace std;
    handle::list* head = handle::root;
    int i = 1;
    while (head) {
        std::cout.width(4);
        std::cout << firtsIndex + i << " ";
        std::cout << head->data->fullName << " ";
        std::cout.width(22);
        std::cout << head->data->streetName << " ";
        std::cout.width(6);
        std::cout << head->data->house << " ";
        std::cout.width(10);
        std::cout << head->data->apartment << " ";
        std::cout.width(22);
        std::cout << head->data->date << std::endl;
        head = head->next;
        i++;
    }
}

void handle::DeleteList()
{
    list* head = handle::root;
    list* p = head;
    while (p != nullptr) {
        head = p->next;
        delete p;
        p = head;
    }
    root = nullptr;
}

// AVL

void handle::MoveToTree()
{
    handle::list* head = handle::root;
    while (head) {
        AddToAVL(head->data);
        head = head->next;
    }
}

char* TrueDate(char date[10])
{
    char* dateRev = new char[10];
    dateRev[0] = date[6];
    dateRev[1] = date[7];
    dateRev[2] = date[3];
    dateRev[3] = date[4];
    dateRev[4] = date[0];
    dateRev[5] = date[1];
    return dateRev;
}

void handle::LeftLeftRotation(vertex** head)
{
    handle::vertex* q = (*head)->left;
    q->balance = 0;
    (*head)->balance = 0;
    (*head)->left = q->right;
    q->right = *head;
    *head = q;
    handle::increase = false;
}

void handle::LeftRightRotation(vertex** head)
{
    handle::vertex* q = (*head)->left;
    handle::vertex* r = q->right;
    if (r->balance < 0) {
        (*head)->balance = 1; //+=1
    } else {
        (*head)->balance = 0;
    }
    if (r->balance > 0) {
        q->balance = -1; //-=1
    } else {
        q->balance = 0;
    }
    r->balance = 0;
    (*head)->left = r->right;
    q->right = r->left;
    r->left = q;
    r->right = (*head);
    (*head) = r;
    handle::increase = false;
}

void handle::RightRightRotation(vertex** head)
{
    handle::vertex* q = (*head)->right;
    q->balance = 0;
    (*head)->balance = 0;
    (*head)->right = q->left;
    q->left = (*head);
    (*head) = q;
    handle::increase = false;
}

void handle::RightLeftRotation(vertex** head)
{
    handle::vertex* q = (*head)->right;
    handle::vertex* r = q->left;
    if (r->balance > 0)
        (*head)->balance = -1;
    else
        (*head)->balance = 0;
    if (r->balance < 0)
        q->balance = 1;
    else
        q->balance = 0;
    r->balance = 0;
    (*head)->right = r->left;
    q->left = r->right;
    r->left = (*head);
    r->right = q;
    (*head) = r;
    handle::increase = false;
}

void handle::AVLTree(vertex** head, inhabitedLocality* key)
{
    char* trueDateDB = nullptr;
    char* trueDateKey = TrueDate(key->date);
    if (*head != nullptr) {
        trueDateDB = TrueDate((*head)->data->date);
    }
    if (*head == nullptr) {
        (*head) = new handle::vertex;
        (*head)->data = key;
        handle::increase = true;
    } else if (strcmp(trueDateDB, trueDateKey) > 0) {
        AVLTree(&((*head)->left), key);
        if (handle::increase == true) {
            if ((*head)->balance > 0) {
                (*head)->balance = 0;
                handle::increase = false;
            } else if ((*head)->balance == 0) {
                (*head)->balance = -1;
                handle::increase = true;
            } else if ((*head)->left->balance < 0) {
                LeftLeftRotation(head);
            } else {
                LeftRightRotation(head);
            }
        }
    } else if (strcmp(trueDateDB, trueDateKey) < 0) {
        AVLTree(&((*head)->right), key);
        if (handle::increase == true) {
            if ((*head)->balance < 0) {
                (*head)->balance = 0;
                handle::increase = false;
            } else if ((*head)->balance == 0) {
                (*head)->balance = 1;
                handle::increase = true;
            } else if ((*head)->right->balance > 0) {
                RightRightRotation(head);
            } else {
                RightLeftRotation(head);
            }
        }
    } else {
        handle::vertex* tmp = (*head);
        char* trueDateTmp = TrueDate((tmp->data)->date);
        if (strcmp(trueDateTmp, trueDateKey) == 0) {
            if (tmp->equal == nullptr) {
                tmp->equal = new handle::vertex;
                (tmp->equal)->data = key;
            } else {
                while (tmp->equal != nullptr) {
                    tmp = tmp->equal;
                }
                tmp->equal = new handle::vertex;
                (tmp->equal)->data = key;
            }
        }
        handle::increase = false;
        delete[] trueDateTmp;
    }
    delete[] trueDateDB;
    delete[] trueDateKey;
}

void handle::LeftToRight(vertex* head)
{
    if (head) {
        LeftToRight(head->left);
        std::cout << head->data->fullName << " ";
        std::cout.width(22);
        std::cout << head->data->streetName << " ";
        std::cout.width(6);
        std::cout << head->data->house << " ";
        std::cout.width(10);
        std::cout << head->data->apartment << " ";
        std::cout.width(22);
        std::cout << head->data->date << std::endl;
        handle::vertex* p = head;
        while (p->equal != nullptr) {
            p = p->equal;
            std::cout << p->data->fullName << " ";
            std::cout.width(22);
            std::cout << p->data->streetName << " ";
            std::cout.width(6);
            std::cout << p->data->house << " ";
            std::cout.width(10);
            std::cout << p->data->apartment << " ";
            std::cout.width(22);
            std::cout << p->data->date << std::endl;
        }
        LeftToRight(head->right);
    }
}

void handle::AddToAVL(inhabitedLocality* key)
{
    handle::vertex** head = &(handle::vertexRoot);
    AVLTree(head, key);
}

handle::vertex* handle::ReturnVertexRoot()
{
    return vertexRoot;
}

void handle::FindKeyTree(char key[])
{
    handle::vertex* head = handle::vertexRoot;
    char* trueDateDB;
    char* trueDateKey = TrueDate(key);
    while (head) {
        trueDateDB = TrueDate(head->data->date);
        if (strncmp(trueDateDB, trueDateKey, 8) < 0) {
            head = head->right;
        } else if (strncmp(trueDateDB, trueDateKey, 8) > 0) {
            head = head->left;
        } else if (strncmp(trueDateDB, trueDateKey, 8) == 0) {
            delete[] trueDateDB;
            break;
        }
        delete[] trueDateDB;
    }
    if (head) {
        std::cout << "Key been found.\n\n";
        std::cout << head->data->fullName << " ";
        std::cout.width(22);
        std::cout << head->data->streetName << " ";
        std::cout.width(6);
        std::cout << head->data->house << " ";
        std::cout.width(10);
        std::cout << head->data->apartment << " ";
        std::cout.width(22);
        std::cout << head->data->date << std::endl;
        handle::vertex* p = head;
        while (p->equal != nullptr) {
            p = p->equal;
            std::cout << p->data->fullName << " ";
            std::cout.width(22);
            std::cout << p->data->streetName << " ";
            std::cout.width(6);
            std::cout << p->data->house << " ";
            std::cout.width(10);
            std::cout << p->data->apartment << " ";
            std::cout.width(22);
            std::cout << p->data->date << std::endl;
        }
    } else {
        std::cout << "Key not found.\n";
    }
    delete[] trueDateKey;
}

void handle::DestroyRecursive(vertex*& leaf)
{
    if (leaf) {
        DestroyRecursive(leaf->equal);
        DestroyRecursive(leaf->left);
        DestroyRecursive(leaf->right);
        delete *&leaf;
    }
}

void handle::DeleteTree()
{
    DestroyRecursive(handle::vertexRoot);
    vertexRoot = nullptr;
}
handle::~handle()
{
    DeleteList();
    DeleteTree();
    delete[] indexRecords;
}
