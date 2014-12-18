#include "Geode.h"

// Constructors
Geode::Geode() {
    model2world = Matrix4();
    model2world.identity();
    
}


Geode::Geode(Matrix4 C) {
    model2world = C;
}


// Destructor
Geode::~Geode() {
    
}


// Setter and Getter
void Geode::setMatrix(Matrix4 C) {
    model2world = C;
}


Matrix4 Geode::getModelView() {
    return model2world;
}


// Drawing and Rendering
void Geode::draw(Matrix4 C, bool shade) {
  // clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    
  // Tell OpenGL what ModelView matrix to use:
    
    model2world = C;
    model2world.transpose();
    glLoadMatrixd(model2world.getPointer());
    
    render( C, shade );
}


void Geode::draw(Matrix4 C, bool cond, bool shade) {
    // clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    
    // Tell OpenGL what ModelView matrix to use:
    
    model2world = C;
    model2world.transpose();
    glLoadMatrixd(model2world.getPointer());
    
    render( C, shade );
    
    Vector4 cent = Vector4(0.0, 0.0, 0.0, 1.0);
    Vector4 scale = Vector4(0.5, 0.5, 0.5, 0.0);
    
    Vector4 nCent = C * cent;
    Vector4 nScale = C * scale;
    
    
    double rad = nScale.length();
    
    if( cond ) {
        Matrix4 transM = Matrix4();
        transM.identity();
        transM.makeTranslate(nCent.getValue(0),nCent.getValue(1),nCent.getValue(2));
        
        Matrix4 scaleM = Matrix4();
        scaleM.identity();
        scaleM.makeScale(rad, rad, rad);
        
        Matrix4 mat = transM * scaleM;
        mat.transpose();
        glPushMatrix();
        glLoadMatrixd(mat.getPointer());
        glutWireSphere(1, 20, 20);
        glPopMatrix();
        
        if( getName().compare("body") == 0 ) {
            transM.makeTranslate(nCent.getValue(0),nCent.getValue(1)-(0.7),nCent.getValue(2));
            scaleM.makeScale(rad * 1.9, rad * 1.9, rad * 1.9);
            mat = transM * scaleM;
            mat.transpose();
            glPushMatrix();
            glLoadMatrixd(mat.getPointer());
            glColor3f(0.6, 0.7, 0.8);
            glutWireSphere(1, 20, 20);
            glPopMatrix();
        }
    }
}