#include "CustomIterator.h"
template <typename T>
class CustomVector {
public:
	CustomVector() {

	}
	T& at(unsigned index) {
		T t = T();
		return t;
	}
	T& operator[](const unsigned index) {
		T t = T();
		return t;
	}
	void push_back(const T& val) {

	}
	const size_t size(void) {
		return 0;
	}
	const size_t capacity(void) {
		return 0;
	}
	void resize(const unsigned n) {

	}
	void resize(const unsigned n, const T& val) {

	}
	void reserve(unsigned n) {

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