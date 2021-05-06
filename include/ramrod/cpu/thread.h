#ifndef RAMROD_CPU_THREAD_H
#define RAMROD_CPU_THREAD_H

#include <functional>
#include <thread>

namespace ramrod {
  namespace cpu {
    class thread
    {
    public:
      thread();
      ~thread();

      bool check();

      void detach();

      std::thread::id id();
      std::size_t hashed_id();

      void join();


    protected:

    private:
      std::thread *thread_;
      bool finished_;
    };
  } // namespace: cpu
} // namespace: ramrod

#endif // RAMROD_CPU_THREAD_H
