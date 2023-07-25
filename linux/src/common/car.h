#ifndef DEF_CAR_H
#define DEF_CAR_H
#include"objloader.hpp"
#include"collision/collisionplane.h"
#include"collision/collisionsphere.h"
#include<vector>
#include<math.h>
#include<string>
#include"particuleSystem.h"
#include"collision/collision.h"
#include<GL/freeglut.h>
#define ni 8
#define SPACEBAR 32

class roue
{
public:
		roue(const char * filename);
		~roue();
		void update();
		void draw();
		vector3d getRotation();
		void setRotationz(float m);
		void setRotationzegal(float m);
		void setRotationy(float m);
		void setRotationyegal(float m);
	private:
		objloader *obj;
		int roue_;	
		vector3d rot_roue;
};


class vehicule
{
	public:
		vehicule( const char* n,collisionsphere ccs, float sprints,float normals,float looks);
		~vehicule();
		void ouvrirPorte1();
		void ouvrirPorte2();
		void update();
		void draw();
		void update(std::vector<collisionplane>& collplane);
		void update2(std::vector<collisionplane>& collplane);
		void update3(std::vector<collisionplane>& collplane);
		void update4(std::vector<collisionplane>& collplane);
		void setPosition(vector3d pos);
		void setLocation(vector3d vec);
		vector3d getLocation();
		void setLocationIncX(float y);
		void setLocationIncZ(float y);
			void move();
			void setRotation(vector3d r);
			vector3d getRotation();
			int getUP();
			int getDOWN();
			int getRIGHT();
			int getLEFT();
			void setUP(int num);
			void setDOWN(int num);
			void setRIGHT(int num);
			void setLEFT(int num);
			float setSpeed(float num);
		void setSpeed(float s,float speedJoy);
		float getSpeed();
		float getMaxSpeed();
		void keyboard(char key, int x, int y);
		void keyboardUP(char key, int x, int y);
		void inputSpecial(char key,int x, int y);
		void inputSpecialUP(char key,int x, int y);
		void control();
		void setActif(bool b);
		bool getActif();
		void fermerPorte1();
		void fermerPorte2();
		int getA();
		void setA(int A);
		collisionsphere getCollissionSphere();
		std::vector<roue *> wheel;
		objloader *obj;
		std::vector<particule*> part;
	

		
	private:
	int car;
	collisionsphere cs;
	vector3d force;
	std::string name;
	vector3d direction;
	bool isground,iscollision, issprint,actif;
	float sprintspeed,normalspeed;
	float lookspeed;
	float acc, dec,dec2;
	vector3d a;
	vector3d loc;
	int up,down,left,right,a_touch;
 	float angle;
	float turnSpeed;
	float speed;
	float maxSpeed;	
	float s;
	float rr,rr2;
	float force_;

	

};

#endif
