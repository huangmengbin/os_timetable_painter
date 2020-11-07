#pragma once

#include "Equipment.h"
#include "Base.h"

class Equipment;

class Task :
	public Base
{

public:
	Task();
	~Task();
	Task* usingEquipment(Equipment*, PII);
	Task* usingEquipment(Equipment* , int, int);

	vector<Triplet(Equipment*, int, int)> equipmentInfos;
};

