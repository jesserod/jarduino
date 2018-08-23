#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <string>
#include <assert.h>
// TODO: DO NOT SUBMIT
// TODO: DO NOT SUBMIT
// TODO: DO NOT SUBMIT
// TODO: DO NOT SUBMIT
// TODO: DO NOT SUBMIT
// TODO: DO NOT SUBMIT
// TODO: DO NOT SUBMIT
#include <iostream>
using namespace std;

namespace jarduino {

template <typename T>
class Array {
 public:
  Array() {
    Init(0);
  }

  ~Array() {
    Cleanup();
  }

  Array(const int& size) {
    Init(size);
  }

  void Init(const int& size) {
    cerr << "initting to " << size << endl;
    size_ = 0;  // Prevent Resize() from cleaning up when we haven't allocated yet.
    Resize(size);
  }

  Array& operator= (const Array& other) {
    size_ = other.size_;
    array_ = other.array_;
    other.size_ = 0;  // Prevent other's destructor from de-allocating.
    return *this;
  }

  T* GetUnderlying() const { return array_; }

  int Size() const { return size_; }

  T& Get(int i) const {
    // std::cerr << "Get " << i << " of " << Size() << std::endl;
    assert(i >= 0 && i < Size()); 
    return array_[i];
  }

  void Set(int i, const T& value) {
    assert(i >= 0 && i < Size()); 
    array_[i] = value;
  }

  T* Resize(const int& new_size) {
    cerr << "resizing to " << new_size << endl;
    assert(new_size >= 0);
    if (new_size <= size_) {
      size_ = new_size;
      return array_;
    }
    T* new_arr = new T[new_size]();  // Use () to zero initialize
    for (int i = 0; i < size_; ++i) {
      new_arr[i] = array_[i];
    }
    Cleanup();
    size_ = new_size;
    array_ = new_arr;
    return array_;
  }

 private:
  T* array_;
  int size_;

  void Cleanup() {
    if (size_ > 0) {
      cerr << "deleting old" << endl;
      delete [] array_;
    }
  }
};

}  // namespace jarduino
#endif
