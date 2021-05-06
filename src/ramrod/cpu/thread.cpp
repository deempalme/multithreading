#include "ramrod/cpu/thread.h"

namespace ramrod {
  namespace cpu {
    thread::thread() :
      finished_{false}
    {
    }

    thread::~thread(){

    }

    bool thread::check(){
      if(finished_) return true;
    }

    void thread::detach(){
      thread_->detach();
    }

    std::thread::id thread::id(){
      return std::this_thread::get_id();
    }

    std::size_t thread::hashed_id(){
      return std::hash<std::thread::id>()(std::this_thread::get_id());
    }

    void thread::join(){
      thread_->join();
    }
  } // namespace: cpu
} // namespace: ramrod
