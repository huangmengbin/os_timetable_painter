 #pragma once
#include"Base.h"
#include"Equipment.h"
#include"Task.h"



inline string toUnderLine(string s);
string getDashedUnderLine(int n);
string getSpaces(int n);
string getSpaces(int n, string mid);

const int NO_PRINT_NAME = 0;
const int PRINT_NAME_INLINE = 1;
const int PRINT_NAME_ABOVE = 2;

class Painter
{
public:
	Painter();
	~Painter();
	Painter* add(string name, Base*);
	Painter* buildByEquipmentInfoOfTask();
	Painter* buildByTaskInfoOfEquipment();
	Painter* setSplit(int);
	Painter* setPrintMode(int);
	Painter* setFontSize(int);
	Painter* setVerticalLineLen(int);
	Painter* setLineSpacing(double);
	Painter* setZoomIn(int);
	Painter* setZoomOut(int);
	Painter* printText();
	Painter* drawGraph();

	map<Base*, string> base2name;
	vector<Equipment*> equipments;
	vector<Task*> tasks;

private:
	vector<int> times;
	int maxTime;
	int split = 10;		//�����ϣ�ÿ�� split ���ָ�һ��
	int verticalLineLength = 5;
	int mode = PRINT_NAME_ABOVE;
	int font_size = 15;
	double lineSpacing = 0.67;
	int zoom_in = 1;
	int zoom_out = 1;

	void mysort();
	void calculateTimes();
	string getTimeAxis();
	string getVerticalLines();
	bool checkVallid();
	inline int getAdjustedValue(int value) {
		return zoom_in * value / zoom_out;
	}

	template<typename T>
	string getStates(vector<Triplet(T*, int, int)> v);

};


inline Painter* Painter::add(string name, Base* base) {//����д�е㲻�ã�����add��ܻ���hhh
	this->base2name[base] = name;
	if (typeid(*base) == typeid(Task)) {
		tasks.push_back((Task*)base);
	}
	elif(typeid(*base) == typeid(Equipment)) {
		equipments.push_back((Equipment*)base);
	}
	return this;
}
#define add(a) add((#a),(a))						//��������add(string name, Base* base) �����ٱ�����ʹ�ã����Ǹ������ĳ�push-backʲô��


template<typename T>
string Painter::getStates(vector<Triplet(T*, int, int)> v) {	//T must be a subclass of Base
		//�������ģ�庯����ôʵ�ְ���������ô����д�� Base* ??
	string names = SPACE;			//PRINT_NAME_ABOVE ʱ������
	string result = _SEPATATOR_;	//����״̬��
	int old_right = 0;
	for (Triplet(T*, int, int) info : v) {
		Base* base = (Base*)(info.first);
		const int new_left = info.second.first;
		const int new_right = info.second.second;

		if (old_right < new_left) {//֮ǰ��right�����ڵ�left�в���
			const int cnt = getAdjustedValue(new_left - old_right);
			names += getSpaces(cnt);
			if (old_right) {			//�м䱻�Ͽ���Ӧ��Ū����
				result += (getDashedUnderLine(cnt - 1) + _SEPATATOR_);
			}
			else {						//��һ�Σ�ע��result�Ǽӵ����ȥ��
				result = getSpaces(cnt) + result;
			}
		}

		const int cnt = getAdjustedValue(new_right - new_left);
		names += getSpaces(cnt - 1, base2name[base]) + SPACE;

		if (mode & PRINT_NAME_INLINE) {
			result += toUnderLine(getSpaces(cnt - 1, base2name[base]) + SEPATATOR);
		}
		else {
			result += toUnderLine(getSpaces(cnt - 1) + SEPATATOR);
		}

		old_right = new_right;
	}//END for

	if (mode & PRINT_NAME_ABOVE) {
		return names + LINE_BREAK + result + LINE_BREAK + LINE_BREAK;
	}
	else {
		return LINE_BREAK + result + LINE_BREAK + LINE_BREAK;
	}

}