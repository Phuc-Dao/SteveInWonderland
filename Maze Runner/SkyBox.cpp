#include "SkyBox.h"

SkyBox::SkyBox() {
    center = Vector3();
    
    loadTextures();
}

SkyBox::SkyBox(string s) {
    center = Vector3();
    setName(s);
    
    loadTextures();
}

// Destructor
SkyBox::~SkyBox() {
    
}

void SkyBox::loadTextures() {
    // LEFT
    textures[0] = SOIL_load_OGL_texture(
                 "clouds_left.jpg",
                 SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y
    );
    
    // BEHIND
    textures[1] = SOIL_load_OGL_texture(
                 "clouds_back.jpg",
                 SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y
    );
    
    // RIGHT
    textures[2] = SOIL_load_OGL_texture(
                  "clouds_right.jpg",
                   SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y
    );
    
    // FRONT
    textures[3] = SOIL_load_OGL_texture(
                  "clouds_front.jpg",
                  SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y
    );
    
    // ABOVE
    textures[4] = SOIL_load_OGL_texture(
                  "clouds_top.jpg",
                  SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y
    );
    /*
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/
    
}

void SkyBox::render(Matrix4 mat, bool) {
    noEMRender();

}


//
void SkyBox::noEMRender() {
    glDisable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_TEXTURE_2D);
    
    // LEFT FACE
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // Use bilinear interpolation:
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d((-100.0), -0.1, 100.1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d((-100.0), -0.1, (-100.1));
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d((-100.0), 100.1, (-100.1));
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d((-100.0), 100.1, 100.1);
    glEnd();
    
    //BEHIND FACE
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(100.1, -0.1, 100.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d((-100.1), -0.1, 100.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d((-100.1), 100.1, 100.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(100.1, 100.1, 100.0);
    glEnd();
    
    // RIGHT FACE
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(100.0, -0.1, (-100.1));
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(100.0, -0.1, 100.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(100.0, 100.1, 100.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(100.0, 100.1, (-100.1));
    glEnd();
    
    // FRONT FACE
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d((-100.1), -0.1, (-100.0));
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(100.1, -0.1, (-100.0));
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(100.1, 100.1, (-100.0));
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d((-100.1), 100.1, (-100.0));
    glEnd();
    
    // TOP FACE
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d((-100.1), 100.0, (-100.1));
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(100.1, 100.0, (-100.1));
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(100.1, 100.0, 100.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d((-100.1), 100.0, 100.1);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    
}


//
void SkyBox::eMRender() {

    
}