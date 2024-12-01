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
unsigned int map8=obj->load("data/decor/engrenage.obj",NULL);
unsigned int map9=obj->load("data/decor/decor3.obj",NULL);


levels.push_back(new decor("name",map,mapcp,mapsp));
levels.push_back(new decor("name",map2,mapcp,mapsp));
levels.push_back(new decor("name",map3,mapcp,mapsp));
//levels.push_back(new decor("name",map3_2,mapcp4,mapsp));
levels.push_back(new decor("name",map8,mapcp,mapsp));
levels.push_back(new decor("name",map9,mapcp,mapsp));



sky=new skybox();
player=new playerCam("player1",collisionsphere(vector3d(-500,250,1260),75.0),1.2,10.0,0.25);
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
hudTex=0;
hudTex2=0;
hudTex3=0;
hudTex4=0;
rotAiguille=0;
time=20;
finishedGame=false;
keyV=false;
startcameraFollow=false;
startFreeCamera=true;

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
		keyV=true;
		glutPostRedisplay();
		case 'V': 
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

void setup::resetCar(bool startFreeCamera)
{
	
	
	if(allCars[0]->car->getPOINTS()>=15000)
	{
		finishedGame=true;
	}

	
   for(int w=1;w<allCars.size();w++)
	for(int i=0;i<allCars[w]->carAI.size();i++)
	{
	if(allCars[w]->carAI[i]->getPOINTS()>=15000)
	{
		finishedGame=true;

	}
 }
 

 
 
 if(keyV && time>0 && finishedGame)
 {
 	finishedGame=false;
 }
	
    if( !finishedGame)
		 time-=0.1f;
		
	 else if(finishedGame)
 {

   time=80;
   player->cam.setLocation(vector3d(-500,250,1260));
   allCars[0]->car->resetPoints();
   allCars[0]->car->setLocation(vector3d(-2400,180,1280));
   allCars[0]->car->limitSpeed(0.0f);
   allCars[0]->car->setRotation(vector3d(0,0,0));
   //allCars[0]->car->placementRoues();
   allCars[0]->car->setGravity();
   
   
   for(int w=1;w<allCars.size();w++)
	for(int i=0;i<allCars[w]->carAI.size();i++)
	{
      allCars[w]->carAI[i]->resetPoints();
      allCars[1]->carAI[i]->setLocation(vector3d(-450,180,1200));
      allCars[2]->carAI[i]->setLocation(vector3d(-850,180,1200));
      allCars[3]->carAI[i]->setLocation(vector3d(-100,180,1200));
      allCars[4]->carAI[i]->setLocation(vector3d(550,180,1200));
      allCars[5]->carAI[i]->setLocation(vector3d(1200,180,1200));
	  allCars[6]->carAI[i]->setLocation(vector3d(-1000,180,1200));
      allCars[w]->carAI[i]->setRotation(vector3d(0,0,0));
    // allCars[w]->carAI[i]->limitSpeed(0.0f);
      allCars[w]->carAI[i]->setNumberPath(0);
     // allCars[w]->carAI[i]->placeRoues(startFreeCamera);
      allCars[w]->carAI[i]->setGravity();

  	}
  	
  	
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
	vector3d camPos=vector3d(allCars[0]->car->getLocation().x+cos(allCars[0]->car->getRotation().y*M_PI/180.0f)*-550,590.5,allCars[0]->car->getLocation().z-sin(allCars[0]->car->getRotation().y*M_PI/180.0f)*-550);
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

fog_variation=0.0002f;


}

void setup::lighting()
{
			GLfloat ambient[] = {0.15f,0.15f,0.35f,0.9f};
            GLfloat diffuse[] = {0.49f,0.49f,0.49f,0.49f};
            GLfloat light0_position [] = {10.0f, 20.0f, -100.0f, 1.0f};
            GLfloat specular_reflexion[] = {0.6f,0.9f,0.9f,1.0f};
            GLubyte shiny_obj = 128;

                        //positionnement de la lumi\E8re avec les diff\E9rents param\E8tres
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
	if(time>0)
	{
	
	 player->cam.update();
	 gestionCam();
	}
	else
	{
	   cameraFollowCar();
	   allCars[0]->car->update(time);
	}
}



void setup:: drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);
    if (glGetError() != GL_NO_ERROR) {
        std::cerr << "Erreur: Position raster invalide.\n";
        return;
    }
    
     for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }
   // glutBitmapCharacter(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}


void setup::hud(const char* filename)
{
	glEnable(GL_TEXTURE_2D);
	if(hudTex==0)
	 hudTex=texture.loadBMP_custom(filename);
	glPushMatrix();
	glTranslated(-0.68,-0.85,0);
	glScaled(0.2,0.17,0);
	glBindTexture(GL_TEXTURE_2D,hudTex);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	
glTexCoord2i(0,1);glVertex3i(-1,-1,-1);
glTexCoord2i(1,1);glVertex3i(+1,-1,-1);
glTexCoord2i(1,0);glVertex3i(+1,+1,-1); 
glTexCoord2i(0,0);glVertex3i(-1,+1,-1);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
}

void setup::hud2(const char* filename)
{
	glEnable(GL_TEXTURE_2D);
	if(hudTex2==0)
	 hudTex2=texture.loadBMP_custom(filename);
	glPushMatrix();
	glTranslated(-0.75,-0.9,0);
	glRotatef(rotAiguille,0,0,0.5);
	glTranslated(-0.025,0.0,0);
	glScaled(0.015,0.015,0);
	glBindTexture(GL_TEXTURE_2D,hudTex2);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	
	glTexCoord2i(0,1);glVertex3i(-1,-1,-1);
	glTexCoord2i(1,1);glVertex3i(+1,-1,-1);
	glTexCoord2i(1,0);glVertex3i(+1,+1,-1); 
	glTexCoord2i(0,0);glVertex3i(-1,+1,-1);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void setup::hud3(const char* filename)
{
	glEnable(GL_TEXTURE_2D);
	if(hudTex3==0)
	 hudTex3=texture.loadBMP_custom(filename);
	glPushMatrix();
	glTranslated(-0.5,0.3,0);
	glScaled(0.2,0.98,0);
	glBindTexture(GL_TEXTURE_2D,hudTex3);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	
	glTexCoord2i(0,1);glVertex3i(-1,-1,-1);
	glTexCoord2i(1,1);glVertex3i(+1,-1,-1);
	glTexCoord2i(1,0);glVertex3i(+1,+1,-1); 
	glTexCoord2i(0,0);glVertex3i(-1,+1,-1);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void setup::hud4(const char* filename)
{
	glEnable(GL_TEXTURE_2D);
	if(hudTex4==0)
	 hudTex4=texture.loadBMP_custom(filename);
	glPushMatrix();
	glTranslated(0.75,-0.15,0);
	glScaled(0.2,0.55,0);
	glBindTexture(GL_TEXTURE_2D,hudTex4);
	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	
	glTexCoord2i(0,1);glVertex3i(-1,-1,-1);
	glTexCoord2i(1,1);glVertex3i(+1,-1,-1);
	glTexCoord2i(1,0);glVertex3i(+1,+1,-1); 
	glTexCoord2i(0,0);glVertex3i(-1,+1,-1);

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

std::string setup::int2str(int x) {
    // converts int to string
    std::stringstream ss;
    ss << x;
    return ss.str( );
}

void setup::drawHud()
{

	    
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	hud2("data/aiguille.bmp");	
	hud("data/tableaubord2.bmp");	
	
	glDisable(GL_DEPTH_TEST);
	drawText(0.1,0.9,"CARPLAYER:");
	glEnable(GL_DEPTH_TEST);

	if(allCars[0]->car->getSpeed()>0)
	 drawText(-0.6,0.8,"VITESSE: "+int2str(allCars[0]->car->getSpeed()*30));
	else if(allCars[0]->car->getSpeed()<0)
	 drawText(-0.6,0.8,"VITESSE: "+int2str(allCars[0]->car->getSpeed()*-30)); 
	else
	  drawText(-0.6,0.8,"VITESSE: "+int2str(allCars[0]->car->getSpeed())); 
	  
	drawText(-0.6,0.7,"POINTS: "+int2str(allCars[0]->car->getPOINTS()));
	
	drawText(-0.6,0.5,"CARPLAYERAI:");
	
   for(int w=1;w<allCars.size();w++)
	for(int i=0;i<allCars[w]->carAI.size();i++)
	{
	 drawText(-0.6,0.55-(w*0.2),"CARAI: POINTS: "+int2str(allCars[w]->carAI[i]->getPOINTS()));
	}
	
   for(int w=1;w<allCars.size();w++)
	 for(int i=0;i<allCars[w]->carAI.size();i++)
	 {
	  drawText(0.6,0.55-(w*0.2),"VITESSE: "+int2str(allCars[w]->carAI[i]->getSpeed())); 
	}
	
	if(time>0)
  	{
	drawText(-0.15,0.3,"START GAME INTO: "+int2str(time));
	}
	
	for(int w=1;w<allCars.size();w++)
		 for(int i=0;i<allCars[w]->carAI.size();i++)
		 {
	if( allCars[0]->car->getPOINTS()>=15000 && allCars[w]->carAI[i]->getPOINTS()<15000)
	{
		drawText(0.8,0.4,"YOU WIN!!!! "); 
	}
	else
	{
	  if( allCars[0]->car->getPOINTS()<15000 && allCars[w]->carAI[i]->getPOINTS()>=15000)
	  {
			drawText(0.8,0.4,"YOU LOSE!!!! "); 
	  }
   }
 }
	
	hud3("data/fond_.bmp");
	hud4("data/fond_.bmp");
		
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
}


void setup::collisionCar(vector3d pos,vector3d pos2)
{
	
	float dist=sqrt((pos.x-pos2.x)*(pos.x-pos2.x) + (pos.z-pos2.z)*(pos.z-pos2.z));
	
		 	  if(dist<80)
		 	  {
		 	allCars[0]->car->limitSpeed(-5.0f);
		 	allCars[0]->car->setPoints(1);
			  }
		 
}

void setup::carMovement(float speed)
{
	 
	      allCars[0]->car->limitSpeed(speed);
	      allCars[0]->car->setPoints(1);
	   
}



void setup::cameraMovement(float speed)
{
	      
	  player->cam.setSpeed(speed); 
	  
}


void setup::collisionCameraAndWall()
{
  if(linePointDetection(player->cam.collidersDetection[0]->getLocation().x,
	player->cam.collidersDetection[0]->getLocation().z,player->cam.collidersDetection[1]->getLocation().x,
	player->cam.collidersDetection[1]->getLocation().z,player->cam.bb->getLocation().x,player->cam.bb->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-20.8f);

	}
	
	
	else if(linePointDetection(player->cam.collidersDetection[2]->getLocation().x,
	player->cam.collidersDetection[2]->getLocation().z,player->cam.collidersDetection[3]->getLocation().x,
	player->cam.collidersDetection[3]->getLocation().z,player->cam.bb->getLocation().x,player->cam.bb->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-20.8f);

	}
	
	
	
	else if(linePointDetection(player->cam.collidersDetection[4]->getLocation().x,
	player->cam.collidersDetection[4]->getLocation().z,player->cam.collidersDetection[5]->getLocation().x,
	player->cam.collidersDetection[5]->getLocation().z,player->cam.bb->getLocation().x,player->cam.bb->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-20.8f);

	}
	
	
	 else if(linePointDetection(player->cam.collidersDetection[6]->getLocation().x,
	player->cam.collidersDetection[6]->getLocation().z,player->cam.collidersDetection[7]->getLocation().x,
	player->cam.collidersDetection[7]->getLocation().z,player->cam.bb->getLocation().x,player->cam.bb->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-20.8f);

	}

	
	else if(linePointDetection(player->cam.collidersDetection[8]->getLocation().x,
	player->cam.collidersDetection[8]->getLocation().z,player->cam.collidersDetection[9]->getLocation().x,
	player->cam.collidersDetection[9]->getLocation().z,player->cam.bb->getLocation().x,player->cam.bb->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-20.8f);

	}

	
	else if(linePointDetection(player->cam.collidersDetection[10]->getLocation().x,
	player->cam.collidersDetection[10]->getLocation().z,player->cam.collidersDetection[11]->getLocation().x,
	player->cam.collidersDetection[11]->getLocation().z,player->cam.bb->getLocation().x,player->cam.bb->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-20.8f);

	}

	else if(linePointDetection(player->cam.collidersDetection[12]->getLocation().x,
	player->cam.collidersDetection[12]->getLocation().z,player->cam.collidersDetection[13]->getLocation().x,
	player->cam.collidersDetection[13]->getLocation().z,player->cam.bb->getLocation().x,player->cam.bb->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-20.8f);

	}
	
	
	else if(linePointDetection(player->cam.collidersDetection[14]->getLocation().x,
	player->cam.collidersDetection[14]->getLocation().z,player->cam.collidersDetection[15]->getLocation().x,
	player->cam.collidersDetection[15]->getLocation().z,player->cam.bb->getLocation().x,player->cam.bb->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-20.8f);

	}

	
	else if(linePointDetection(player->cam.collidersDetection[16]->getLocation().x,
	player->cam.collidersDetection[16]->getLocation().z,player->cam.collidersDetection[17]->getLocation().x,
	player->cam.collidersDetection[17]->getLocation().z,player->cam.bb->getLocation().x,player->cam.bb->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-20.8f);

	}

	
	
	else if(linePointDetection(player->cam.collidersDetection[18]->getLocation().x,
	player->cam.collidersDetection[18]->getLocation().z,player->cam.collidersDetection[19]->getLocation().x,
	player->cam.collidersDetection[19]->getLocation().z,player->cam.bb->getLocation().x,player->cam.bb->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-20.8f);

	}


	else if(linePointDetection(player->cam.collidersDetection[20]->getLocation().x,
	player->cam.collidersDetection[20]->getLocation().z,player->cam.collidersDetection[21]->getLocation().x,
	player->cam.collidersDetection[21]->getLocation().z,player->cam.bb->getLocation().x,player->cam.bb->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-20.8f);

	}

	
	else if(linePointDetection(player->cam.collidersDetection[22]->getLocation().x,
	player->cam.collidersDetection[22]->getLocation().z,player->cam.collidersDetection[23]->getLocation().x,
	player->cam.collidersDetection[23]->getLocation().z,player->cam.bb->getLocation().x,player->cam.bb->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-20.8f);

	}

	
	else if(linePointDetection(player->cam.collidersDetection[24]->getLocation().x,
	player->cam.collidersDetection[24]->getLocation().z,player->cam.collidersDetection[25]->getLocation().x,
	player->cam.collidersDetection[25]->getLocation().z,player->cam.bb->getLocation().x,player->cam.bb->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-20.8f);

	}

	
	else if(linePointDetection(player->cam.collidersDetection[26]->getLocation().x,
	player->cam.collidersDetection[26]->getLocation().z,player->cam.collidersDetection[27]->getLocation().x,
	player->cam.collidersDetection[27]->getLocation().z,player->cam.bb->getLocation().x,player->cam.bb->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         cameraMovement(-20.8f);

	}
	else
	{
		   cameraMovement(1.0f);
	}
}


void setup::collisionCarAndWall()
{
	
 	
   for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[0]->getLocation().x,
	allCars[w]->car->collidersDetection[0]->getLocation().z,allCars[w]->car->collidersDetection[1]->getLocation().x,
	allCars[w]->car->collidersDetection[1]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         carMovement(-4.0f);

	}
	
	  for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[0]->getLocation().x,
	allCars[w]->car->collidersDetection[0]->getLocation().z,allCars[w]->car->collidersDetection[1]->getLocation().x,
	allCars[w]->car->collidersDetection[1]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
      carMovement(4.0f);

	}
	

   for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[2]->getLocation().x,
	allCars[w]->car->collidersDetection[2]->getLocation().z,allCars[w]->car->collidersDetection[3]->getLocation().x,
	allCars[w]->car->collidersDetection[3]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
   
    carMovement(-4.0f);
      

	}
	
	
   for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[2]->getLocation().x,
	allCars[w]->car->collidersDetection[2]->getLocation().z,allCars[w]->car->collidersDetection[3]->getLocation().x,
	allCars[w]->car->collidersDetection[3]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
   
     carMovement(4.0f);
      

	}

	for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[4]->getLocation().x,
	allCars[w]->car->collidersDetection[4]->getLocation().z,allCars[w]->car->collidersDetection[5]->getLocation().x,
	allCars[w]->car->collidersDetection[5]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
      carMovement(-4.0f);
       

	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[4]->getLocation().x,
	allCars[w]->car->collidersDetection[4]->getLocation().z,allCars[w]->car->collidersDetection[5]->getLocation().x,
	allCars[w]->car->collidersDetection[5]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
    	
     carMovement(4.0f);
       

	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[6]->getLocation().x,
	allCars[w]->car->collidersDetection[6]->getLocation().z,allCars[w]->car->collidersDetection[7]->getLocation().x,
	allCars[w]->car->collidersDetection[7]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
      carMovement(-4.0f);
       

	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[6]->getLocation().x,
	allCars[w]->car->collidersDetection[6]->getLocation().z,allCars[w]->car->collidersDetection[7]->getLocation().x,
	allCars[w]->car->collidersDetection[7]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
    	
     carMovement(4.0f);
       

	}		


	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[8]->getLocation().x,
	allCars[w]->car->collidersDetection[8]->getLocation().z,allCars[w]->car->collidersDetection[9]->getLocation().x,
	allCars[w]->car->collidersDetection[9]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
    carMovement(-4.0f);
       

	}
	
		
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[8]->getLocation().x,
	allCars[w]->car->collidersDetection[8]->getLocation().z,allCars[w]->car->collidersDetection[9]->getLocation().x,
	allCars[w]->car->collidersDetection[9]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
      carMovement(4.0f);
       

	}
	

		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[10]->getLocation().x,
	allCars[w]->car->collidersDetection[10]->getLocation().z,allCars[w]->car->collidersDetection[11]->getLocation().x,
	allCars[w]->car->collidersDetection[11]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {

   carMovement(-4.0f);
       
  
	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[10]->getLocation().x,
	allCars[w]->car->collidersDetection[10]->getLocation().z,allCars[w]->car->collidersDetection[11]->getLocation().x,
	allCars[w]->car->collidersDetection[11]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {

carMovement(4.0f);
       
  
	}

	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[12]->getLocation().x,
	allCars[w]->car->collidersDetection[12]->getLocation().z,allCars[w]->car->collidersDetection[13]->getLocation().x,
	allCars[w]->car->collidersDetection[13]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
      carMovement(-4.0f);
       

	}
	
	

		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[12]->getLocation().x,
	allCars[w]->car->collidersDetection[12]->getLocation().z,allCars[w]->car->collidersDetection[13]->getLocation().x,
	allCars[w]->car->collidersDetection[13]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
      carMovement(4.0f);
       

	}
	
	
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[14]->getLocation().x,
	allCars[w]->car->collidersDetection[14]->getLocation().z,allCars[w]->car->collidersDetection[15]->getLocation().x,
	allCars[w]->car->collidersDetection[15]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
 
      carMovement(-4.0f);
       
      
	}
	
	

	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[14]->getLocation().x,
	allCars[w]->car->collidersDetection[14]->getLocation().z,allCars[w]->car->collidersDetection[15]->getLocation().x,
	allCars[w]->car->collidersDetection[15]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
 
      carMovement(4.0f);
       
      
	}
	
	
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[16]->getLocation().x,
	allCars[w]->car->collidersDetection[16]->getLocation().z,allCars[w]->car->collidersDetection[17]->getLocation().x,
	allCars[w]->car->collidersDetection[17]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {

      carMovement(-4.0f);
    
	}
	
		
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[16]->getLocation().x,
	allCars[w]->car->collidersDetection[16]->getLocation().z,allCars[w]->car->collidersDetection[17]->getLocation().x,
	allCars[w]->car->collidersDetection[17]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {

    carMovement(4.0f);
    
	}
		
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[18]->getLocation().x,
	allCars[w]->car->collidersDetection[18]->getLocation().z,allCars[w]->car->collidersDetection[19]->getLocation().x,
	allCars[w]->car->collidersDetection[19]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {

      carMovement(-4.0f);
       

	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[18]->getLocation().x,
	allCars[w]->car->collidersDetection[18]->getLocation().z,allCars[w]->car->collidersDetection[19]->getLocation().x,
	allCars[w]->car->collidersDetection[19]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {

     carMovement(4.0f);
       

	}
		
		
		
		
		
		//////////////////////////////////
		
		
		
	

		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[20]->getLocation().x,
	allCars[w]->car->collidersDetection[20]->getLocation().z,allCars[w]->car->collidersDetection[21]->getLocation().x,
	allCars[w]->car->collidersDetection[21]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
  carMovement(-4.0f);
       
 
	}
	
	
		for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[20]->getLocation().x,
	allCars[w]->car->collidersDetection[20]->getLocation().z,allCars[w]->car->collidersDetection[21]->getLocation().x,
	allCars[w]->car->collidersDetection[21]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
      carMovement(4.0f);
       
 
	}

	
	
			for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[22]->getLocation().x,
	allCars[w]->car->collidersDetection[22]->getLocation().z,allCars[w]->car->collidersDetection[23]->getLocation().x,
	allCars[w]->car->collidersDetection[23]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
    carMovement(-4.0f);

	}
	
	
			for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[22]->getLocation().x,
	allCars[w]->car->collidersDetection[22]->getLocation().z,allCars[w]->car->collidersDetection[23]->getLocation().x,
	allCars[w]->car->collidersDetection[23]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
      carMovement(4.0f);

	}
	
	
	
	//////////////////////////////////
	
	
	
	
	   for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[24]->getLocation().x,
	allCars[w]->car->collidersDetection[24]->getLocation().z,allCars[w]->car->collidersDetection[25]->getLocation().x,
	allCars[w]->car->collidersDetection[25]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         carMovement(-4.0f);

	}
	
	  for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[24]->getLocation().x,
	allCars[w]->car->collidersDetection[24]->getLocation().z,allCars[w]->car->collidersDetection[25]->getLocation().x,
	allCars[w]->car->collidersDetection[25]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
      carMovement(4.0f);

	}
	
	
	   for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[26]->getLocation().x,
	allCars[w]->car->collidersDetection[26]->getLocation().z,allCars[w]->car->collidersDetection[27]->getLocation().x,
	allCars[w]->car->collidersDetection[27]->getLocation().z,allCars[w]->car->bb[0]->getLocation().x,allCars[w]->car->bb[0]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
         carMovement(-4.0f);

	}
	
	  for(int w=0;w<1;w++)
    if(linePointDetection(allCars[w]->car->collidersDetection[26]->getLocation().x,
	allCars[w]->car->collidersDetection[26]->getLocation().z,allCars[w]->car->collidersDetection[27]->getLocation().x,
	allCars[w]->car->collidersDetection[27]->getLocation().z,allCars[w]->car->bb[1]->getLocation().x,allCars[w]->car->bb[1]->getLocation().z))
    {
    //	allCars[w]->car->setLocationIncZ(15.5f);
      carMovement(4.0f);

	}

	
	
}

inline float dist(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

bool setup:: linePointDetection(float x1, float y1, float x2, float y2, float px, float py) {

  // get distance from the point to the two ends of the line
  float distX = px - x1;
  float distY = py - y1;

  float d1 = dist(px,py, x1,y1);
  float d2 = dist(px,py, x2,y2);

  // get the length of the line
  float lineLen = dist(x1,y1, x2,y2);

  // since floats are so minutely accurate, add
  // a little buffer zone that will give collision
  float buffer = 0.1;    // higher # = less accurate

  // if the two distances are equal to the line's
  // length, the point is on the line!
  // note we use the buffer here to give a range,
  // rather than one #
  if (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer) {
    return true;
  }
  return false;
}


void setup::update()
{

    deltaTime = clock() - oldTime;
	fps = (1.0 / deltaTime) * 1000;
	oldTime = clock();
	
	resetCar(startFreeCamera);
	
	if(startFreeCamera)
	{
	collisionCameraAndWall();
	player->cam.collisionCameraAndGround();
	player->cam.updateCollision();
	}
	
	ocean->update(295);
	ressort->update(100);
	tuyeau->update(100);
	
    time-=0.01f;
    
    if(time>0)
    {
		startcameraFollow=false;
		startFreeCamera=true;
	}
	
	if(time<=0 && !finishedGame)
	{
		
    time=0.0f;
    keyV=false;
    startcameraFollow=true;
	startFreeCamera=false;
	audio->setListener(allCars[0]->car->getLocation(),allCars[0]->car->getLocation());
	audio->playSound(sound1,allCars[0]->car->getLocation(),(allCars[0]->car->getSpeed()/allCars[0]->car->getMaxSpeed())+1);
	
   for(int w=1;w<allCars.size();w++)
	for(int i=0;i<allCars[w]->carAI.size();i++)
	  allCars[w]->carAI[i]->update();
	 
	for(int w=1;w<allCars.size();w++)
	 for(int i=0;i<allCars[w]->carAI.size();i++)
	 allCars[w]->carAI[i]->update(levels[1]->getCollisionPlanes());
	
    allCars[0]->car->update(levels[1]->getCollisionPlanes());
    
	collisionCarAndWall();
	
	  allCars[0]->car->checkPoints(vector3d(4000,50,1100),allCars[0]->car->getLocation());
	  allCars[0]->car->checkPoints(vector3d(-7000,50,1800),allCars[0]->car->getLocation());
	  allCars[0]->car->checkPoints(vector3d(-2800,50,-200),allCars[0]->car->getLocation());
	  allCars[0]->car->checkPoints(vector3d(-600,50,1200),allCars[0]->car->getLocation());
	  
   for(int w=1;w<allCars.size();w++)
	for(int i=0;i<allCars[w]->carAI.size();i++)
	{
	  allCars[w]->carAI[i]->checkPoints(vector3d(4000,50,1100),allCars[w]->carAI[i]->getLocation());
	  allCars[w]->carAI[i]->checkPoints(vector3d(-7000,50,1800),allCars[w]->carAI[i]->getLocation());
	  allCars[w]->carAI[i]->checkPoints(vector3d(-2800,50,-200),allCars[w]->carAI[i]->getLocation());
	  allCars[w]->carAI[i]->checkPoints(vector3d(-600,50,1200),allCars[w]->carAI[i]->getLocation());
	}
 	
	   for(int w=1;w<allCars.size();w++)
		 for(int i=0;i<allCars[w]->carAI.size();i++)
	       collisionCar(allCars[0]->car->getLocation(),allCars[w]->carAI[i]->getLocation());


	sky->update();
	//changeKey();
   for(int w=1;w<allCars.size();w++)
	for(int i=0;i<allCars[w]->carAI.size();i++)
	{
	allCars[w]->carAI[i]->move();
    allCars[w]->carAI[i]->findTarget();
	}
  }
	else
	{
	for(int w=1;w<allCars.size();w++)
	 for(int i=0;i<allCars[w]->carAI.size();i++)
	 allCars[w]->carAI[i]->update(levels[1]->getCollisionPlanes());
	
    allCars[0]->car->update(levels[1]->getCollisionPlanes());
	}

	
	fog();
}


void setup::draw()
{
	rotAiguille=allCars[0]->car->getSpeed()/-0.25;
	//glTranslated(0,-10,-100);
	updateCamera();
	glPushMatrix();
	player->cam.drawCollision();
	glPopMatrix();
	glPushMatrix();
	//player->cam.bb[0]->draw();
	glPopMatrix();
	
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
	glPushMatrix();
	
	for(int i=0;i<allCars[0]->car->bb.size();i++)
	  allCars[0]->car->bb[i]->draw();
	  
	for(int i=0;i<allCars[0]->car->collidersDetection.size();i++)
	  allCars[0]->car->collidersDetection[i]->draw();
	  
	glPopMatrix();
	
	
	drawHud();

}
