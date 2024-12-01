#ifndef DEF_DECOR_H
#define DEF_DECOR_H
#include"collision/vector.h"
#include"objloader.hpp"

class decor
{
	public:
		decor(const char* c,unsigned int map , std::vector<collisionplane>& cplane, std::vector<vector3d>& sp);
		~decor();
		void update();
		void draw();
		std::vector<collisionplane>& getCollisionPlanes();
std::string& getName();
  void change(const char* c,unsigned int map , std::vector<collisionplane>& cplane, std::vector<vector3d>& sp);
 	std::vector<vector3d>& getSpawnPoints();
 	
	private:
		int mesh;
		std::vector<collisionplane> cp;
	std::vector<vector3d> spawnpoints;
	std::string name;
	
};
#endif
