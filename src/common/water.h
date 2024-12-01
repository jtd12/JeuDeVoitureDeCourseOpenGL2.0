#ifndef DEF_WATER_H
#define DEF_WATER_H
#include"collision/vector.h"
#include<vector>
#include <GL/gl.h>
#include<GL/glu.h>
#include<iostream>
#include<string>

class water
{
	public:
		water(std::vector<unsigned int> & anim,unsigned int na,vector3d pos,int sp,
		const char * nam);
		~water();
		void update(int f);
		void draw();
		
	private:
		std::vector<unsigned int> frames;
				unsigned int outerview;
				unsigned int normalAnimation;
				vector3d position;
				vector3d aimPosition;
				vector3d aimRotation;
				vector3d rotation;
				vector3d curPos;
				unsigned int speed;
				unsigned int curFrame;
				std::string name;
};

#endif
