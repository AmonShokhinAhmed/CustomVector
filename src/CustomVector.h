#include <cassert>
template <typename T>
class CustomVector {
private:
	T* _data; 
	//TODO: maybe don't hard code this and instead actually find out the correct value
	const unsigned int _maxSize = 10e8;
	unsigned int _size;
	unsigned int _capacity;
public:
	struct Iterator {
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;  // or also value_type*
		using reference = T&;  // or also value_type&

		Iterator(pointer ptr): m_ptr(ptr) {}
		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }
		Iterator& operator++() { m_ptr++; return *this; }
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
		Iterator operator+(const int& i) {
			Iterator iterator(*this);
			for (int j = 0; j < i; j++) {
				iterator++;
			}
			return iterator;
		}
	private:
		T* m_ptr;
	};
	CustomVector(): _data(nullptr), _capacity(0), _size(0) {
	}
	~CustomVector() {
		for (unsigned int i = 0; i < _size; i++) {
			_data[i].~T();
		}
		delete[] reinterpret_cast<char*>(_data);
	}

	T& at(const unsigned int index) {
		assert(index >= 0 && index < _size);
		return _data[index];
	}
	T& operator[](const unsigned index) {
		return _data[index];
	}
	
	void push_back(const T& val) {
		unsigned int newSize = _size + 1;
		assert(newSize<=_maxSize);
		if (newSize > _capacity) {
			unsigned int newCapacity = _size + (_size / 2);
			newCapacity = newCapacity >= newSize ? newCapacity : newSize;
			reserve(newCapacity);
		}
		_data[_size] = T(val);
		_size = newSize;
	}

	const unsigned int size(void) {
		return _size;
	}
	const unsigned int max_size(void) {
		return _maxSize;
	}
	const unsigned int capacity(void) {
		return _capacity;
	}
	
	void resize(const unsigned int n) {
		resize(n, T());
	}
	void resize(const unsigned int n, const T& val) {
		if (n > _maxSize) {
			//TODO: throw error maybe
			return;
		}

		unsigned int newCapacity = _capacity;
		while (newCapacity < n) {
			newCapacity += (newCapacity / 2);
		}
		T* newData = reinterpret_cast<T*>(new char[sizeof(T) * newCapacity]);
		if (n <= _size) {
			for (int i = 0; i < n; i++) {
				newData[i] = _data[i];
				_data[i].~T();
			}
		}
		else {
			for (int i = 0; i < _size; i++) {
				newData[i] = _data[i];
				_data[i].~T();
			}
			for (int i = _size; i < n; i++) {
				//This will throw an error if no default constructor is provided, but std::vector does as well
				newData[i] = T(val);
			}
		}
		_capacity = newCapacity;
		_size = n;
		T* oldData = _data;
		_data = newData;
		delete[] reinterpret_cast<char*>(oldData);
	}
	void reserve(const unsigned int n) {
		if (n <= _capacity) {
			return;
		}
		T* newData = reinterpret_cast<T*>(new char[sizeof(T) * n]);
		for (unsigned int i = 0; i < _size; i++) {
			newData[i] = _data[i];
			_data[i].~T();
		}
		T* oldData = _data;
		_data = newData;
		delete[] reinterpret_cast<char*>(oldData);
		_capacity = n;
	}

	const T* as_array(void) {
		return _data;
	}
	void erase_by_swap(const unsigned int n) {
		assert(n < _size);
		_size--;
		if (n != _size) {
			_data[n].~T();
			_data[n] = _data[_size];
		}
		_data[_size].~T();
	}

	Iterator begin() {
		return Iterator(&_data[0]);
	}
	Iterator end() {
		return Iterator(&_data[_size]);
	}
	Iterator erase(Iterator position) {
		return erase(position, position);
	}
	Iterator erase(Iterator first, Iterator last) {
		if (first == end()) {
			return first;
		}
		Iterator curPosition = first;
		Iterator nextPosition = last + 1;
		while (nextPosition != end()) {
			(*curPosition).~T();
			(*curPosition) = (*(nextPosition));
			++curPosition;
			++nextPosition;
		}
		unsigned int delAmount = 0;
		while (curPosition != end()) {
			(*curPosition).~T();
			++curPosition;
			delAmount++;
		}
		_size -= delAmount;
		return first;
	}
}; 