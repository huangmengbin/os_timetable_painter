#include "Painter.h"



Painter::Painter()
{
}


Painter::~Painter()
{
}

void Painter::mysort() {
	for (Task* task : this->tasks) {
		sort(all(task->equipmentInfos), [](Triplet(Base*, int, int)a, Triplet(Base*, int, int)b) {return a.second.first < b.second.first; });
	}
	for (Equipment* equipment : this->equipments) {
		sort(all(equipment->taskInfos), [](Triplet(Base*, int, int)a, Triplet(Base*, int, int)b) {return a.second.first < b.second.first; });
	}
}

void Painter::calculateTimes() {
	this->times.clear();
	for (Task* task : this->tasks) {
		for (Triplet(Base*, int, int) equipmentInfo : task->equipmentInfos) {
			this->times.push_back(equipmentInfo.second.second);
		}
	}
	sort(all(times));
	times.erase( unique(all(times)), times.end());
	this->maxTime = times.back();
}

string Painter::getTimeAxis() {
	string numbers = "0";
	string result = SPACE;
	const int cnt = getAdjustedValue(split);
	for_range_n(i,split,maxTime+split,split) {
		const string number = to_string(i);
		numbers += getSpaces(cnt-number.length());
		result += getSpaces(cnt-1);
		numbers += number;
		result += SEPATATOR;
	}
	return numbers + LINE_BREAK + toUnderLine(result) + LINE_BREAK + LINE_BREAK;

}


string Painter::getVerticalLines() {
	string result = SPACE;
	int history = 0;
	for (const int time : times) {
		if (time != 0) {
			const int cnt = getAdjustedValue(time - history);
			result += getSpaces(cnt - 1);
			result += VERTICAL_LINE;
			history = time;
		}
	}
	return "<font color=\"blue\">" + result + "</font>" + BR;
}


Painter* Painter::buildByEquipmentInfoOfTask() {
	for (Equipment* equipment : this->equipments) {
		equipment->taskInfos.clear();
	}
	for (Task* task : this->tasks) {
		for (Triplet(Equipment*, int, int) equipmentInfo : task->equipmentInfos) {
			equipmentInfo.first->usedByTask(task, equipmentInfo.second);
		}
	}
	mysort();
	calculateTimes();
	return this;
}

Painter* Painter::buildByTaskInfoOfEquipment() {
	for (Task* task : this->tasks) {
		task->equipmentInfos.clear();
	}
	for (Equipment* equipment : this->equipments) {
		for (Triplet(Task*, int, int) taskInfo : equipment->taskInfos) {
			taskInfo.first->usingEquipment(equipment, taskInfo.second);
		}
	}
	mysort();
	calculateTimes();
	return this;
}

Painter* Painter::setSplit(int split) {
	this->split = split;
	return this;
}

Painter* Painter::setVerticalLineLen(int l) {
	this->verticalLineLength = l;
	return this;
}

Painter* Painter::setPrintMode(int mode) {
	this->mode = mode;
	return this;
}

Painter* Painter::setFontSize(int size) {
	this->font_size = size;
	return this;
}

Painter* Painter::setLineSpacing(double spacing) {
	this->lineSpacing = spacing;
	return this;
}

Painter* Painter::setZoomIn(int zoom_in){
	this->zoom_in = zoom_in;
	return this;
}
Painter* Painter::setZoomOut(int zoom_out){
	this->zoom_out = zoom_out;
	return this;
}

Painter* Painter::printText() {
	cout << "任务运行情况：" << endl;
	for (Task* task : this->tasks) {
		cout << " " << base2name[task] << ":" << endl;
		for (Triplet(Equipment*, int, int) equipmentInfo : task->equipmentInfos) {
			cout << "\t" << base2name[equipmentInfo.first] << '\t' << equipmentInfo.second.first << ' ' << equipmentInfo.second.second << endl;
		}
	}
	cout << endl;
	cout << "设备使用情况：" << endl;
	for (Equipment* equipment : this->equipments) {
		cout << " " << base2name[equipment] << ":" << endl;
		for (Triplet(Task*, int, int) taskInfo : equipment->taskInfos) {
			cout << "\t" << base2name[taskInfo.first] << '\t' << taskInfo.second.first << ' ' << taskInfo.second.second << endl;
		}
	}
	cout << endl << endl;;
	return this;
}

bool Painter::checkVallid() {
	if ( zoom_in * split % zoom_out != 0) {
		return false;
	}
	for (Equipment* equipment : this->equipments) {
		for (Triplet(Task*, int, int) taskInfo : equipment->taskInfos) {
			if (taskInfo.second.first  * zoom_in % zoom_out != 0) {
				return false;
			}
			if (taskInfo.second.second  * zoom_in % zoom_out != 0) {
				return false;
			}
		}
	}
	for (Task* task : this->tasks) {
		for (Triplet(Equipment*, int, int) equipmentInfo : task->equipmentInfos) {
			if (equipmentInfo.second.first  * zoom_in % zoom_out != 0) {
				return false;
			}
			if (equipmentInfo.second.second  * zoom_in % zoom_out != 0) {
				return false;
			}
		}
	}
	return true;
}



Painter* Painter::drawGraph() {

	if (! checkVallid()) {
		debug(this->split);
		debug(this->zoom_in);
		debug(this->zoom_out);
		return nullptr;
	}

	cout << " <div style=\" line-height:" << (lineSpacing) << "; font-size:" + to_string(font_size) + "px; font-family:consolas; \"> " << endl << endl;
	cout << getTimeAxis();
	const string LINE = getVerticalLines();
	for (Task* task : this->tasks) {
		for_range(i, 0, verticalLineLength) cout << LINE;
		cout << "<B>" << base2name[task] << "</B>" << BR;
		cout << getStates(task->equipmentInfos);
	}
	for (Equipment* equipment : this->equipments) {
		for_range(i, 0, verticalLineLength) cout << LINE;
		cout << "<B>" << base2name[equipment] << "</B>" << BR;
		cout << getStates(equipment->taskInfos);
	}
	cout << "<div>";
	return this;
}



string toUnderLine(string s) {
	return UNDERLINE_BEGIN + s + UNDERLINE_END;
}

string getDashedUnderLine(int n) {
	string result = "";
	for_range(i, 0, n) {
		if (i % 2 == 1) {				//奇
			result += SHORT_UNDERLINE;
		}
		else {						//偶
			result += SPACE;
		}
	}
	return result;
}

string getSpaces(int n) {
	string result = "";
	for_range(i, 0, n) {
		result += SPACE;
	}
	return result;
}

string getSpaces(int n, string mid) {
	string result = "";
	const int diffrence = n - mid.length();
	if (diffrence < 0) {
		return getSpaces(n);
	}

	const int left = (diffrence + 1) / 2;
	const int right = (diffrence) / 2;
	for_range(i, 0, left) {
		result += SPACE;
	}
	result += mid;
	for_range(i, 0, right) {
		result += SPACE;
	}
	return result;
}


