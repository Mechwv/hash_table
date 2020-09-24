//
// Created by alviz on 20.09.2020.
//
#include <iostream>
#include "HashTable.h"
#include <ctime>
#include <random>
#include <fstream>
#include <cstring>

using namespace std;

string keygen(int length){
    static const std::string alphabet = "abcdefghijklmnopqrstuvwxyz" ;
    static std::default_random_engine rng( std::time(nullptr) ) ;
    static std::uniform_int_distribution<std::size_t> distribution( 0, alphabet.size() - 1 ) ;

    std::string str ;
    while( str.size() < length ) str += alphabet[ distribution(rng) ] ;
    return str ;
}

struct Node
{
    char key[50];
    char value[50];
    bool isfree;
};

int main() {
    HashTable H;
    int N = 80;
    Node node;
    cout << sizeof(Node) << "\n\n";
    ofstream out("test.bin", ios::binary);
    for (int i =0; i < N; i++) {
        strcpy(node.key, keygen(3+i/10).c_str());
        strcpy(node.value, keygen(3+i/10).c_str());
        node.isfree = true;
        out.write((char*)&node, sizeof(Node));
    }
    out.close();

    Node output;

    ifstream in("test.bin", ios::binary);
    in.seekg(0, ios::beg);
    for (int i = 0; i < N; i++) {
        in.read((char*)&output, sizeof(Node));
        H.insert(output.key,output.value);
    }
    in.close();
    cout << H;
    cout << H.getbuffer_size() << "\n";
    cout << H.getKollisions();
}