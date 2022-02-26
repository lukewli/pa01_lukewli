// cards.h


#ifndef CardBST_H
#define CardBST_H

#include <iostream>
#include <string>

using namespace std;


class CardBST {

 
 private:

    struct Node {
	string suit;
    string rank;
	Node *left, *right, *parent;
	// useful constructor:
    Node(string s = "", string r = "") : suit(s), rank(r), left(nullptr), right(nullptr), parent(nullptr) { }
    };

    // just one instance variable (pointer to root node):
    Node *root;

    // recursive utility functions for use by public methods above
    Node* getNodeFor(Node *card, Node* n); // IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
    void clear(Node *n); // for destructor
    bool insert(Node *card, Node *n); // note overloading names for simplicity
    void printPreOrder(Node *n) const;
    void printInOrder(Node *n) const;
    void printPostOrder(Node *n) const;
    int count(Node *n) const;

    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
    Node* getSuccessorNode(Node *card) ;   // returns the Node containing the successor of the given value
    Node* getPredecessorNode(Node *card) ; // returns the Node containing the predecessor of the given value 

public:
    CardBST();                   // constructor
    ~CardBST();                  // destructor
    bool insert(string suit, string rank);     // insert value; return false if duplicate
    void printPreOrder() const; // prints tree data pre-order to cout

    void printInOrder() const;       // print tree data in-order to cout
    void printPostOrder() const;     // print tree data post-order to cout
    int count() const;               // count of values
    bool contains(Node *card) ;  // true if value is in tree

    // THESE ARE HARDER! DO THESE LAST
    Node* getPredecessor(Node *card) ;       // returns the predecessor value of the given value or 0 if there is none
    Node* getSuccessor(Node *card) ;         // returns the successor value of the given value or 0 if there is none
    bool remove(Node *card);                    // deletes the Node containing the given value from the tree
    bool comparelessthan(Node *lhs, Node *rhs);
    void playgame(CardBST& other);

};

#endif
