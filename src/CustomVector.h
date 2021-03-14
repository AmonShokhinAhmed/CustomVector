#include <cassert>

#define MAXSIZE 10e8

template <typename T> class CustomVector {
private:
  T *_data;
  // TODO: maybe don't hard code this and instead actually find out the correct
  // value
  const uint32_t m_maxSize;
  uint32_t m_size;
  uint32_t m_capacity;

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
  CustomVector()
      : _data(nullptr), m_maxSize(MAXSIZE), m_size(0), m_capacity(0) {}
  ~CustomVector() {
    for (uint32_t i = 0; i < m_size; i++) {
      _data[i].~T();
    }
    delete[] reinterpret_cast<char *>(_data);
  }

  T &at(const uint32_t index) {
    assert(index >= 0 && index < m_size);
    return _data[index];
  }
  T &operator[](const uint32_t index) { return _data[index]; }

  void push_back(const T &val) {
    uint32_t newSize = m_size + 1;
    assert(newSize <= m_maxSize);
    if (newSize > m_capacity) {
      uint32_t newCapacity = m_size + (m_size / 2);
      newCapacity = newCapacity >= newSize ? newCapacity : newSize;
      reserve(newCapacity);
    }
    _data[m_size] = T(val);
    m_size = newSize;
  }

  uint32_t size(void) { return m_size; }
  uint32_t max_size(void) { return m_maxSize; }
  uint32_t capacity(void) { return m_capacity; }

  void resize(const uint32_t n) { resize(n, T()); }
  void resize(const uint32_t n, const T &val) {
    if (n > m_maxSize) {
      // TODO: throw error maybe
      return;
    }

    uint32_t newCapacity = m_capacity;
    while (newCapacity < n) {
      newCapacity += (newCapacity / 2);
    }
    T *newData = reinterpret_cast<T *>(new char[sizeof(T) * newCapacity]);
    if (n <= m_size) {
      for (uint32_t i = 0; i < n; i++) {
        newData[i] = _data[i];
        _data[i].~T();
      }
    } else {
      for (uint32_t i = 0; i < m_size; i++) {
        newData[i] = _data[i];
        _data[i].~T();
      }
      for (uint32_t i = m_size; i < n; i++) {
        // This will throw an error if no default constructor is provided, but
        // std::vector does as well
        newData[i] = T(val);
      }
    }
    m_capacity = newCapacity;
    m_size = n;
    T *oldData = _data;
    _data = newData;
    delete[] reinterpret_cast<char *>(oldData);
  }
  void reserve(const uint32_t n) {
    if (n <= m_capacity) {
      return;
    }
    T *newData = reinterpret_cast<T *>(new char[sizeof(T) * n]);
    for (uint32_t i = 0; i < m_size; i++) {
      newData[i] = _data[i];
      _data[i].~T();
    }
    T *oldData = _data;
    _data = newData;
    delete[] reinterpret_cast<char *>(oldData);
    m_capacity = n;
  }

  const T *as_array(void) { return _data; }
  void erase_by_swap(const uint32_t n) {
    assert(n < m_size);
    m_size--;
    if (n != m_size) {
      _data[n].~T();
      _data[n] = _data[m_size];
    }
    _data[m_size].~T();
  }

  Iterator begin() { return Iterator(&_data[0]); }
  Iterator end() { return Iterator(&_data[m_size]); }
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
    m_size -= delAmount;
    return first;
  }
};