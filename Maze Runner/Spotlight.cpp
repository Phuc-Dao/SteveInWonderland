#include "Spotlight.h"

#include <iostream>


// Constructors
Spotlight::Spotlight() {
    // AMBIENT
    ambient[0] = 0.0;
    ambient[1] = 0.0;
    ambient[2] = 0.0;
    ambient[3] = 1.0;
    
    // DIFFUSE
    diffuse[0] = 1.0;
    diffuse[1] = 1.0;
    diffuse[2] = 1.0;
    diffuse[3] = 1.0;
    
    // SPECULAR
    specular[0] = 1.0;
    specular[1] = 1.0;
    specular[2] = 1.0;
    specular[3] = 1.0;
    
    // POSITION
    position[0] = 0.0;
    position[1] = 0.0;
    position[2] = 1.0;
    position[3] = 0.0;
    
    // LIGHT DIRECTION
    direction[0] = 0.0;
    direction[1] = 0.0;
    direction[2] = -1.0;
    
    // SPOLIGHT EXPONENT
    exponent = 0.0;
    
    // SPOTLIGHT CUTOFF
    cutOff = 180;
    
    // ATTENUATION FACTORS
    cAtten = 1.0;
    lAtten = 0.0;
    qAtten = 0.0;
    
    // a number
    num = 0;
    light = GL_LIGHT0;
    
    // if light is a spotlight or not
    spotLight = false;
    
}

// Deconstructor
Spotlight::~Spotlight() {
    
}

// Three light properties
// AMBIENT------------------
void Spotlight::setAmbient(float* amb) {
    ambient[0] = amb[0];
    ambient[1] = amb[1];
    ambient[2] = amb[2];
    ambient[3] = amb[3];
    
    glLightfv(light, GL_AMBIENT, ambient);
}


// DIFFUSE-------------------
void Spotlight::setDiffuse(float* dif) {
    diffuse[0] = dif[0];
    diffuse[1] = dif[1];
    diffuse[2] = dif[2];
    diffuse[3] = dif[3];
    
    glLightfv(light, GL_DIFFUSE, diffuse);
}


// SPECULAR------------------
void Spotlight::setSpecular(float* spe) {
    specular[0] = spe[0];
    specular[1] = spe[1];
    specular[2] = spe[2];
    specular[3] = spe[3];
    
    glLightfv(light, GL_SPECULAR, specular);
}



void Spotlight::setPosition(float* pos) {
    position[0] = pos[0];
    position[1] = pos[1];
    position[2] = pos[2];
    position[3] = pos[3];
    
    glLightfv(light, GL_POSITION, position);
}


void Spotlight::setSpotDirection(float* dir) {
    direction[0] = dir[0];
    direction[1] = dir[1];
    direction[2] = dir[2];
    
    if( spotLight ) {
        glLightfv(light, GL_SPOT_DIRECTION, direction);
    }
}


void Spotlight::setSpotExponent(float e) {
    exponent = e;
    
    if( spotLight ) {
        glLightfv(light, GL_SPOT_EXPONENT, &exponent);
    }
}


void Spotlight::setSpotCutoff(float c) {
    cutOff = c;
    
    if( spotLight ) {
        glLightfv(light, GL_SPOT_CUTOFF, &cutOff);
    }
}


void Spotlight::setAtten(float c, float l, float q) {
    cAtten = c;
    lAtten = l;
    qAtten = q;
    
    glLightf(light, GL_CONSTANT_ATTENUATION, cAtten);
    glLightf(light, GL_LINEAR_ATTENUATION, lAtten);
    glLightf(light, GL_QUADRATIC_ATTENUATION, qAtten);
}


void Spotlight::setNum(int n) {
    num = n;
    
    switch( num ) {
        case '0': {
            light = GL_LIGHT0;
            break;
        }
        case '1': {
            light = GL_LIGHT1;
            break;
        }
        case '2': {
            light = GL_LIGHT2;
            break;
        }
        case '3': {
            light = GL_LIGHT3;
            break;
        }
        case '4': {
            light = GL_LIGHT4;
            break;
        }
        case '5': {
            light = GL_LIGHT5;
            break;
        }
        case '6': {
            light = GL_LIGHT6;
            break;
        }
        case '7': {
            light = GL_LIGHT7;
            break;
        }
    }
    
    
}


void Spotlight::setSpotlight(bool s) {
    spotLight = s;
}


void Spotlight::turnOn() {
    glEnable(light);
    
    glLightfv(light, GL_AMBIENT, ambient);
    glLightfv(light, GL_DIFFUSE, diffuse);
    glLightfv(light, GL_SPECULAR, specular);
    
    /*glLightfv(light, GL_AMBIENT, ambient);
     glLightfv(light, GL_DIFFUSE, diffuse);
     glLightfv(light, GL_SPECULAR, specular);
     glLightfv(light, GL_POSITION, position);
     glLightf(light, GL_CONSTANT_ATTENUATION, cAtten);
     glLightf(light, GL_LINEAR_ATTENUATION, lAtten);
     glLightf(light, GL_QUADRATIC_ATTENUATION, qAtten);
     
     if( spotLight ) {
     glLightfv(light, GL_SPOT_DIRECTION, direction);
     glLightfv(light, GL_SPOT_EXPONENT, &exponent);
     glLightfv(light, GL_SPOT_CUTOFF, &cutOff);
     }*/
  
}


void Spotlight::turnOff() {
    glDisable(light);
    
    float dark[] = {0.0, 0.0, 0.0, 0.0};
    
    glLightfv(light, GL_DIFFUSE, dark);
    glLightfv(light, GL_SPECULAR, dark);
    
}