#define CUSTOMVECTOR

#include <iostream>
#ifdef CUSTOMVECTOR
	#include "CustomVector.h"
	template <typename T>
	using vector = CustomVector<T>;
#else
	#include <vector>
	template <typename T>
	using vector = std::vector<T>;
#endif

	class Foo
	{
	public:
		int data; 
		Foo(int data):data(data) {
			std::cout << "Constructor" << std::endl;
		}
		Foo(const Foo &foo):data(foo.data){ 
			std::cout << "Copy Constructor" << std::endl; 
		}
		~Foo() {
			std::cout << "Destructor" << std::endl;
		}
	};
int main() {
	vector<int> intVector;
	std::cout << intVector.capacity() << std::endl;
	std::cout << intVector.max_size() << std::endl;
	for (unsigned i = 0; i < 10; ++i) {
		intVector.push_back(i);
		std::cout << intVector.capacity() << std::endl;
	}
	std::cout << "Size: " << intVector.size() <<std::endl;
	std::cout << "At 2: " << intVector.at(2) << std::endl;
	std::cout << "[]: " << intVector[2] << std::endl;
	intVector.erase(intVector.begin()+2);
	std::cout << "Size after erase: "<< intVector.size() << std::endl;
	std::cout << "At 2 after erase: " << intVector.at(2) << std::endl;
	intVector.resize(5);
	std::cout << "Size after resize(5): " << intVector.size() << std::endl;
	std::cout << "Capacity: " << intVector.capacity() << std::endl;
	intVector.reserve(24);
	std::cout << "Capacity before reserve(24): " << intVector.capacity() << std::endl;

	
	vector<Foo>* fooVector = new vector<Foo>();
	for (int i = 0; i < 10; ++i) {
		fooVector->push_back(Foo(i));
	}
	vector<Foo>* secondFooVector = new vector<Foo>();
	for (int i = 0; i < fooVector->size(); ++i) {
		secondFooVector->push_back(fooVector->at(i));
	}
	for (int i = 0; i < 10; ++i) {
		std::cout << &fooVector->at(i) << std::endl;
		std::cout << &secondFooVector->at(i) << std::endl;
	}
	delete fooVector;
	for (int i = 0; i < secondFooVector->size(); ++i) {
		std::cout << secondFooVector->at(i).data << std::endl;
	}
	delete secondFooVector;
	
}