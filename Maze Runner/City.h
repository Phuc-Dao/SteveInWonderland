#ifndef __CITY__
#define __CITY__
#include <string>

#include "Matrix4.h"
#include "Vector3.h"
#include "Material.h"
#include "Geode.h"
#include "Building.h"

#include "SOIL.h"


class City : public Geode {
protected:
    int mapID;                 // Map id
    Vector3 color;          // vector for color
    Material * material;    // Material of patch
    Building construct;
    bool bounding;       // Boolean for Bounding Box
    GLuint textures[3];
    double highest;     // tallest building
  
    
public:
  Vector3 points[12][12];  // points for patches
  int numOfBuild[11][11];  // figures out which build to call
  int tex[11][11];
  double height[11][11];   // Randomly generated heights
  double paveHeight;
  
    // Constructor
  City();
  City(string, int);
    City(string, Material*, int);
    
    // Deconstructor
    virtual ~City();
    
    // Color-related
    void setColor(double, double, double);
    double getColor(int);
    void setMaterial(Material*);
  
    // MAP
    void setMap(int);
    int getMap();
    double getWinX(int);
    double getWinZ(int);
  
    // BOUNDING BOX RELATED
    void setBound(bool);
    void toggleBound();
    bool isBound();
    bool checkBound(Vector3);
	bool checkWin(Vector3);
  
    // Set up and Render
    void setUp();
    void loadTexture();
    void render(Matrix4, bool);
  
    void build(int, int, bool);
  
    // BUILDINGS
    void buildBound();
    void build_Pave(int, int, double);
    void build01(int, int, double);
    void add();
    void sub();
  
    void reset();
    double fRand(double, double);
    Vector3 calcNorm(Vector3, Vector3, Vector3);
};

#endif