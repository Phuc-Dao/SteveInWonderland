#include "Node.h"

using namespace std;

// Generic constructor with no name passed in; all max/min values set to 0
Node::Node() {
    name = "";
    parent = nullptr;
}


// Constructor with name passed in
Node::Node(string n) {
    name = n;
    parent = nullptr;
}


// Destructor
Node::~Node() {
    
}


// Parent Checker
// checks if the node has a parent;
// if there is a parent, return true; else false
bool Node::hasParent() {
    if( parent == nullptr ) {
        return false;
    }
    else {
        return true;
    }
}


Node* Node::getParent() {
    return parent;
}


void Node::setParent( Node* p ) {
    parent = p;
}

// Getters and Setters
// sets name
void Node::setName(string n) {
    name = n;
}


// gets name of Node
string Node::getName() {
    return name;
}