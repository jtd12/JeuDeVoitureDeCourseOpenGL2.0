#ifndef DEF_SOUND_H
#define DEF_SOUND_H
#include<fstream>
#include"C:\library\mathsutils\include\vector.h"
#include<iostream>
#include<cstring>
#include<vector>
#include"C:\library\OpenAL 1.1 SDK\include\al.h"
#include"C:\library\OpenAL 1.1 SDK\include\alc.h"

using namespace std;
class sound
{
public:
	
sound();
~sound();
unsigned int loadSound(const char * name);
void deleteSound(unsigned int id);
void playSound(unsigned int id);
void playSound(unsigned int id,const vector3d & position,float pitch);
void stopSound(unsigned int id);
void setListener(const vector3d & position,const vector3d & orientation);


struct data
{
	 int sourceid,bufferid;
	char * buffer;
	std::string name;
	data(unsigned int si, unsigned int bi,char *d,const char *n): sourceid(si),bufferid(bi),buffer(d),name(n){
	}
};

private:
	std::vector<data> datas;
	ALCcontext * context;
	ALCdevice * device;
	bool isBigEndian;
	char * loadWAV(const char * fn,int & chan,int & samplerate,int & bps,int & size);
	int convertToInt(char * buffer, int len);
	bool isBigEndian_();
	
};

#endif
