#include <stdlib.h>
#include <math.h>
#include <cmath>
#include "City.h"

#define MAX_HEIGHT 25.0
#define MIN_HEIGHT 3.0


using namespace std;

static const double dist[] = {-100.0, -84.0, -76.0, -44.0, -36.0, -4.0,
                                4.0,   36.0,  44.0,  76.0,  84.0, 100.0};


// MAZE ONE MAP
static const int map01[11][11] = {
  {0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0},
  {3, 0, 3, 3, 3, 3, 3, 0, 3, 3, 0},
  {0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0},
  {3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0},
  {0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0},
  {0, 3, 3, 3, 3, 1, 3, 3, 0, 3, 0},
  {0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0},
  {3, 0, 3, 3, 3, 3, 3, 3, 0, 3, 0},
  {0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0},
  {3, 0, 3, 3, 3, 3, 0, 3, 3, 3, 0},
  {0, 3, 0, 0, 0, 2, 0, 0, 0, 0, 0}
};

// MAZE ONE INV MAP
static const int mapI01[11][11] = {
  {0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0},
  {0, 3, 3, 0, 3, 3, 3, 3, 3, 0, 3},
  {0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0},
  {0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3},
  {0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0},
  {0, 3, 0, 3, 3, 1, 3, 3, 3, 3, 0},
  {0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0},
  {0, 3, 0, 3, 3, 3, 3, 3, 3, 0, 3},
  {0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0},
  {0, 3, 3, 3, 0, 3, 3, 3, 3, 0, 3},
  {0, 0, 0, 0, 0, 2, 0, 0, 0, 3, 0}
};


// MAZE TWO MAP
static const int map02[11][11] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {2, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0},
  {0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0},
  {0, 3, 3, 3, 0, 3, 3, 3, 0, 3, 0},
  {0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0},
  {0, 3, 3, 0, 3, 1, 0, 3, 3, 3, 0},
  {0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0},
  {0, 3, 3, 3, 0, 3, 3, 0, 3, 3, 0},
  {0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0},
  {3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0},
  {0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

// MAZE TWO INV MAP
static const int mapI02[11][11] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 2 },
		{ 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0 },
		{ 0, 3, 0, 3, 3, 3, 0, 3, 3, 3, 0 },
		{ 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0 },
		{ 0, 3, 3, 3, 0, 1, 3, 0, 3, 3, 0 },
		{ 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0 },
		{ 0, 3, 3, 0, 3, 3, 0, 3, 3, 3, 0 },
		{ 0, 3, 0, 3, 0, 0, 0, 3, 0, 3, 0 },
		{ 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0 }
};

// BASE MAP
static const int map_basic[11][11] = {
  {0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0},
  {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
  {0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0},
  {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
  {0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0},
  {3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3},
  {0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0},
  {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
  {0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0},
  {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
  {0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0}
};


// CONSTRUCTOR
City::City() {
    color = Vector3(1.0, 1.0, 1.0);
	paveHeight = 0.1;
    mapID = 0;
    bounding = false;
    highest = 0.0;
    loadTexture();
    construct = Building();
    setUp();
  
}

City::City(string s, int map) {
	color = Vector3(1.0, 1.0, 1.0);

	paveHeight = 0.1;
	setName(s);
	bounding = false;
	highest = 0.0;
	loadTexture();
	construct = Building();
	setUp();

}
City::City(string s, Material* mat, int map) {
    color = Vector3(1.0, 1.0, 1.0);
    
	paveHeight = 0.1;
    setName(s);
    material = mat;
    mapID = map;
    bounding = false;
    highest = 0.0;
    loadTexture();
    construct = Building();
    setUp();
  
}


// -----------------------------------------------------------------------------
// DESTRUCTOR
City::~City() {
}


// -----------------------------------------------------------------------------
// SETS BASE COLOR
void City::setColor(double r, double g, double b) {
    color.set(r,g,b);
}


// GETS COLOR OF OVERALL CITY OBJECT
double City::getColor(int pos) {
    // GETS RED
    if( pos == 1 ) {
        return color.getX();
    }
    // GETS BLUE
    if ( pos == 2 ) {
        return color.getY();
    }
    // GETS GREEN
    if( pos == 3 ) {
        return color.getZ();
    }
    return (-1.0);
}


// -----------------------------------------------------------------------------
// SETS MATERIAL
void City::setMaterial(Material* mat) {
    material = mat;
}


// -----------------------------------------------------------------------------
// Sets the Bounding boolean
void City::setBound(bool b) {
  bounding = b;
}


// -----------------------------------------------------------------------------
// Switches the bounding boolean between true and false
void City::toggleBound() {
  bounding = !bounding;
}


// -----------------------------------------------------------------------------
// Returns value of bounding boolean
bool City::isBound() {
  return bounding;
}


// -----------------------------------------------------------------------------
// SETS THE BASIC LAYOUT OF THE MAP
void City::setMap(int m) {
  // BASIC MAP
  if( m == 0 ) {
    mapID = 0;
  }
  // MAP 1
  if( m == 1 ) {
    mapID = 1;
  }
  // MAP 2
  if( m == 2 ) {
    mapID = 2;
  }
}


// -----------------------------------------------------------------------------
// SETS THE BASIC LAYOUT OF THE MAP
int City::getMap() {
  return mapID;
}


// -----------------------------------------------------------------------------
// GETS X POSITION OF WINNING LOCATION
double City::getWinX(int x) {
  switch (x) {
    // BASE MAP
    case 0: {
      return 0.0;
      break;
    }
    // MAP 1
    case 1: {
      return 92.0;
      break;
    }
    // MAP 2
    case 2: {
      return (-80.0);
      break;
    }
    // ANYTHING ELSE
    default:
      return 0.0;
      break;
  }
  return 0.0;
}


// -----------------------------------------------------------------------------
// GETS Z POSITION OF WINNING LOCATION
double City::getWinZ(int z) {
  switch (z) {
    // BASE MAP
    case 0: {
      return 0.0;
      break;
    }
    // MAP 1
    case 1: {
      return 0.0;
      break;
    }
    // MAP 2
    case 2: {
      return 92.0;
      break;
    }
    // ANYTHING ELSE
    default:
      return 0.0;
      break;
  }
  return 0.0;
}


// -----------------------------------------------------------------------------
// SETS UP MAP
void City::setUp() {
  
  // calculates a random height variable and number of buildings per spot
  for(int row = 0; row < 11; row++ ) {
    for( int col = 0; col < 11; col++) {
      height[row][col] = fRand(MIN_HEIGHT, MAX_HEIGHT);
      
      if( height[row][col] > highest ) {
        highest = height[row][col];
      }
      
      tex[row][col] = rand() % 4;
      
      if( row == 0 || row == 10 ) {
        if( col == 0 || col == 10 ) {
          numOfBuild[row][col] = 1;
        }
        else {
          numOfBuild[row][col] = (rand() % 2) + 1;
        }
      }
      else {
        numOfBuild[row][col] = (rand() % 2) + 3;
      }
    }
  }
  
  
  // Iterators for the actual point map
  int x = 0;
  int z = 0;
  
  // Iterators through the dist array
  for(int i = 0; i < 12; i++) {
    for(int j = 11; j >= 0; j--) {
      
      // Inserts a point into the point array
      points[x][z] = Vector3( dist[i], 0.0, dist[j]);
      
      z++;
    }
    x++;
    z = 0;
  }


}


// -----------------------------------------------------------------------------
//
void City::loadTexture() {
  
	// STREETS -------------------------------------------------------------- ==
	// Vertical Streets
	textures[0] =
		SOIL_load_OGL_texture("road_01.jpg",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	// Horizontal Streets
	textures[1] =
		SOIL_load_OGL_texture("road_02.jpg",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	// Intersections
	textures[2] =
		SOIL_load_OGL_texture("road_03.jpg",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
  
}

// -----------------------------------------------------------------------------
//
void City::render(Matrix4 C, bool shade) {
    // If there is a material, update
    if( material != nullptr ) {
        material->update();
    }
  
    for(int i = 0; i < 11; i++) {
        for( int j = 0; j < 11; j++) {
      
          if( (mapID == 0 && map_basic[i][j] == 0) ||
              (mapID == 1 && map01[i][j] == 0) ||
              (mapID == 2 && map02[i][j] == 0) ) {
            build(i, j, shade);
          }
          
          glEnable(GL_TEXTURE_2D);
          if( i % 2 == 0 ) {
            glBindTexture(GL_TEXTURE_2D, textures[1]);
          }
          else {
            if( j % 2 == 1 ) {
              glBindTexture(GL_TEXTURE_2D, textures[2]);
            }
            else {
              glBindTexture(GL_TEXTURE_2D, textures[0]);
            }
          }
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

          glBegin(GL_QUADS);
            
            Vector3 normal = calcNorm(points[i][j], points[i+1][j],
                                      points[i][j+1]);
            
            //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
            //glColor3d((86.0/256.0), (69.0/256.0), (35.0/256.0));
            glNormal3d(normal.getX(), normal.getY(), normal.getZ());
            glTexCoord2f(0.0f, 0.0f);
            glVertex3d(points[i][j].getX(), points[i][j].getY(),
                       points[i][j].getZ());
          
          
            //glColor3d((176.0/256.0), (115.0/256.0), (90.0/256.0));
            glTexCoord2f(1.0f, 0.0f);
            glVertex3d(points[i+1][j].getX(), points[i+1][j].getY(),
                       points[i+1][j].getZ());
          
          
            //glColor3d((103.0/256.0), (69.0/256.0), (35.0/256.0));
            glTexCoord2f(1.0f, 1.0f);
            glVertex3d(points[i+1][j+1].getX(),
                       points[i+1][j+1].getY(),
                       points[i+1][j+1].getZ());
            
            
            //glColor3d((18.0/256.0), (18.0/256.0), (18.0/256.0));
            glTexCoord2f(0.0f, 1.0f);
            glVertex3d(points[i][j+1].getX(), points[i][j+1].getY(),
                       points[i][j+1].getZ());
          glEnd();
          }
        }
    //glEnd();

    //if (glGetError() != GL_NO_ERROR) {
       // cerr << "GL error" << endl;
  //  }
  
}


// -----------------------------------------------------------------------------
// Builds a building
void City::build(int i, int j, bool shade) {
  
  construct.build(points[i][j], points[i+1][j], points[i+1][j+1],
                  points[i][j+1], paveHeight, height[i][j], numOfBuild[i][j],
                  tex[i][j], shade);
  if( bounding ) {
    buildBound();
    construct.buildBound(points[i][j], points[i+1][j], points[i+1][j+1],
                       points[i][j+1], paveHeight, height[i][j], shade);
  }
  
}

// -----------------------------------------------------------------------------
// BUILDS BOUNDING BOX FOR EACH BUILDING
void City::buildBound() {
  double y = paveHeight + highest;
  //double x = abs(points[0][0].getX() - points[0][11].getX());
  //double z = abs(v0.getZ() - v3.getZ());
  //double diffX = (v0.getX() + v1.getX())/2.0;
  //double diffZ = (v0.getZ() + v3.getZ())/2.0;
  double diffY = y / 2.0;
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glPushMatrix();
  glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
  glTranslatef(0, diffY, 0);
 //glScalef(200.1, y + 0.2, 200.1);
  glScalef(200.1, 200.0, 200.1);
  glutSolidCube(1);
  glPopMatrix();
  
  glDisable(GL_BLEND);
  
}

bool City::checkWin(Vector3 c) {
	int xb1 = 0;
	int xb2 = 0;
	int zb1 = 0;
	int zb2 = 0;
	double xC = c.getX();
	double zC = c.getZ();

	// Locates which Row the character is in
	if (xC > 0) {
		for (int i = 11; i >= 0; i--) {
			if (dist[i] > xC) {
				xb2 = i;
			}
			else {
				xb1 = i;
				break;
			}
		}
	}
	else {
		for (int i = 0; i < 12; i++) {
			if (dist[i] < xC) {
				xb1 = i;
			}
			else {
				xb2 = i;
				break;
			}
		}
	}

	// Locates which Column the character is in
	if (c.getZ() > 0) {
		for (int j = 11; j >= 0; j--) {
			if (dist[j] > zC) {
				zb1 = j;
			}
			else {
				zb2 = j;
				break;
			}
		}
	}
	else {
		for (int j = 0; j < 12; j++) {
			if (dist[j] < zC) {
				zb2 = j;
			}
			else {
				zb1 = j;
				break;
			}
		}
	}

	if ((mapID == 1 && mapI01[xb1][zb2] == 2) ||
		(mapID == 2 && mapI02[xb1][zb2] == 2)) {
		return true;
	}

	return false;
}


// -----------------------------------------------------------------------------
// BUILDS BOUNDING BOX FOR EACH BUILDING
bool City::checkBound(Vector3 c) {
  int xb1 = 0;
  int xb2 = 0;
  int zb1 = 0;
  int zb2 = 0;
  double x = 2.0;
  double z = 1.1;
  
  double xC = c.getX();
  double zC = c.getZ();
  
  double fxC = xC + x;
  double fzC = zC + z;
  double bxC = xC - x;
  double bzC = zC - z;
  
  // OUT OF BOUNDS CHECK
  if( ((fxC + x) > 100.0) ||
      ((bxC - x)  < (-100.0))) {
    //cerr << "OUT OF BOUNDS" << endl;
    return true;
  }
  
  if( ((fzC + z) > 100.0) ||
      ((bzC - z) < (-100.0))) {
    //cerr << "OUT OF BOUNDS" << endl;
    return true;
  }
  
  // Locates which Row the character is in
  if( xC > 0 ) {
    for(int i = 11; i >= 0; i-- ) {
      if(dist[i] > xC) {
        xb2 = i;
      }
      else {
        xb1 = i;
        break;
      }
    }
  }
  else {
    for(int i = 0; i < 12; i++ ) {
      if(dist[i] < xC ) {
        xb1 = i;
      }
      else {
        xb2 = i;
        break;
      }
    }
  }
  
  // Locates which Column the character is in
  if( c.getZ() > 0 ) {
    for(int j = 11; j >= 0; j-- ) {
      if(dist[j] > zC) {
        zb1 = j;
      }
      else {
        zb2 = j;
        break;
      }
    }
  }
  else {
    for(int j = 0; j < 12; j++ ) {
      if(dist[j] < zC ) {
        zb2 = j;
      }
      else {
        zb1 = j;
        break;
      }
    }
  }
  
  for(int d = 0; d < 90; d++) {
    double angle = (double)d / 180.0 * M_PI;
    double offset = x * sin(angle);
    
    double x1 = c.getX() + offset;
    double x2 = c.getX() - offset;
    //double z1 = c.getZ() + offset;
    //double z2 = c.getZ() - offset;
    
    if( x1 > dist[xb2]) {
      if( xb2 == 10 ) {
        if( xC > dist[xb2] ) {
          //cerr << "WILL BE OUT OF BOUNDS: x1" << endl;
          return true;
        }
        else {
          return false;
        }
      }
      else {
        if(( mapID == 0 && map_basic[xb2][zb2] == 0 )||
          ( mapID == 1 && mapI01[xb2][zb2] == 0 ) ||
          ( mapID == 2 && mapI02[xb2][zb2] == 0 )) {
          //cerr << "WILL BE MAPPED OUT OF BOUNDS: x1" << endl;
          return true;
          
        }
      }
    }
  
    if( x2 < dist[xb1]) {
      if( xb1 == 0 ) {
        if( xC < dist[xb1]) {
          //cerr << "WILL BE OUT OF BOUNDS: x2" << endl;
          return true;
        }
        else {
          return false;
        }
      }
      else {
        if(( mapID == 0 && map_basic[xb1 - 1][zb2] == 0 )||
           ( mapID == 1 && mapI01[xb1 - 1][zb2] == 0 ) ||
           ( mapID == 2 && mapI02[xb1 - 1][zb2] == 0 )) {
          //cerr << "WILL BE MAPPED OUT OF BOUNDS: x2" << endl;
          return true;
          
        }
      }
    }
    
    /*if( z2 < dist[zb1]) {
      if( zb1 == 10 ) {
        cerr << "WILL BE OUT OF BOUNDS: z2" << endl;
        return true;
      }
      else {
        if(( mapID == 0 && map_basic[xb1][zb1] == 0 )||
           ( mapID == 1 && mapI01[xb1][zb1] == 0 ) ||
           ( mapID == 2 && map02[xb1][zb1] == 0 )) {
          cerr << "Z2: " << z2 << " at " << dist[zb1] << endl;
          cerr << "WILL BE MAPPED OUT OF BOUNDS: z2" << endl;
          return true;
          
        }
      }
    }
    
    if( z1 > dist[zb2]) {
      if( zb2 == 0 ) {
        cerr << "WILL BE OUT OF BOUNDS: z1" << endl;
        return true;
      }
      else {
        if(( mapID == 0 && map_basic[xb1][zb2 - 1] == 0 )||
           ( mapID == 1 && mapI01[xb1][zb2 - 1] == 0 ) ||
           ( mapID == 2 && map02[xb1][zb2 - 1] == 0 )) {
          cerr << "WILL BE MAPPED OUT OF BOUNDS: z1" << endl;
          return true;
          
        }
      }
    }*/
  }
  
  //cerr << "DOOP" << zb2 << ", " << zb1 << endl;
  //cerr << "CURRENT IN BOX: " << xb1 << ", " << zb2 << endl;
  
  if(( mapID == 0 && map_basic[xb1][zb2] == 0 )||
     ( mapID == 1 && mapI01[xb1][zb2] == 0 ) ||
     ( mapID == 2 && mapI02[xb1][zb2] == 0 )) {
    return true;
    
  }
  
  return false;
}


// -----------------------------------------------------------------------------
// BUILDS FOUNDATION/PAVEMENT
/*void City::build_Pave(int i, int j, double h) {
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textures[3]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  glBegin(GL_QUADS);
  // TOP
  Vector3 nTop = calcNorm(Vector3(points[i][j].getX(), h, points[i][j].getZ()),
                          Vector3(points[i+1][j].getX(), h, points[i][j].getZ()),
                          Vector3(points[i][j+1].getX(), h, points[i][j+1].getZ())
                          );
  
  //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
  glNormal3d(nTop.getX(), nTop.getY(), nTop.getZ());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(points[i][j].getX(), h, points[i][j].getZ());
  
  
  //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
  glTexCoord2f(8.0f, 0.0f);
  glVertex3d(points[i+1][j].getX(), h, points[i+1][j].getZ());
  
  
  //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
  glTexCoord2f(8.0f, 8.0f);
  glVertex3d(points[i+1][j+1].getX(), h, points[i+1][j+1].getZ());
  
  
  //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
  glTexCoord2f(0.0f, 8.0f);
  glVertex3d(points[i][j+1].getX(), h, points[i][j+1].getZ());
  
  
  // FRONT
  Vector3 nFront = calcNorm(points[i+1][j+1], points[i][j+1],
                            Vector3(points[i+1][j+1].getX(), h, points[i+1][j+1].getZ())
                            );
  //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
  glNormal3d(nFront.getX(), nFront.getY(), nFront.getZ());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(points[i+1][j+1].getX(),
             points[i+1][j+1].getY(),
             points[i+1][j+1].getZ());
  
  
  //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
  glTexCoord2f(8.0f, 0.0f);
  glVertex3d(points[i][j+1].getX(), points[i][j+1].getY(),
             points[i][j+1].getZ());
  
  
  //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
  glTexCoord2f(8.0f, 8.0f);
  glVertex3d(points[i][j+1].getX(), h, points[i][j+1].getZ());
  
  
  //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
  glTexCoord2f(0.0f, 8.0f);
  glVertex3d(points[i+1][j+1].getX(),
             h,
             points[i+1][j+1].getZ());
  
  
  // BACK
  Vector3 nBack = calcNorm(points[i][j], points[i+1][j],
                           Vector3(points[i][j].getX(), h, points[i][j].getZ())
                           );
  //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
  glNormal3d(nBack.getX(), nBack.getY(), nBack.getZ());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(points[i][j].getX(), points[i][j].getY(),
             points[i][j].getZ());
  
  
  //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
  glTexCoord2f(8.0f, 0.0f);
  glVertex3d(points[i+1][j].getX(), points[i+1][j].getY(),
             points[i+1][j].getZ());
  
  
  //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
  glTexCoord2f(8.0f, 8.0f);
  glVertex3d(points[i+1][j].getX(), h, points[i+1][j].getZ());
  
  
  //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
  glTexCoord2f(0.0f, 8.0f);
  glVertex3d(points[i][j].getX(), h, points[i][j].getZ());
  
  
  // RIGHT
  Vector3 nRight = calcNorm(points[i+1][j], points[i+1][j+1],
                            Vector3(points[i+1][j].getX(), h, points[i+1][j].getZ())
                            );
  //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
  glNormal3d(nRight.getX(), nRight.getY(), nRight.getZ());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(points[i+1][j].getX(), points[i+1][j].getY(),
             points[i+1][j].getZ());
  
  
  //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
  glTexCoord2f(8.0f, 0.0f);
  glVertex3d(points[i+1][j+1].getX(),
             points[i+1][j+1].getY(),
             points[i+1][j+1].getZ());
  
  
  //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
  glTexCoord2f(8.0f, 8.0f);
  glVertex3d(points[i+1][j+1].getX(),
             h,
             points[i+1][j+1].getZ());
  
  
  //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
  glTexCoord2f(0.0f, 8.0f);
  glVertex3d(points[i+1][j].getX(), h, points[i+1][j].getZ());
  
  
  // LEFT
  Vector3 nLeft = calcNorm(points[i][j+1], points[i][j],
                           Vector3(points[i][j+1].getX(), h, points[i][j+1].getZ()));
  
  //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
  glNormal3d(nLeft.getX(), nLeft.getY(), nLeft.getZ());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(points[i][j+1].getX(), points[i][j+1].getY(),
             points[i][j+1].getZ());
  
  
  //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
  glTexCoord2f(8.0f, 0.0f);
  glVertex3d(points[i][j].getX(), points[i][j].getY(),
             points[i][j].getZ());
  
  
  //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
  glTexCoord2f(8.0f, 8.0f);
  glVertex3d(points[i][j].getX(), h, points[i][j].getZ());
  
  
  //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
  glTexCoord2f(0.0f, 8.0f);
  glVertex3d(points[i][j+1].getX(), h, points[i][j+1].getZ());
  
  glEnd();
  glDisable(GL_TEXTURE_2D);
}


// -----------------------------------------------------------------------------
// Basic single block building
void City::build01(int i, int j, double h) {
  
  double diffX = (abs(points[i][j].getX() - points[i+1][j].getX())/2.0) * 0.05;
  double diffZ = (abs(points[i][j].getZ() - points[i][j+1].getZ())/2.0) * 0.05;
  
  Vector3 p0 = Vector3(points[i][j].getX() + diffX,
                       h, points[i][j].getZ() - diffZ);
  
  Vector3 p1 = Vector3(points[i+1][j].getX() - diffX,
                       h, points[i+1][j].getZ() - diffZ);
  
  Vector3 p2 = Vector3(points[i+1][j+1].getX() - diffX,
                       h, points[i+1][j+1].getZ() + diffZ);
  
  Vector3 p3 = Vector3(points[i][j+1].getX() + diffX,
                       h, points[i][j+1].getZ() + diffZ);
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textures[5]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  glBegin(GL_QUADS);
  // TOP
  Vector3 nTop = calcNorm(Vector3(p0.getX(), h+height[i][j], p0.getZ()),
                          Vector3(p1.getX(), h+height[i][j], p1.getZ()),
                          Vector3(p3.getX(), h+height[i][j], p3.getZ())
                          );
  
  //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
  glNormal3d(nTop.getX(), nTop.getY(), nTop.getZ());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(p0.getX(), h+height[i][j], p0.getZ());
  
  
  //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
  glTexCoord2f(8.0f, 0.0f);
  glVertex3d(p1.getX(), h+height[i][j], p1.getZ());
  
  
  //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
  glTexCoord2f(8.0f, 8.0f);
  glVertex3d(p2.getX(), h+height[i][j], p2.getZ());
  
  
  //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
  glTexCoord2f(0.0f, 8.0f);
  glVertex3d(p3.getX(), h+height[i][j], p3.getZ());
  
  glEnd();
  
  glBindTexture(GL_TEXTURE_2D, textures[4]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glBegin(GL_QUADS);
  
  // FRONT
  Vector3 nFront = calcNorm(p2, p3,
                            Vector3(p2.getX(), h+height[i][j], p2.getZ())
                            );
  //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
  glNormal3d(nFront.getX(), nFront.getY(), nFront.getZ());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(p2.getX(), h, p2.getZ());
  
  
  //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
  glTexCoord2f(8.0f, 0.0f);
  glVertex3d(p3.getX(), h, p3.getZ());
  
  
  //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
  glTexCoord2f(8.0f, 8.0f);
  glVertex3d(p3.getX(), h+height[i][j], p3.getZ());
  
  
  //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
  glTexCoord2f(0.0f, 8.0f);
  glVertex3d(p2.getX(), h+height[i][j], p2.getZ());
  
  
  // BACK
  Vector3 nBack = calcNorm(p0, p1,
                           Vector3(p0.getX(), h+height[i][j], p0.getZ())
                           );
  //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
  glNormal3d(nBack.getX(), nBack.getY(), nBack.getZ());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(p0.getX(), h, p0.getZ());
  
  
  //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
  glTexCoord2f(8.0f, 0.0f);
  glVertex3d(p1.getX(), h, p1.getZ());
  
  
  //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
  glTexCoord2f(8.0f, 8.0f);
  glVertex3d(p1.getX(), h+height[i][j], p1.getZ());
  
  
  //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
  glTexCoord2f(0.0f, 8.0f);
  glVertex3d(p0.getX(), h+height[i][j], p0.getZ());
  
  
  // RIGHT
  Vector3 nRight = calcNorm(p1, p2,
                            Vector3(p1.getX(), h, p1.getZ())
                            );
  //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
  glNormal3d(nRight.getX(), nRight.getY(), nRight.getZ());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(p1.getX(), h, p1.getZ());
  
  
  //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
  glTexCoord2f(8.0f, 0.0f);
  glVertex3d(p2.getX(), h, p2.getZ());
  
  
  //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
  glTexCoord2f(8.0f, 8.0f);
  glVertex3d(p2.getX(), h+height[i][j], p2.getZ());
  
  
  //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
  glTexCoord2f(0.0f, 8.0f);
  glVertex3d(p1.getX(), h+height[i][j], p1.getZ());
  
  
  // LEFT
  Vector3 nLeft = calcNorm(p3, p0,
                           Vector3(p3.getX(), h+height[i][j], p3.getZ()));
  
  //glColor3d((170.0/256.0), (187.0/256.0), (221.0/256.0));
  glNormal3d(nLeft.getX(), nLeft.getY(), nLeft.getZ());
  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(p3.getX(), h, p3.getZ());
  
  
  //glColor3d((80.0/256.0), (141.0/256.0), (166.0/256.0));
  glTexCoord2f(8.0f, 0.0f);
  glVertex3d(p0.getX(), h, p0.getZ());
  
  
  //glColor3d((153.0/256.0), (187.0/256.0), (221.0/256.0));
  glTexCoord2f(8.0f, 8.0f);
  glVertex3d(p0.getX(), h+height[i][j], p0.getZ());
  
  
  //glColor3d((238.0/256.0), (238.0/256.0), (238.0/256.0));
  glTexCoord2f(0.0f, 8.0f);
  glVertex3d(p3.getX(), h+height[i][j], p3.getZ());
  
  glEnd();
  glDisable(GL_TEXTURE_2D);
}*/

// -----------------------------------------------------------------------------
// Adds height to pavement
void City::add() {
  paveHeight += 0.1;
}

// -----------------------------------------------------------------------------
// Subtracts height from pavement
void City::sub() {
  if( paveHeight > 0.1) {
    paveHeight -= 0.1;
  }
}


// -----------------------------------------------------------------------------
// REBUILDS CITY
void City::reset() {
  setUp();
}


// -----------------------------------------------------------------------------
// Found from StackOverflow
double City::fRand(double fMin, double fMax) {
  double f = (double)rand() / RAND_MAX;
  return fMin + f * (fMax - fMin);
}


// -----------------------------------------------------------------------------
// Calculates normal of a face
Vector3 City::calcNorm(Vector3 p0, Vector3 p1, Vector3 p2) {
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