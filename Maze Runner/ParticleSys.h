#ifndef _PARTICLESYS_H_
#define _PARTICLESYS_H_

#include "Vector3.h"
#include <algorithm>
#include <math.h>
#include <GL/glut.h>
#define maxParticles 1000

class ParticleSys{
protected:
	struct Particle{
		//Vector3 pos, speed, targetSpeed;
		double pos_X, pos_Y, pos_Z;
		double speed_X, speed_Y, speed_Z;
		double targetSpeed_X, targetSpeed_Y, targetSpeed_Z;
		float r, g, b, a;
		double size;
		int life;
		bool alive;
		int bounce;
	}particleContainer[maxParticles];
    
    Vector3 colors[8];
    double pos_x;
    double pos_y;
    double pos_z;
public:
	ParticleSys();
	virtual ~ParticleSys();

	void init();
    void init(double, double, double);
	void wake();
	void update();
	void render();
    
    void relocate(double, double, double);
	
};

#endif