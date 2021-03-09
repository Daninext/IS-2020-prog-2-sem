#include "geometry.h"

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
	: PointNum(n)
{
	AllPoints = new Point[n];
	memcpy(AllPoints, a, PointNum * sizeof(Point));
}

PolygonalChain::PolygonalChain(const PolygonalChain& other)
	: PointNum(other.PointNum), AllPoints(other.AllPoints)
{ }

Point PolygonalChain::getPoint(int i) const {
	return AllPoints[i];
}

float PolygonalChain::perimeter() const {
	float perimeter_ = 0;
	//todo variables should start with capital letters
	Point* AllVectors = new Point[PointNum - 1];
	for (int i = 0; i != PointNum - 1; i++) {
		AllVectors[i] = Point((AllPoints[i + 1].getX() - AllPoints[i].getX()), (AllPoints[i + 1].getY() - AllPoints[i].getY()));
	}
	for (int i = 0; i != PointNum - 1; i++) {
		perimeter_ += (float)sqrt(pow(AllVectors[i].getX(), 2) + pow(AllVectors[i].getY(), 2));
	}

	return perimeter_;
}

int PolygonalChain::getN() const {
	return PointNum;
}

ClosedPolygonalChain::ClosedPolygonalChain(int n, Point* a)
	: PolygonalChain(n, a)
{ }

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain& other)
	: PolygonalChain(other) 
{ }

float ClosedPolygonalChain::perimeter() const {
	float perimeter_ = 0;
	//todo memory leak
	//todo use perimeter from base class
	Point* AllVectors = new Point[PointNum];
	for (int i = 0; i != PointNum - 1; i++) {
		AllVectors[i] = Point((AllPoints[i + 1].getX() - AllPoints[i].getX()), (AllPoints[i + 1].getY() - AllPoints[i].getY()));
	}
	AllVectors[PointNum - 1] = Point((AllPoints[0].getX() - AllPoints[PointNum - 1].getX()), (AllPoints[0].getY() - AllPoints[PointNum - 1].getY()));

	for (int i = 0; i != PointNum; i++) {
		perimeter_ += (float)sqrt(pow(AllVectors[i].getX(), 2) + pow(AllVectors[i].getY(), 2));
	}

	return perimeter_;
}

Polygon::Polygon(int n, Point* a)
	: ClosedPolygonalChain(n, a)
{ }

Polygon::Polygon(const Polygon& other)
	: ClosedPolygonalChain(other)
{ }

float Polygon::area() const {
	int area_ = 0;

	for (int i = 0; i != PointNum - 1; i++) {
		area_ += AllPoints[i].getX() * AllPoints[i + 1].getY();
	}
	area_ += AllPoints[PointNum - 1].getX() * AllPoints[0].getY();
	for (int i = 0; i != PointNum - 1; i++) {
		area_ -= AllPoints[i + 1].getX() * AllPoints[i].getY();
	}
	area_ -= AllPoints[0].getX() * AllPoints[PointNum - 1].getY();

	return (float)abs(area_) / 2;
}

Triangle::Triangle(int n, Point* a) 
	: Polygon(n, a) 
{ }

Triangle::Triangle(const Triangle& other) 
	: Polygon(other) 
{ }

bool Triangle::hasRightAngle() const {
	if (((AllPoints[1].getX() - AllPoints[0].getX()) * (AllPoints[2].getX() - AllPoints[0].getX())) + ((AllPoints[1].getY() - AllPoints[0].getY()) * (AllPoints[2].getY() - AllPoints[0].getY())) == 0) {
		return true;
	}
	if (((AllPoints[0].getX() - AllPoints[1].getX()) * (AllPoints[2].getX() - AllPoints[1].getX())) + ((AllPoints[0].getY() - AllPoints[1].getY()) * (AllPoints[2].getY() - AllPoints[1].getY())) == 0) {
		return true;
	}
	if (((AllPoints[0].getX() - AllPoints[2].getX()) * (AllPoints[1].getX() - AllPoints[2].getX())) + ((AllPoints[0].getY() - AllPoints[2].getY()) * (AllPoints[1].getY() - AllPoints[2].getY())) == 0) {
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
	Point* AllVectors = new Point[PointNum];
	for (int i = 0; i != PointNum - 1; i++) {
		AllVectors[i] = Point((AllPoints[i + 1].getX() - AllPoints[i].getX()), (AllPoints[i + 1].getY() - AllPoints[i].getY()));
	}
	AllVectors[PointNum - 1] = Point((AllPoints[0].getX() - AllPoints[PointNum - 1].getX()), (AllPoints[0].getY() - AllPoints[PointNum - 1].getY()));

	int i = 0;
	int j = 0;
	bool flag = false;
	for (; i != PointNum; i++) {
		for (j = i + 1; j != PointNum; j++) {
			if ((AllVectors[i].getX() * AllVectors[j].getY()) - (AllVectors[i].getY() * AllVectors[j].getX()) == 0) {
				flag = true;
				break;
			}
		}
		if (flag)
			break;
	}

	return ((area() * 2) / ((float)sqrt(pow(AllVectors[i].getX(), 2) + pow(AllVectors[i].getY(), 2)) + (float)sqrt(pow(AllVectors[j].getX(), 2) + pow(AllVectors[j].getY(), 2))));
}

RegularPolygon::RegularPolygon(int n, Point* a) 
	: Polygon(n, a) 
{ }

RegularPolygon::RegularPolygon(const RegularPolygon& other) 
	: Polygon(other) 
{ }

float RegularPolygon::area() const {
	return (PointNum * (pow((long long)AllPoints[1].getX() - (long long)AllPoints[0].getX(), 2) + pow((long long)AllPoints[1].getY() - (long long)AllPoints[0].getY(), 2))) / (4 * tan(PI / PointNum));
}

float RegularPolygon::perimeter() const {
	return (float)sqrt((pow((long long)AllPoints[1].getX() - (long long)AllPoints[0].getX(), 2) + pow((long long)AllPoints[1].getY() - (long long)AllPoints[0].getY(), 2))) * PointNum;
}