#include "stoper.h"

Route::Route(int value)
	: value_(value) { }

void Route::ItValue() {
	value_++;
}

void Route::SetName(std::string name) {
	name_ = name;
}

std::string Route::name() const {
	return name_;
}

int Route::value() const {
	return value_;
}

void Route::AddCoord(float x, float y) {
	x_.push_back(x);
	y_.push_back(y);
}

float Route::GetSize() {
	float weight = 0;

	matr.resize(x_.size());
	for (int i = 0; i != x_.size(); i++) {
		matr[i].resize(x_.size());
	}

	float w;
	for (int i = 0; i != x_.size(); i++) {
		for (int j = 0; j != x_.size(); j++) {
			if (i != j) {
				w = sqrt(pow((x_[j] - x_[i]), 2) + pow((y_[j] - y_[i]), 2));
				matr[i][j] = w;
				matr[j][i] = w;
			}
			else
				matr[i][j] = INF;
		}
	}

	std::vector<bool> used(x_.size());
	std::vector<float> min_e(x_.size(), INF), sel_e(x_.size(), -1);
	min_e[0] = 0;
	for (int i = 0; i != x_.size(); i++) {
		int v = -1;
		for (int j = 0; j != x_.size(); j++)
			if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
				v = j;

		if (min_e[v] == INF) {
			break;
		}

		used[v] = true;
		if (sel_e[v] != -1)
			weight += matr[v][sel_e[v]];

		for (int to = 0; to != x_.size(); to++)
			if (matr[v][to] < min_e[to]) {
				min_e[to] = matr[v][to];
				sel_e[to] = v;
			}
	}

	return weight;
}