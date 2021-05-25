#pragma once
#pragma warning(disable : 4996)

template <class T>
class CircularBuffer {
	template<typename T>
	class Iter : public std::iterator<std::random_access_iterator_tag, T> {
	private:
		T* p;
		size_t offset, maxOffset;
		typedef std::iterator<std::random_access_iterator_tag, T> base_template;
	public:
		typedef typename base_template::value_type           value_type;
		typedef typename base_template::pointer              pointer;
		typedef typename base_template::reference            reference;
		typedef typename base_template::iterator_category    iterator_category;
		typedef typename base_template::difference_type      difference_type;

		friend class CircularBuffer;

		Iter(pointer o = nullptr, size_t off = 0, size_t maxOff = 0)
			: p(o), offset(off), maxOffset(maxOff)
		{ }

		~Iter() { p = nullptr; offset = 0; maxOffset = 0; }

		Iter(const Iter<T>& other)
			: p(other.p), offset(other.offset), maxOffset(other.maxOffset)
		{ }

		Iter<T>& operator=(const Iter<T>& other) {
			if (this != &other) {
				p = other.p;
				offset = other.offset;
				maxOffset = other.maxOffset;
			}
			return *this;
		}

		Iter<T>& operator++() {
			if (offset + 1 <= maxOffset)
				++offset;
			else
				offset = 0;
			return *this;
		}

		Iter<T>& operator--() {
			if (offset <= 0)
				offset = maxOffset;
			else
				--offset;
			return *this;
		}

		Iter<T>& operator--(int) {
			Iter<T> tmp(*this);
			operator--();
			return tmp;
		}

		Iter<T> operator++(int) {
			Iter<T> tmp(this);
			operator++();
			return tmp;
		}

		reference operator*() { return *(p + offset); }

		const reference operator*() const { return *(p + offset); }

		pointer operator->() { return (p + offset); }

		difference_type operator -(const Iter& value) const {
			return maxOffset + p + offset - value.p - value.offset;
		}

		difference_type operator +(const Iter& value) const {
			return p + offset + value.p + value.offset;
		}

		Iter<T> operator -(const int& value) const {
			return Iter<T>(p, offset - value, maxOffset);
		}

		Iter<T> operator +(const int& value) const {
			return Iter<T>(p, offset + value, maxOffset);
		}

		bool operator==(Iter<T>& other) { return (p + offset) == (other.p + other.offset); }

		bool operator<(Iter<T>& other) { return (p + offset) < (other.p + other.offset); }

		friend bool operator!=(Iter<T> one, Iter<T> other) { return (one.p + one.offset) != (other.p + other.offset); }
		friend class CircularBuffer;
	};
private:
	T* v;
	size_t size, maxSize;
	Iter<T> _begin, _end;
public:
	CircularBuffer(size_t siz) 
		: size(0), maxSize(siz) 
	{
		Iter<T> begin(new T[siz + 1], 0, maxSize);
		_begin = begin;
		_end = begin;
	}
	~CircularBuffer() { }

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

	T delLast() {
		if (size > 0) {
			size--;
			--_end;
			return *_end;
		}
	}

	T delFirst() {
		if (size > 0) {
			T tmp = *_begin;
			size--;
			++_begin;
			return tmp;
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
			//throw out_of_range("out of range");
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
			//throw out_of_range("out of range");
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
		if (size > capacity)
			size = capacity;
		for (int i = 0; i != size; i++) {
			tmp[i] = this->operator[](i);
		}
		maxSize = capacity;
		Iter<T> begin(tmp, 0, maxSize);
		_begin = begin;
		size_t endOffset = size ? size : 0;
		Iter<T> end(tmp, endOffset, maxSize);
		_end = end;
	}

	Iter<T> begin() const { return _begin; }

	Iter<T> end() const { return _end; }
};