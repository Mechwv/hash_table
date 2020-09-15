//
// Created by alviz on 12.09.2020.
//

#ifndef PRAKTIKA1_HASHTABLE_H
#define PRAKTIKA1_HASHTABLE_H

#include<iostream>
using namespace std;

class HashTable {
private:
    static const int _default_size = 1000;
    const double _rehash_size = 0.75;
    int _size;
    int _buffer_size;
    int kollisions = 0;
    struct Node
    {
        string key;
        string value;
        bool isfree;
    };
    Node* _arr;
public:
    HashTable();
    bool insert(string key1, string value1);
    void resize();
    void rehash();
    long long hashfunc(string key);
    int getbuffer_size() { return _buffer_size; }
    string getKey(int i){ return _arr[i].key; }
    string getValue(int i){ return _arr[i].value; }
    friend ostream& operator<< (ostream& os, HashTable& H);
    int find(string key);
    void Delete(string key);
    int getKollisions() const;
    ~HashTable();
};



#endif //PRAKTIKA1_HASHTABLE_H
