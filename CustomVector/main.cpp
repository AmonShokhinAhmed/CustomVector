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
	static int fooCount;
	int data;
	Foo(int data) :data(data) {
		std::cout << "Constructor" << std::endl;
		fooCount++;
	}
	Foo& operator=(const Foo& foo) {
		std::cout << "Copy Assignment" << std::endl;
		data = foo.data;
		fooCount ++;
		return *this;
	}
	Foo(const Foo& foo) :data(foo.data) {
		std::cout << "Copy" << std::endl;
		fooCount++;
	}
	~Foo() {
		std::cout << "Destructor" << std::endl;
		fooCount--;
	}
};
int Foo::fooCount = 0;
int main() {
	/*
	vector<int> intVector;
	std::cout << intVector.capacity() << std::endl;
	for (unsigned i = 0; i < 10; ++i) {
		intVector.push_back(i);
		std::cout << intVector.capacity() << std::endl;
	}
	std::cout << "Size: " << intVector.size() << std::endl;
	std::cout << "At 2: " << intVector.at(2) << std::endl;
	std::cout << "[]: " << intVector[2] << std::endl;
	//intVector.erase(intVector.begin()+2);
	//std::cout << "Size after erase: "<< intVector.size() << std::endl;
	//std::cout << "At 2 after erase: " << intVector.at(2) << std::endl;
	intVector.resize(5);
	std::cout << "Size after resize(5): " << intVector.size() << std::endl;
	std::cout << "Capacity after resize(5): " << intVector.capacity() << std::endl;
	intVector.resize(15);
	std::cout << "Size after resize(5): " << intVector.size() << std::endl;
	std::cout << "Capacity after resize(15): " << intVector.capacity() << std::endl;
	std::cout << intVector.at(14) << std::endl;
	intVector.resize(20, 2);
	std::cout << "Size after resize(5): " << intVector.size() << std::endl;
	std::cout << "Capacity after resize(20): " << intVector.capacity() << std::endl;
	intVector.reserve(48);
	std::cout << "Capacity after reserve(48): " << intVector.capacity() << std::endl;
	*/

	vector<Foo>* fooVector = new vector<Foo>();
	for (int i = 0; i < 2; ++i) {

		std::cout << std::endl << "Foo foo = Foo(i);" <<  std::endl ;
		Foo foo = Foo(i);

		std::cout << std::endl << "fooVector->push_back(foo);" <<  std::endl ;
		fooVector->push_back(foo);
	}

	std::cout << std::endl  << "fooVector->size(): "<<fooVector->size()<<" Foocount: " << Foo::fooCount << std::endl;

	std::cout << std::endl << "fooVector->resize(20, Foo(1));" << std::endl;
	fooVector->resize(20, Foo(1));

	std::cout << std::endl << "fooVector->size(): " << fooVector->size() << " Foocount: " << Foo::fooCount << std::endl;

	std::cout << std::endl << "vector<Foo>* secondFooVector = new vector<Foo>();" << std::endl;
	vector<Foo>* secondFooVector = new vector<Foo>();

	for (int i = 0; i < fooVector->size(); ++i) {
		secondFooVector->push_back(fooVector->at(i));
	}
	delete fooVector;
	delete secondFooVector;
	std::cout << "Foocount: " << Foo::fooCount << std::endl;
}