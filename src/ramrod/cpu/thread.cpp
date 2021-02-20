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

    void thread::join(){
      thread_->join();
    }
  } // namespace: cpu
} // namespace: ramrod
