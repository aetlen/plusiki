#include <iostream>
#include "supertuv.h"

using namespace std;

int main()
{
    cout << "Bitwise AND test" << endl;
    AND<char> andc;
    cout << andc('c', 'c') << endl; // Outputs c
    AND<int> andi;
    cout << andi(6,3) << endl; // Outputs 2, 011 and 110 is 010 equals 2
    AND<bitset<67>> andb;
    cout << andb(bitset<67>("110"),bitset<67>("011")) << endl;

    cout << "Bitwise OR test" << endl;
    OR<char> orc;
    cout << orc('c', 'c') << endl; // Outputs c
    OR<int> ori;
    cout << ori(6,3) << endl; // Outputs 2, 011 and 110 is 111 equals 7
    OR<bitset<67>> orb;
    cout << orb(bitset<67>("110"),bitset<67>("011")) << endl;

    cout << "Bitwise XOR test" << endl;
    XOR<char> xorc;
    cout << xorc('c', '\0') << endl; // Outputs c
    XOR<int> xori;
    cout << xori(6,3) << endl; // Outputs 2, 011 and 110 is 101 equals 5
    XOR<bitset<67>> xorb;
    cout << xorb(bitset<67>("110"),bitset<67>("011")) << endl;

    cout << "Bitwise NOT test" << endl;
    NOT<char> notc;
    cout << notc(0x9c) << endl; // Outputs c (not c)
    NOT<int> noti;
    cout << noti(-4) << endl; // Outputs 3 (-4 is in two’s complement form)
    NOT<bitset<67>> notb;
    cout << notb(bitset<67>("110")) << endl;

    return 0;
}


