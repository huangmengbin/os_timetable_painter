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
	int split = 10;		//数轴上，每个 split 个分隔一次
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


inline Painter* Painter::add(string name, Base* base) {//这样写有点不好，两个add会很混乱hhh
	this->base2name[base] = name;
	if (typeid(*base) == typeid(Task)) {
		tasks.push_back((Task*)base);
	}
	elif(typeid(*base) == typeid(Equipment)) {
		equipments.push_back((Equipment*)base);
	}
	return this;
}
#define add(a) add((#a),(a))						//用了它，add(string name, Base* base) 不会再被外面使用，除非改名，改成push-back什么的


template<typename T>
string Painter::getStates(vector<Triplet(T*, int, int)> v) {	//T must be a subclass of Base
		//这个不用模板函数怎么实现啊？？？怎么才能写上 Base* ??
	string names = SPACE;			//PRINT_NAME_ABOVE 时候有用
	string result = _SEPATATOR_;	//那条状态轴
	int old_right = 0;
	for (Triplet(T*, int, int) info : v) {
		Base* base = (Base*)(info.first);
		const int new_left = info.second.first;
		const int new_right = info.second.second;

		if (old_right < new_left) {//之前的right和现在的left有差异
			const int cnt = getAdjustedValue(new_left - old_right);
			names += getSpaces(cnt);
			if (old_right) {			//中间被断开，应该弄虚线
				result += (getDashedUnderLine(cnt - 1) + _SEPATATOR_);
			}
			else {						//第一次，注意result是加到左边去了
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