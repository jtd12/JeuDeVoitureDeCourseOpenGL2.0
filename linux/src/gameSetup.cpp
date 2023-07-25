#include"gameSetup.hpp"

setup::setup()
{
	
//int randNumber = rand() % 50 + 10;

std::vector<collisionplane> mapcp;
std::vector<collisionplane> mapcp2;
std::vector<collisionplane> mapcp3;
std::vector<collisionplane> mapcp4;

std::vector<vector3d> mapsp;

mapsp.push_back(vector3d(0.1,0.2,0.1));
obj=new objloader();
unsigned int map=obj->load("data/decor/decor.obj",NULL);
unsigned int map2=obj->load("data/decor/collision.obj",&mapcp);
unsigned int map3=obj->load("data/decor/decor2.obj",NULL);
unsigned int map6=obj->load("data/decor/collision2.obj",&mapcp2);
unsigned int map7=obj->load("data/decor/collision3.obj",&mapcp3);
unsigned int map8=obj->load("data/decor/engrenage.obj",NULL);
unsigned int map9=obj->load("data/decor/decor3.obj",NULL);
unsigned int map10=obj->load("data/decor/collision4.obj",&mapcp4);

levels.push_back(new decor("name",map,mapcp,mapsp));
levels.push_back(new decor("name",map2,mapcp,mapsp));
levels.push_back(new decor("name",map3,mapcp,mapsp));
//levels.push_back(new decor("name",map3_2,mapcp4,mapsp));
levels.push_back(new decor("name",map6,mapcp2,mapsp));
levels.push_back(new decor("name",map7,mapcp3,mapsp));
levels.push_back(new decor("name",map8,mapcp,mapsp));
levels.push_back(new decor("name",map9,mapcp,mapsp));
levels.push_back(new decor("name",map10,mapcp4,mapsp));


sky=new skybox();
player=new playerCam("player1",collisionsphere(vector3d(2180,500.0,1160),75.0),1.2,30.0,0.5);
step=0;
step_cam_follow=0;
std::vector<unsigned int> anim;
obj->loadAnimation(anim,"data/water/ocean",300);
std::vector<unsigned int> animRessort;
obj->loadAnimation(animRessort,"data/engrenage/ressort/ressort_element",100);
std::vector<unsigned int> animTuyeau;
obj->loadAnimation(animTuyeau,"data/engrenage/tuyeau/tuyeau_element",100);
ocean=new water(anim,anim[0],vector3d(0.0,0,0.0),0,"tuyeau");
ressort=new water(animRessort,animRessort[0],vector3d(0.0,0,0.0),0,"ressort");
tuyeau=new water(animTuyeau,animTuyeau[0],vector3d(0.0,0,0.0),0,"tuyeau");

for(int i=0;i<7;i++)
	allCars.push_back(new allVehicule());

unsigned int carAI_=obj->load("data/vehicule/vehicule0.obj",NULL);
unsigned int carAI2_=obj->load("data/vehicule/vehicule1.obj",NULL);
unsigned int carAI3_=obj->load("data/vehicule/vehicule2.obj",NULL);
unsigned int carAI4_=obj->load("data/vehicule/vehicule3.obj",NULL);
unsigned int carAI5_=obj->load("data/vehicule/vehicule4.obj",NULL);
unsigned int carAI6_=obj->load("data/vehicule/vehicule5.obj",NULL);

allCars[0]->car=new vehicule("voiture",collisionsphere(vector3d(-2400,180,1280),70.0),0.02,0.0,0.2);
allCars[1]->carAI.push_back(new vehiculeAI(carAI_,"voitureAI",collisionsphere(vector3d(-2100,180,1260),70.0),0.02,0.0));
allCars[2]->carAI.push_back(new vehiculeAI(carAI2_,"voitureAI2",collisionsphere(vector3d(500,180,1260),70.0),0.02,0.0));
allCars[3]->carAI.push_back(new vehiculeAI(carAI3_,"voitureAI3",collisionsphere(vector3d(0,180,1260),70.0),0.02,0.0));
allCars[4]->carAI.push_back(new vehiculeAI(carAI4_,"voitureAI4",collisionsphere(vector3d(-500,180,1260),70.0),0.02,0.0));
allCars[5]->carAI.push_back(new vehiculeAI(carAI5_,"voitureAI5",collisionsphere(vector3d(-1000,180,1260),70.0),0.02,0.0));
allCars[6]->carAI.push_back(new vehiculeAI(carAI6_,"voitureAI6",collisionsphere(vector3d(-1500,180,1260),70.0),0.02,0.0));


audio=new sound;
sound1=audio->loadSound("data/audio/vehicule.wav");



lighting();


}



setup::~setup()
{
for(int i=0;i<levels.size();i++)
 delete levels[i];
delete sky;
delete player;
delete obj;
delete ocean;
delete tuyeau;
delete ressort;
for(int i=0;i<allCars.size();i++)
  delete allCars[i];
}

void setup::mouseMove(int mx,int my)
{
	player->cam.control(mx,my);
}
void setup:: mouseState(int button, int state, int x, int y)
{
	player->cam.mouse( button,  state,  x,  y);
}
void setup::keyboard(unsigned char key, int x, int y)
{
	
	allCars[0]->car->keyboard(key,x,y);
	switch(key)
	{
		case 'c':
		case 'C': 
	
		glutPostRedisplay();
		break;
		
		case 'v':
		case 'V': 
	
		glutPostRedisplay();
		break;
		
		case 'b':
		case 'B':
		
			glutPostRedisplay();
			break;
			
		case 'l':
		case 'L':
		
			glutPostRedisplay();
			break;
			 
		
		case 'm':
		case 'M':
			
			step++;
			if(step>5)
			 step=0;
			glutPostRedisplay();
			break;
		     
	}
}

void setup::passiveKeyboard(unsigned char key, int x, int y)
 {
 	allCars[0]->car->keyboardUP(key,x,y);

 }
 
void setup::specialKey(int key, int x, int y)
{
	allCars[0]->car->inputSpecial(key,x,y);
	switch(key)
	{
		case GLUT_KEY_UP:
			player->cam.setUP(true);
		 
		glutPostRedisplay();
			break;
			
		case GLUT_KEY_DOWN:
			player->cam.setDOWN(true);
		 
		glutPostRedisplay();
			break;
			
		case GLUT_KEY_RIGHT:
			player->cam.setRIGHT(true);
			glutPostRedisplay();
			break;
			
		case GLUT_KEY_LEFT:
			
			player->cam.setLEFT(true);
			glutPostRedisplay();
			break;	
			
			 
		
	}
}

void setup::controlSpecialPassiveKeyboard(int key,int x, int y)
{
	allCars[0]->car->inputSpecialUP(key,x,y);
	
		switch(key)
	{
		case GLUT_KEY_UP:
			player->cam.setUP(false);
			break;
		case GLUT_KEY_DOWN:
			player->cam.setDOWN(false);
			break;
		case GLUT_KEY_RIGHT:
			player->cam.setRIGHT(false);
			break;
		case GLUT_KEY_LEFT:
			player->cam.setLEFT(false);
			break;	
			
	}
	
}

void setup::gestionCam()
{
	if(player->cam.getUP())
	{
	
	  if(player->cam.getPitch()!=90 && player->cam.getPitch()!=-90)
			player->cam.moveCamera(0);
		player->cam.moveCameraUp(0.0);
	}
	
	if(player->cam.getDOWN())
	{
	
	 if(player->cam.getPitch()!=90 && player->cam.getPitch()!=-90)
			player->cam.moveCamera(180);
		player->cam.moveCameraUp(180.0);
	}
	
	if(player->cam.getRIGHT())
	{
	
		player->cam.moveCamera(-90);
	}
	
	if(player->cam.getLEFT())
	{
	
	 player->cam.moveCamera(90);
}

}

void setup::changeKey()
{
 	if(step<=2)
{

	player->cam.setActif(true);
	allCars[0]->car->setActif(false);
}
else
{
	player->cam.setActif(false);
	allCars[0]->car->setActif(true);
}

}

void setup::cameraFollowCar()
{

 if(allCars[0]->car->getSpeed()>0.01f)
	{
		
	vector3d camPos=vector3d(allCars[0]->car->getLocation().x+cos(allCars[0]->car->getRotation().y*M_PI/180.0f)*-650,390.5,allCars[0]->car->getLocation().z-sin(allCars[0]->car->getRotation().y*M_PI/180.0f)*-650);
	vector3d target=allCars[0]->car->getLocation();
	vector3d camUp=vector3d(0,1,0);

	gluLookAt(camPos.x,camPos.y,camPos.z,target.x,target.y,target.z,camUp.x,camUp.y,camUp.z);
}

	if(allCars[0]->car->getSpeed()<-0.01f)
		
	{
	
	vector3d camPos=vector3d(allCars[0]->car->getLocation().x+cos(allCars[0]->car->getRotation().y*M_PI/180.0f)*650,390.5,allCars[0]->car->getLocation().z-sin(allCars[0]->car->getRotation().y*M_PI/180.0f)*650);
	vector3d target=allCars[0]->car->getLocation();
	vector3d camUp=vector3d(0,1,0);
	gluLookAt(camPos.x,camPos.y,camPos.z,target.x,target.y,target.z,camUp.x,camUp.y,camUp.z);
}
	if(allCars[0]->car->getSpeed()==0.0f)
	{
	vector3d camPos=vector3d(allCars[0]->car->getLocation().x+cos(allCars[0]->car->getRotation().y*M_PI/180.0f)*-550,390.5,allCars[0]->car->getLocation().z-sin(allCars[0]->car->getRotation().y*M_PI/180.0f)*-550);
	vector3d target=allCars[0]->car->getLocation();
	vector3d camUp=vector3d(0,1,0);
	gluLookAt(camPos.x,camPos.y,camPos.z,target.x,target.y,target.z,camUp.x,camUp.y,camUp.z);	
	}



}

void setup::fog()
{

glEnable(GL_FOG) ;
GLfloat fogcolor[4] = {0.6, 0.7, 0.8, 1} ;
GLint fogmode = GL_EXP ;
glFogi (GL_FOG_MODE, fogmode) ;
glFogfv(GL_FOG_COLOR, fogcolor) ;
glFogf(GL_FOG_DENSITY, fog_variation) ;
glFogf(GL_FOG_START, 80.0) ;
glFogf(GL_FOG_END, 8500.0) ;

fog_variation=fps/90000.0f;

if(fog_variation>.01f)
  fog_variation=fps/90000.0f;

}

void setup::lighting()
{
			GLfloat ambient[] = {0.15f,0.15f,0.35f,0.9f};
            GLfloat diffuse[] = {0.49f,0.49f,0.49f,0.49f};
            GLfloat light0_position [] = {10.0f, 20.0f, -100.0f, 1.0f};
            GLfloat specular_reflexion[] = {0.6f,0.9f,0.9f,1.0f};
            GLubyte shiny_obj = 128;

                        //positionnement de la lumière avec les différents paramètres
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
            glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
            glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
     
            glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
            glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
            glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular_reflexion);
            glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,shiny_obj);
}


void setup::updateCamera()
{
	if(player->cam.getActif() && allCars[0]->car->getActif()==false)
	{
	
	 player->cam.update();
	 gestionCam();
	}
	else
	{
	   cameraFollowCar();
	   allCars[0]->car->update();
	}
}

void setup::update()
{

    deltaTime = clock() - oldTime;
	fps = (1.0 / deltaTime) * 1000;
	oldTime = clock();
	
	audio->setListener(allCars[0]->car->getLocation(),allCars[0]->car->getLocation());
	audio->playSound(sound1,allCars[0]->car->getLocation(),(allCars[0]->car->getSpeed()/allCars[0]->car->getMaxSpeed())+1);

//	printf("v1: %.2f\n",allCars[1]->carAI[0]->getSpeed());
//	printf("v2: %.2f\n",allCars[2]->carAI[0]->getSpeed());
	
	/*
	if(player->cam.getActif()==false && car->getActif())
	{
	 player->cam.setLocation(car->getLocation());
	 car->control();
	
	}*/

	ocean->update(295);
	ressort->update(100);
	tuyeau->update(100);
	
	
	
   for(int w=1;w<allCars.size();w++)
	for(int i=0;i<allCars[w]->carAI.size();i++)
	  allCars[w]->carAI[i]->update();
	 
	for(int w=1;w<allCars.size();w++)
	 for(int i=0;i<allCars[w]->carAI.size();i++)
	 allCars[w]->carAI[i]->update(levels[1]->getCollisionPlanes());
	 
	
		for(int w=1;w<allCars.size();w++)
	 for(int i=0;i<allCars[w]->carAI.size();i++)
	 allCars[w]->carAI[i]->update2(levels[7]->getCollisionPlanes());
	 
	 
	 //allCars[w]->carAI[i]->update2(levels[5]->getCollisionPlanes());
    allCars[0]->car->update(levels[1]->getCollisionPlanes());
 	allCars[0]->car->update2(levels[3]->getCollisionPlanes());
	allCars[0]->car->update3(levels[4]->getCollisionPlanes());
	allCars[0]->car->update4(levels[7]->getCollisionPlanes());
    //player->update(levels[0]->getCollisionPlanes());


	sky->update();
	//changeKey();
   for(int w=1;w<allCars.size();w++)
	for(int i=0;i<allCars[w]->carAI.size();i++)
	{
	allCars[w]->carAI[i]->move();
    allCars[w]->carAI[i]->findTarget();
	}

	changeKey();
	
				
	fog();
	
}


void setup::draw()
{
	//glTranslated(0,-10,-100);
	updateCamera();
	//cameraFollowCar();
	glPushMatrix();
	ocean->draw();
	tuyeau->draw();
	ressort->draw();
	glPopMatrix();
	glPushMatrix();
	glRotated(sky->getRot(),0,0.5,0);
	sky->drawSkybox(100000);
	glPopMatrix();
	glPushMatrix();
	for(int i=0;i<levels.size();i++)
	 levels[i]->draw();
	glPopMatrix();
	glPushMatrix();
	allCars[0]->car->draw();
	glPopMatrix();
	glPushMatrix();
	for(int w=1;w<allCars.size();w++)
	 for(int i=0;i<allCars[w]->carAI.size();i++)
	  allCars[w]->carAI[0]->draw();
	glPopMatrix();
	

}
