#include "CustomIterator.h"
template <typename T>
class CustomVector {
private:
	T* _data; 
	//TODO: maybe don't hard code this and instead actually find out the correct value
	const unsigned int _maxSize = 10e8;
	unsigned int _size;
	unsigned int _capacity;
public:
	CustomVector(): _data(nullptr), _capacity(0), _size(0) {
	}

	~CustomVector() {
		for (unsigned int i = 0; i < _size; i++) {
			_data[i].~T();
		}
	}

	T& at(const unsigned int index) {
		if (index >= _size) {
			//TODO: throw error maybe
		}
		return _data[index];
	}

	T& operator[](const unsigned index) {
		return _data[index];
	}
	
	void push_back(const T& val) {
		unsigned int newSize = _size + 1;
		if (newSize > _maxSize) {
			//TODO: throw error maybe
			return;
		}
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

	void reserve(unsigned int n) {
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

	CustomIterator begin(void) {
		return CustomIterator();
	}
	CustomIterator end(void) {
		return CustomIterator();
	}
	CustomIterator erase(CustomIterator position) {
		return CustomIterator();
	}
	CustomIterator erase(CustomIterator first, CustomIterator last) {
		return CustomIterator();
	}
}; 