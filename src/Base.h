#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

#define __DEBUG__

#ifdef __DEBUG__
#define debug(a) cout<<endl<<(#a)<<" :\t"<<(a)<<endl
#else
#define debug(a)
#endif

typedef pair<int, int> PII;

#define elif else if
#define for_range(i,a,b) for(int (i)=(a);(i)<(b);(i)++)
#define for_range_n(i,a,b,n) for(int (i)=(a);(i)<(b);(i)+=(n))
#define Triplet(a,b,c) pair<a,pair<b,c>>					//三元组
#define mktp(a,b,c) make_pair((a),(make_pair((b),(c))))		//三元组的构建
#define all(a) (a).begin(),(a).end()


const string SPACE = "&ensp;";			//空格
const string UNDERLINE_BEGIN = "<u>";
const string UNDERLINE_END = "</u>";
const string SHORT_UNDERLINE = UNDERLINE_BEGIN + SPACE + UNDERLINE_END;//简短的实线
const string VERTICAL_LINE = ":";		//竖直的虚线
const string SEPATATOR = "|";			//数轴上的一些点
const string _SEPATATOR_ = UNDERLINE_BEGIN + SEPATATOR + UNDERLINE_END;
const string BR = "<br>";
const string LINE_BREAK = "\n";

class Base
{
public:
	Base(){}
	virtual ~Base() {}//虚析构还是要有的
};
