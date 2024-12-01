#include"sound.h"

sound::sound()
{
	ALCdevice * device=alcOpenDevice(NULL);
	if(device==NULL)
	{
		std::cout<<"not open card sound"<<std::endl;

	}
	ALCcontext * context=alcCreateContext(device,NULL);
	if(context==NULL)
	{
		std::cout<<"context not open"<<std::endl;
		
	}
	alcMakeContextCurrent(context);
}
sound::~sound()
{
	for(int i=0;i<datas.size();i++)
	{
		alDeleteSources(1,(unsigned int *) &datas[i].sourceid);
		if(datas[i].bufferid!=-1)
		{
		
		  alDeleteSources(1,(unsigned int *) &datas[i].bufferid);
		  delete[] datas[i].buffer;
	}
	}
	alcDestroyContext(context);
	alcCloseDevice(device);
}
unsigned int sound::loadSound(const char * filename)
{
	bool found=false;
	unsigned int sourceId,bufferId;
	char * soundData=NULL;
	for(int i=0;i<datas.size();i++)
		if(datas[i].name==filename && datas[i].bufferid!=-1)
		{
			bufferId=datas[i].bufferid;
			found=true;
			break;
		}
		if(!found)
		{
			int channel,samplerate,bps,size;
			char * soundData=loadWAV(filename,channel,samplerate,bps,size);
			unsigned int format;
			alGenBuffers(1,&bufferId);
			if(channel==1)
			{
				if(bps==8)
				{
					format=AL_FORMAT_MONO8;
				}
				else
				{
					format=AL_FORMAT_MONO16;
				}
				
			}
			else
			{
				if(bps==8)
				{
					format=AL_FORMAT_STEREO8;
				}
				else
				{
					format=AL_FORMAT_STEREO16;
				}
			}
			alBufferData(bufferId,format,soundData,size,samplerate);
			
		}
		alGenSources(1,&sourceId);
		alSourcei(sourceId,AL_BUFFER,bufferId);
		alSourcef(sourceId,AL_REFERENCE_DISTANCE,3.0);
		datas.push_back(data(sourceId,(!found ? bufferId : -1),soundData,filename));
		return sourceId;
	
}
void sound::playSound(unsigned int id)
{
	alSourcePlay(id);
}
void sound::playSound(unsigned int id,const vector3d & position,float pitch)
{
	//alSourcei(id, AL_LOOPING, 1);
	alSourcef(id, AL_PITCH, pitch);
	alSource3f(id,AL_POSITION,position.x,position.y,position.z);
	alSourcePlay(id);
}
void sound::stopSound(unsigned int id)
{
	alSourceStop(id);
}
void sound:: setListener(const vector3d & position,const vector3d & orien)
{
	alListener3f(AL_POSITION,position.x,position.y,position.z);
	float orientation[6]={orien.x,orien.y,orien.z,0,1,0};
	alListenerfv(AL_ORIENTATION,orientation);
}
bool sound::isBigEndian_()
{
	int a=1;
	return!((char*)&a)[0];
}
int sound::convertToInt(char * buffer, int len)
{
	int a=0;
	if(!isBigEndian_())
	{
		for(int i=0;i<len;i++)
		{
			((char*) &a)[i]=buffer[i];
		}
	}
	else
	{
		for(int i=0;i<len;i++)
		{
			((char*) &a)[3-i]=buffer[i];
		}
	}
	return a;
}

char * sound::loadWAV(const char * fn,int & chan,int & samplerate,int & bps,int & size)
{
	char buffer[4];
	std::ifstream in(fn,std::ios::binary);
	in.read(buffer,4);
	if(strncmp(buffer,"RIFF",4)!=0)
	{
		std::cout<<"not wave!"<<std::endl;
	}
	in.read(buffer,4);
	in.read(buffer,4);
	in.read(buffer,4);
	in.read(buffer,4);
	in.read(buffer,2);
	in.read(buffer,2);
	chan=convertToInt(buffer,2);
	in.read(buffer,4);
	samplerate=convertToInt(buffer,4);
	in.read(buffer,4);
	in.read(buffer,2);
	in.read(buffer,2);
	size=convertToInt(buffer,4);
	char * soundData=new char[size];
	in.read(soundData,size);
	return soundData;
}
