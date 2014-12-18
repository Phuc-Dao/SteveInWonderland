#ifndef _MATERIAL_
#define _MATERIAL_

#include <GL/glut.h>

class Material {
    protected:
        float ambient[4];
        float diffuse[4];
        float specular[4];
        float emission[4];
        float shine;
        float color[3];

    public:
      // Constructor
        Material();
  
      // Destructor
        virtual ~Material();
  
        void setAmbient(float*);
        void setDiffuse(float*);
        void setSpecular(float*);
        void setEmmission(float*);
        void setShine(float);
        void setColor(float*);

        void update();
};

#endif
