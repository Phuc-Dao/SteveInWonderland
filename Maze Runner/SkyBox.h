#ifndef __SKYBOX__
#define __SKYBOX__

#include <string>

#include <GL/glut.h>
#include "Geode.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "SOIL.h"


class SkyBox : public Geode {
  protected:
    GLuint textures[5];    // five textures
    GLuint envMap;           // Environment map
    Vector3 center;        // center of skybox
    GLuint vao;

  public:
    // Constructors
    SkyBox();
    SkyBox(string);
  
    // Destructor
    virtual ~SkyBox();
  
    void loadTextures();
    void createCubeMap();
    void render(Matrix4, bool);
    void noEMRender();
    void eMRender();
  
};

#endif
