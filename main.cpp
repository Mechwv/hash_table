//
// Created by alviz on 12.09.2020.
//
#include <iostream>
#include "HashTable.h"
#include <ctime>
#include <random>
#include <fstream>

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
        out << keygen(3+i/1000) << " " << keygen(3+i/1000) << "\n";
        i++;
    }
    out.close();
    ifstream in("test.txt");
    string line1,line2;
    i = 0;
    while (i<N){
        in >> line1 >> line2;
        H.insert(line1,line2);
        i++;
    }
    cout << H;
    cout << H.getbuffer_size() << "\n";
    cout << H.getKollisions();
}
