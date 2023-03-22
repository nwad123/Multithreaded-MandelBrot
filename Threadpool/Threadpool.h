#pragma once

#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

// class Job {
// private:
//   std::function<void(const size_t, const size_t)> work;
//   size_t start;
//   size_t end;
//
// public:
//   Job(std::function<void(const size_t, const size_t)> work, size_t start,
//       size_t end) {
//     this->work = work;
//     this->start = start;
//     this->end = end;
//   }
//
//   void run() { work(start, end); }
// };

class Threadpool {
private:
  void thread_loop();

  bool should_terminate;
  std::mutex queue_mutex;
  std::condition_variable mutex_condition;
  std::vector<std::thread> threads;
  std::queue<std::function<void(const size_t, const size_t)>> jobs;

public:
  Threadpool() {
    should_terminate = false;
    start();
  }

  void start();
  void add_job(const std::function<void(const size_t, const size_t)> &job,
               size_t start, size_t end);
  void stop();
  bool busy();
};
