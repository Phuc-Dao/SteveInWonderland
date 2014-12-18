#include "MatrixTransform.h"

// Constructors
MatrixTransform::MatrixTransform() {
    Matrix4 mat = Matrix4();
    mat.identity();
    trans = mat;
}


MatrixTransform::MatrixTransform(string n, Matrix4 C) {
    setName(n);
    trans = C;
}


// Desctructor
MatrixTransform::~MatrixTransform() {
    
}


// Setter
void MatrixTransform::setMatrix(Matrix4 C) {
    trans = C;
}


// Getter
Matrix4 MatrixTransform::getMatrix() {
    return trans;
}


// applies the transformation matrix to the matrix
void MatrixTransform::draw(Matrix4 C, bool shade) {
    Matrix4 mat = C * trans;
    
    vector<Node*>::iterator vIt = children.begin();
    while( vIt != children.end() ) {
        Node* child = (*vIt);
        child->draw(mat, shade);
        
        // increment iterator
        vIt++;
    }
    
}


// applies the transformation matrix to the matrix
void MatrixTransform::draw(Matrix4 C, bool cond, bool shade) {
    Matrix4 mat = C * trans;
    
    vector<Node*>::iterator vIt = children.begin();
    while( vIt != children.end() ) {
        Node* child = (*vIt);
        child->draw(mat, cond, shade);
        
        // increment iterator
        vIt++;
    }
    
}