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

int main() {
	vector<int> intVector;
	for (unsigned i = 0; i < 10; ++i) {
		intVector.push_back(i);
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


}