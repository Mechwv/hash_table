//
// Created by alviz on 12.09.2020.
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

int main()
{
    HashTable H;
    int N = 1000;
    int i = 0;
    ofstream out("test.txt");
    while (i < N){
        out << keygen(3+i/100) << " " << keygen(3+i/100) << "\n";
        i++;
    }
    out.close();
    ifstream in("test.txt");
    string line1,line2;
    i = 0;
    while (i<N){
        in >> line1 >> line2;
        char a[50], b[50];
        strcpy(a,line1.c_str());
        strcpy(b,line2.c_str());
        H.insert(a,b);
        i++;
    }
    cout << H;
    cout << H.getbuffer_size() << "\n";
    cout << H.getKollisions();
}