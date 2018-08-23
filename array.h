#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <string>
#include <assert.h>

namespace jarduino {

template <typename T>
class Array {
 public:
  Array() {
    Init(0);
  }

  Array(const int& size) {
    Init(size);
  }

  void Init(const int& size) {
    array_ = new T[0]();  // Use () to zero initialize
    size_ = 0;
    Resize(size);
  }

  T* GetUnderlying() const { return array_; }

  int Size() const { return size_; }

  const T& Get(int i) const {
    assert(i >= 0 && i < Size()); 
    return array_[i];
  }

  void Set(int i, const T& value) {
    assert(i >= 0 && i < Size()); 
    array_[i] = value;
  }

  T* Resize(const int& new_size) {
    assert(new_size >= 0);
    if (new_size <= size_) {
      size_ = new_size;
      return array_;
    }
    T* new_arr = new T[new_size]();  // Use () to zero initialize
    for (int i = 0; i < size_; ++i) {
      new_arr[i] = array_[i];
    }
    size_ = new_size;
    delete [] array_;
    array_ = new_arr;
    return array_;
  }

 private:
  T* array_;
  int size_;
};

}  // namespace jarduino
#endif
