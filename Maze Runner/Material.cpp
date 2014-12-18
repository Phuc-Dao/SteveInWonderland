#include "Material.h"


// Constructor
Material::Material() {
    // AMBIENT
    ambient[0] = 0.2;
    ambient[1] = 0.2;
    ambient[2] = 0.2;
    ambient[3] = 1.0;
    
    // DIFFUSE
    diffuse[0] = 0.8;
    diffuse[1] = 0.8;
    diffuse[2] = 0.8;
    diffuse[3] = 1.0;
    
    // SPECULAR
    specular[0] = 0.0;
    specular[1] = 0.0;
    specular[2] = 0.0;
    specular[3] = 1.0;
    
    // EMISSION
    emission[0] = 0.0;
    emission[1] = 0.0;
    emission[2] = 0.0;
    emission[3] = 1.0;
    
    // SHINE
    shine = 0.0;
    
    // COLOR
    color[0] = 0.0;
    color[1] = 1.0;
    color[2] = 1.0;
    
}

// Destructor
Material::~Material() {
    
}


void Material::setAmbient(float* amb) {
    ambient[0] = amb[0];
    ambient[1] = amb[1];
    ambient[2] = amb[2];
    ambient[3] = amb[3];
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
}


void Material::setDiffuse(float* dif) {
    diffuse[0] = dif[0];
    diffuse[1] = dif[1];
    diffuse[2] = dif[2];
    diffuse[3] = dif[3];
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
}


void Material::setSpecular(float* spe) {
    specular[0] = spe[0];
    specular[1] = spe[1];
    specular[2] = spe[2];
    specular[3] = spe[3];
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
}


void Material::setEmmission(float* em) {
    emission[0] = em[0];
    emission[1] = em[1];
    emission[2] = em[2];
    emission[3] = em[3];
    
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
}


void Material::setShine(float s) {
    shine = s;
    
    glMaterialfv(GL_FRONT, GL_SHININESS, &shine);
}


void Material::setColor(float* c) {
    color[0] = c[0];
    color[1] = c[1];
    color[2] = c[2];
    
    glMaterialfv(GL_FRONT, GL_COLOR_INDEXES, color);
    
}

void Material::update() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shine);
    glMaterialfv(GL_FRONT, GL_COLOR_INDEXES, color);
}