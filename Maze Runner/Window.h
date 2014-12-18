#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
#include <vector>
#include <time.h>
#include <GL/glut.h>

#include "main.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Camera.h"
#include "Projection.h"
#include "Viewport.h"

#include "Object.h"

#include "Node.h"
#include "Group.h"
#include "MatrixTransform.h"
#include "Geode.h"
#include "City.h"
#include "Cube.h"
#include "SkyBox.h"
#include "Box.h"

#include "Light.h"
#include "Spotlight.h"
#include "Material.h"

#include "ParticleSys.h"
#include "BezierCurve.h"
#include "SOIL.h"
#include "bigPatch.h"


class Window	  // OpenGL output window related routines
{
  public:
    static int width, height; 	            // window size
    
    static void loadData();
    
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static void keyboardCallback(unsigned char, int, int);
    static void keyboardRelease(unsigned char, int, int);
    static void keyboardSpecialRelease(int, int, int);
    static void keyboardSpecialCallback(int, int, int);
    static void mouseClick(int, int, int, int);
    static void mouseMove(int, int);
    
    static void makeModel();
    static void makeCharacter();
    static void loadTexture();
    static void animate();

    static void setMatrix(Matrix4, Matrix4);
    static void setMatrix(Matrix4);
};

#endif

