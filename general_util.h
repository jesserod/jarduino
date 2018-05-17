#ifndef GENERAL_UTIL_H
#define GENERAL_UTIL_H

class GeneralUtil {
 public:
  static int* ResizeIntArray(int* arr, int old_size, int new_size) {
    if (new_size <= old_size) {
      return arr;
    }
    int* new_arr = new int[new_size];
    for (int i = 0; i < old_size; ++i) {
      new_arr[i] = arr[i];
    }
    delete [] arr;
    return new_arr;
  }
  
  static int* PushBack(int *arr, int arr_size, int value) {
    arr = ResizeIntArray(arr, arr_size, arr_size + 1);
    arr[arr_size] = value;
    return arr;
  }

  static int Clamp(int val, int low, int high) {
    return min(max(val, low), high);
  }
  
};

#endif
