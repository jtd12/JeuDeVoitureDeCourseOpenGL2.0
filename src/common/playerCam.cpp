#include"playerCam.h"

playerCam::playerCam(const char * n,collisionsphere ccs,float sprints,float normals,float looks)
{
	name=n;
	cs=ccs;
	sprintspeed=sprints;
	normalspeed=normals;
	//force.change(0,-0.05f,0);
	setPosition(ccs.center);
	cam.setSpeed(normalspeed,looks);
	isground=iscollision=issprint=false;
	energy=20;
	bulletDelay=0.1f;
	rot=0.0f;
	rot2=0.0f;
	points=0;
	energy=10;
	health=100;
	curWep=0;
	headPosition=0;
	dir=vector3d(0,0,0);
	headUp=false;
	
 
}
playerCam::~playerCam()
{


	
}


void playerCam::setSprint()
{
	if(energy>30.0)
	{
		issprint=true;
		cam.setSpeed(sprintspeed,cam.getMousevel());
	}
	else
	{
		issprint=false;
	}
}
void playerCam::stopSprint()
{
	issprint=false;
		cam.setSpeed(normalspeed,cam.getMousevel());
}

void playerCam::update(std::vector<collisionplane>& collplane)
{
	
		if(direction.y>=force.y)
			direction+=force;
			vector3d newPos(cam.getLocation());
	 		newPos+=direction;
	 			vector3d oldpos(newPos);
	 		for(int i=0;i<collplane.size();i++)
				collision::sphereplane(newPos,collplane[i].normal,collplane[i].p[0],collplane[i].p[1],collplane[i].p[2],collplane[i].p[3],cs.r);
	 					if(oldpos.y<newPos.y)
	 				{
					 isground=true;
				}
				else
				{
					isground=false;
				}
	 		setPosition(newPos);
				 
}

void playerCam::setPosition(vector3d pos)
{
	cs.center=pos;
	cam.setLocation(pos);
}

		vector3d playerCam::getLocation()
{
	return loc;
}
	 	void playerCam::setLocation(vector3d newLoc)
	 	{
	 		cs.center+=newLoc;
	 		cam.setLocation2(newLoc);
		 }
		 void playerCam::setLocation2(vector3d newLoc)
		 {
		    cs.center=newLoc;
		 	cam.setLocation(newLoc);
		 }
		 
		
		
		
	collisionsphere playerCam::getCollissionSphere()
	 	{
	 		return cs;
		 }
	
