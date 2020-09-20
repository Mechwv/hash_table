//
// Created by alviz on 12.09.2020.
//

#include "HashTable.h"

HashTable::HashTable()
{
    _buffer_size = _default_size;
    _size = 0;
    this->_arr = new Node[_buffer_size];
    for (int i = 0; i < _buffer_size; i++) {
        this->_arr[i].key[0] = '0';
        this->_arr[i].value[0] = '0';
        this->_arr[i].isfree = true;
    }
}
long long HashTable::hashfunc(char key[50]) {
    const int p = 31;
    long long hash = 0, p_pow = 4;
    for (size_t i=0; i<3; ++i)
    {
        hash += (key[i]) * p_pow;
        p_pow *= p;
    }
    return hash % _buffer_size;
}

bool HashTable::insert(char key1[50], char value1[50])
{
    if (_size + 1 > int(_rehash_size * _buffer_size))
        resize();
    long long h = hashfunc(key1);
    while (h > _buffer_size)
        resize();
    int i = 0;
    bool flagIns = false;
    while (i < _buffer_size && !flagIns) {
        if (this->_arr[h].value == value1)
            return false;
        if (this->_arr[h].isfree == true) {
            strcpy(this->_arr[h].key, key1);
            strcpy(this->_arr[h].value, value1);
            flagIns = true;
            ++_size;
        }
        else {
            kollisions++;
            h++;
        }
        ++i;
    }
    return true;
}

void HashTable::resize() {
    if (kollisions > _buffer_size / 10) {
        rehash();
    }
    int oldTableSize = _buffer_size;
    _buffer_size = (int) (_buffer_size * 2);
    Node *newtable = new Node[_buffer_size];
    for (int i = 0; i < _buffer_size; i++){
        newtable[i].key[0] = '0';
        newtable[i].value[0] = '0';
        newtable[i].isfree = true;
    }
    for (int i = 0; i < oldTableSize; i++)
        if (this->_arr[i].key[0] != '0') {
            strcpy(newtable[i].key, this->_arr[i].key);
            strcpy(newtable[i].value, this->_arr[i].value);
            newtable[i].isfree = false;
        }
    delete[] this->_arr;
    this->_arr = newtable;
}

void HashTable::rehash()
{
    int i = 0;
    bool flagIns = false;
    long long h = hashfunc(this->_arr[i].key);
    while (i < _buffer_size && !flagIns) {
        if (this->_arr[i].key[0] != '0'){
            if (this->_arr[h].isfree) {
                strcpy(this->_arr[h].key, this->_arr[i].key);
                strcpy(this->_arr[h].value, this->_arr[i].value);
                flagIns = true;
                ++_size;
            }
            else {
                kollisions++;
                h++;
            }
            ++i;
        }
    }

}


ostream& operator<<(ostream& os, HashTable& H)
{
    for (int i = 0; i < H.getbuffer_size(); i++) {
//        if (H.getKey(i)[0] != '0')
            os << H.getKey(i) << ' ' << H.getValue(i) << endl;
    }
    return os;
}

HashTable::~HashTable()
{
    delete[] this->_arr;
}

int HashTable::getKollisions() const {
    return kollisions;
}

long long HashTable::find(char key[50]) {
    for (long long i = hashfunc(key); i <_default_size; i++){
        if (this->_arr[i].key == key)
            return i;
    }
    return 0;
}

void HashTable::Delete(char key[50]) {
    long long i = find(key);
    this->_arr[i].key[0] = '0';
    this->_arr[i].value[0] = '0';
}
