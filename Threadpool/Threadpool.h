#pragma once

#include <condition_variable>
#include <functional>
#include <iostream>
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
  Threadpool() {
    should_terminate = false;
    start();
  }

  void start();
  void add_job(const std::function<void()> &job);
  void stop();
  bool busy();
};
