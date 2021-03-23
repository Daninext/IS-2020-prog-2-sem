#include "polynomial.h"

Polynomial::Polynomial(int minimum, int maximum)
	:min_(minimum), max_(maximum)
{
	sequenceMembers = new int[1];
	sequenceMembers[0] = 0;
}

Polynomial::Polynomial(int minimum, int maximum, int* nums)
	:min_(minimum), max_(maximum)
{
	sequenceMembers = new int[max_ - min_ + 1];
	std::copy_n(nums, max_ - min_ + 1, sequenceMembers);
}

Polynomial::Polynomial(const Polynomial& other)
	: sequenceMembers(other.sequenceMembers), min_(other.min_), max_(other.max_)
{ }

bool operator==(const Polynomial& lother, const Polynomial& rother) {
	int max__ = lother.max_ > rother.max_ ? lother.max_ : rother.max_;
	int min__ = lother.min_ > rother.min_ ? rother.min_ : lother.min_;
	for (int i = max__ - min__; i != -1; i--) {
		if (lother[i + min__] != rother[i + min__])
			return false;
	}

	return true;
}

bool Polynomial::operator!=(const Polynomial& other) {
	return !(*this == other);
}

Polynomial operator+(const Polynomial& lother, const Polynomial& rother) {
	return lother += rother;
}

//todo += return Polynomail&, *this
Polynomial operator+=(const Polynomial& lother, const Polynomial& rother) {
	int realMax = lother.max_ > rother.max_ ? lother.max_ : rother.max_;
	int realMin = lother.min_ > rother.min_ ? rother.min_ : lother.min_;

	int* nums = new int[realMax - realMin + 1];
	std::for_each(nums, nums + realMax - realMin + 1, [](int& num) {num = 0;});

	for (int i = realMax - realMin; i != -1; i--) {
		if (i + realMin >= lother.min_ && i + realMin <= lother.max_) {
			nums[i] += lother[i + realMin];
		}

		if (i + realMin >= rother.min_ && i + realMin <= rother.max_) {
			nums[i] += rother[i + realMin];
		}
	}

	Polynomial tmp = Polynomial(realMin, realMax, nums);
	return tmp;
}

Polynomial operator-(const Polynomial& lother, const Polynomial& rother) {
	return lother -= rother;
}

Polynomial operator-=(const Polynomial& lother, const Polynomial& rother) {
	Polynomial tmp = Polynomial(rother.min_, rother.max_, rother.sequenceMembers);
	return (lother += (-tmp));
}

Polynomial Polynomial::operator-() {
	Polynomial tmp = Polynomial(min_, max_, sequenceMembers);
	for (int i = 0; i != max_ - min_ + 1; i++) {
		tmp.sequenceMembers[i] = -sequenceMembers[i];
	}

	return tmp;
}

Polynomial operator*(const Polynomial& lother, const Polynomial& rother) {
	return (lother *= rother);
}

Polynomial operator*(const Polynomial& other, int num) {
	return (other *= num);
}

Polynomial operator*(int num, const Polynomial& other) {
	return (other * num);
}

Polynomial operator/(const Polynomial& other, int num) {
	return (other /= num);
}

Polynomial operator*=(const Polynomial& lother, const Polynomial& rother) {
	int newMax = lother.max_ + rother.max_;
	int newMin = lother.min_ + rother.min_;

	int* nums = new int[newMax - newMin + 1];
	std::for_each(nums, nums + newMax - newMin + 1, [](int& num) {num = 0; });

	for (int i = lother.max_ - lother.min_; i != -1; i--) {
		for (int j = rother.max_ - rother.min_; j != -1; j--) {
			nums[i + lother.min_ + j + rother.min_ - newMin] += (lother[i + lother.min_] * rother[j + rother.min_]);
		}
	}

	Polynomial tmp = Polynomial(newMin, newMax, nums);
	return tmp;
}

Polynomial operator*=(const Polynomial& other, int num) {
	Polynomial tmp = Polynomial(other.min_, other.max_, other.sequenceMembers);
	for (int i = 0; i != tmp.max_ - tmp.min_ + 1; i++) {
		tmp.sequenceMembers[i] *= num;
	}

	return tmp;
}

Polynomial operator/=(const Polynomial& other, int num) {
	Polynomial tmp = Polynomial(other.min_, other.max_, other.sequenceMembers);
	for (int i = 0; i != tmp.max_ - tmp.min_ + 1; i++) {
		tmp.sequenceMembers[i] /= num;
	}

	return tmp;
}

int& Polynomial::operator[](int i) {
	if (i >= min_ && i <= max_) {
		return sequenceMembers[i - min_];
	}

	if (i > max_) {
		int* nums = new int[i - min_ + 1];
		for (int j = 0; j != max_ - min_ + 1; j++) {
			nums[j] = sequenceMembers[j];
		}
		for (int j = max_ - min_ + 1; j != i - min_ + 1; j++) {
			nums[j] = 0;
		}
		*this = Polynomial(min_, i, nums);

		return sequenceMembers[i - min_];
	}
	else {
		int* nums = new int[max_ - i + 1];
		for (int j = 0; j != min_ - i; j++) {
			nums[j] = 0;
		}
		for (int j = min_ - i; j != max_ - min_ + 1; j++) {
			nums[j] = sequenceMembers[j - max_ + 1];
		}

		*this = Polynomial(i, max_, nums);

		return sequenceMembers[0];
	}
}

int Polynomial::operator[](int i) const {
	if (i >= min_ && i <= max_) {
		return sequenceMembers[i - min_];
	}

	return 0;
}

std::ostream& operator<<(std::ostream& strm, const Polynomial& other) {
	if (other.max_ == other.min_) {
		if (other[0] == 0)
			strm << "0";
		else if (other.max_ == 0)
			strm << other[0];
		else if (other.max_ == 1)
			strm << other[0] << "x";
		else
			strm << other[0] << "x^" << other.max_;

		return strm;
	}

	for (int i = other.max_ - other.min_; i != -1; i--) {
		if ((i + other.min_) != 0) {
			if ((i + other.min_) == 1) {
				if (i == other.max_ - other.min_ && other[(i + other.min_)] != 0) {
					if (other[(i + other.min_)] == 1)
						strm << "x";
					else if (other[(i + other.min_)] == -1)
						strm << "-x";
					else
						strm << other[(i + other.min_)] << "x";
				}
				else {
					if (other[(i + other.min_)] == 1)
						strm << "+x";
					else if (other[(i + other.min_)] == -1)
						strm << "-x";
					else if (other[(i + other.min_)] > 0)
						strm << "+" << other[(i + other.min_)] << "x";
					else if (other[(i + other.min_)] < 0)
						strm << other[(i + other.min_)] << "x";
				}
			}
			else if (i == other.max_ - other.min_ && other[(i + other.min_)] != 0) {
				if (other[(i + other.min_)] == 1)
					strm << "x^" << (i + other.min_);
				else if (other[(i + other.min_)] == -1)
					strm << "-x^" << (i + other.min_);
				else
					strm << other[(i + other.min_)] << "x^" << (i + other.min_);
			}
			else {
				if (other[(i + other.min_)] == 1)
					strm << "+x^" << (i + other.min_);
				else if (other[(i + other.min_)] == -1)
					strm << "-x^" << (i + other.min_);
				else if (other[(i + other.min_)] > 0)
					strm << "+" << other[(i + other.min_)] << "x^" << (i + other.min_);
				else if (other[(i + other.min_)] < 0)
					strm << other[(i + other.min_)] << "x^" << (i + other.min_);
			}
		}
		else {
			if (i == other.max_ - other.min_ && other[(i + other.min_)] != 0) {
				strm << other[(i + other.min_)];
			}
			else {
				if (other[(i + other.min_)] > 0) {
					strm << "+" << other[(i + other.min_)];
				}
				else if (other[(i + other.min_)] < 0) {
					strm << other[(i + other.min_)];
				}
			}
		}
	}

	return strm;
}

std::istream& operator>>(std::istream& strm, Polynomial& other) {
	int newMin, newMax;
	strm >> newMin >> newMax;

	int* nums = new int[newMax - newMin + 1];
	for (int i = 0; i != newMax - newMin + 1; i++) {
		strm >> nums[i];
	}

	other.max_ = newMax;
	other.min_ = newMin;
	other.sequenceMembers = nums;
	return strm;
}

//todo get O(n)
float Polynomial::get(int x) const {
	float Sum = 0;
	for (int i = max_ - min_; i != -1; i--) {
		Sum += pow(x, (i + min_)) * sequenceMembers[i];
	}
	return Sum;
}