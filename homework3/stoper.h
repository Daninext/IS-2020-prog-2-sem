#pragma once
#include <string>
#include <vector>
#include <math.h>

class Route {
public:
	Route(int value = 0);

	void ItValue();

	void SetName(std::string name);

	std::string name() const;

	int value() const;

	void AddCoord(float x, float y);

	float GetSize();

protected:
	const int INF = INT32_MAX;
	std::vector<std::vector<float>> matr;

	int value_;
	std::string name_ = "none";
	std::vector<float> x_;
	std::vector<float> y_;
};