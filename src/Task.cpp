#include "Task.h"
#include "Equipment.h"


Task::Task()
{
}


Task::~Task()
{
}

Task* Task::usingEquipment(Equipment* equipment, const PII pii) {
	equipmentInfos.push_back(make_pair(equipment, pii));
	return this;
}
Task* Task::usingEquipment(Equipment* equipment, int start, int end) {
	equipmentInfos.push_back(mktp(equipment, start, end));
	return this;
}