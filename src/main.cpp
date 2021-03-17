#define CUSTOMVECTOR
//#define PRINT_CONSTRUCTION_AND_DESTRUCTION

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
  explicit Foo(int data) : m_data(data) {
#ifdef PRINT_CONSTRUCTION_AND_DESTRUCTION
    std::cout << "Constructor" << std::endl;
#endif // PRINT_CONSTRUCTION_AND_DESTRUCTION
    fooCount++;
  }

  Foo &operator=(const Foo &foo) {
#ifdef PRINT_CONSTRUCTION_AND_DESTRUCTION
    std::cout << "Copy Assignment" << std::endl;
#endif // PRINT_CONSTRUCTION_AND_DESTRUCTION
    m_data = foo.m_data;
    fooCount++;
    return *this;
  }

  Foo(const Foo &foo) : m_data(foo.m_data) {
#ifdef PRINT_CONSTRUCTION_AND_DESTRUCTION
    std::cout << "Copy Constructor" << std::endl;
#endif // PRINT_CONSTRUCTION_AND_DESTRUCTION
    fooCount++;
  }

  Foo(Foo &&foo) noexcept {
#ifdef PRINT_CONSTRUCTION_AND_DESTRUCTION
    std::cout << "Move Constructor" << std::endl;
#endif // PRINT_CONSTRUCTION_AND_DESTRUCTION
    m_data = foo.m_data;
    fooCount++;
  }

  Foo &operator=(Foo &&foo) noexcept {
#ifdef PRINT_CONSTRUCTION_AND_DESTRUCTION
    std::cout << "Move Assignment" << std::endl;
#endif // PRINT_CONSTRUCTION_AND_DESTRUCTION
    if (this != &foo) {
      m_data = foo.m_data;

      // counting up kind of falsely here, because we create objects without
      // calling the constructor in vector, so the count would be wrong otherwise
      fooCount++;
    }
    return *this;
  }

  ~Foo() {
#ifdef PRINT_CONSTRUCTION_AND_DESTRUCTION
    std::cout << "Destructor" << std::endl;
#endif // PRINT_CONSTRUCTION_AND_DESTRUCTION
    fooCount--;
  }
};
int Foo::fooCount = 0;

void Test() {
  std::cout << "Creating vector: " << std::endl;
  vector<Foo> fooVector = vector<Foo>();

  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-------------"
            << std::endl
            << std::endl;

  std::cout << "Pushing back with reference: " << std::endl;
  for (int i = 0; i < 5; ++i) {
    Foo foo = Foo(i);
    fooVector.push_back(foo);
  }

  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-------------"
            << std::endl
            << std::endl;

  std::cout << "Pushing back with rvalue: " << std::endl;
  for (int i = 5; i < 10; ++i) {
    fooVector.push_back(Foo(i));
  }
  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-------------"
            << std::endl
            << std::endl;

  std::cout << "Range based for loop: " << std::endl;
  for (const auto& f : fooVector) {
    std::cout << f.GetData() << ", ";
  }
  std::cout << std::endl;

  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-------------"
            << std::endl
            << std::endl;

  std::cout << "Current size: " << fooVector.size() << std::endl;

  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-------------"
            << std::endl
            << std::endl;

  std::cout << "Current Capacity: " << fooVector.capacity() << std::endl;

  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-------------"
            << std::endl
            << std::endl;

  std::cout << "Erasing element at index 2: " << std::endl;

  std::cout << "Size before erasing: " << fooVector.size() << std::endl;
  std::cout << "Capacity before erasing: " << fooVector.capacity() << std::endl;
  std::cout << "Elements before erasing: " << std::endl;
  for (const auto& f : fooVector) {
    std::cout << f.GetData() << ", ";
  }
  std::cout << std::endl;

  fooVector.erase(fooVector.begin() + 2);

  std::cout << "Size after erasing: " << fooVector.size() << std::endl;
  std::cout << "Capacity after erasing: " << fooVector.capacity() << std::endl;
  std::cout << "Elements after erasing: " << std::endl;
  for (const auto& f : fooVector) {
    std::cout << f.GetData() << ", ";
  }
  std::cout << std::endl;

  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-------------"
            << std::endl
            << std::endl;

  std::cout << "Erasing element between index 2 and 5: " << std::endl;

  std::cout << "Size before erasing: " << fooVector.size() << std::endl;
  std::cout << "Capacity before erasing: " << fooVector.capacity() << std::endl;
  std::cout << "Elements before erasing: " << std::endl;
  for (const auto& f : fooVector) {
    std::cout << f.GetData() << ", ";
  }
  std::cout << std::endl;

  fooVector.erase(fooVector.begin() + 2, fooVector.begin() + 5);

  std::cout << "Size after erasing: " << fooVector.size() << std::endl;
  std::cout << "Capacity after erasing: " << fooVector.capacity() << std::endl;
  std::cout << "Elements after erasing: " << std::endl;
   for (const auto& f : fooVector) {
    std::cout << f.GetData() << ", ";
  }
  std::cout << std::endl;

  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-------------"
            << std::endl
            << std::endl;

  std::cout << "Loop using at()" << std::endl;
  for (uint32_t i = 0; i < fooVector.size(); ++i) {
    std::cout << fooVector.at(i).GetData() << ", ";
  }

  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-------------"
            << std::endl
            << std::endl;

  std::cout << "Loop using []" << std::endl;
  for (uint32_t i = 0; i < fooVector.size(); ++i) {
    std::cout << fooVector[i].GetData() << ", ";
  }

  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-------------"
            << std::endl
            << std::endl;

  std::cout << "Reserving with new capacity of 20: " << std::endl;
  std::cout << "Capacity before reserve: " << fooVector.capacity() << std::endl;
  fooVector.reserve(20);
  std::cout << "Capacity after reserve: " << fooVector.capacity() << std::endl;

  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-------------"
            << std::endl
            << std::endl;

  std::cout << "Resizing to size 20: " << std::endl;
  std::cout << "Size before resize: " << fooVector.size() << std::endl;
  fooVector.resize(20, Foo(20));
  std::cout << "Size after resize: " << fooVector.size() << std::endl;

  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-------------"
            << std::endl
            << std::endl;

  std::cout << "Loop using raw pointer: " << std::endl;
  for (uint32_t i = 0; i < fooVector.size(); ++i) {
    std::cout << (fooVector.as_array() + i)->GetData() << std::endl;
  }

  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-------------"
            << std::endl
            << std::endl;

#ifdef CUSTOMVECTOR
  std::cout << "Changing vector elments to new values: " << std::endl;
  std::cout << "Elements before change: " << std::endl;
  for (const auto& f : fooVector) {
    std::cout << f.GetData() << ", ";
  }
  std::cout << std::endl;

  for (uint32_t i = 0; i < fooVector.size(); ++i) {
    // decrementing here because we have to falsely count up in foo because of
    // allocating of memory without calling the constructor of Foo in vector
    Foo::fooCount--;
    fooVector[i] = Foo(i);
  }
  std::cout << "Elements after change: " << std::endl;
  for (const auto& f : fooVector) {
    std::cout << f.GetData() << ", ";
  }
  std::cout << std::endl;

  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-------------"
            << std::endl
            << std::endl;

  std::cout << "Erasing element at index 2 by swap:" << std::endl;
  std::cout << "Size before erase: " << fooVector.size() << std::endl;
  std::cout << "Element at index 2 before erase: " << fooVector.at(2).GetData()
            << std::endl;
  std::cout << "Element at last position before erase: "
            << fooVector.at(fooVector.size() - 1).GetData() << std::endl;
  fooVector.erase_by_swap(2);
  std::cout << "Size after erase: " << fooVector.size() << std::endl;
  std::cout << "Element at index 2 after erase: " << fooVector.at(2).GetData()
            << std::endl;
  std::cout << "Element at last position before erase: "
            << fooVector.at(fooVector.size() - 1).GetData() << std::endl;

#endif // CUSTOMVECTOR
}

int main() {
  { Test(); }
  std::cout << "Foocount: " << Foo::fooCount << std::endl;
}