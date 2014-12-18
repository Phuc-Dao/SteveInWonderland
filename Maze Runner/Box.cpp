#include "Box.h"


Box::Box() {
    t = 0.0;
    center = Vector3(0.0, 0.0, 0.0);
}

Box::Box(string n) {
    t = 0.0;
    center = Vector3(0.0, 0.0, 0.0);
    setName(n);
}

Box::Box(string n, double s, Vector3 v) {
    setName(n);
    t = s;
    center = v;
}

Box::~Box() { }

void Box::render(bool shade) {
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glPushMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
    glTranslatef(0.0, 4.0, 0.0);
    glScalef(4.1, 8.1, 2.3 + t);
    glutSolidCube(1);
    glPopMatrix();
    
    glDisable(GL_BLEND);
    
}

void Box::render(Matrix4 C, bool shade) {
	render(shade);
}


void Box::setCenter(Vector3 v) {
    center = v;
}


void Box::setT(double s) {
    t = s;
}

void Box::setMatrix(Matrix4 C) {
    model2world = C;
}


Matrix4 Box::getModelView() {
    return model2world;
}