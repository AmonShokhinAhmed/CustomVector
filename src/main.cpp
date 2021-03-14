#define CUSTOMVECTOR

#include <iostream>
#ifdef CUSTOMVECTOR
#include "CustomVector.h"
template <typename T> using vector = CustomVector<T>;
#else
#include <vector>
template <typename T> using vector = std::vector<T>;
#endif

class Foo {
private:
  int m_data;

public:
  static int fooCount;

  int GetData() const { return m_data; }
  Foo(int data) : m_data(data) {
    std::cout << "Constructor" << std::endl;
    fooCount++;
  }

  Foo &operator=(const Foo &foo) {
    std::cout << "Copy Assignment" << std::endl;
    m_data = foo.m_data;
    fooCount++;
    return *this;
  }

  Foo(const Foo &foo) : m_data(foo.m_data) {
    std::cout << "Copy Constructor" << std::endl;
    fooCount++;
  }

  Foo(Foo &&foo) : m_data(std::move(foo.m_data)) {
    std::cout << "Move Constructor" << std::endl;
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
  for (uint32_t i = 0; i < 10; ++i) {
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
  std::cout << "Capacity after resize(5): " << intVector.capacity() <<
  std::endl; intVector.resize(15); std::cout << "Size after resize(5): " <<
  intVector.size() << std::endl; std::cout << "Capacity after resize(15): " <<
  intVector.capacity() << std::endl; std::cout << intVector.at(14) << std::endl;
  intVector.resize(20, 2);
  std::cout << "Size after resize(5): " << intVector.size() << std::endl;
  std::cout << "Capacity after resize(20): " << intVector.capacity() <<
  std::endl; intVector.reserve(48); std::cout << "Capacity after reserve(48): "
  << intVector.capacity() << std::endl;
  */
  {
    vector<Foo> fooVector = vector<Foo>();
    for (int i = 0; i < 10; ++i) {
      Foo foo = Foo(i);
      fooVector.push_back(foo);
    }
    for (auto i = fooVector.begin(); i != fooVector.end(); i++) {
      std::cout << "iterator loop at: " << (*i).GetData() << std::endl;
    }
    std::cout << "size before erase at: " << fooVector.size() << std::endl
              << std::endl;

    fooVector.erase(fooVector.begin() + 2, fooVector.begin() + 5);
    for (auto i = fooVector.begin(); i != fooVector.end(); i++) {
      std::cout << "iterator loop after erase at: " << (*i).GetData()
                << std::endl;
    }
    std::cout << "size after erase at: " << fooVector.size() << std::endl
              << std::endl;

    fooVector.erase(fooVector.begin() + 2);
    for (auto i = fooVector.begin(); i != fooVector.end(); i++) {
      std::cout << "iterator loop after erase at: " << (*i).GetData()
                << std::endl;
    }
    std::cout << "size after erase at: " << fooVector.size() << std::endl
              << std::endl;

    std::cout << std::endl
              << "fooVector->size(): " << fooVector.size()
              << " Foocount: " << Foo::fooCount << std::endl;
    std::cout << std::endl << "fooVector->resize(20, Foo(1));" << std::endl;
    fooVector.resize(20, Foo(1));

    std::cout << std::endl
              << "fooVector->size(): " << fooVector.size()
              << " Foocount: " << Foo::fooCount << std::endl;

    std::cout << std::endl
              << "vector<Foo>* secondFooVector = new vector<Foo>();"
              << std::endl;
    vector<Foo> secondFooVector = vector<Foo>();

    for (uint32_t i = 0; i < fooVector.size(); ++i) {
      secondFooVector.push_back(fooVector.at(i));
    }
    fooVector.erase_by_swap(2);
    // fooVector.erase(fooVector.begin() + 2);
    std::cout << std::endl << "for loop" << std::endl << std::endl;
    for (auto f : fooVector) {
      std::cout << f.GetData() << std::endl;
    }
  }
  std::cout << "Foocount: " << Foo::fooCount << std::endl;
}