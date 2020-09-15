//
// Created by alviz on 12.09.2020.
//
#include <iostream>
#include "HashTable.h"
#include <ctime>
#include <random>

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
    int i = 0;
    while (i < 100000){
        H.insert(keygen(3+i/1000), keygen(3+i/1000));
        i++;
    }
//    H.insert("zzzzzzzzz", "spat");
//    H.insert("alphabet", "alfavit");
//    H.insert("ara", "ara");
//    H.insert("nose", "nos");
//    H.insert("bongo", "bongo");
//    H.insert("ballista", "ballista");
    cout << H;
    cout << H.getbuffer_size() << "\n";
    cout << H.getKollisions();
}
