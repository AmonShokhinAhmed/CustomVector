#include <cassert>
#include <new>

#define MAXSIZE 10e8

template <typename T> class CustomVector {
private:
  T *m_data;
  // TODO: maybe don't hard code this and instead actually find out the correct
  // value
  const uint32_t m_maxSize;
  uint32_t m_size;
  uint32_t m_capacity;

public:
  struct Iterator {

    // necessary to work with standard semantic e.g. range based loop
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;   // or also value_type*
    using reference = T &; // or also value_type&

    explicit Iterator(pointer ptr) : m_ptr(ptr) {}
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
        ++iterator;
      }
      return iterator;
    }

  private:
    T *m_ptr;
  };

  // initializing empty, maybe we should initialize with default capacity, but
  // capacity size depends on application so leaving it empty for now
  CustomVector()
      : m_data(nullptr), m_maxSize((int)MAXSIZE), m_size(0), m_capacity(0) {}

  ~CustomVector() {
    // manually calling destructors because we later delete without calling the
    // destructors
    for (uint32_t i = 0; i < m_size; i++) {
      m_data[i].~T();
    }
    ::operator delete(m_data);
  }

  T &at(const uint32_t index) {
    assert(index < m_size);
    return m_data[index];
  }
  T &operator[](const uint32_t index) { return m_data[index]; }

  // push back by reference uses copy constructor
  void push_back(const T &val) {
    uint32_t newSize = m_size + 1;
    reserveForPush(newSize);
    new (m_data + m_size) T(val);
    m_size = newSize;
  }

  // push back by rvalue uses move assignment
  void push_back(T &&val) {
    uint32_t newSize = m_size + 1;
    reserveForPush(newSize);
    new (m_data + m_size)T(std::move(val));
    m_size = newSize;
  }

  uint32_t size(void) const { return m_size; }
  uint32_t max_size(void) const { return m_maxSize; }
  uint32_t capacity(void) const { return m_capacity; }
  T *as_array(void) const { return m_data; }

  // This will throw an error if no default constructor is provided, but
  // std::vector does as well
  void resize(const uint32_t n) { resize(n, T()); }

  void resize(const uint32_t n, const T &val) {
    assert(n <= MAXSIZE);

    uint32_t newCapacity = m_capacity;

    // growing capacity geometrically so we don't alway have to reallocate
    // memory but growth is also not as wastefull as simply duplicating
    while (newCapacity < n) {
      newCapacity += (newCapacity / 2);
    }

    // allocating memory without calling constructors
    T *newData = (T *)::operator new(newCapacity * sizeof(T));

    // shrinking the vector
    if (n <= m_size) {
      // move data to new location
      for (uint32_t i = 0; i < n; i++) {
        new (newData + i) T(std::move(m_data[i]));
        m_data[i].~T();
      }
      // delete leftover data
      for (uint32_t i = n; i < m_size; i++) {
        m_data[i].~T();
      }
    }
    // growing the vector
    else {
      for (uint32_t i = 0; i < m_size; i++) {
        // using this syntax so we don't actually read from un initialized
        // location, because this generates a warning using move here because we
        // just take the data from the old array
        new (newData + i) T(std::move(m_data[i]));
        m_data[i].~T();
      }
      for (uint32_t i = m_size; i < n; i++) {
        // using this syntax so we don't actually read from un initialized
        // location, because this generates a warning copying here because we
        // duplicate the given value to all positions
        new (newData + i) T(val);
      }
    }

    T *oldData = m_data;
    m_data = newData;
    // deleting without calling destructors, because we called them manually in
    // the loops before
    ::operator delete(oldData);
    m_size = n;
    m_capacity = newCapacity;
  }

  void reserve(const uint32_t n) {
    if (n <= m_capacity) {
      return;
    }

    // allocating without calling constructors
    T *newData = (T *)::operator new(n * sizeof(T));

    // moving old data over to new location
    for (uint32_t i = 0; i < m_size; i++) {
      new (newData + i) T(std::move(m_data[i]));
      m_data[i].~T();
    }
    T *oldData = m_data;
    m_data = newData;
    // delete without calling destructors, because we called them manually in
    // the moving loop
    ::operator delete(oldData);
    m_capacity = n;
  }

  void erase_by_swap(const uint32_t n) {
    assert(n < m_size);
    m_size--;
    if (n != m_size) {
      m_data[n].~T();
      m_data[n] = std::move(m_data[m_size]);
    }
    m_data[m_size].~T();
  }

  Iterator begin() { return Iterator(&m_data[0]); }
  Iterator end() { return Iterator(&m_data[m_size]); }
  Iterator erase(Iterator position) { return erase(position, position); }
  Iterator erase(Iterator first, Iterator last) {
    if (first == end()) {
      return first;
    }
    Iterator curPosition = first;
    Iterator nextPosition = last + 1;

    // repeat for every element in the section between first and last
    while (nextPosition != end()) {
      // deleting the data
      (*curPosition).~T();
      // moving over the data into the gap that the delete creates
      (*curPosition) = std::move(*(nextPosition));
      ++curPosition;
      ++nextPosition;
    }
    uint32_t delAmount = 0;
    // delete leftover empty positions
    while (curPosition != end()) {
      (*curPosition).~T();
      ++curPosition;
      ++delAmount;
    }
    m_size -= delAmount;
    return first;
  }

private:
  void reserveForPush(uint32_t newSize) {
    assert(newSize <= m_maxSize);
    if (newSize > m_capacity) {
      // using geometric growth
      uint32_t newCapacity = m_size + (m_size / 2);
      newCapacity = newCapacity >= newSize ? newCapacity : newSize;
      reserve(newCapacity);
    }
  }
};