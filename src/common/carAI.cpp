#include"carAI.hpp"

vehiculeAI::vehiculeAI(unsigned int car_,const char* n,collisionsphere ccs, float sprints,float looks)
{
		
		name=n;
		cs=ccs;
		sprintspeed=sprints;
		force.change(0.0,-0.45f,0.0);
		setPosition(vector3d(ccs.center));
		setSpeed(speed,looks);
		isground=iscollision=issprint=false;
		speed=rand() % 20 + 8;
		angle=0;
		maxSpeed=5.0f;
		acc=0.01f;
		dec=0.015f;
		turnSpeed=2.5f;
		s=0;
		a=vector3d(0.0,0.0,0);
		dec2=0.1f;
	    rr=0.0f;
	    rr2=0.0f;
	 	car=car_;
		actif=false;
		nn=0;
		force_=200;
		points_=0;
		for(int i=0;i<4;i++)
	 		wheel.push_back(new roue("data/vehicule/camionnete_roue.obj"));




}

vehiculeAI::~vehiculeAI()
{

	for(int i=0;i<wheel.size();i++)
	 delete wheel[i];

}

void vehiculeAI::update()
{

	for(int i=0;i<wheel.size();i++)
	 wheel[i]->update();
	 
	 for(int i=0;i<wheel.size();i++)
	  wheel[i]->setRotationz(5.5f);


}




void vehiculeAI::update(std::vector<collisionplane>& collplane)
		{
			
	
			 
			 
		if(direction.y>=force.y)
			
				direction+=force;
			//setPosition(cs.center+direction);	
			vector3d newPos(getLocation());
			newPos+=direction;
			for(int i=0;i<collplane.size();i++)
				collision::sphereplane(newPos,collplane[i].normal,collplane[i].p[0],collplane[i].p[1],collplane[i].p[2],collplane[i].p[3],cs.r);
				
				 if(getLocation().y<newPos.y)
				  isground=true;
				  else
				   isground=false;
		    	setPosition(newPos);
	
			//setPosition(cs.center+direction);	
		
		
		    /*	if(isWeapon)
		    	
		        	weapons[curWeapon]->update();
					*/
		}
	
				void vehiculeAI::update2(std::vector<collisionplane>& collplane)
		{
		
	
				vector3d newPos(getLocation());
			for(int i=0;i<collplane.size();i++)
				if(collision::sphereplane(newPos,collplane[i].normal,collplane[i].p[0],collplane[i].p[1],collplane[i].p[2],collplane[i].p[3],cs.r))
				{
		
					//speed=0.0f;
				loc=vector3d(-2400,180,1280);
			
		}
	
		
		}
		
		void vehiculeAI::setPosition(vector3d pos)
		{
			cs.center=pos;
			setLocation(pos);
		}
	
		vector3d vehiculeAI::getLocation()
{
	return loc;
}
vector3d vehiculeAI::getRotation()
{
	return  vector3d(a.x,a.y,a.z);
}

int vehiculeAI::getPOINTS()
{
	return points_;
}

void vehiculeAI::resetPoints()
{
	points_=0;

}

void vehiculeAI::setRotation(vector3d rot)
{
	a=rot;
	angle=0.0f;
}

void vehiculeAI::collisionCarAndGround()
{
	if(loc.x>-2500 && loc.x<9000 && loc.z>1000 && loc.z<1300)
	{
		loc.y=70;
	}
	else
	{
		loc.y=110;
	}
}

void vehiculeAI::setGravity()
{
	loc.y-=0.2f;
	collisionCarAndGround();
}

void vehiculeAI::limitSpeed(float s)
{
	speed=s;
	}	
	
void vehiculeAI::checkPoints(vector3d loc,vector3d loc2)
{
	float dist=sqrt(loc2.x-loc.x)*(loc2.x-loc.x)+(loc2.y-loc.y)*(loc2.y-loc.y)+(loc2.z-loc.z)*(loc2.z-loc.z);
	
	if(dist<50000)
	{
		points_+=5;
	}
}

void vehiculeAI::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glTranslated(loc.x,loc.y,loc.z);
	glRotated(a.y*180/M_PI,0,.5,0);	
	glScaled(3,3,3);

	
	glCallList(car);
	
	glTranslated(32.5,-8,-20);
	wheel[0]->draw();
	glTranslated(-60,0,0);
	wheel[1]->draw();
	glTranslated(0,0,40);
	glRotated(180,0,0.5,0);
	wheel[2]->draw();
	glTranslated(-60,0,0);
	wheel[3]->draw();

	glPopMatrix();
}




void vehiculeAI::setLocation(vector3d vec)
{
	loc.change(vec);
}
   void vehiculeAI::move()
   {
    loc.x += cos(-a.y) * speed;
    loc.z += sin(-a.y) * speed;
  
   }
   
   void vehiculeAI::setLocationIncX(float y)
{
	loc.x+=y;
}

void vehiculeAI::setLocationIncZ(float y)
{
	loc.z+=y;
}

  
 float vehiculeAI::getSpeed()
 {
 	return speed;
 }
void vehiculeAI::setSpeed(float s,float speedJoy)
{
	speed=s*speedJoy;
}

float vehiculeAI::getMaxSpeed()
{
	return maxSpeed;
}

collisionsphere vehiculeAI::getCollisionSphere()
	 	{
	 		return cs;
		 }
		 void vehiculeAI::setActif(bool b)
		 {
		 	actif=b;
		 }
		 	 bool vehiculeAI::getActif()
		 {
		 	return actif;
		 }


void vehiculeAI::findTarget()
  {
    float tx=points[nn][0];
    float ty=points[nn][1];
    float beta = a.y-atan2(-ty+loc.z,tx-loc.x);
    if (sin(beta)<0) a.y+=0.005*speed; else a.y-=0.005*speed;
    if ((loc.x-tx)*(loc.x-tx)+(loc.z-ty)*(loc.z-ty)<250*250) nn=(nn+1)%num;
   }
   
   void vehiculeAI::setNumberPath(int num)
   {
   	nn=num;
   }
