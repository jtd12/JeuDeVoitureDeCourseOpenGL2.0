#ifndef DEF_PLAYERCAM_H
#define DEF_PLAYERCAM_H
#include <GL/gl.h>
#include <GL/glu.h>
#include<vector>
#include"C:\library\mathsutils\include\vector.h"
#include"C:\library\mathsutils\include\collision.h"
#include"C:\library\mathsutils\include\collisionsphere.h"
#include"C:\library\mathsutils\include\collisionplane.h"
#include"objloader.hpp"
#include"camera.h"
#include<cmath>
#include<iostream>
#include<C:\library\freeglut\include\GL\freeglut.h>
#define pi 3.14159265359 // on definit un nombre pi

class playerCam
{
public:
	playerCam(const char * n,collisionsphere ccs,float sprints,float normals,float looks);
	~playerCam();
	camera cam;
void showBalle();
void updateBalle();
	void update(std::vector<collisionplane>& collplane);
	 	collisionsphere getCollissionSphere();
	 		void setPosition(vector3d pos);
	 		void setLocation(vector3d  loc);
	 		void setLocation2(vector3d newLoc);
			vector3d getLocation();
			void setJump();
			void setSprint();
			void stopSprint();
			void relacherSpecial(char key,int x, int y);
	    	vector3d dir;
			
private:
		unsigned int w;
		float speed;
		int points;
		std::vector<unsigned int> frames;
		unsigned int a_;
		bool up,down,right,left;
		float curFrame;
		std::string name;
		int mesh;
		std::string file_;
		vector3d force;
		bool isground,iscollision, issprint;
		int headPosition;
		bool headUp;
		vector3d loc;
		float rot;
		float rot2;
		float energy;
		float 	sprintspeed;
		float normalspeed,lookSpeed;
		vector3d rotation;
  		bool balleVisible;
		float bulletDelay;
		int curWep;
		int health;
		//arme *arm;
		bool isWeapon;
		collisionsphere cs;
		vector3d direction;
		unsigned int attackSound;
};
#endif
