#pragma once
#include <math.h>
#include <memory.h>
class Point {
public:
	Point(int x = 0, int y = 0)
		: x_(x), y_(y)
	{

	}

	Point(const Point& other)
		: x_(other.x_), y_(other.y_)
	{

	}

	Point& operator=(const Point& other) {
		if (&other == this)
			return *this;

		x_ = other.x_;
		y_ = other.y_;

		return *this;
	}

	~Point() {}

	int getX() const {
		return x_;
	}

	int getY() const {
		return y_;
	}

private:
	int x_;
	int y_;
};

class Vector {
public:
	Vector(int x = 0, int y = 0)
		: x_(x), y_(y)
	{

	}

	Vector(const Vector& other)
		: x_(other.x_), y_(other.y_)
	{

	}

	Vector& operator=(const Vector& other) {
		if (&other == this)
			return *this;

		x_ = other.x_;
		y_ = other.y_;

		return *this;
	}

	~Vector() {}

	int getX() const {
		return x_;
	}

	int getY() const {
		return y_;
	}

private:
	int x_;
	int y_;
};

class Polygon {
public:
	Polygon() = delete;

	explicit Polygon(int n, Point* a)
		: PointNum(n)
	{
		AllPoints = new Point[n];
		memcpy(AllPoints, a, PointNum * sizeof(Point));
		FindArea();
		FindVectors();
		FindPerimeter();
	}

	Polygon(const Polygon& other)
		: PointNum(other.PointNum), AllPoints(other.AllPoints), AllVectors(other.AllVectors), area_(other.area_), perimeter_(other.perimeter_)
	{

	}

	Polygon& operator=(const Polygon& other) {
		if (&other == this)
			return *this;

		PointNum = other.PointNum;
		AllPoints = other.AllPoints;
		AllVectors = other.AllVectors;
		area_ = other.area_;
		perimeter_ = other.perimeter_;

		return *this;
	}

	~Polygon() {}

	Point getPoint(int i) const {
		return AllPoints[i];
	}

	float area() const {
		return area_;
	}

	int perimeter() const {
		return perimeter_;
	}

protected:
	void FindArea() {
		for (int i = 0; i != PointNum - 1; i++) {
			area_ += AllPoints[i].getX() * AllPoints[i + 1].getY();
		}
		area_ += AllPoints[PointNum - 1].getX() * AllPoints[0].getY();
		for (int i = 0; i != PointNum - 1; i++) {
			area_ -= AllPoints[i + 1].getX() * AllPoints[i].getY();
		}
		area_ -= AllPoints[0].getX() * AllPoints[PointNum - 1].getY();
		area_ = 0.5f * abs(area_);
	}

	void FindVectors() {
		AllVectors = new Vector[PointNum];
		for (int i = 0; i != PointNum - 1; i++) {
			AllVectors[i] = Vector((AllPoints[i + 1].getX() - AllPoints[i].getX()), (AllPoints[i + 1].getY() - AllPoints[i].getY()));
		}
		AllVectors[PointNum - 1] = Vector((AllPoints[0].getX() - AllPoints[PointNum - 1].getX()), (AllPoints[0].getY() - AllPoints[PointNum - 1].getY()));
	}

	void FindPerimeter() {
		for (int i = 0; i != PointNum; i++) {
			perimeter_ += (int)sqrt(pow(AllVectors[i].getX(), 2) + pow(AllVectors[i].getY(), 2));
		}
	}

	int PointNum;
	Point* AllPoints;
	Vector* AllVectors;
	float area_;
	int perimeter_;
};

class Triangle : public Polygon {
public:
	Triangle(int n, Point* a) : Polygon(n, a) { }

	Triangle(const Triangle& other) : Polygon(other) { }

	Triangle& operator=(const Triangle& other) {
		if (&other == this)
			return *this;

		PointNum = other.PointNum;
		AllPoints = other.AllPoints;
		AllVectors = other.AllVectors;
		area_ = other.area_;
		perimeter_ = other.perimeter_;

		return *this;
	}

	~Triangle() {}

	bool hasRightAngle() const {
		bool flag = false;
		
		if (((AllPoints[1].getX() - AllPoints[0].getX()) * (AllPoints[2].getX() - AllPoints[0].getX())) + ((AllPoints[1].getY() - AllPoints[0].getY()) * (AllPoints[2].getY() - AllPoints[0].getY())) == 0) {
			flag = true;
			return flag;
		}
		if (((AllPoints[0].getX() - AllPoints[1].getX()) * (AllPoints[2].getX() - AllPoints[1].getX())) + ((AllPoints[0].getY() - AllPoints[1].getY()) * (AllPoints[2].getY() - AllPoints[1].getY())) == 0) {
			flag = true;
			return flag;
		}
		if (((AllPoints[0].getX() - AllPoints[2].getX()) * (AllPoints[1].getX() - AllPoints[2].getX())) + ((AllPoints[0].getY() - AllPoints[2].getY()) * (AllPoints[1].getY() - AllPoints[2].getY())) == 0) {
			flag = true;
			return flag;
		}
		return flag;
	}
};

class Trapezoid : public Polygon {
public:
	Trapezoid(int n, Point* a) : Polygon(n, a) {
		FindHeight();
	}

	Trapezoid(const Trapezoid& other) : Polygon(other) {
		height_ = other.height_;
	}

	Trapezoid& operator=(const Trapezoid& other) {
		if (&other == this)
			return *this;

		PointNum = other.PointNum;
		AllPoints = other.AllPoints;
		AllVectors = other.AllVectors;
		area_ = other.area_;
		perimeter_ = other.perimeter_;
		height_ = other.height_;

		return *this;
	}

	~Trapezoid() {}

	float height() const {
		return height_;
	}

private:
	void FindHeight() {
		int i = 0;
		int j = 0;
		bool flag = false;
		for ( ; i != PointNum; i++) {
			for (j = i + 1; j != PointNum; j++) {
				if ((AllVectors[i].getX() * AllVectors[j].getY()) - (AllVectors[i].getY() * AllVectors[j].getX()) == 0) {
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}

		height_ = ((long long)area_ * 2) / (sqrt(pow(AllVectors[i].getX(), 2) + pow(AllVectors[i].getY(), 2)) + sqrt(pow(AllVectors[j].getX(), 2) + pow(AllVectors[j].getY(), 2)));
	}

	float height_ = 0;
};

class RegularPolygon : public Polygon {
public:
	RegularPolygon(int n, Point* a) : Polygon(n, a) { }

	RegularPolygon(const RegularPolygon& other) : Polygon(other) { }

	RegularPolygon& operator=(const RegularPolygon& other) {
		if (&other == this)
			return *this;

		PointNum = other.PointNum;
		AllPoints = other.AllPoints;
		AllVectors = other.AllVectors;
		area_ = other.area_;
		perimeter_ = other.perimeter_;

		return *this;
	}

	~RegularPolygon() {}
};

class PolygonalChain {
public:
	PolygonalChain(int n, Point* a)
		: PointNum(n)
	{
		AllPoints = new Point[n];
		memcpy(AllPoints, a, PointNum * sizeof(Point));
		FindVectors();
		FindPerimeter();
	}

	PolygonalChain(const PolygonalChain& other)
		: PointNum(other.PointNum), AllPoints(other.AllPoints), AllVectors(other.AllVectors), perimeter_(other.perimeter_)
	{

	}

	PolygonalChain& operator=(const PolygonalChain& other) {
		if (&other == this)
			return *this;

		PointNum = other.PointNum;
		AllPoints = other.AllPoints;
		AllVectors = other.AllVectors;
		perimeter_ = other.perimeter_;

		return *this;
	}

	~PolygonalChain() {}

	Point getPoint(int i) const {
		return AllPoints[i];
	}

	int perimeter() const {
		return perimeter_;
	}

	int getN() const {
		return PointNum;
	}

protected:
	void FindVectors() {
		AllVectors = new Vector[PointNum - 1];
		for (int i = 0; i != PointNum - 1; i++) {
			AllVectors[i] = Vector((AllPoints[i + 1].getX() - AllPoints[i].getX()), (AllPoints[i + 1].getY() - AllPoints[i].getY()));
		}
	}

	void FindPerimeter() {
		for (int i = 0; i != PointNum - 1; i++) {
			perimeter_ += (int)sqrt(pow(AllVectors[i].getX(), 2) + pow(AllVectors[i].getY(), 2));
		}
	}

	int PointNum;
	Point* AllPoints;
	Vector* AllVectors;
	int perimeter_;
};

class ClosedPolygonalChain: public PolygonalChain {
public:
	ClosedPolygonalChain(int n, Point* a)
		: PolygonalChain(n, a)
	{
		FindVectors();
		FindPerimeter();
	}

	ClosedPolygonalChain(const ClosedPolygonalChain& other) : PolygonalChain(other) { }

	ClosedPolygonalChain& operator=(const ClosedPolygonalChain& other) {
		if (&other == this)
			return *this;

		PointNum = other.PointNum;
		AllPoints = other.AllPoints;
		AllVectors = other.AllVectors;
		perimeter_ = other.perimeter_;

		return *this;
	}

	~ClosedPolygonalChain() {}

	Point getPoint(int i) const {
		return AllPoints[i];
	}

	int perimeter() const {
		return perimeter_;
	}

	int getN() const {
		return PointNum;
	}

private:
	void FindVectors() {
		AllVectors = new Vector[PointNum];

		for (int i = 0; i != PointNum - 1; i++) {
			AllVectors[i] = Vector((AllPoints[i + 1].getX() - AllPoints[i].getX()), (AllPoints[i + 1].getY() - AllPoints[i].getY()));
		}
		AllVectors[PointNum - 1] = Vector((AllPoints[0].getX() - AllPoints[PointNum - 1].getX()), (AllPoints[0].getY() - AllPoints[PointNum - 1].getY()));
	}

	void FindPerimeter() {
		perimeter_ = 0;
		for (int i = 0; i != PointNum; i++) {
			perimeter_ += (int)sqrt(pow(AllVectors[i].getX(), 2) + pow(AllVectors[i].getY(), 2));
		}
	}
};