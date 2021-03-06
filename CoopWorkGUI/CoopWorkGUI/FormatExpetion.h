#pragma once
#include <exception>
#include<string>
using namespace std;

/*Too Few*/
class TFException : public exception {
public:
	const string info() const throw() {
		return "请输入至少两个图形！";
	}
};

/*DotSame*/
class DSException : public exception {
public:
	const string info() const throw() {
		return "用来确定直线的两点不能重合！";
	}
};

/*Same Line*/
class SLException : public exception {
public:
	const string info() const throw() {
		return "有两个几何图形之间有无穷的交点";
	}
};

/*TypeError*/
class TException : public exception {
public:
	const string info() const throw() {
		return "支持的图形种类仅为：C, L, S, R";
	}
};

/*IntegerNeeded*/
class INException : public exception {
public:
	const string info() const throw() {
		return "坐标请输入一个(-100000, 100000)之间的无前导0标准整数";
	}
};

/*RadicusInvaild*/
class RIException : public exception {
public:
	const string info() const throw() {
		return "圆的半径不可以小于或等于0或者大于或等于100000";
	}
};