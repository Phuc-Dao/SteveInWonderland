#ifndef _SPOTLIGHT_
#define _SPOTLIGHT_


#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include <GL/glut.h>


class Spotlight {
protected:
    
    int num;
    GLenum light;
    
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float position[4];
    float direction[3];
    float exponent;
    float cutOff;
    float cAtten, lAtten, qAtten;
    bool spotLight;
    
public:
    
    // Constructor
    Spotlight();
    
    // Deconstructor
    virtual ~Spotlight();
    
    // Three light properties
    void setAmbient(float*);
    void setDiffuse(float*);
    void setSpecular(float*);
    
    void setPosition(float*);
    void setSpotDirection(float*);
    void setSpotExponent(float);
    void setSpotCutoff(float);
    
    void setAtten(float, float, float);
    void setNum(int);
    void setSpotlight(bool);
    
    void turnOn();
    void turnOff();
};

#endif
