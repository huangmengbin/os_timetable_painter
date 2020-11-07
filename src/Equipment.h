#pragma once
#include "Task.h"
#include "Base.h"

class Task;

class Equipment :
	public Base
{

public:
	Equipment();
	~Equipment();
	Equipment* usedByTask(Task*, const PII);
	Equipment* usedByTask(Task*  , int, int);

	vector<Triplet(Task*, int, int)> taskInfos;
};

