#pragma once
#include <exception>

template <class T>
class CircularBuffer {
	template<typename ItType = T>
	class Iter {
	private:
		ItType* p;
		size_t offset, maxOffset;
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = ItType;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;

		friend class CircularBuffer;

		Iter(pointer o = nullptr, size_t off = 0, size_t maxOff = 0)
			: p(o), offset(off), maxOffset(maxOff)
		{ }

		~Iter() { p = nullptr; offset = 0; maxOffset = 0; }

		Iter(const Iter<ItType>& other)
			: p(other.p), offset(other.offset), maxOffset(other.maxOffset)
		{ }

		Iter<ItType>& operator=(const Iter<ItType>& other) {
			if (this != &other) {
				p = other.p;
				offset = other.offset;
				maxOffset = other.maxOffset;
			}
			return *this;
		}

		Iter<ItType>& operator++() {
			if (offset + 1 <= maxOffset)
				++offset;
			else
				offset = 0;
			return *this;
		}

		Iter<ItType>& operator--() {
			if (offset <= 0)
				offset = maxOffset;
			else
				--offset;
			return *this;
		}

		Iter<ItType> operator--(int) {
			Iter<ItType> tmp(this);
			operator--();
			return tmp;
		}

		Iter<ItType> operator++(int) {
			Iter<ItType> tmp(this);
			operator++();
			return tmp;
		}

		reference operator*() { return *(p + offset); }

		const reference operator*() const { return *(p + offset); }

		pointer operator->() { return (p + offset); }

		difference_type operator -(const Iter& value) const {
			return (p + offset - value.p - value.offset) % maxOffset;
		}

		difference_type operator +(const Iter& value) const {
			return (p + offset + value.p + value.offset) % maxOffset;
		}

		Iter<ItType> operator -(const int& value) const {
			Iter<ItType> tmp(p, offset, maxOffset);
			if (value > 0) {
				for (int i = 0; i != value; i++)
					--tmp;
			}
			else {
				for (int i = 0; i != value; i--)
					++tmp;
			}
			return tmp;
		}

		Iter<ItType> operator +(const int& value) const {
			Iter<ItType> tmp(p, offset, maxOffset);
			if (value > 0) {
				for (int i = 0; i != value; i++)
					++tmp;
			}
			else {
				for (int i = 0; i != value; i--)
					--tmp;
			}
			return tmp;
		}

		bool operator==(Iter<ItType>& other) { return (p + offset) == (other.p + other.offset); }

		bool operator<(Iter<ItType>& other) { return (p + offset) < (other.p + other.offset); }
		bool operator<=(Iter<ItType>& other) { return (p + offset) <= (other.p + other.offset); }
		bool operator>(Iter<ItType>& other) { return (p + offset) > (other.p + other.offset); }
		bool operator>=(Iter<ItType>& other) { return (p + offset) >= (other.p + other.offset); }

		friend bool operator!=(Iter<ItType> one, Iter<ItType> other) { return (one.p + one.offset) != (other.p + other.offset); }
	};
private:
	T* v;
	size_t size, maxSize;
	Iter<T> _begin, _end;
public:
	CircularBuffer(size_t siz) 
		: size(0), maxSize(siz) 
	{
		v = new T[siz + 1];
		Iter<T> begin(v, 0, maxSize);
		_begin = begin;
		_end = begin;
	}
	~CircularBuffer() { delete[] v; }

	void addLast(T value) {
		if (size < maxSize) {
			size++;
			*_end = value;
			++_end;
		}
	}

	void addFirst(T value) {
		if (size < maxSize) {
			size++;
			--_begin;
			*_begin = value;
		} else if (size == maxSize) {
			delLast();
			size++;
			--_begin;
			*_begin = value;
		}
	}

	void delLast() {
		if (size > 0) {
			size--;
			--_end;
		}
	}

	void delFirst() {
		if (size > 0) {
			size--;
			++_begin;
		}
	}

	T first() { return *_begin; }

	T last() {
		Iter<T> tmp = _end;
		--tmp;
		return *tmp;
	}

	T& operator[](size_t i) {
		if (i >= size) {
			throw std::out_of_range("out of range");
		}
		else {
			Iter<T> tmp = _begin;
			for (size_t j = 0; j != i; j++) {
				++tmp;
			}
			return *tmp;
		}
	}

	T operator[](size_t i) const {
		if (i >= size) {
			throw std::out_of_range("out of range");
		}
		else {
			Iter<T> tmp = _begin;
			for (size_t j = 0; j != i; j++) {
				++tmp;
			}
			return *tmp;
		}
	}

	void changeCapacity(size_t capacity) {
		T* tmp = new T[capacity + 1];
		std::copy_n(v, size, tmp);
		if (size > capacity)
			size = capacity;
		delete[] v;
		v = tmp;
		maxSize = capacity;
		_begin = Iter<T>(v, 0, maxSize);
		size_t endOffset = size ? size : 0;
		_end = Iter<T>(v, endOffset, maxSize);
	}

	Iter<T> begin() const { return _begin; }

	Iter<T> end() const { return _end; }
};