#ifndef _CUBE_H_
#define _CUBE_H_

#include "Geode.h"

class Cube : public Geode {
protected:
    GLuint texture[6];
    
public:
	Cube();
	Cube(double);
	void render(bool);
    void render(Matrix4, bool);
	void setMatrix(Matrix4);
    void setTexture(GLuint tex[6]);
    
    Matrix4 getModelView();
    
};

#endif