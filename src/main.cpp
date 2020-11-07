#include"Painter.h"

void book_page52_t5() {
	Equipment* CPU = new Equipment();
	Equipment* IO1 = new Equipment();
	Equipment* IO2 = new Equipment();
	Base* job1 = (new Task())->usingEquipment(IO2, 0, 30)->usingEquipment(CPU, 30, 40)->usingEquipment(IO1, 40, 70)->usingEquipment(CPU, 70, 80);
	Base* job2 = (new Task())->usingEquipment(IO1, 0, 20)->usingEquipment(CPU, 20, 30)->usingEquipment(CPU, 40, 50)->usingEquipment(IO2, 50, 90);
	Base* job3 = (new Task())->usingEquipment(CPU, 0, 20)->usingEquipment(CPU, 50, 60)->usingEquipment(IO1, 70, 90);

	(new Painter())
		->add(CPU)->add(IO1)->add(IO2)->add(job1)->add(job2)->add(job3)
		->buildByEquipmentInfoOfTask()
		->setPrintMode(PRINT_NAME_ABOVE)
		->setVerticalLineLen(4)
		->setSplit(5)
		->setFontSize(20)
		->setLineSpacing(0.66)
		->printText();

	/*ÔÝÎ´ÊÍ·ÅÄÚ´æ*/
}



/*
	todo
*/
void t1();
void t2();
void t3();
void t4();
void t5();


int main() 
{
	book_page52_t5();
	//t1();
	//t2();
	//t3();
	//t4();
	//t5();
	getchar();
}