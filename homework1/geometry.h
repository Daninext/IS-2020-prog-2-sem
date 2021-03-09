#pragma once
#include <math.h>
#include <memory.h>
#define PI 3.14159265
class Point {
public:
	Point(int x = 0, int y = 0);

	Point(const Point& other);

	Point& operator=(const Point& other) = default;

	~Point() = default;

	int getX() const;

	int getY() const;

private:
	int x_;
	int y_;
};

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
};

class ClosedPolygonalChain : public PolygonalChain {
public:
	ClosedPolygonalChain(int n, Point* a);

	ClosedPolygonalChain(const ClosedPolygonalChain& other);

	ClosedPolygonalChain& operator=(const ClosedPolygonalChain& other) = default;

	~ClosedPolygonalChain() = default;

	float perimeter() const override;
};

class Polygon : public ClosedPolygonalChain {
public:
	Polygon(int n, Point* a);

	Polygon(const Polygon& other);

	Polygon& operator=(const Polygon& other) = default;

	~Polygon() = default;

	float virtual area() const;
};

class Triangle : public Polygon {
public:
	Triangle(int n, Point* a);

	Triangle(const Triangle& other);

	Triangle& operator=(const Triangle& other) = default;

	~Triangle() = default;

	bool hasRightAngle() const;
};

class Trapezoid : public Polygon {
public:
	Trapezoid(int n, Point* a);

	Trapezoid(const Trapezoid& other);
	Trapezoid& operator=(const Trapezoid& other) = default;

	~Trapezoid() = default;

	float height() const;
};

class RegularPolygon : public Polygon {
public:
	RegularPolygon(int n, Point* a);

	RegularPolygon(const RegularPolygon& other);

	RegularPolygon& operator=(const RegularPolygon& other) = default;

	~RegularPolygon() = default;

	float area() const override;

	float perimeter() const override;
};