#include"AllCars.h"

allVehicule::allVehicule()
{
	
}

allVehicule::~allVehicule()
{
	
  for(int i=0;i<carAI.size();i++)
	delete carAI[i];
	
	delete car;
}


