//
// Created by alviz on 12.09.2020.
//

#ifndef PRAKTIKA1_HASHTABLE_H
#define PRAKTIKA1_HASHTABLE_H

#include <iostream>
#include <ctime>
#include <random>
#include <fstream>
#include <cstring>
using namespace std;

class HashTable {
private:
    static const int _default_size = 100;
    const double _rehash_size = 0.75;
    static const constexpr char *file_name = "HashTable.bin";
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
    fstream file;
public:
    HashTable();
    void init(int size);
    bool insert(char key[50], char value[50]);
    void resize();
    void rehash();
    int hashfunc(char key[50]);
    int getbuffer_size() { return _buffer_size; }
    string getKey(int i){ return _arr[i].key; }
    string getValue(int i){ return _arr[i].value; }
    friend ostream& operator<< (ostream& os, HashTable& H);
    int find(char key[50]);
    void Delete(char key[50]);
    int getKollisions() const;
    string keygen(int length);
    ~HashTable();

    void load();

    Node load_one(int pos);

    void put_one(int pos, Node r);

    void put();
};



#endif //PRAKTIKA1_HASHTABLE_H
