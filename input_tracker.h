#ifndef INPUT_TRACKER_H
#define INPUT_TRACKER_H

#include <flat_long_map.h>

class InputTracker {
 public:
  InputTracker(int max_pin) : pin_states_(max_pin + 1) {
    pins_ = new int[0];
    num_pins_ = 0;
  }
  
  // Sets pin mode and gets initial pin state
  void RegisterInputPin(int pin, bool pullup) {
    pinMode(pin, pullup ? INPUT_PULLUP : INPUT);
    delay(10);
    if (!pin_states_.Has(pin)) {    
      pins_ = GeneralUtil::PushBack(pins_, num_pins_, pin);
      ++num_pins_;
    }
    long state = digitalRead(pin);
    pin_states_.Insert(pin, state);
  }
  
  bool IsChanged(int pin) {
    return pin_states_.Get(pin) != digitalRead(pin);
  }
  
  bool IsChangedTo(int pin, int state) {
    return IsChanged(pin) && digitalRead(pin) == state;
  }
  
  // Call after all checking is complete
  void Update() {
    for (int i = 0; i < num_pins_; ++i) {
      UpdatePin(pins_[i]);
    }
  }
  
 protected:
  void UpdatePin(int pin) {
    long state = digitalRead(pin);
    pin_states_.Insert(pin, state);
  }
  
 private:
  FlatLongMap pin_states_;
  int* pins_;
  int num_pins_;
};

#endif
