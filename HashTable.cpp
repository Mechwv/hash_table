//
// Created by alviz on 12.09.2020.
//

#include "HashTable.h"

HashTable::HashTable()
{
    _buffer_size = _default_size;
    _size = 0;
    _arr = new Node[_buffer_size];
    for (int i = 0; i < _buffer_size; i++) {
        _arr[i].key = "0";
        _arr[i].value = "0";
        _arr[i].isfree = true;
    }
}
long long HashTable::hashfunc(string key) {
    const int p = 31;
    long long hash = 0, p_pow = 4;
    for (size_t i=0; i<3; ++i)
    {
        hash += (key[i] - 'a' + 1) * p_pow;
        p_pow *= p;
    }
    return hash % _buffer_size;
}

bool HashTable::insert(string key1, string value1)
{
    if (_size + 1 > int(_rehash_size * _buffer_size))
        resize();
    long long h = hashfunc(key1);
    while (h > _buffer_size)
        resize();
    int i = 0;
    bool flagIns = false;
    while (i < _buffer_size && !flagIns) {
        if (_arr[h].value == value1)
            return false;
        if (_arr[h].isfree == true) {
            _arr[h].key = key1;
            _arr[h].value = value1;
            flagIns = true;
            ++_size;
        }
        else {
//            cout << "Kolliziya klucha" << key1;
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
        newtable[i].key = '0';
        newtable[i].value = '0';
        newtable[i].isfree = true;
    }
    for (int i = 0; i < oldTableSize; i++)
        if (_arr[i].key != "0") {
            newtable[i].key = _arr[i].key;
            newtable[i].value = _arr[i].value;
            newtable[i].isfree = false;
        }
    delete[] _arr;
    _arr = newtable;
}

void HashTable::rehash()
{
    int i = 0;
    bool flagIns = false;
    long long h = hashfunc(_arr[i].key);
    while (i < _buffer_size && !flagIns) {
        if (_arr[i].key != "0"){
            if (_arr[h].isfree) {
                _arr[h].key = _arr[i].key;
                _arr[h].value = _arr[i].value;
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
//        if (H.getKey(i) != "0")
            os << H.getKey(i) << ' ' << H.getValue(i) << endl;
    }
    return os;
}

HashTable::~HashTable()
{
    delete[] _arr;
}

int HashTable::getKollisions() const {
    return kollisions;
}

int HashTable::find(string key) {
    for (int i = hashfunc(key); i <_default_size; i++){
        if (_arr[i].key == key)
            return i;
    }
    return 0;
}

void HashTable::Delete(string key) {
    int i = find(key);
    _arr[i].key = "0";
    _arr[i].value = "0";
}
