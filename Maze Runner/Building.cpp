#include "Building.h"
#include <math.h>
#include <cmath>
#include "main.h"
#include "SOIL.h"

using namespace std;


// -----------------------------------------------------------------------------
// Constructor
Building::Building() {
    loadTexture();
    bounding = false;
}


// -----------------------------------------------------------------------------
// Destructor
Building::~Building() {}


// -----------------------------------------------------------------------------
// Sets the Bounding boolean
void Building::setBound(bool b) {
    bounding = b;
}


// -----------------------------------------------------------------------------
// Switches the bounding boolean between true and false
void Building::toggleBound() {
    bounding = !bounding;
}


// -----------------------------------------------------------------------------
// Returns value of bounding boolean
bool Building::isBound() {
    return bounding;
}


// -----------------------------------------------------------------------------
//
void Building::loadTexture() {
    
    // STREETS -------------------------------------------------------------- ==
    // Vertical Streets
    textures[0] =
    SOIL_load_OGL_texture( "road_01.jpg",
                          SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y );
    // Horizontal Streets
    textures[1] =
    SOIL_load_OGL_texture( "road_02.jpg",
                          SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y );
    // Intersections
    textures[2] =
    SOIL_load_OGL_texture( "road_03.jpg",
                          SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y );
    
    // SIDEWALK ------------------------------------------------------------- ==
    textures[3] =
    SOIL_load_OGL_texture( "pave.jpg",
                          SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y );
    
    // BUILDINGS ------------------------------------------------------------ ==
    // Generic WALL
    textures[4] =
    SOIL_load_OGL_texture( "wall01.jpg",
                          SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y );
    // GENERIC TOP
    textures[5] =
    SOIL_load_OGL_texture( "top01.jpg",
                          SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y );
    
    // Destroyed
    textures[6] =
    SOIL_load_OGL_texture( "wall02.jpg",
                          SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y );
    
    textures[7] =
    SOIL_load_OGL_texture( "wall03.jpg",
                          SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y );
	textures[8] =
		SOIL_load_OGL_texture("wall04.jpg",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    
}

// -----------------------------------------------------------------------------
//
void Building::build(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, double h,
                     double height, int key, int r, bool shade) {
    
    buildPave(p0, p1, p2, p3, h, shade);
    
    switch(key) {
        case 1: {
            buildBasic(p0, p1, p2, p3, h, height, r, shade);
            break;
        }
        case 2: {
            buildBasic(p0, p1, p2, p3, h, height, r, shade);
        }
        default: {
            buildBasic(p0, p1, p2, p3, h, height, r, shade);
            break;
        }
    }
}

// -----------------------------------------------------------------------------
//
void Building::buildPave(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3,
                         double h, bool shade) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
	if (shade)
		Globals::texShader->bind();
	else
		Globals::texShader->unbind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBegin(GL_QUADS);
    // TOP
    Vector3 nTop = calcNorm(Vector3(p0.getX(), h, p0.getZ()),
                            Vector3(p1.getX(), h, p0.getZ()),
                            Vector3(p3.getX(), h, p3.getZ())
                            );
    
    //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
    glNormal3d(nTop.getX(), nTop.getY(), nTop.getZ());
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(p0.getX(), h, p0.getZ());
    
    
    //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
    glTexCoord2f(8.0f, 0.0f);
    glVertex3d(p1.getX(), h, p1.getZ());
    
    
    //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
    glTexCoord2f(8.0f, 8.0f);
    glVertex3d(p2.getX(), h, p2.getZ());
    
    
    //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
    glTexCoord2f(0.0f, 8.0f);
    glVertex3d(p3.getX(), h, p3.getZ());
    
    
    // FRONT
    Vector3 nFront = calcNorm(p2, p3,
                              Vector3(p2.getX(), h, p2.getZ())
                              );
    //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
    glNormal3d(nFront.getX(), nFront.getY(), nFront.getZ());
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(p2.getX(),
               p2.getY(),
               p2.getZ());
    
    
    //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
    glTexCoord2f(4.0f, 0.0f);
    glVertex3d(p3.getX(), p3.getY(),
               p3.getZ());
    
    
    //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
    glTexCoord2f(4.0f, 4.0f);
    glVertex3d(p3.getX(), h, p3.getZ());
    
    
    //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
    glTexCoord2f(0.0f, 4.0f);
    glVertex3d(p2.getX(),
               h,
               p2.getZ());
    
    
    // BACK
    Vector3 nBack = calcNorm(p0, p1,
                             Vector3(p0.getX(), h, p0.getZ())
                             );
    //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
    glNormal3d(nBack.getX(), nBack.getY(), nBack.getZ());
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(p0.getX(), p0.getY(),
               p0.getZ());
    
    
    //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
    glTexCoord2f(4.0f, 0.0f);
    glVertex3d(p1.getX(), p1.getY(),
               p1.getZ());
    
    
    //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
    glTexCoord2f(4.0f, 4.0f);
    glVertex3d(p1.getX(), h, p1.getZ());
    
    
    //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
    glTexCoord2f(0.0f, 4.0f);
    glVertex3d(p0.getX(), h, p0.getZ());
    
    
    // RIGHT
    Vector3 nRight = calcNorm(p1, p2,
                              Vector3(p1.getX(), h, p1.getZ())
                              );
    //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
    glNormal3d(nRight.getX(), nRight.getY(), nRight.getZ());
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(p1.getX(), p1.getY(),
               p1.getZ());
    
    
    //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
    glTexCoord2f(4.0f, 0.0f);
    glVertex3d(p2.getX(),
               p2.getY(),
               p2.getZ());
    
    
    //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
    glTexCoord2f(4.0f, 4.0f);
    glVertex3d(p2.getX(),
               h,
               p2.getZ());
    
    
    //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
    glTexCoord2f(0.0f, 4.0f);
    glVertex3d(p1.getX(), h, p1.getZ());
    
    
    // LEFT
    Vector3 nLeft = calcNorm(p3, p0,
                             Vector3(p3.getX(), h, p3.getZ()));
    
    //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
    glNormal3d(nLeft.getX(), nLeft.getY(), nLeft.getZ());
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(p3.getX(), p3.getY(),
               p3.getZ());
    
    
    //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
    glTexCoord2f(4.0f, 0.0f);
    glVertex3d(p0.getX(), p0.getY(),
               p0.getZ());
    
    
    //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
    glTexCoord2f(4.0f, 4.0f);
    glVertex3d(p0.getX(), h, p0.getZ());
    
    
    //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
    glTexCoord2f(0.0f, 4.0f);
    glVertex3d(p3.getX(), h, p3.getZ());
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
}


// -----------------------------------------------------------------------------
//
void Building::buildBasic(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3,
                         double h, double height, int r, bool shade) {
    
    // Caculates the pavement width
    double diffX = (abs(v0.getX() - v1.getX())/2.0) * 0.05;
    double diffZ = (abs(v0.getZ() - v3.getZ())/2.0) * 0.05;
    
    
    // New points based on pavement height
    Vector3 p0 = Vector3(v0.getX() + diffX,
                         h, v0.getZ() - diffZ);
    
    Vector3 p1 = Vector3(v1.getX() - diffX,
                         h, v1.getZ() - diffZ);
    
    Vector3 p2 = Vector3(v2.getX() - diffX,
                         h, v2.getZ() + diffZ);
    
    Vector3 p3 = Vector3(v3.getX() + diffX,
                         h, v3.getZ() + diffZ);
    
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
	if (shade)
		Globals::texShader->bind();
	else
		Globals::texShader->unbind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBegin(GL_QUADS);
    // TOP   -------------------------------------------------------- =
    Vector3 nTop = calcNorm(Vector3(p0.getX(), h+height, p0.getZ()),
                            Vector3(p1.getX(), h+height, p1.getZ()),
                            Vector3(p3.getX(), h+height, p3.getZ())
                            );
    
    //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
    glNormal3d(nTop.getX(), nTop.getY(), nTop.getZ());
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(p0.getX(), h+height, p0.getZ());
    
    
    //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
    glTexCoord2f(6.0f, 0.0f);
    glVertex3d(p1.getX(), h+height, p1.getZ());
    
    
    //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
    glTexCoord2f(6.0f, 6.0f);
    glVertex3d(p2.getX(), h+height, p2.getZ());
    
    
    //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
    glTexCoord2f(0.0f, 6.0f);
    glVertex3d(p3.getX(), h+height, p3.getZ());
    
    glEnd();
    
	if (r == 0) {
		glBindTexture(GL_TEXTURE_2D, textures[4]);
		glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
		if (shade)
			Globals::texShader->bind();
		else
			Globals::texShader->unbind();
    }
	if (r == 1) {
		glBindTexture(GL_TEXTURE_2D, textures[6]);
		glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
		if (shade)
			Globals::texShader->bind();
		else
			Globals::texShader->unbind();
    }
	if (r == 2) {
		glBindTexture(GL_TEXTURE_2D, textures[7]);
		glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
		if (shade)
			Globals::texShader->bind();
		else
			Globals::texShader->unbind();
    }
	if (r == 3) {
		glBindTexture(GL_TEXTURE_2D, textures[8]);
		glUniform1i(glGetUniformLocation(Globals::texShader->getPid(), "texture"), 0);
		if (shade)
			Globals::texShader->bind();
		else
			Globals::texShader->unbind();
	}
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBegin(GL_QUADS);
    
    // FRONT -------------------------------------------------------- =
    Vector3 nFront = calcNorm(p2, p3,
                              Vector3(p2.getX(), h+height, p2.getZ())
                              );
    //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
    glNormal3d(nFront.getX(), nFront.getY(), nFront.getZ());
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(p2.getX(), h, p2.getZ());
    
    
    //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
    glTexCoord2f(6.0f, 0.0f);
    glVertex3d(p3.getX(), h, p3.getZ());
    
    
    //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
    glTexCoord2f(6.0f, 6.0f);
    glVertex3d(p3.getX(), h+height, p3.getZ());
    
    
    //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
    glTexCoord2f(0.0f, 6.0f);
    glVertex3d(p2.getX(), h+height, p2.getZ());
    
    
    // BACK -------------------------------------------------------- =
    Vector3 nBack = calcNorm(p0, p1,
                             Vector3(p0.getX(), h+height, p0.getZ())
                             );
    //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
    glNormal3d(nBack.getX(), nBack.getY(), nBack.getZ());
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(p0.getX(), h, p0.getZ());
    
    
    //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
    glTexCoord2f(6.0f, 0.0f);
    glVertex3d(p1.getX(), h, p1.getZ());
    
    
    //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
    glTexCoord2f(6.0f, 6.0f);
    glVertex3d(p1.getX(), h+height, p1.getZ());
    
    
    //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
    glTexCoord2f(0.0f, 6.0f);
    glVertex3d(p0.getX(), h+height, p0.getZ());
    
    
    // RIGHT -------------------------------------------------------- =
    Vector3 nRight = calcNorm(p1, p2,
                              Vector3(p1.getX(), h, p1.getZ())
                              );
    //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
    glNormal3d(nRight.getX(), nRight.getY(), nRight.getZ());
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(p1.getX(), h, p1.getZ());
    
    
    //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
    glTexCoord2f(6.0f, 0.0f);
    glVertex3d(p2.getX(), h, p2.getZ());
    
    
    //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
    glTexCoord2f(6.0f, 6.0f);
    glVertex3d(p2.getX(), h+height, p2.getZ());
    
    
    //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
    glTexCoord2f(0.0f, 8.0f);
    glVertex3d(p1.getX(), h+height, p1.getZ());
    
    
    // LEFT  -------------------------------------------------------- =
    Vector3 nLeft = calcNorm(p3, p0,
                             Vector3(p3.getX(), h+height, p3.getZ()));
    
    //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
    glNormal3d(nLeft.getX(), nLeft.getY(), nLeft.getZ());
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(p3.getX(), h, p3.getZ());
    
    
    //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
    glTexCoord2f(6.0f, 0.0f);
    glVertex3d(p0.getX(), h, p0.getZ());
    
    
    //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
    glTexCoord2f(6.0f, 6.0f);
    glVertex3d(p0.getX(), h+height, p0.getZ());
    
    
    //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
    glTexCoord2f(0.0f, 6.0f);
    glVertex3d(p3.getX(), h+height, p3.getZ());
    
    glEnd();
	Globals::texShader->unbind();
    glDisable(GL_TEXTURE_2D);

}


// -----------------------------------------------------------------------------
// Builds bounding box for entire map
void Building::buildBound(Vector3 v0, Vector3 v1, Vector3 v2, Vector3 v3,
                          double h, double height, bool shade) {
    
    double y = h + height;
    double x = abs(v0.getX() - v1.getX());
    double z = abs(v0.getZ() - v3.getZ());
    double diffX = (v0.getX() + v1.getX())/2.0;
    double diffZ = (v0.getZ() + v3.getZ())/2.0;
    double diffY = y / 2.0;
    
    //cerr << "CENTER: " << diffX << ", " << diffZ << endl;
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glPushMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
    glTranslatef(diffX, diffY, diffZ);
    glScalef(x + 0.1, y + 0.1, z + 0.1);
    glutSolidCube(1);
    glPopMatrix();
    
    glDisable(GL_BLEND);
    
}


// -----------------------------------------------------------------------------
// Found from StackOverflow
double Building::fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


// -----------------------------------------------------------------------------
// Calculates normal of a face
Vector3 Building::calcNorm(Vector3 p0, Vector3 p1, Vector3 p2) {
    Vector3 pA = Vector3(p1.getX() - p0.getX(),
                         p1.getY() - p0.getY(),
                         p1.getZ() - p0.getZ());
    
    Vector3 pB = Vector3(p2.getX() - p0.getX(),
                         p2.getY() - p0.getY(),
                         p2.getZ() - p0.getZ());
    
    pA.normalize();
    pB.normalize();
    
    Vector3 tangent;
    tangent = tangent.cross(pA, pB);
    
    return Vector3(tangent.getX(), tangent.getY(), tangent.getZ());
}
