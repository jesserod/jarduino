#include <general_util.h>
#include <flat_long_map.h>

class TaskTimer {
 public:
  TaskTimer(int max_task_id) : max_task_id_(max_task_id), timers_(max_task_id) {
    tasks_ = new int[0];
    num_tasks_ = 0;
    last_time_ = millis();
  };
  
  void RegisterTask(int task_id) {
    tasks_ = GeneralUtil::PushBack(tasks_, num_tasks_, task_id);
    ++num_tasks_;
  }
  
  bool IsTimeUp(int task_id) {
    if (timers_.Has(task_id) && timers_.Get(task_id) <= 0) {
      return true;
    }
    return false;
  }

  long RemainingMillis(int task_id) {
    return timers_.GetWithDefault(task_id, 0);
  }
  
  void SetTimer(int task_id, long millis) {
    timers_.Insert(task_id, millis);
  }
  
  void ClearTimer(int task_id) {
    timers_.Remove(task_id);
  }

  void Update() {
    long time = millis();
    long elapsed = time - last_time_;
    for (int i = 0; i < num_tasks_; ++i) {
      int task_id = tasks_[i];
      if (timers_.Has(task_id) && timers_.Get(task_id) > 0) {
        timers_.Increment(task_id, -elapsed);
      }
    }
     
    last_time_ = time;
  }
 
 private:
  int max_task_id_;
  long last_time_;
  FlatLongMap timers_;
  
  // Reigstered tasks
  int num_tasks_;
  int* tasks_;
};

