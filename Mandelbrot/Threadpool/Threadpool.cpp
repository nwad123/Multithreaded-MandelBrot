#include "Threadpool.h"
#include <thread>

// Starts the threadpool
void Threadpool::start() {
  // get the number of threads available on the system
  const int num_threads = std::thread::hardware_concurrency();

  // resize the threads container
  threads.resize(num_threads);

  // start each of the threads
  for (int i = 0; i < num_threads; i++) {
    threads.push_back(std::thread(&Threadpool::thread_loop, this));
  }

  // report on threads spawned
  std::cout << "Successfully started thread pool with " << num_threads
            << " threads." << std::endl;
}

// The worker function
void Threadpool::thread_loop() {
  // job variable
  std::function<void()> job;

  // infinite loop that checks if there are tasks available
  while (true) {
    {
      // lock the queue
      std::unique_lock<std::mutex> lock(queue_mutex);

      // check if the queue is empty
      mutex_condition.wait(
          lock, [this] { return !jobs.empty() || should_terminate; });

      // check if thread should terminate
      if (should_terminate) {
        return;
      }

      // get the next job
      job = jobs.front();
      jobs.pop();
    }

    // run the job
    job();
  }
}

// Add a job to the pool
void Threadpool::add_job(const std::function<void()> &job) {
  {
    std::unique_lock<std::mutex> lock(queue_mutex);

    jobs.push(job);
  }
  mutex_condition.notify_one();
}

//
bool Threadpool::busy() {
  bool pool_is_busy;
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    pool_is_busy = !jobs.empty();
  }
  return pool_is_busy;
}

//
void Threadpool::stop() {
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    should_terminate = true;
  }
  mutex_condition.notify_all();

  for (std::thread &thread : threads) {
    if (thread.joinable()) {
      thread.join();
    }
  }

  threads.clear();
}
