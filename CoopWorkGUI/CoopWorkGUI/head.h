#pragma once
#include <iostream>
#include <fstream>
#include <set>
#include <cmath>
#include <vector>
#include <set>
#include<string>
#include <unordered_set>
#include<algorithm>
#include<regex>
using namespace std;
#define EPS 1e-7

// Point: (x, y)
struct Point
{
	double x, y;

	Point() :x(), y() {}

	Point(double x, double y) :x(x), y(y) {}

	bool operator == (const Point& other) const {
		return fabs(x - other.x) <= EPS && fabs(y - other.y) <= EPS;
	}

	bool operator < (const Point& other) const {
		if (fabs(x - other.x) <= EPS && fabs(y - other.y) <= EPS) return false;
		else return (x != other.x) ? x < other.x : y < other.y;
	}

};

// Line: ax + by + c = 0 (a^2+b^2!=0)
class Line
{
public:
	int a, b, c;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	Line() :a(), b(), c() {}

	Line(int a, int b, int c) :a(a), b(b), c(c) {}

	Line(int x1, int y1, int x2, int y2) : a(y1 - y2), b(x2 - x1), c(x1* y2 - x2 * y1),
	x1(x1), y1(y1), x2(x2), y2(y2){}

	bool isParel(Line B) {
		return a * B.b == B.a * b;
	}

	bool isSame(Line B) {
		return isParel(B) && a * B.c == c * B.a;
	}
};

// Circle: (x-x0)^2 + (y-y0)^2 = r0^2, x^2 + y^2 + dx + ey + f = 0
class Circle
{
public:
	int x, y, r;
	int d, e, f;

	Circle() :x(), y(), r(), d(), e(), f() {}

	Circle(int x0, int y0, int r0) :x(x0), y(y0), r(r0), d(-2 * x0), e(-2 * y0),
		f((int)(pow(x0, 2) + pow(y0, 2) - pow(r0, 2))) {}
};

class Ray : public Line {
public:
	struct Point startPoint;
	int type;

	Ray(int x1, int y1, int x2, int y2) :Line(x1, y1, x2, y2) {
		startPoint = Point(x1, y1);
		if (x1 < x2 && y1 < y2) type = 1;
		else if (x1 < x2 && y1 > y2) type = 2;
		else if (x1 > x2&& y1 > y2) type = 3;
		else if (x1 > x2&& y1 < y2) type = 4;
		else if (x1 == x2 && y1 < y2) type = 5;
		else if (y1 == y2 && x1 < x2) type = 6;
		else if (x1 == x2 && y1 > y2) type = 7;
		else if (y1 == y2 && x1 > x2) type = 8;
		else type = 0;
	}

	Ray() : Line(){
		startPoint = Point();
		type = 0;
	}

	int vaild(Point A) {
		if (startPoint.x == A.x && startPoint.y == A.y) return 2;
		else if (
			type == 1 && startPoint.x < A.x && startPoint.y < A.y
			|| type == 2 && startPoint.x < A.x && startPoint.y > A.y
			|| type == 3 && startPoint.x > A.x&& startPoint.y > A.y
			|| type == 4 && startPoint.x > A.x&& startPoint.y < A.y
			|| type == 5 && startPoint.y < A.y
			|| type == 6 && startPoint.x < A.x
			|| type == 7 && startPoint.y > A.y
			|| type == 8 && startPoint.x > A.x) 
			return 1;
		return 0;
	}

	bool isCoincide(Ray A) {
		return Line::isSame(A) && (vaild(A.startPoint) == 1 || vaild(A.startPoint) == 2 && A.type == type);
	}
};

class Segment : public Ray {
public:
	struct Point endPoint;

	Segment() : Ray(){
		endPoint = Point();
	}

	Segment(int x1, int y1, int x2, int y2) : Ray(x1, y1, x2, y2) {
		endPoint = Point(x2, y2);
	}

	int vaild(Point A) {
		if (startPoint.x == A.x && startPoint.y == A.y) return 3;
		else if (endPoint.x == A.x && endPoint.y == A.y) return 2;
		else if (
			type == 1 && startPoint.x < A.x && startPoint.y < A.y && endPoint.x > A.x&& endPoint.y > A.y
			|| type == 2 && startPoint.x < A.x && startPoint.y > A.y && endPoint.x > A.x&& endPoint.y < A.y
			|| type == 3 && startPoint.x > A.x&& startPoint.y > A.y&& endPoint.x < A.x && endPoint.y < A.y
			|| type == 4 && startPoint.x > A.x && startPoint.y < A.y && endPoint.x < A.x && endPoint.y > A.y
			|| type == 5 && startPoint.y < A.y && endPoint.y > A.y
			|| type == 6 && startPoint.x < A.x && endPoint.x > A.x
			|| type == 7 && startPoint.y > A.y && endPoint.y < A.y
			|| type == 8 && startPoint.x > A.x && endPoint.x < A.x)
			return 1;
		return 0;
	}

	bool isCoincide(Ray A) {
		return Line::isSame(A) && (vaild(A.startPoint) == 1 
			|| vaild(A.startPoint) == 3 && A.type == type 
			||vaild(A.startPoint) == 2 && A.type != type);
	}

	bool isCoincide(Segment A) {
		return Line::isSame(A)
			&& (vaild(A.startPoint) == 1
				|| vaild(endPoint) == 1
				|| vaild(A.startPoint) == 3 && type == A.type
				|| vaild(A.endPoint) == 2 && type != A.type);
	}
};

//hash of point set
struct PointHash {
	std::size_t operator()(const Point& point) const
	{
		return std::hash<double>()(point.x) + (std::hash<double>()(point.y) << 16);
	}
};

typedef std::set<Point> MySet;

__declspec(dllimport) bool isNum(std::string s);
__declspec(dllimport) bool rangeVaild(int n);
__declspec(dllimport) void inputCheck(ifstream& fileIn, int& x1, int& y1, int& x2, int& y2);
__declspec(dllimport) void inputCheck(ifstream& fileIn, int& x, int& y, int& r);
// calculate the intersections of two lines
__declspec(dllimport) Point* calLineLineIst(Line line1, Line line2);

// calculate the intersections of line and Circle
__declspec(dllimport) vector<Point> calLineCircleIst(Line line, Circle circle);

// calculate intersections of two circles
__declspec(dllimport) vector<Point> calCircleCircleIst(Circle circle1, Circle circle2);


__declspec(dllimport) vector<string> split(const string& str, const string& pattern);

__declspec(dllimport) void inputCheck2(vector<string> input, int& x1, int& y1, int& x2, int& y2);

__declspec(dllimport) void inputCheck2(vector<string> input, int& x, int& y, int& r);

__declspec(dllimport) MySet result(vector<string> fileIn);