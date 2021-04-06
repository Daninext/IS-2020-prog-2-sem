#include "polynomial.h"

Polynomial::Polynomial(int minimum, int maximum)
	:min_(minimum), max_(maximum)
{
	sequenceMembers = new int[1]();
}

Polynomial::Polynomial(int minimum, int maximum, int* nums)
	:min_(minimum), max_(maximum)
{
	sequenceMembers = new int[max_ - min_ + 1];
	std::copy_n(nums, max_ - min_ + 1, sequenceMembers);
}

Polynomial::Polynomial(const Polynomial& other)
	: min_(other.min_), max_(other.max_)
{ 
	sequenceMembers = new int[max_ - min_ + 1];
	std::copy_n(other.sequenceMembers, max_ - min_ + 1, sequenceMembers);
}

bool operator==(const Polynomial& lother, const Polynomial& rother) {
	int max__ = lother.max_ > rother.max_ ? lother.max_ : rother.max_;
	int min__ = lother.min_ > rother.min_ ? rother.min_ : lother.min_;
	for (int i = max__ - min__; i != -1; i--) {
		if (lother[i + min__] != rother[i + min__]) {
			return false;
		}
	}

	return true;
}

Polynomial::~Polynomial() {
	delete[] sequenceMembers;
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
	this->max_ = other.max_;
	this->min_ = other.min_;

	delete[] this->sequenceMembers;

	sequenceMembers = new int[max_ - min_ + 1];
	std::copy_n(other.sequenceMembers, max_ - min_ + 1, sequenceMembers);

	return *this;
}

bool Polynomial::operator!=(const Polynomial& other) {
	return !(*this == other);
}

Polynomial operator+(const Polynomial& lother, const Polynomial& rother){
	Polynomial lo = lother; Polynomial ro = rother;
	return lo += ro;
}

Polynomial& Polynomial::operator+=(const Polynomial& rother) {
	int realMax = max_ > rother.max_ ? max_ : rother.max_;
	int realMin = min_ > rother.min_ ? rother.min_ : min_;

	int* lnums = new int[realMax - realMin + 1]();
	resizebuff(lnums, this->sequenceMembers, min_ - realMin, max_ - min_ + 1);
	int* rnums = new int[realMax - realMin + 1]();
	resizebuff(rnums, rother.sequenceMembers, rother.min_ - realMin, rother.max_ - rother.min_ + 1);

	for (int i = 0; i != realMax - realMin + 1; i++) {
		lnums[i] += rnums[i];
	}

	this->max_ = realMax;
	this->min_ = realMin;
	delete[] sequenceMembers;
	this->sequenceMembers = lnums;

	delete[] rnums;

	return *this;
}

Polynomial operator-(Polynomial& lother, const Polynomial& rother) {
	return lother -= rother;
}

//fixed without creating new object
Polynomial& operator-=(Polynomial& lother, const Polynomial& rother) {
	auto ro = rother;
	return (lother += (-ro));
}

Polynomial Polynomial::operator-() {
	Polynomial tmp = Polynomial(min_, max_, sequenceMembers);
	std::for_each(tmp.sequenceMembers, tmp.sequenceMembers + max_ - min_ + 1, [](int& nums) {nums *= -1; });

	return tmp;
}

Polynomial operator*(const Polynomial& lother, const Polynomial& rother) {
	return (lother *= rother);
}

Polynomial operator*(const Polynomial& other, int num) {
	auto o = other;
	return (o *= num);
}

Polynomial operator*(int num, const Polynomial& other) {
	auto o = other;
	return (o *= num);
}

Polynomial operator/(const Polynomial& other, int num) {
	auto o = other;
	return (o /= num);
}

Polynomial operator*=(const Polynomial& lother, const Polynomial& rother) {
	int newMax = lother.max_ + rother.max_;
	int newMin = lother.min_ + rother.min_;

	int* nums = new int[newMax - newMin + 1]();

	for (int i = lother.max_ - lother.min_; i != -1; i--) {
		for (int j = rother.max_ - rother.min_; j != -1; j--) {
			nums[i + lother.min_ + j + rother.min_ - newMin] += (lother[i + lother.min_] * rother[j + rother.min_]);
		}
	}

	Polynomial tmp = Polynomial(newMin, newMax, nums);
	return tmp;
}

Polynomial& Polynomial::operator*=(int num) {
	int* nums = new int[max_ - min_ + 1]();
	std::copy_n(sequenceMembers, max_ - min_ + 1, nums);

	std::for_each(nums, nums + max_ - min_ + 1, [num](int& num_) {num_ *= num; });

	sequenceMembers = nums;

	return *this;
}

Polynomial& Polynomial::operator/=(int num) {
	int* nums = new int[max_ - min_ + 1]();
	std::copy_n(sequenceMembers, max_ - min_ + 1, nums);
	//fixed use for_each
	std::for_each(nums, nums + max_ - min_ + 1, [num](int& num_) {num_ /= num; });

	sequenceMembers = nums;

	return *this;
}

int& Polynomial::operator[](int i) {
	if (i >= min_ && i <= max_) {
		return sequenceMembers[i - min_];
	}

	if (i > max_) {
		int* nums = new int[i - min_ + 1]();
		for (int j = 0; j != max_ - min_ + 1; j++) {
			nums[j] = sequenceMembers[j];
		}
		*this = Polynomial(min_, i, nums);

		return sequenceMembers[i - min_];
	}
	else {
		int* nums = new int[max_ - i + 1]();
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

float Polynomial::get(int x) const {
	float num = pow(x, max_);
	float sum = 0;
	for (int i = max_ - min_; i != -1; i--) {
		sum += num * sequenceMembers[i];
		num /= x;
	}
	return sum;
}

void Polynomial::resizebuff(int* newbuff, int* oldbuff, int down, int target) {
	std::copy_n(oldbuff, target, newbuff + down);
}