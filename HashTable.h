//
// Created by alviz on 12.09.2020.
//

#ifndef PRAKTIKA1_HASHTABLE_H
#define PRAKTIKA1_HASHTABLE_H

#include<iostream>
#include <cstring>
using namespace std;

class HashTable {
private:
    static const int _default_size = 15;
    const double _rehash_size = 0.75;
    int _size;
    int _buffer_size;
    int kollisions = 0;
    struct Node
    {
        char key[50];
        char value[50];
        bool isfree;
    };
    Node* _arr;
public:
    HashTable();
    bool insert(char key[50], char value[50]);
    void resize();
    void rehash();
    long long hashfunc(char key[50]);
    int getbuffer_size() { return _buffer_size; }
    string getKey(int i){ return _arr[i].key; }
    string getValue(int i){ return _arr[i].value; }
    friend ostream& operator<< (ostream& os, HashTable& H);
    long long find(char key[50]);
    void Delete(char key[50]);
    int getKollisions() const;
    ~HashTable();
};



#endif //PRAKTIKA1_HASHTABLE_H
