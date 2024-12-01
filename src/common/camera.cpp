#include"camera.h"

boundingboxCam::boundingboxCam()
{
	
}
boundingboxCam::boundingboxCam(vector3d pos)
{
	position=pos;
	rot=0.0f;
}

boundingboxCam::~boundingboxCam()
{
	
}

void boundingboxCam::update()
{


}

void boundingboxCam::draw()
{
	glPushMatrix();
	glTranslated(position.x,position.y,position.z);
	glRotated(rot,0,0.5,0);
	glScaled(1,1,1);
	glColor3d(0.5,0.4,0.4);
	glutSolidCube(10);
	glPopMatrix();
}

vector3d boundingboxCam::getLocation()
{
	return position;
}

void boundingboxCam::setInFrontOfCamera( vector3d cameraPosition,  vector3d cameraOrientation, float distanceFromCamera) {
    // Placer le cube à une distance fixe devant la caméra
    vector3d normalizedCamOrientation = cameraOrientation;
	normalizedCamOrientation.normalize();
	position = cameraPosition + normalizedCamOrientation * distanceFromCamera;	
    // Garder la même orientation que la caméra
    rot = atan2(cameraOrientation.z, cameraOrientation.x); // Met à jour l'angle Y du cube pour correspondre à la caméra
    
}


camera::camera()
{
		
	camPitch=0.0f;
	camYaw=-90.0f;
	mousevel=0.2f;
	movevel=0.9f;
	mi=false;
	mi2=false;
	MidX=480;
	MidY=270;
	up=0;
	down=0;
	left=0;
	right=0;
	actif=false;
	
	bb=new boundingboxCam(vector3d(180,0,0));
//	bb.push_back(new boundingboxCam(vector3d(-140,0,0)));
	
	collidersDetection.push_back(new boundingboxCam(vector3d(-500,50,1000)));
	collidersDetection.push_back(new boundingboxCam(vector3d(6200,50,1000)));
	
	collidersDetection.push_back(new boundingboxCam  (vector3d(-500,50,1300)));
	collidersDetection.push_back(new boundingboxCam  (vector3d(4500,50,1300)));
	
	collidersDetection.push_back(new boundingboxCam  (vector3d(4500,50,1300)));
	collidersDetection.push_back(new boundingboxCam  (vector3d(4500,50,1700)));
	
	collidersDetection.push_back(new boundingboxCam  (vector3d(6200,50,-1000)));
	collidersDetection.push_back(new boundingboxCam  (vector3d(6200,50,2500)));
	
	collidersDetection.push_back(new boundingboxCam  (vector3d(5500,50,2200)));
	collidersDetection.push_back(new boundingboxCam  (vector3d(-9800,50,2200)));
	
	
	collidersDetection.push_back(new boundingboxCam  (vector3d(4500,50,1700)));
	collidersDetection.push_back(new boundingboxCam  (vector3d(-9200,50,1700)));
	
	collidersDetection.push_back(new boundingboxCam  (vector3d(-9800,50,2200)));
	collidersDetection.push_back(new boundingboxCam  (vector3d(-9800,50,-100)));
	
	collidersDetection.push_back(new boundingboxCam  (vector3d(-9200,50,1700)));
	collidersDetection.push_back(new boundingboxCam  (vector3d(-9200,50,200)));
	
	collidersDetection.push_back(new boundingboxCam  (vector3d(-9800,50,-300)));
	collidersDetection.push_back(new boundingboxCam  (vector3d(-2500,50,-300)));
	
	collidersDetection.push_back(new boundingboxCam  (vector3d(-9200,50,100)));
	collidersDetection.push_back(new boundingboxCam  (vector3d(-2900,50,100)));

	collidersDetection.push_back(new boundingboxCam  (vector3d(-2900,50,100)));
	collidersDetection.push_back(new boundingboxCam  (vector3d(-2900,50,1600)));
	
	collidersDetection.push_back(new boundingboxCam  (vector3d(-2500,50,-300)));
	collidersDetection.push_back(new boundingboxCam  (vector3d(-2500,50,1100)));
	
	collidersDetection.push_back(new boundingboxCam  (vector3d(-2500,50,1100)));
	collidersDetection.push_back(new boundingboxCam  (vector3d(-500,50,1100)));
	
	collidersDetection.push_back(new boundingboxCam  (vector3d(-2900,50,1300)));
	collidersDetection.push_back(new boundingboxCam  (vector3d(-500,50,1300)));
}
camera::~camera()
{
	delete bb;
}
void camera::moveCamera(float dir)
{
	float rad=(camYaw+dir)*M_PI/180.0;

	loc.x-=sin(rad)*movevel*speed;
	loc.z-=cos(rad)*movevel*speed;


}
void camera::lockCamera()
{
	if(camPitch>90)
		camPitch=90;
	if(camPitch<-90)
		camPitch=-90;
	if(camYaw<0.0)
		camYaw+=360.0;
	if(camYaw>360.0)
		camYaw-=360;
}


void camera::moveCameraUp(float dir)
{
  float rad=(camPitch+dir)*M_PI/180.0;
  loc.y+=sin(rad)*movevel;
}

void camera::control(int x,int y)
{


		
if(mi)
{
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		lockCamera();
		camYaw+=mousevel*(MidX-x);
		camPitch+=mousevel*(MidY-y);
		glutWarpPointer(MidX,MidY);
	}

	else
	{
	
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}
	
}

void camera::collisionCameraAndGround()
{
	if(getLocation().x>-2500 && getLocation().x<9000 && getLocation().z>1000 && getLocation().z<1300 && getLocation().y<70)
	{
		setLocation(vector3d(getLocation().x,70,getLocation().z));
	}
	else
	{
	   if(getLocation().y<110)
		setLocation(vector3d(getLocation().x,110,getLocation().z));
	}
}


void camera::updateCollision()
{
	float radPitch = camPitch * (M_PI / 180.0f);
	float radYaw = camYaw * (M_PI / 180.0f);
	
	float dirX = cos(radPitch) * sin(radYaw);
	float dirY = sin(radPitch);
	float dirZ = cos(radPitch) * cos(radYaw);

// Direction vector (normalized)
	vector3d direction(dirX, dirY, dirZ);
	direction.normalize(); // Ensure the vector is a unit vector
	vector3d positionInFront = loc + (direction * 50.0f);

	bb->setInFrontOfCamera(getLocation(), direction , 50.0f);
}

void camera::drawCollision()
{
	bb->draw();
}

void camera::update()
{
	glRotated(-camPitch,1,0,0);
	glRotated(-camYaw,0,1,0);
	glTranslated(-loc.x,-loc.y,-loc.z);
}



void camera::setLocation(vector3d l)
{
	loc=l;
}
void camera::setLocation2(vector3d vec)
{
	loc+=vec;
}
vector3d camera::getLocation()
{
	return loc;
}
void camera::mouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON)
	{
	mi=true;
	}
		else if(state==GLUT_DOWN && button==GLUT_RIGHT_BUTTON)
	{
	mi2=true;
	}
else
	{
		mi2=false;
		mi=false;
	
	}
	
	

	

}

void camera::setMouseVel(float speed)
{
	movevel+=speed;
	if(	movevel>2.0f)
	{
			movevel=2.0f;
	}
		if(	movevel<0.0f)
	{
			movevel=0.0f;
	}
}

	

float camera::getMousevel()
{
	return mousevel;
}

float camera::getPitch()
{
	return camPitch;
}
float camera::getYaw()
{
	return camYaw;
}

int camera::getUP()
{
	return up;
	
}
int camera::getDOWN()
{
	return down;
	
}
int camera::getRIGHT()
{
	return right;
	
}
int camera::getLEFT()
{
	return left;
	
}

void camera::setUP(int num)
{
	up=num;
}
void camera::setDOWN(int num)
{
	down=num;
}
void camera::setRIGHT(int num)
{
	right=num;
}
void camera::setLEFT(int num)
{
	left=num;
}
	 void camera::setActif(bool b)
		 {
		 	actif=b;
		 }
		 
		 bool camera::getActif()
		 {
		 	return actif;
		 }
		
		void camera::lookAt(float pitch,float yaw)
{
	camPitch=pitch;
	camYaw=yaw;
}

void camera::mouseIn(bool b)
{
	mi=b;
}

void camera::setSpeed(float mv,float mov)
{
	movevel=mv;
	mousevel=mov;
}

void camera::setSpeed(float s)
{
	speed=s;
}

bool camera::isMoved()
{
	return ismoved;
}

float camera::getMovevel()
{
	return movevel;
}
vector3d camera::getVector()
{
	//Google->spherical to cartesian
 	return (vector3d(-cos(camPitch*M_PI/180.0)*sin(camYaw*M_PI/180.0),sin(camPitch*M_PI/180.0),-cos(camPitch*M_PI/180.0)*cos(camYaw*M_PI/180.0)));
}


