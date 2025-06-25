#include"car.h"

roue::roue(const char * filename)
{
	//collision::modifyValueCollision(10.0f);
	obj=new objloader();
	roue_=obj->load(filename,NULL);
}

roue::~roue()
{
	delete obj;
}
void roue::update()
{
	
}
void roue::draw()
{
	glPushMatrix();
	glRotated(rot_roue.y,0,0.5,0);
	glRotated(rot_roue.z,0,0,0.5);
	glCallList(roue_);
	glPopMatrix();
}

vector3d roue::getRotation()
{
	return rot_roue;
}
		void roue::setRotationz(float m)
		{
			rot_roue.z+=m;
			
		}
	
			void roue::setRotationzegal(float m)
		{
			rot_roue.z=m;
		}
		
			void roue::setRotationy(float m)
		{
			rot_roue.y+=m;
			
		}
	
			void roue::setRotationyegal(float m)
		{
			rot_roue.y=m;
		}


boundingbox::boundingbox(vector3d pos)
{
	position=pos;
}

boundingbox::~boundingbox()
{
	
}

void boundingbox::update()
{


}

void boundingbox::draw()
{
	glPushMatrix();
	glTranslated(position.x,position.y,position.z);
	glRotated(rot,0,0.5,0);
	glScaled(1,1,1);
	glColor3d(0.5,0.4,0.4);
	glutSolidCube(30);
	glPopMatrix();
}

vector3d boundingbox::getLocation()
{
	return position;
}

void boundingbox::setParent(vector3d parent,float rotationY,int offset)
{
	position=vector3d(parent.x+cos(-rotationY*M_PI/180)*offset,parent.y+2,parent.z+sin(-rotationY*M_PI/180)*offset);
	rot=rotationY;
}


vehicule::vehicule(const char* n,collisionsphere ccs, float sprints,float normals,float looks)
{
		name=n;
		cs=ccs;
		sprintspeed=sprints;
		normalspeed=normals;
		force.change(0.0,-0.15f,0.0);
		setPosition(vector3d(cs.center));
		setSpeed(normalspeed,looks);
		isground=iscollision=issprint=false;
		speed=normals;
		angle=0;
		maxSpeed=rand() % 10 + 12;
		acc=0.04f;
		dec=0.05f;
		turnSpeed=2.5f;
		up=0;
		down=0;
		left=0;
		right=0;
		s=0;
		a=vector3d(0.0,0.0,0);
		a_touch=0;
		dec2=0.9f;
	    rr=0.0f;
	    rr2=0.0f;
	    force_=200;
	    points=0;
	    
	collidersDetection.push_back(new boundingbox(vector3d(-500,50,1000)));
	collidersDetection.push_back(new boundingbox(vector3d(6200,50,1000)));
	
	collidersDetection.push_back(new boundingbox(vector3d(-500,50,1300)));
	collidersDetection.push_back(new boundingbox(vector3d(4500,50,1300)));
	
	collidersDetection.push_back(new boundingbox(vector3d(4500,50,1300)));
	collidersDetection.push_back(new boundingbox(vector3d(4500,50,1700)));
	
	collidersDetection.push_back(new boundingbox(vector3d(6200,50,-1000)));
	collidersDetection.push_back(new boundingbox(vector3d(6200,50,2500)));
	
	collidersDetection.push_back(new boundingbox(vector3d(5500,50,2200)));
	collidersDetection.push_back(new boundingbox(vector3d(-9800,50,2200)));
	
	
	collidersDetection.push_back(new boundingbox(vector3d(4500,50,1700)));
	collidersDetection.push_back(new boundingbox(vector3d(-9200,50,1700)));
	
	collidersDetection.push_back(new boundingbox(vector3d(-9800,50,2200)));
	collidersDetection.push_back(new boundingbox(vector3d(-9800,50,-100)));
	
	collidersDetection.push_back(new boundingbox(vector3d(-9200,50,1700)));
	collidersDetection.push_back(new boundingbox(vector3d(-9200,50,200)));
	
	collidersDetection.push_back(new boundingbox(vector3d(-9800,50,-300)));
	collidersDetection.push_back(new boundingbox(vector3d(-2500,50,-300)));
	
	collidersDetection.push_back(new boundingbox(vector3d(-9200,50,100)));
	collidersDetection.push_back(new boundingbox(vector3d(-2900,50,100)));

	collidersDetection.push_back(new boundingbox(vector3d(-2900,50,100)));
	collidersDetection.push_back(new boundingbox(vector3d(-2900,50,1600)));
	
	collidersDetection.push_back(new boundingbox(vector3d(-2500,50,-300)));
	collidersDetection.push_back(new boundingbox(vector3d(-2500,50,1100)));
	
	collidersDetection.push_back(new boundingbox(vector3d(-2500,50,1100)));
	collidersDetection.push_back(new boundingbox(vector3d(-500,50,1100)));
	
//	collidersDetection.push_back(new boundingbox(vector3d(-2900,50,1300)));
//	collidersDetection.push_back(new boundingbox(vector3d(-500,50,1300)));
	
	obj=new objloader();	
	car=obj->load("data/vehicule/vehicule0.obj",NULL);
	collision::modifyValueCollision(15.0f);
	actif=true;
	part.push_back(new particule((int)speed));
	part.push_back(new particule((int)speed));
	bb.push_back(new boundingbox(vector3d(180,0,0)));
	bb.push_back(new boundingbox(vector3d(-140,0,0)));
	for(int i=0;i<4;i++)
	 wheel.push_back(new roue("data/vehicule/camionnete_roue.obj"));




}

vehicule::~vehicule()
{
	delete obj;
for(int i=0;i<part.size();i++)
	delete part[i];
	for(int i=0;i<wheel.size();i++)
	 delete wheel[i];
	for(int i=0;i<bb.size();i++)
	delete bb[i];
}

void vehicule::update(float time)
{

	control(time);
	
   
	bb[0]->setParent(getLocation(),getRotation().y,150);
	bb[1]->setParent(getLocation(),getRotation().y,-150);
	
	for(int i=0;i<wheel.size();i++)
	 wheel[i]->update();


}

void vehicule::checkPoints(vector3d loc,vector3d loc2)
{
	float dist=sqrt(loc2.x-loc.x)*(loc2.x-loc.x)+(loc2.y-loc.y)*(loc2.y-loc.y)+(loc2.z-loc.z)*(loc2.z-loc.z);
	
	if(dist<50000)
	{
		points+=5;
	}
}

void vehicule::setPoints(int p)
{
	points-=p;
	if(points<0)
	{
		points=0;
	}
}

int vehicule::getPOINTS()
{
	return points;
}

void vehicule::resetPoints()
{
	points=0;

}

void vehicule::setGravity()
{
	loc.y-=0.2f;
	collisionCarAndGround();
}


void vehicule::collisionCarAndGround()
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


void vehicule::limitSpeed(float s)
{
	speed=s;
	}	

void vehicule::update(std::vector<collisionplane>& collplane)
		{
			
printf("maxSpeed: %.2f",maxSpeed);
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
	

		
		
		
		void vehicule::setPosition(vector3d pos)
		{
			cs.center=pos;
			setLocation(pos);
		}
	
		vector3d vehicule::getLocation()
{
	return loc;
}
vector3d vehicule::getRotation()
{
	return  vector3d(a.x,a.y,a.z);
}

void vehicule::setRotation(vector3d rot)
{
	a=rot;
	angle=0.0f;
}

void vehicule::setLocationIncX(float y)
{
	cs.center.x+=y;
}

void vehicule::setLocationIncZ(float y)
{
	loc.z+=y;
}



void vehicule::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glTranslated(loc.x,loc.y,loc.z);
	glRotated(a.y,0,0.5,0);	
	glScaled(3,3,3);
	
	glCallList(car);
	
	

	part[0]->draw(-10,(int)speed);
	part[1]->draw(10,(int)speed);

	
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

void vehicule::setLocation(vector3d vec)
{
	loc.change(vec);
}
   void vehicule::move()
   {
    loc.x += cos(-a.y*M_PI/180) * s;
    loc.z += sin(-a.y*M_PI/180) * s;
  
   }
   void vehicule::inputSpecial(char key,int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
		 up=true;
	
		 glutPostRedisplay();
		 break;
		 case GLUT_KEY_DOWN:

		 down=true;	
		 glutPostRedisplay();
		 break;
		 case GLUT_KEY_RIGHT:
	
		 right=true;
		 glutPostRedisplay();
		 break;
		 case GLUT_KEY_LEFT:
		 	
		left=true;
		glutPostRedisplay();
	
	}
}
   void vehicule::inputSpecialUP(char key,int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
		 up=false;
		 glutPostRedisplay();
		 break;
		 case GLUT_KEY_DOWN:
		 down=false;
		 glutPostRedisplay();	
		 break;
		 case GLUT_KEY_RIGHT:
		 right=false;
		 glutPostRedisplay();
		 break;
		 case GLUT_KEY_LEFT:
		left=false;
		glutPostRedisplay();
		break;
	
	}
}
void vehicule::keyboard(char key, int x, int y)
{
	switch(key)
	{
	
		case  SPACEBAR:
		a_touch=true;
		glutPostRedisplay();
		break;
	}
}
void vehicule::keyboardUP(char key, int x, int y)
{
switch(key)
{

	case  SPACEBAR:
		a_touch=false;
		glutPostRedisplay();
		break;
	}
	}
	
void vehicule::control(float time)
{
	/*
	
			if(state[SDLK_m])
			{
					clavierAct++;
				
				}
				*/
			if(up==1 && speed<=40 && speed>1)
			{
		
			
			}
				if(up==1 && speed<=60 && speed>40)
			{
			
		
			}
			
				if(up==1 && speed<=100 && speed>60)
			{
			
			
			}
				if(up==1 && speed<=250 && speed>100)
			{
			
			
			}
			
					if(down==1 && speed>=-40 && speed<-1)
			{
			
			}
				if(down==1 && speed>=-60 && speed<-40)
			{
			
			}
			
				if(down==1 && speed>=-100 && speed<-60)
			{
			
			}
				if(down==1 && speed>=-250 && speed<-100)
			{
			
			}
			if(a_touch==1)
			{
				
			}
			
			
				if(up==1)
				{
						for(int i=0;i<wheel.size();i++)
				{
				
					wheel[i]->setRotationz(1.5f);
				}
			}
					if(down==1)
				{
						for(int i=0;i<wheel.size();i++)
				{
				
					wheel[i]->setRotationz(-1.5f);
				}
			}
			
				if(right==1)
				{
				
					wheel[0]->setRotationy(-1.0f);
					wheel[3]->setRotationy(-1.0f);
					if(wheel[0]->getRotation().y<-50.0f)
					{
						wheel[0]->setRotationyegal(-50.0f);
					}	if(wheel[3]->getRotation().y<-50.0f)
					{
						wheel[3]->setRotationyegal(-50.0f);
					}
					
				
			}
			
				if(left==1)
				{
			
					wheel[0]->setRotationy(1.0f);
					wheel[3]->setRotationy(1.0f);
						if(wheel[0]->getRotation().y>50.0f)
					{
						wheel[0]->setRotationyegal(50.0f);
					}
					if(wheel[3]->getRotation().y>50.0f)
					{
						wheel[3]->setRotationyegal(50.0f);
					}
						
				}
				
					if(right==0 && left==0)
				{
				
					wheel[0]->setRotationyegal(0.0f);
					wheel[3]->setRotationyegal(0.0f);
				
				}
			
					
					
	if(up==1 && speed<maxSpeed)
			{
			
				if(speed<0)
				{
					
					speed+=dec;
			 }
				else
				{
					speed+=acc;
				}
			}
			if(down==1 && speed>-maxSpeed)
			{
				 
				if(speed>0)
				{
				
					speed-=dec;
				}
				else
				{
					speed-=acc;
				}
				
			}
			
			if(up==0 && down==0)
			{
				if(speed-dec>0)
				{
					speed-=dec;
				}
				else if(speed+dec<0)
				{
					speed+=dec;
				}
				else
				{
					speed=0;
				}
			}
			
				if(a_touch==1)
			{
				
				
				if(speed-dec2>0)
				{
					speed-=dec2;
				}
				else if(speed+dec2<0)
				{
					speed+=dec2;
				}
				else
				{
					speed=0;
				}
			}

		if(right)
	{
		angle-=turnSpeed*(speed/maxSpeed);
	}
		if(left)
	{
		angle+=turnSpeed*(speed/maxSpeed);
	}
		s=speed;
		a.y=angle;
		
		//angle=turnSpeed;
	
	if(time<=0)	
	 move();
	
	
	
		
	
}

	
		
int vehicule::getUP()
{
	return up;
	
}
int vehicule::getDOWN()
{
	return down;
	
}
int vehicule::getRIGHT()
{
	return right;
	
}
int vehicule::getLEFT()
{
	return left;
	
}
int vehicule::getA()
{
	return a_touch;
}
void vehicule::setA(int A)
{
	a_touch=A;
}

void vehicule::setUP(int num)
{
	up=num;
}
void vehicule::setDOWN(int num)
{
	down=num;
}
void vehicule::setRIGHT(int num)
{
	right=num;
}
void vehicule::setLEFT(int num)
{
	left=num;
}


 float vehicule::getSpeed()
 {
 	return speed;
 }
void vehicule::setSpeed(float s,float speedJoy)
{
	speed=s*speedJoy;
}

float vehicule::getMaxSpeed()
{
	return maxSpeed;
}

collisionsphere vehicule::getCollissionSphere()
	 	{
	 		return cs;
		 }
		 void vehicule::setActif(bool b)
		 {
		 	actif=b;
		 }
		 	 bool vehicule::getActif()
		 {
		 	return actif;
		 }
		 


