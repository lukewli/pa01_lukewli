#include <iostream>
#include "cards.h"

using namespace std;

int main() {
    CardBST A, B;
    A.insert("d", "4");
    A.insert("h", "3");
    A.insert("s", "10");
    A.insert("c", "5");
    A.insert("h", "k");
    A.insert("c", "10");
    A.insert("d", "k");
    A.printInOrder();
    cout << endl;
    B.insert("h", "6");
    B.insert("s", "j");
    B.insert("d", "5");
    B.insert("s", "q");
    B.insert("h", "7");
    B.insert("d", "k");
    B.insert("c", "10");
    B.printInOrder();
    cout << endl;
    A.playgame(B);
    
}