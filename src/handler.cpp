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

void handle::ShowDB()
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
            std::cout << handle::indexRecords[i]->fullName << " ";
            std::cout.width(22);
            std::cout << handle::indexRecords[i]->streetName << " ";
            std::cout.width(6);
            std::cout << handle::indexRecords[i]->house << " ";
            std::cout.width(10);
            std::cout << handle::indexRecords[i]->apartment << " ";
            std::cout.width(22);
            std::cout << handle::indexRecords[i]->date << std::endl;
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
    int L = 0, R = 3999, sero = 0;
    while (L < R) {
        sero = (L + R) / 2;
        if (strncmp(indexRecords[sero]->fullName, key, 3) < 0) {
            L = sero + 1;
        } else {
            R = sero;
        }
    }
    if (strncmp(indexRecords[R]->fullName, key, 3) == 0) {
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
    while (head) {
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
    }
}

void handle::MoveToTree()
{
    handle::list* head = handle::root;
    while (head) {
        AddToAVL(head->data);
        head = head->next;
    }
}

// void DeleteList(struct List** head)
// {
// struct List* p = *head;
// while (p != NULL) {
// *head = p->next;
// free(p);
// p = *head;
// }
// }

// AVL

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
    if (*head == nullptr) {
        (*head) = new handle::vertex;
        (*head)->data = key;
        handle::increase = true;
    } else if (strcmp((*head)->data->date, key->date) > 0) {
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
    } else if (strcmp((*head)->data->date, key->date) < 0) {
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
        if (strcmp((*head)->data->date, key->date) == 0) {
            /*
                here equal keys been added into pointer by named "vertex* equal"
            */
        }
    }
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
        handle::vertex* p = head->equal;
        while (p) {
            std::cout << p->data->fullName << " ";
            std::cout.width(22);
            std::cout << p->data->streetName << " ";
            std::cout.width(6);
            std::cout << p->data->house << " ";
            std::cout.width(10);
            std::cout << p->data->apartment << " ";
            std::cout.width(22);
            std::cout << p->data->date << std::endl;
            p = p->equal;
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