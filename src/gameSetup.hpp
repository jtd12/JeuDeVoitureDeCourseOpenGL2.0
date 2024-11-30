#ifndef DEF_GAMESETUP_HPP
#define DEF_GAMESETUP_HPP
#include"common/objloader.hpp"
#include"common/skybox.h"
#include"common/car.h"
#include"common/decor.h"
#include"common/playerCam.h"
#include"common/water.h"
#include"common/carAI.hpp"
#include"common/AllCars.h"
#include"common/sound.h"
#include<time.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<windows.h>
#include <conio.h>
#include <mmsystem.h>
#include"C:\library\freeglut\include\GL\freeglut.h"
#define R 21

inline float dist(int x1, int y1, int x2, int y2);

class setup
{
	public:
		
	setup();
	~setup();
	void init();
	void keyboard(unsigned char key, int x, int y);
	void mouseMove(int mx,int my);
	void specialKey(int key, int x, int y);
	void mouseState(int button, int state, int x, int y);
	void update();
	void draw();
	void controlSpecialPassiveKeyboard(int key,int x, int y);
	void passiveKeyboard(unsigned char key, int x, int y);
	
	private:
		
	void hud(const char * filename);
	void hud2(const char * filename);
	void hud3(const char * filename);
	void hud4(const char* filename);
	void drawHud();
	bool linePointDetection(float x1, float y1, float x2, float y2, float px, float py);
	std::string int2str(int x);
	void gestionCam();
	void updateCamera();
	void cameraFollowCar();
	void collisionCar();
	void collisionCarAI();
	void collisionCarAndWall();
	void collisionCameraAndWall();
	void cameraMovement(float speed);
	void resetCar(bool startFreeCamera);
	void carMovement(float speed);
	void drawText(float x, float y, std::string text) ;
	void collisionCar(vector3d pos,vector3d pos2);
	void fog();
	void lighting();
	objloader *obj;
	skybox *sky;
	std::vector<allVehicule*> allCars;
	water *ocean;
	water *ressort;
	water *tuyeau;
	sound* audio;
	int sound1;
	playerCam * player;
	std::vector<decor *> levels;
	int step;
	int step_cam_follow;
	float fog_variation;
	float deltaTime;
	float oldTime;
	double fps;
	float rotAiguille;
	GLuint hudTex,hudTex2,hudTex3,hudTex4;
	textures texture;
	float time;
	bool finishedGame;
	bool keyV;
	bool startcameraFollow;
	bool startFreeCamera;
		

	
};

#endif

