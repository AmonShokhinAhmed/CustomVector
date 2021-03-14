#include <cassert>

#define MAXSIZE 10e8

template <typename T> class CustomVector {
private:
  T *_data;
  // TODO: maybe don't hard code this and instead actually find out the correct
  // value
  const uint32_t _maxSize;
  uint32_t _size;
  uint32_t _capacity;

public:
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;   // or also value_type*
    using reference = T &; // or also value_type&

    Iterator(pointer ptr) : m_ptr(ptr) {}
    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }
    Iterator &operator++() {
      m_ptr++;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const Iterator &a, const Iterator &b) {
      return a.m_ptr == b.m_ptr;
    };
    friend bool operator!=(const Iterator &a, const Iterator &b) {
      return a.m_ptr != b.m_ptr;
    };
    Iterator operator+(const int &i) {
      Iterator iterator(*this);
      for (int j = 0; j < i; j++) {
        iterator++;
      }
      return iterator;
    }

  private:
    T *m_ptr;
  };
  CustomVector() : _data(nullptr), _maxSize(MAXSIZE), _size(0), _capacity(0) {}
  ~CustomVector() {
    for (uint32_t i = 0; i < _size; i++) {
      _data[i].~T();
    }
    delete[] reinterpret_cast<char *>(_data);
  }

  T &at(const uint32_t index) {
    assert(index >= 0 && index < _size);
    return _data[index];
  }
  T &operator[](const uint32_t index) { return _data[index]; }

  void push_back(const T &val) {
    uint32_t newSize = _size + 1;
    assert(newSize <= _maxSize);
    if (newSize > _capacity) {
      uint32_t newCapacity = _size + (_size / 2);
      newCapacity = newCapacity >= newSize ? newCapacity : newSize;
      reserve(newCapacity);
    }
    _data[_size] = T(val);
    _size = newSize;
  }

  uint32_t size(void) { return _size; }
  uint32_t max_size(void) { return _maxSize; }
  uint32_t capacity(void) { return _capacity; }

  void resize(const uint32_t n) { resize(n, T()); }
  void resize(const uint32_t n, const T &val) {
    if (n > _maxSize) {
      // TODO: throw error maybe
      return;
    }

    uint32_t newCapacity = _capacity;
    while (newCapacity < n) {
      newCapacity += (newCapacity / 2);
    }
    T *newData = reinterpret_cast<T *>(new char[sizeof(T) * newCapacity]);
    if (n <= _size) {
      for (uint32_t i = 0; i < n; i++) {
        newData[i] = _data[i];
        _data[i].~T();
      }
    } else {
      for (uint32_t i = 0; i < _size; i++) {
        newData[i] = _data[i];
        _data[i].~T();
      }
      for (uint32_t i = _size; i < n; i++) {
        // This will throw an error if no default constructor is provided, but
        // std::vector does as well
        newData[i] = T(val);
      }
    }
    _capacity = newCapacity;
    _size = n;
    T *oldData = _data;
    _data = newData;
    delete[] reinterpret_cast<char *>(oldData);
  }
  void reserve(const uint32_t n) {
    if (n <= _capacity) {
      return;
    }
    T *newData = reinterpret_cast<T *>(new char[sizeof(T) * n]);
    for (uint32_t i = 0; i < _size; i++) {
      newData[i] = _data[i];
      _data[i].~T();
    }
    T *oldData = _data;
    _data = newData;
    delete[] reinterpret_cast<char *>(oldData);
    _capacity = n;
  }

  const T *as_array(void) { return _data; }
  void erase_by_swap(const uint32_t n) {
    assert(n < _size);
    _size--;
    if (n != _size) {
      _data[n].~T();
      _data[n] = _data[_size];
    }
    _data[_size].~T();
  }

  Iterator begin() { return Iterator(&_data[0]); }
  Iterator end() { return Iterator(&_data[_size]); }
  Iterator erase(Iterator position) { return erase(position, position); }
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
    uint32_t delAmount = 0;
    while (curPosition != end()) {
      (*curPosition).~T();
      ++curPosition;
      delAmount++;
    }
    _size -= delAmount;
    return first;
  }
};