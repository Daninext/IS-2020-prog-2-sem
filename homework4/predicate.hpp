#pragma once
#include <functional>
//fixed T is a bad name for iterator                
template<class Iterator, class cmp_t>
bool allOf(Iterator first, Iterator last, cmp_t cmp) {
	while (first != last) {
		if (!cmp(*first))
			return false;
		first++;
	}
	return true;
}

template<class Iterator, class cmp_t>
bool anyOf(Iterator first, Iterator last, cmp_t cmp) {
	while (first != last) {
		if (cmp(*first))
			return true;
		first++;
	}
	return false;
}

template<class Iterator, class cmp_t>
bool noneOf(Iterator first, Iterator last, cmp_t cmp) {
	while (first != last) {
		if (cmp(*first))
			return false;
		first++;
	}
	return true;
}

template<class Iterator, class cmp_t>
bool oneOf(Iterator first, Iterator last, cmp_t cmp) {
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

template<class Iterator, class cmp_t = std::less<>>
bool isSorted(Iterator first, Iterator last, cmp_t cmp = cmp_t()) {
	while (first != last - 1) {
		if (!cmp(*first, *(first + 1)))
			return false;
		first++;
	}
	return true;
}

template<class Iterator, class cmp_t>
bool isPartitioned(Iterator first, Iterator last, cmp_t cmp) {
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

template<class Iterator, class cmp_num>
Iterator findNot(Iterator first, Iterator last, cmp_num cmp) {
	while (first != last) {
		if (*first != cmp)
			return first;
		first++;
	}
	return first;
}

template<class Iterator, class cmp_num>
Iterator findBackward(Iterator first, Iterator last, cmp_num cmp) {
	Iterator tmp = last;
	last += (-1);
	while (first != last) {
		if (*last == cmp)
			return last;
		last += (-1);
	}
	return tmp;
}

template<class Iterator, class cmp_t>
bool isPalindrome(Iterator first, Iterator last, cmp_t cmp) {
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