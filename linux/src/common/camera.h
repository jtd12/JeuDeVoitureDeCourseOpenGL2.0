#ifndef DEF_CAMERA_H
#define DEF_CAMERA_H
#include"collision/vector.h"
#include"collision/collisionplane.h"
#include"collision/collisionsphere.h"
#include"collision/collision.h"
#include<vector>
#include <GL/gl.h>
#include<GL/glu.h>
#include<stdio.h>
#include<GL/freeglut.h>

class camera
{
	public:
		camera();
		~camera();
		void control(int x,int y);
		void moveCamera(float dir);
		void moveCameraUp(float dir);
		void moveLateral(float dir,float x,float y);
		void update();
		void lockCamera();
		void setLocation(vector3d l);
		vector3d getLocation();
		void mouse(int button, int state, int x, int y);
		void setMouseVel(float speed);
		float getMouseVel();
		float getPitch();
		float getYaw();
		void setUP(int num);
		void setDOWN(int num);
		void setRIGHT(int num);
		void setLEFT(int num);
		int getUP();
		int getDOWN();
		int getRIGHT();
		int getLEFT();
		void setActif(bool b);
		bool getActif();
		void lookAt(float pitch,float yaw);
		void mouseIn(bool b);
		void setSpeed(float mv,float mov);
		bool isMoved();
		void setLocation2(vector3d vec);
		float getMovevel();
		float getMousevel();
		
		private:
			int up,down,left,right;
			float camYaw;
			float camPitch;
			float mousevel;
			float movevel;
			vector3d loc;
			bool mi,mi2,ismoved;
			int MidX;
			int MidY;
			bool actif;
	

};
#endif
