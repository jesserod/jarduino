#ifndef FLAT_LONG_MAP_H
#define FLAT_LONG_MAP_H

// A map backed by an array of longs.  Keys are always ints.
class FlatLongMap {
 public:
  FlatLongMap() {
    Init(10);
  }
  
  FlatLongMap(int max_size) {
    Init(max_size);
  }
    
  ~FlatLongMap() {
    delete [] arr_;
    delete [] occupied_;
  }
  
  bool Has(int key) {
    int i = constrain(key, 0, max_size_ - 1);
    return occupied_[i];
  }
  
  long Get(int key) {
    int i = constrain(key, 0, max_size_ - 1);
    return arr_[i];
  }
  
  long GetWithDefault(int key, long def) {
    if (!Has(key)) {
      return def;
    } else {
      return Get(key);
    }
  }
  
  void Insert(int key, long val) {
    int i = constrain(key, 0, max_size_ - 1);
    arr_[i] = val;
    if (!Has(i)) {
      num_items_++;
    }
    occupied_[i] = true;
  }
  
  bool Remove(int key) {
    int i = constrain(key, 0, max_size_ - 1);
    if (Has(i)) {
      occupied_[i] = false;
      num_items_--;
      return true;
    }
    return false;
  }
  
  void Increment(int key, long value) {
    Insert(key, GetWithDefault(key, 0) + value);
  }
  
  int size() {
    return num_items_; 
  }
  
  int MaxSize() {
    return max_size_;
  }
    
 protected:

  void Init(int max_size) {
    max_size_ = max_size;
    arr_ = new long[max_size_];
    occupied_ = new bool[max_size_];
    for (int i = 0; i < max_size_; ++i) {
      occupied_[i] = false;
      arr_[i] = 0;
    }
    num_items_ = 0;
  }

  
 private:
  int max_size_;
  long* arr_;
  bool* occupied_;
  // How many items are actually in the map right now
  int num_items_;
};

#endif
