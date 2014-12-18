#include "ParticleSys.h"
#include <iostream>

ParticleSys::ParticleSys(){
}

void ParticleSys::init(){
	//particleContainer = new Particle[maxParticles];
	for (int i = 0; i < maxParticles; i++){
		particleContainer[i].alive = false; //Initiate all particles as dead. :P
		particleContainer[i].targetSpeed_X = 0.0;
		particleContainer[i].targetSpeed_Y = -0.1;
		particleContainer[i].targetSpeed_Z = 0.0;
        
        pos_x = 0;
        pos_y = 10;
        pos_z = 0;
	}
    
    // GOLD
    colors[0] = Vector3(1.0, 0.843137, 0.0);
    // ORANGE
    colors[1] = Vector3(1.0, 0.647059, 0.0);
    // LIGHT YELLOW
    /*colors[2] = Vector3(1.0, 1.0, (153.0/255));
    // PINK
    colors[3] = Vector3(1.0, (148.0/255.0), (184.0/255.0));
    // PALE FUSHIA
    colors[4] = Vector3((245.0/255.0), (204.0/255.0), (245.0/255.0));
    // What are you?
    colors[5] = Vector3((170.0/255.0), 60.0/255.0, 57.0/255.0);
    // DARK TEAL
    colors[6] = Vector3(69.0/255.0, 116.0/255.0, 133.0/255.0);
    // DARK VIOLET
    colors[7] = Vector3(94.0/255.0, 16.0/255.0, 74.0/255.0);*/
    
    
}


void ParticleSys::init(double x, double y, double z){
    //particleContainer = new Particle[maxParticles];
    for (int i = 0; i < maxParticles; i++){
        particleContainer[i].alive = false; //Initiate all particles as dead. :P
        particleContainer[i].targetSpeed_X = 0.0;
        particleContainer[i].targetSpeed_Y = -0.1;
        particleContainer[i].targetSpeed_Z = 0.0;
        
        pos_x = x;
        pos_y = y;
        pos_z = z;
        
    }
}


void ParticleSys::wake(){
	//int c;
    
    for (int i = 0; i < maxParticles; i++){
        //c = rand()%2;
        
        
        
		if (particleContainer[i].alive == false){
			//particleContainer[i].pos = Vector3(0, 0, 0);
			particleContainer[i].pos_X = pos_x;
			particleContainer[i].pos_Y = pos_y;
			particleContainer[i].pos_Z = pos_z;
            
            /*particleContainer[i].r = colors[c].getX();
            particleContainer[i].g = colors[c].getY();
            particleContainer[i].b = colors[c].getZ();*/
            
            
			/*double x = (((float)((rand() % 100) + 1)) /	1000.0f) - 0.05f;
			double y = (((float)((rand() % 100) + 50)) / 500.0f);
			double z = (((float)((rand() % 100) + 1)) / 1000.0f) - 0.05f;*/

			//cout << i << " " << x << endl;

			particleContainer[i].speed_X = (((double)((rand() % 100) + 1)) / 1000.0f) - 0.05f;
			particleContainer[i].speed_Y = -(((double)((rand() % 1000) + 50)) / 500.0f);
			particleContainer[i].speed_Z = (((double)((rand() % 100) + 1)) / 1000.0f) - 0.05f;
			//= Vector3(((rand() % 10 + 1) / 1000.0) - 0.05, ((rand() % 100 + 50) / 500.0), ((rand() % 100 + 1) / 1000.0) - 1.0);

			particleContainer[i].alive = true;
			particleContainer[i].life = 0;
			particleContainer[i].bounce = 0;
        
			return;
		}
	}
}

void ParticleSys::update(){
	for (int i = 0; i < maxParticles; i++){
		particleContainer[i].speed_X += (particleContainer[i].targetSpeed_X - particleContainer[i].speed_X) / 20.0;
		particleContainer[i].speed_Y += (particleContainer[i].targetSpeed_Y - particleContainer[i].speed_Y) / 20.0;
		particleContainer[i].speed_Z += (particleContainer[i].targetSpeed_Z - particleContainer[i].speed_Z) / 20.0;

		particleContainer[i].pos_X += particleContainer[i].speed_X;
		particleContainer[i].pos_Y += particleContainer[i].speed_Y;
		particleContainer[i].pos_Z += particleContainer[i].speed_Z;
		
		/*particleContainer[i].speed.setX(particleContainer[i].speed.getX() + (particleContainer[i].targetSpeed.getX() - particleContainer[i].speed.getX()) / 20.0);
		particleContainer[i].speed.setY(particleContainer[i].speed.getY() + (particleContainer[i].targetSpeed.getY() - particleContainer[i].speed.getY()) / 20.0);
		particleContainer[i].speed.setZ(particleContainer[i].speed.getZ() + (particleContainer[i].targetSpeed.getZ() - particleContainer[i].speed.getZ()) / 20.0);
		particleContainer[i].pos.setX(particleContainer[i].pos.getX() + particleContainer[i].speed.getX());
		particleContainer[i].pos.setY(particleContainer[i].pos.getY() + particleContainer[i].speed.getY());
		particleContainer[i].pos.setZ(particleContainer[i].pos.getZ() + particleContainer[i].speed.getZ());*/

		//cout << particleContainer[i].pos.getY() << endl;

		if (particleContainer[i].pos_Y < 0.0f){
			particleContainer[i].pos_Y = 0.0f;
			particleContainer[i].speed_Y = -particleContainer[i].speed_Y;
			particleContainer[i].bounce++;
			if (particleContainer[i].bounce > 3){
				particleContainer[i].alive = false;
			}
		}

		particleContainer[i].life++;

		if (particleContainer[i].life > 5000){
			particleContainer[i].alive = false;

		}
	}
}

void ParticleSys::render(){
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(10);
	glBegin(GL_POINTS);
	for (int i = 0; i < maxParticles; i++){
		if (particleContainer[i].alive){
				//cout << "ALIVE!" << endl;
            glColor4f(1.0, 0.843137, 0.0, 0.5);
            //glColor4f((170.0/256.0), (187.0/256.0), (221.0/256.0), 0.5);
            //glColor4f(particleContainer[i].r, particleContainer[i].g, particleContainer[i].b, 0.5);
			//glVertex3f(0.0, 0.0, 0.0);
			//cout << i << " " << particleContainer[i].pos.getY() << endl;

			glVertex3f(particleContainer[i].pos_X, particleContainer[i].pos_Y, particleContainer[i].pos_Z);
		}
	}
	glEnd();
    glDisable(GL_BLEND);
	/*glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glBegin(GL_POINTS);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();*/

	
}

ParticleSys::~ParticleSys(){
	//free(particleContainer);
}

void ParticleSys::relocate(double x, double y, double z) {
    //particleContainer = new Particle[maxParticles];
    for (int i = 0; i < maxParticles; i++){
        particleContainer[i].alive = false; //Initiate all particles as dead. :P
        particleContainer[i].targetSpeed_X = 0.0;
        particleContainer[i].targetSpeed_Y = -0.01;
        particleContainer[i].targetSpeed_Z = 0.0;
        
        pos_x = x;
        pos_y = y;
        pos_z = z;
        
    }
}