#pragma once
#include <math.h>
#include <iostream>
#include <algorithm>

class Polynomial {
public:
	Polynomial(int minimum = 0, int maximum = 0);

	Polynomial(int minimum, int maximum, int* nums);

	Polynomial(const Polynomial& other);

	//fixed default is not ok
	~Polynomial();

	Polynomial& operator=(const Polynomial& other);

	friend bool operator==(const Polynomial& lother, const Polynomial& rother);

	bool operator!=(const Polynomial& other);

	friend Polynomial operator+(const Polynomial& lother, const Polynomial& rother);

	Polynomial& operator+=(const Polynomial& rother);

	friend Polynomial operator-(const Polynomial& lother, const Polynomial& rother);

	friend Polynomial& operator-=(Polynomial& lother, const Polynomial& rother);

	Polynomial operator-() const;

	friend Polynomial operator*(const Polynomial& lother, const Polynomial& rother);

	friend Polynomial operator*(const Polynomial& other, int num);

	friend Polynomial operator*(int num, const Polynomial& other);

	friend Polynomial operator/(const Polynomial& other, int num);

	friend Polynomial operator*=(const Polynomial& lother, const Polynomial& rother);

	Polynomial& operator*=(int num);

	Polynomial& operator/=(int num);

	int& operator[](int i);

	int operator[](int i) const;

	friend std::ostream& operator<<(std::ostream& strm, const Polynomial& other);

	friend std::istream& operator>>(std::istream& strm, Polynomial& other);

	float get(int x) const;

protected:
	mutable int* sequenceMembers;
	int min_;
	int max_;

	void resizebuff(int* newbuff,int* oldbuff, int down, int target);
};