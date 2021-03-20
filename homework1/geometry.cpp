#include "geometry.h"

//fixed NOTE
Point::Point(int x, int y)
	: x_(x), y_(y) 
{ }

Point::Point(const Point& other)
	: x_(other.x_), y_(other.y_)
{ }

int Point::getX() const {
	return x_;
}

int Point::getY() const {
	return y_;
}

PolygonalChain::PolygonalChain(int n, Point* a) 
	: pointNum(n)
{
	allPoints = new Point[pointNum];
	std::copy_n(a, pointNum, allPoints);
}

PolygonalChain::PolygonalChain(const PolygonalChain& other)
	: pointNum(other.pointNum), allPoints(other.allPoints)
{ }

Point PolygonalChain::getPoint(int i) const {
	return allPoints[i];
}

float PolygonalChain::perimeter() const {
	float perimeter = 0;
	//fixed variables should not (sorry) start with capital letters

	for (int i = 0; i != pointNum - 1; i++) {
		perimeter += (float)sqrt(pow((allPoints[i + 1].getX() - allPoints[i].getX()), 2) + pow((allPoints[i + 1].getY() - allPoints[i].getY()), 2));
	}

	return perimeter;
}

int PolygonalChain::getN() const {
	return pointNum;
}

ClosedPolygonalChain::ClosedPolygonalChain(int n, Point* a)
	: PolygonalChain(n, a)
{ }

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain& other)
	: PolygonalChain(other) 
{ }

float ClosedPolygonalChain::perimeter() const {
	float perimeter = 0;
	perimeter = PolygonalChain::perimeter();
	perimeter += (float)sqrt(pow((allPoints[0].getX() - allPoints[pointNum - 1].getX()), 2) + pow((allPoints[0].getY() - allPoints[pointNum - 1].getY()), 2));

	return perimeter;
}

Polygon::Polygon(int n, Point* a)
	: ClosedPolygonalChain(n, a)
{ }

Polygon::Polygon(const Polygon& other)
	: ClosedPolygonalChain(other)
{ }

float Polygon::area() const {
	int area_ = 0;

	for (int i = 0; i != pointNum - 1; i++) {
		area_ += allPoints[i].getX() * allPoints[i + 1].getY();
	}
	area_ += allPoints[pointNum - 1].getX() * allPoints[0].getY();
	for (int i = 0; i != pointNum - 1; i++) {
		area_ -= allPoints[i + 1].getX() * allPoints[i].getY();
	}
	area_ -= allPoints[0].getX() * allPoints[pointNum - 1].getY();

	return (float)abs(area_) / 2;
}

Triangle::Triangle(int n, Point* a) 
	: Polygon(n, a) 
{ }

Triangle::Triangle(const Triangle& other) 
	: Polygon(other) 
{ }

bool Triangle::hasRightAngle() const {
	if (((allPoints[1].getX() - allPoints[0].getX()) * (allPoints[2].getX() - allPoints[0].getX())) + ((allPoints[1].getY() - allPoints[0].getY()) * (allPoints[2].getY() - allPoints[0].getY())) == 0) {
		return true;
	}
	if (((allPoints[0].getX() - allPoints[1].getX()) * (allPoints[2].getX() - allPoints[1].getX())) + ((allPoints[0].getY() - allPoints[1].getY()) * (allPoints[2].getY() - allPoints[1].getY())) == 0) {
		return true;
	}
	if (((allPoints[0].getX() - allPoints[2].getX()) * (allPoints[1].getX() - allPoints[2].getX())) + ((allPoints[0].getY() - allPoints[2].getY()) * (allPoints[1].getY() - allPoints[2].getY())) == 0) {
		return true;
	}
	return false;
}

Trapezoid::Trapezoid(int n, Point* a) 
	: Polygon(n, a) 
{ }

Trapezoid::Trapezoid(const Trapezoid& other) 
	: Polygon(other) 
{ }

float Trapezoid::height() const {
	Point* allVectors = new Point[pointNum];
	for (int i = 0; i != pointNum - 1; i++) {
		allVectors[i] = Point((allPoints[i + 1].getX() - allPoints[i].getX()), (allPoints[i + 1].getY() - allPoints[i].getY()));
	}
	allVectors[pointNum - 1] = Point((allPoints[0].getX() - allPoints[pointNum - 1].getX()), (allPoints[0].getY() - allPoints[pointNum - 1].getY()));

	int i = 0;
	int j = 0;
	bool flag = false;
	for (; i != pointNum; i++) {
		for (j = i + 1; j != pointNum; j++) {
			if ((allVectors[i].getX() * allVectors[j].getY()) - (allVectors[i].getY() * allVectors[j].getX()) == 0) {
				flag = true;
				break;
			}
		}
		if (flag)
			break;
	}

	return ((area() * 2) / ((float)sqrt(pow(allVectors[i].getX(), 2) + pow(allVectors[i].getY(), 2)) + (float)sqrt(pow(allVectors[j].getX(), 2) + pow(allVectors[j].getY(), 2))));
}

RegularPolygon::RegularPolygon(int n, Point* a) 
	: Polygon(n, a) 
{ }

RegularPolygon::RegularPolygon(const RegularPolygon& other) 
	: Polygon(other) 
{ }

float RegularPolygon::area() const {
	return (pointNum * (pow((long long)allPoints[1].getX() - (long long)allPoints[0].getX(), 2) + pow((long long)allPoints[1].getY() - (long long)allPoints[0].getY(), 2))) / (4 * tan(PI / pointNum));
}

float RegularPolygon::perimeter() const {
	return (float)sqrt((pow((long long)allPoints[1].getX() - (long long)allPoints[0].getX(), 2) + pow((long long)allPoints[1].getY() - (long long)allPoints[0].getY(), 2))) * pointNum;
}