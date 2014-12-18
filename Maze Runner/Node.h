#ifndef _NODE_
#define _NODE_

#include <iostream>
#include <string>
#include <GL/glut.h>
#include "Matrix4.h"
#include "Vector4.h"
#include "GLee.h"

using namespace std;

class Node {
  protected:
    string name;    // Name of the node
    Node* parent;   // pointer to parent node; null if root
  
  public:
    Vector4 center;
    Vector4 scale;
  
  // Constructors, Destructors, and Methods, (oh my) //
  // Constructors
    Node();
    Node(string);
  
  // Destructor
    virtual ~Node();
  
  // Parent Checker
    bool hasParent();
    Node* getParent();
    void setParent( Node* );
  
  // Getters and Setters
  // sets name
    void setName(string);
  // gets name
    string getName();
  
  // Abstract draw method for updates; both set to 0
	virtual void draw(Matrix4, bool) = 0;
	virtual void draw(Matrix4, bool, bool) = 0;
  
};

#endif
