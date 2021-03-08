#pragma once
#include <math.h>
#include <memory.h>
#define PI 3.14159265
//fixed cpp
class Point {
public:
	Point(int x = 0, int y = 0);

	Point(const Point& other);

	Point& operator=(const Point& other) = default;

	//fixed = default
	~Point() = default;

	int getX() const;

	int getY() const;

private:
	int x_;
	int y_;
};

//fixed make inherit from point
class PolygonalChain {
public:
	PolygonalChain(int n, Point* a);

	PolygonalChain(const PolygonalChain& other);

	PolygonalChain& operator=(const PolygonalChain& other) = default;

	virtual ~PolygonalChain() = default;

	Point getPoint(int i) const;

	float virtual perimeter() const;

	int getN() const;

protected:
	int PointNum;
	Point* AllPoints;
	//fixed copy-paste
};

class ClosedPolygonalChain : public PolygonalChain {
public:
	ClosedPolygonalChain(int n, Point* a);

	ClosedPolygonalChain(const ClosedPolygonalChain& other);

	ClosedPolygonalChain& operator=(const ClosedPolygonalChain& other) = default;

	~ClosedPolygonalChain() = default;

	float perimeter() const override;
};

//fixed inherit from ClosedPolygonalChain
class Polygon : public ClosedPolygonalChain {
public:
	Polygon(int n, Point* a);

	Polygon(const Polygon& other);

	Polygon& operator=(const Polygon& other) = default;

	~Polygon() = default;

	float virtual area() const;
	//fixed without double until end

	//fixed int perimeter is weird
};

class Triangle : public Polygon {
public:
	Triangle(int n, Point* a);

	Triangle(const Triangle& other);

	Triangle& operator=(const Triangle& other) = default;

	~Triangle() = default;

	//fixed u dont need flag
	bool hasRightAngle() const;
};

class Trapezoid : public Polygon {
public:
	Trapezoid(int n, Point* a);

	Trapezoid(const Trapezoid& other);
	//fixed same arrays between objects
	Trapezoid& operator=(const Trapezoid& other) = default;

	~Trapezoid() = default;

	float height() const;
};

//fixed area and perimeter
class RegularPolygon : public Polygon {
public:
	RegularPolygon(int n, Point* a);

	RegularPolygon(const RegularPolygon& other);

	RegularPolygon& operator=(const RegularPolygon& other) = default;

	~RegularPolygon() = default;

	float area() const override;

	float perimeter() const override;
};