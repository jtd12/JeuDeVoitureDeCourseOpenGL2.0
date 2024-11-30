#ifndef DEF_CAMERA_H
#define DEF_CAMERA_H
#include"C:\library\mathsutils\include\vector.h"
#include"C:\library\mathsutils\include\collisionplane.h"
#include"C:\library\mathsutils\include\collisionsphere.h"
#include"C:\library\mathsutils\include\collision.h"
#include<vector>
#include<gl/gl.h>
#include<gl/glu.h>
#include<stdio.h>
#include"C:\library\freeglut\include\GL\freeglut.h"


class boundingboxCam
{

public:

boundingboxCam();	
boundingboxCam(vector3d pos);
~boundingboxCam();
void update();
void draw();
vector3d getLocation();
void setInFrontOfCamera( vector3d cameraPosition,  vector3d cameraOrientation, float distanceFromCamera);

private:
	vector3d position;
	float rot;
};


class camera
{
	public:
		camera();
		~camera();
		void control(int x,int y);
		void moveCamera(float dir);
		void moveCameraUp(float dir);
		void moveLateral(float dir,float x,float y);
		void collisionCameraAndGround();
		void updateCollision();
		void drawCollision();
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
		vector3d getVector();
		float getMovevel();
		float getMousevel();
		void setSpeed(float s);

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
			float speed;
			
		public:
		boundingboxCam* bb;
		std::vector<boundingboxCam*> collidersDetection;
			
	

};
#endif
