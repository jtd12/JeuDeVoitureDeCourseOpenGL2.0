 #include"water.h"
 

water::water(std::vector<unsigned int> & anim,unsigned int na,vector3d pos,int sp,
		const char * nam)
{
			frames=anim;
			normalAnimation=na;
			speed=sp;
			name=nam;
			curPos=position;
			curFrame=0;
	
}

water::~water()
{
	
	
	
}

void water::update(int f)
{
	curFrame++;
	if(curFrame>=f)
	 curFrame=5;
}

void water::draw()
{
	glPushMatrix();
	glEnable(GL_BLEND) ;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ; 
	glTranslatef(curPos.x,curPos.y,curPos.z);
	glCallList(frames[curFrame]);
	glDisable(GL_BLEND);
	glPopMatrix();
}
