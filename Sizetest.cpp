//
// Created by mechwave on 15.09.2020.
//
#include <iostream>
#include <string>
using namespace std;
class Sizetest{
public:
    struct node_s{
        string s1;
        string s2;
        int i;
    };

    struct node_c{
        char f[40];
        char g[10];
        int i;

    };
    node_s * a;
    node_c * b;
};
int main(){
    Sizetest s = Sizetest();
    cout << sizeof(s.a) << "\n";
    cout << sizeof(s.b);
}