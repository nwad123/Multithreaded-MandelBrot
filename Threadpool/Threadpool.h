#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class Threadpool {
private:
  void thread_loop();

  bool should_terminate;
  std::mutex queue_mutex;
  std::condition_variable mutex_condition;
  std::vector<std::thread> threads;
  std::queue<std::function<void()>> jobs;

public:
  Threadpool();

  ~Threadpool();

  void Start();
  void QueueJob(const std::function<void()> &job);
  void Stop();
  bool busy();
};
