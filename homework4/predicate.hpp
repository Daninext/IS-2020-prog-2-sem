#pragma once
#include <functional>
//todo T is a bad name for iterator                
template<class T, class cmp_t>
bool allOf(T first, T last, cmp_t cmp) {
	while (first != last) {
		if (!cmp(*first))
			return false;
		first++;
	}
	return true;
}

template<class T, class cmp_t>
bool anyOf(T first, T last, cmp_t cmp) {
	while (first != last) {
		if (cmp(*first))
			return true;
		first++;
	}
	return false;
}

template<class T, class cmp_t>
bool noneOf(T first, T last, cmp_t cmp) {
	while (first != last) {
		if (cmp(*first))
			return false;
		first++;
	}
	return true;
}

template<class T, class cmp_t>
bool oneOf(T first, T last, cmp_t cmp) {
	bool flag = false;
	while (first != last) {
		if (cmp(*first) && !flag)
			flag = true;
		else if (cmp(*first) && flag)
			return false;
		first++;
	}
	if (flag)
		return true;
	return false;
}

template<class T, class cmp_t = std::less<>>
bool isSorted(T first, T last, cmp_t cmp = cmp_t()) {
	while (first != last - 1) {
		if (!cmp(*first, *(first + 1)))
			return false;
		first++;
	}
	return true;
}

template<class T, class cmp_t>
bool isPartitioned(T first, T last, cmp_t cmp) {
	if (cmp(*first)) {
		while (cmp(*first) && first != last)
			first++;

		while (first != last) {
			if (cmp(*first))
				return false;
			first++;
		}
	}
	else {
		while (!cmp(*first) && first != last)
			first++;

		while (first != last) {
			first++;
			if (!cmp(*first))
				return false;
		}
	}
	
	return true;
}

template<class T, class cmp_num>
T findNot(T first, T last, cmp_num cmp) {
	while (first != last) {
		if (*first != cmp)
			return first;
		first++;
	}
	return first;
}

template<class T, class cmp_num>
T findBackward(T first, T last, cmp_num cmp) {
	T tmp = last;
	last += (-1);
	while (first != last) {
		if (*last == cmp)
			return last;
		last += (-1);
	}
	return tmp;
}

template<class T, class cmp_t>
bool isPalindrome(T first, T last, cmp_t cmp) {
	last--;
	while (first != last) {
		if (!cmp(*first, *last))
			return false;
		first++;
		if (first == last)
			break;
		last--;
	}
	return true;
}