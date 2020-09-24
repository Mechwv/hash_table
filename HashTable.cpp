//
// Created by alviz on 12.09.2020.
//

#include "HashTable.h"

HashTable::HashTable()
{
    _buffer_size = _default_size;
    _size = 0;
    if (file.is_open()) {
        file.close();
    }
    file.open(file_name, std::ios::out | std::ios::trunc);
    file.close();
    file.open(file_name, std::ios::binary | std::ios::in | std::ios::out);
    init(_buffer_size);
}

void HashTable::init(int size){
    Node r;
    r.isfree = true;
    strcpy(r.key, "0");
    strcpy(r.value, "0");
    for (int i = 0; i < size; i++){
        put_one(i,r);
    }
}

void HashTable::load(){
    Node from_file;
    _arr = new Node[_buffer_size];
    file.seekg(0, ios::beg);
    for (int i = 0; i < _buffer_size; i++) {
        file.read((char *) &from_file, sizeof(Node));
        strcpy(_arr[i].key, from_file.key);
        strcpy(_arr[i].value, from_file.value);
        _arr[i].isfree = from_file.isfree;
//        cout << _arr[i].key << " " << _arr[i].value << " " << _arr[i].isfree << "\n";
    }
    file.flush();
}

void HashTable::put_one(int pos, Node r){
    file.seekp(pos*sizeof(Node),ios::beg);
    file.write((char *) &r, sizeof(Node));
    file.flush();
}

void HashTable::put(){
    Node r;
    for (int i =0; i < _buffer_size; i++){
        strcpy(r.key, _arr[i].key);
        strcpy(r.value, _arr[i].value);
        r.isfree = _arr[i].isfree;
        put_one(i,r);
    }
}

HashTable::Node HashTable::load_one(int pos){
    Node r;
    file.seekg(pos*sizeof(Node),ios::beg);
    file.read((char *) &r, sizeof(Node));
    file.flush();
    return r;
}

int HashTable::hashfunc(char key[50]) {
    const int p = 3;
    int hash = 0, p_pow = 2;
    for (size_t i=0; i<3; ++i)
    {
        hash += (key[i]) * p_pow;
        p_pow *= p;
    }
    return hash % _buffer_size;
}

bool HashTable::insert(char key1[50], char value1[50])
{
    while (_size + 1 > int(_rehash_size * _buffer_size))
        resize();
    int h = hashfunc(key1);
    while (h > _buffer_size)
        resize();
    int i = 0;
    bool flagIns = false;
    Node r = load_one(h);
    while (i < _buffer_size && !flagIns) {
        if (r.value == value1)
            return false;
        if (r.isfree) {
            strcpy(r.key, key1);
            strcpy(r.value, value1);
            r.isfree = false;
            flagIns = true;
            ++_size;
            put_one(h,r);
        }
        else {
            kollisions++;
            h++;
            r = load_one(h);
        }
        ++i;
    }
    return true;
}

void HashTable::resize() {
    load();
    file.open(file_name, std::ios::out | std::ios::trunc);
    file.close();
    file.open(file_name, std::ios::binary | std::ios::in | std::ios::out);
    if (kollisions > _buffer_size / 10) {
//        rehash();
    }
    int oldTableSize = _buffer_size;
    _buffer_size = (int) (_buffer_size * 2);
    Node * newtable = new Node[_buffer_size];
    for (int i = 0; i < oldTableSize; i++)
        if (strcmp(_arr[i].key, "0") != 0) {
            strcpy(newtable[i].key, _arr[i].key);
            strcpy(newtable[i].value, _arr[i].value);
            newtable[i].isfree = false;
        }
    _arr = newtable;
    put();
}

void HashTable::rehash()
{
    int i = 0;
    bool flagIns = false;
    int h = hashfunc(_arr[i].key);
    while (i < _buffer_size && !flagIns) {
        if (strcmp(_arr[i].key, "0") != 0){
            if (_arr[h].isfree) {
                strcpy(_arr[h].key, _arr[i].key);
                strcpy(_arr[h].value, _arr[i].value);
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
    H.load();
    for (int i = 0; i < H._buffer_size; i++) {
        if (H.getKey(i) != "0")
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

int HashTable::find(char key[50]) {
    for (int i = hashfunc(key); i <_default_size; i++){
        if (load_one(i).key == key)
            return i;
    }
    return 0;
}

void HashTable::Delete(char key[50]) {
    int i = find(key);
    Node r;
    strcpy(r.key, "0");
    strcpy(r.value, "0");
    r.isfree = false;
    put_one(i,r);
}

string HashTable::keygen(int length){
    static const std::string alphabet = "abcdefghijklmnopqrstuvwxyz" ;
    static std::default_random_engine rng( std::time(nullptr) ) ;
    static std::uniform_int_distribution<std::size_t> distribution( 0, alphabet.size() - 1 ) ;

    std::string str ;
    while( str.size() < length ) str += alphabet[ distribution(rng) ] ;
    return str ;
}