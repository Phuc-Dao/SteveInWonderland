#include <iostream>

#include "Group.h"

using namespace std;

// Constructor
Group::Group() {
    children.clear();
    numofChildren = 0;
}


Group::Group(string n) {
  children.clear();
  numofChildren = 0;
  setName(n);
}

// Deconstructor
Group::~Group() {
  // creates vector iterator to go through children vector
 /* vector<Node*>::iterator vIt = children.begin();
  
  // while we do not reach the end of the list, loop
  while( vIt != children.end() ) {
    delete (*vIt);
    vIt++;
  }*/
    children.clear();
}


// Checks if group is empty or not
bool Group::isEmpty() {
    if( numofChildren == 0 ) {
        return true;
    }
    else {
        return false;
    }
}


// Returns size of group
int Group::getSize() {
    return numofChildren;
}


// adds a node into the list
void Group::addChild(Node* child) {
    children.push_back(child);
    child->setParent(this);
    numofChildren++;
}


// removes a node with a matching name from the child list
bool Group::removeChild(string name) {
  // creates vector iterator to go through children vector
    vector<Node*>::iterator vIt = children.begin();
  
  // while we do not reach the end of the list, loop
    while( vIt != children.end() ) {
    
    // checks if the name of the current Node in list match with the passed in
    // name; if it does, remove from children vector, decrement, and return true
      string str = (*vIt)->getName();
      if( name.compare(str) == 0 ) {
        children.erase(vIt);
        numofChildren--;
        return true;
      }
    // increment the iterator
      vIt++;
    }
  // match not found; child removal failed
    return false;
}


// traverses the children vector to call each node's draw function
void Group::draw(Matrix4 C, bool shade) {
  // creates vector iterator to go through children vector
    vector<Node*>::iterator vIt = children.begin();
 
  // while we do not reach the end of the list, loop
    while( vIt != children.end() ) {
    // traverse the children vector and have each child node call their draw
    // function
      Node* child = (*vIt);
      child->draw(C, shade);
      
    // increment the iterator
      vIt++;
    }
}


// traverses the children vector to call each node's draw function
void Group::draw(Matrix4 C, bool cond, bool shade) {
  // creates vector iterator to go through children vector
  vector<Node*>::iterator vIt = children.begin();
  
  // while we do not reach the end of the list, loop
  while( vIt != children.end() ) {
    // traverse the children vector and have each child node call their draw
    // function
    Node* child = (*vIt);
    child->draw(C, cond, shade);
 
    // increment the iterator
    vIt++;
  }
}
