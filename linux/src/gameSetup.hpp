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
#include<GL/freeglut.h>
#define R 21



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
		
	void gestionCam();
	void updateCamera();
	void changeKey();
	void cameraFollowCar();
	void collisionCar();
	void collisionCarAI();
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

	
};

#endif

