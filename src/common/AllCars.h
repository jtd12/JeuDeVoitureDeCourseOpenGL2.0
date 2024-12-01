#ifndef DEF_ALLCARS_H
#define DEF_ALLCARS_H
#include"carAI.hpp"
#include"car.h"

class allVehicule
{
public:
	allVehicule();
	~allVehicule();
	std::vector<vehiculeAI*> carAI;
	vehicule* car;
};

#endif
