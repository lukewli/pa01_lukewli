// cards.cpp
// Luke Li

#include "cards.h"
#include <iostream>
#include <string>
using namespace std;



// constructor sets up empty tree
CardBST::CardBST() : root(nullptr) { }

// destructor deletes all nodes
CardBST::~CardBST() {
    clear(root);
}

// recursive helper for destructor
void CardBST::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
bool CardBST::insert(string suit, string rank) {
    Node *card = new Node(suit, rank);
    // handle special case of empty tree first
    if (!root) {
	root = card;
	return true;
    }
    // otherwise use recursive helper
    return insert(card, root);
}

// recursive helper for insert (assumes n is never 0)
bool CardBST::insert(Node *card, Node *n) {
    if (comparelessthan(card, n)) {
	if (n->left)
	    return insert(card, n->left);
	else {
	    n->left = card;
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(card, n->right);
	else {
	    n->right = card;
	    n->right->parent = n;
	    return true;
	}
    }
}

// print tree data pre-order
void CardBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void CardBST::printPreOrder(Node *n) const {
    if (n) {
	cout << n->suit << " " << n->rank << endl;
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void CardBST::printInOrder() const {
    printInOrder(root);
}
void CardBST::printInOrder(Node *n) const {
    if (n) {
        printInOrder(n->left);
        cout << n->suit << " " << n->rank << endl;
        printInOrder(n->right);
    }
}

// prints tree data post-order, with helper
void CardBST::printPostOrder() const {
    printPostOrder(root);
}

void CardBST::printPostOrder(Node *n) const {
    if (n) {
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout << n->suit << " " << n->rank << endl;
    }
}

// return count of values
int CardBST::count() const {
    return count(root);
}

// recursive helper for count
int CardBST::count(Node *n) const {
    int retcount = 0;
    if (n) {
        retcount = retcount + count(n->left);
        retcount = retcount + 1;
        retcount = retcount + count(n->right);
    }
    return retcount;
}

CardBST::Node* CardBST::getNodeFor(Node *card, Node* n) {
    while (n) {
        if (card->suit == n->suit && card->rank == n->rank) {
            return n;
        }
        else if (comparelessthan(card, n)) {
            n = n->left;
        }
        else {
            n = n->right;
        }
    }
    return NULL;
}

bool CardBST::contains(Node *card) {
    if (getNodeFor(card, root)) {
        return true;
    }
    else {
        return false;
    }
}




// returns the Node containing the predecessor of the given value
CardBST::Node* CardBST::getPredecessorNode(Node *card) {
    Node *pred_node = getPredecessor(card);
    if (pred_node->suit != "" && pred_node->rank != "") {
        return getNodeFor(pred_node, root);
    }
    else {
        return 0;
    }
}

CardBST::Node* CardBST::getPredecessor(Node* card){
    Node* pred = new Node;
    Node* cur = getNodeFor(card, root);
    Node* par = cur->parent;
    Node* curL = cur->left;
    if (curL) {
        if (curL->right) {
            while (curL->right) {
                curL = curL->right;
                pred->suit = curL->suit;
                pred->rank = curL->rank;
            }
        }
        else {
            pred->suit = curL->suit;
            pred->rank = curL->rank;
        }
    }
    else if (curL == NULL && par && par->left == cur) {
        if (par->parent) {
            if (par->parent->right == par) {
                par = par->parent;
                pred->suit = par->suit;
                pred->rank = par->rank;
            }
        }
    }
    else if (curL == NULL && par && par->right == cur) {
        pred->suit = par->suit;
        pred->rank = par->rank;
    }
    return pred;
}

// returns the Node containing the successor of the given value
CardBST::Node* CardBST::getSuccessorNode(Node *card) {
    Node *succ_node = getSuccessor(card);
    if (succ_node->suit != "" && succ_node->rank != "") {
        return getNodeFor(succ_node, root);
    }
    else {
        return 0;
    }
}

// returns the successor value of the given value or 0 if there is none
CardBST::Node* CardBST::getSuccessor(Node *card){
    Node *suc = new Node;
    Node* cur = getNodeFor(card, root);
    Node* par = cur->parent;
    Node* curR = cur->right;
    if (curR == NULL && par && par->left == cur) {
        return par;
    }
    else if (curR == NULL && par && par->right == cur) {
        if (par->parent) {
            if (par->parent->left == par) {
                par = par->parent;
                return par;
            }
        }
    }
    else if (curR) {
        while (curR->left) {
            curR = curR->left;
        }
        return curR;
    }
    else {
        return suc;
    }
    return suc;
}



// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool CardBST::remove(Node *card){
    if (getNodeFor(card, root) == 0) return false;
    else {
        Node* cur = getNodeFor(card, root);
        Node* par = cur->parent;
        Node* curR = cur->right;
        Node* curL = cur->left;
        if (curR == NULL and curL == NULL) {
            if (par == NULL) root = NULL;
            else if (par->left == cur) par->left = NULL;
            else par->right = NULL;
            return true;
        }
        else if (curR == NULL) {
            if (par == NULL) root = curL;
            else if (par->left == cur) par->left = curL;
            else par->right = curL;
            return true;
        }
        else if (curL == NULL) {
            if (par == NULL) root = curR;
            else if (par->left == cur) par->left = curR;
            else par->right = curR;
            return true;
        }
        else {
            Node *suc = getSuccessor(cur);
            remove(suc);
            cur->suit = suc->suit;
            cur->rank = suc->rank;
            return true;
        }
    }

}


bool CardBST::comparelessthan(Node *lhs, Node* rhs) {
    string suitL = lhs->suit;
    string rankL = lhs->rank;
    string suitR = rhs->suit;
    string rankR = rhs->rank;
    string arrS[4] = {"c", "d", "s", "h"};
    string arrR[13] = {"a", "2", "3", "4", "5", "6", "7", "8", "9", "10", "j", "q", "k"};
    int sL = 0, rL = 0, sR = 0, rR = 0;
    for (sL; sL<4; sL++) {
        if (arrS[sL] == suitL) break;
    }
    for (rL; rL<13; rL++) {
        if (arrR[rL] == rankL) break;
    }
    for (sR; sR<4; sR++) {
        if (arrS[sR] == suitR) break;
    }
    for(rR; rR<13; rR++) {
        if (arrR[rR] == rankR) break;
    }
    if (sL < sR) {
        return true;
    }
    else if (sL > sR) {
        return false;
    }
    else if (sL == sR) {
        if (rL < rR) {
            return true;
        }
        else {
            return false;
        }
    }
}

void CardBST::playgame(CardBST& other) {
    Node *A_first = this->root;
    while (A_first->left) A_first = A_first->left;
    Node *B_last = other.root;
    while (B_last->right) B_last = B_last->right;
    int limit = this->count();
    int i = 0;
    while(i < limit) {
        while (!(other.contains(A_first)) && i < limit) {
            i++;
            A_first = getSuccessor(A_first);
        }
        if (other.contains(A_first)) {
            cout << "Alice picked matching card " << A_first->suit << " " << A_first->rank << endl;
            Node* temp = A_first;
            A_first = getSuccessor(A_first);
            other.remove(other.getNodeFor(temp, other.root));
            this->remove(temp);
            i++;
            limit--;
        }
        while (!(this->contains(B_last)) && i < limit) {
            i++;
            B_last = other.getPredecessor(B_last);
        }
        if (this->contains(B_last)) {
            cout << "Bob picked matching card " << B_last->suit << " " << B_last->rank << endl;
            Node* temp2 = B_last;
            B_last = other.getPredecessor(B_last);
            this->remove(this->getNodeFor(temp2, this->root));
            other.remove(temp2);
            i++;
            limit--;

        }
        i++;
    }
    cout << endl;
    cout << "Alice's cards:" << endl;
    printInOrder();
    cout << endl;
    cout << "Bob's cards:" << endl;
    other.printInOrder();
}
