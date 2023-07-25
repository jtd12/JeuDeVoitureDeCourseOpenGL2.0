#ifndef DEF_CAR_AI_HPP
#define DEF_CAR_AI_HPP
#include"car.h"
#include"collision/collisionplane.h"
#include"collision/collisionsphere.h"
#include<vector>
#include<math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include<string>
#include"collision/collision.h"
#include<GL/freeglut.h>
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
        

const int num=8; //checkpoints
static int points[num][2] = {1000,1160,
                      5000,1160,
                      5050,1900,
					  -9250,1800,
					  -9250, -20,
					  -2700,-100,
					  -2700,1200,
					  -1500,1250};
   

class vehiculeAI
{
		public:
		vehiculeAI( unsigned int car_,const char* n,collisionsphere ccs, float sprints,float looks);
		~vehiculeAI();
		void ouvrirPorte1();
		void ouvrirPorte2();
		void update();
		void draw();
		void update(std::vector<collisionplane>& collplane);
		void update2(std::vector<collisionplane>& collplane);
		void setPosition(vector3d pos);
		void setLocation(vector3d vec);
		vector3d getLocation();
			void move();
			void setRotation(vector3d r);
			vector3d getRotation();
			void setLocationIncX(float y);
			void setLocationIncZ(float y);
			float setSpeed(float num);
		void setSpeed(float s,float speedJoy);
		float getSpeed();
		float getMaxSpeed();
		void findTarget();
		void setActif(bool b);
		bool getActif();
		void fermerPorte1();
		void fermerPorte2();
		int getA();
		void setA(int A);
		collisionsphere getCollisionSphere();
	std::vector<roue *> wheel;

	
		
	private:
	unsigned int car;
	collisionsphere cs;
	vector3d force;
	std::string name;
	vector3d direction;
	bool isground,iscollision, issprint,actif;
	float sprintspeed;
	float lookspeed;
	vector3d pos;
	float acc, dec,dec2;
	vector3d a;
	vector3d loc;
 	float angle;
	float turnSpeed;
	float speed;
	float maxSpeed;	
	float force_;
	float s;
	float rr,rr2;
	int nn;
	int randNumber;
	
};

#endif
