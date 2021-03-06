#include "torero/cpu/threads.h"

#include <boost/thread.hpp>

namespace torero {
  namespace cpu {
    threads::threads() :
      active_processes_(0),
      awaiting_processes_(0),
      cores_number_{0u},
      active_cores_{0u},
      finished_{true}
    {
      cores_number_ = boost::thread::hardware_concurrency();
      if(cores_number_ <= 1) cores_number_ = boost::thread::physical_concurrency();
      if(cores_number_ < 1) cores_number_ = 1;
    }

    unsigned int threads::multithread_active_threads(){
      return active_cores_;
    }

    void threads::multithread_add_process(boost::function<void (void)> run,
                                          boost::function<void (void)> ready,
                                          boost::mutex *protector_pointer){
      if(cores_number_ == 1){
        run();
        ready();
      }else if(!protector_pointer){
        boost::thread(run).detach();
      }else if(active_cores_ >= cores_number_){
        threads::process new_process{ run, ready, protector_pointer };
        awaiting_processes_.push_back(new_process);
        finished_ = false;
      }else{
        cpu::threads::process new_process{ run, ready, protector_pointer };
        boost::thread(run).detach();

        active_processes_.push_back(new_process);
        finished_ = false;

        ++active_cores_;
      }
    }

    const bool &threads::multithread_all_finished(){
      return finished_;
    }

    std::size_t threads::multithread_number_of_active_processes(){
      return active_processes_.size();
    }

    std::size_t threads::multithread_number_of_awaiting_processes(){
      return awaiting_processes_.size();
    }

    unsigned int threads::multithread_number_of_threads(){
      return cores_number_;
    }

    void threads::multithread_update_process(){
      std::vector<std::size_t> to_delete(0);
      to_delete.reserve(active_cores_);
      const std::size_t active_size{active_processes_.size()};

      for(std::size_t i = 0; i < active_size; ++i){
        if(active_processes_[i].mutex_pointer->try_lock()){
          active_processes_[i].mutex_pointer->unlock();
          active_processes_[i].ready();
          if(awaiting_processes_.size() > 0){
            active_processes_[i] = awaiting_processes_[0];
            awaiting_processes_.erase(awaiting_processes_.begin());
            boost::thread(active_processes_[i].run).detach();
          }else{
            --active_cores_;
            to_delete.push_back(i);
          }
        }
      }

      const int delete_size{static_cast<int>(to_delete.size()) - 1};

      if(delete_size >= 0)
        for(int i = delete_size; i >= 0; --i)
          active_processes_.erase(active_processes_.begin() + to_delete[static_cast<std::size_t>(i)]);

      if((active_processes_.size() + awaiting_processes_.size()) <= 0)
        finished_ = true;
    }
  }
}
