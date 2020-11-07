#include "Equipment.h"
#include "Task.h"



Equipment::Equipment()
{
}


Equipment::~Equipment()
{
}

Equipment* Equipment::usedByTask(Task* task, const PII pii) {
	taskInfos.push_back(make_pair(task, pii));
	return this;
}
Equipment* Equipment::usedByTask(Task* task , int start , int end) {
	taskInfos.push_back(mktp(task, start, end));
	return this;
}