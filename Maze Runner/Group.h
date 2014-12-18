#ifndef _GROUP_
#define _GROUP_

#include <vector>
#include <string>

#include "Node.h"
#include "Geode.h"
#include "Matrix4.h"

using namespace std;

class Group : public Node {
//  protected:
  
  public:
    // vector containing pointers to all the nodes in the scene graph
    vector<Node*> children;
    int numofChildren;       // number of nodes in the children vector
  
//  public:
  
  // Constructor
    Group();
    Group(string);
  // Deconstructor
    virtual ~Group();
  
  // Checks if group is empty or not
    bool isEmpty();
  
  // Returns size of group
    int getSize();
  
  // adds a node into the list
    void addChild(Node*);
  // removes a node with a matching name from the child list
    bool removeChild(string);
  
  // traverses the children vector to call each node's draw function
    virtual void draw(Matrix4, bool);
    virtual void draw(Matrix4, bool, bool);
    //virtual void draw(Matrix4, bool, bool, Frustum);
  
  
};

#endif