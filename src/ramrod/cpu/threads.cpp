#include "ramrod/cpu/threads.h"

#include <thread>

namespace ramrod {
  namespace cpu {
    threads::threads() :
      active_processes_(0),
      awaiting_processes_(0),
      threads_number_{0u},
      active_threads_{0u},
      finished_{true}
    {
      threads_number_ = std::thread::hardware_concurrency();
      if(threads_number_ < 1) threads_number_ = 1;
    }

    unsigned int threads::active_threads(){
      return active_threads_;
    }

    bool threads::add_thread(std::function<void ()> run, std::function<void ()> ready){
      if(threads_number_ == 1){
        run();
        ready();
        return false;
      }else if(active_threads_ >= threads_number_){
        std::mutex *new_mutex { new std::mutex() };

        ramrod::cpu::threads::process new_process{
          std::bind(&threads::unmutex_helper, this, run, new_mutex), ready, new_mutex, true
        };

        awaiting_processes_.push_back(new_process);
        finished_ = false;
      }else{
        std::mutex *new_mutex { new std::mutex() };

        ramrod::cpu::threads::process new_process{
          std::bind(&threads::unmutex_helper, this, run, new_mutex), ready, new_mutex, true
        };
        std::thread(run).detach();

        active_processes_.push_back(new_process);
        finished_ = false;

        ++active_threads_;
      }
      return true;
    }

    bool threads::add_thread(std::function<void (void)> run,
                             std::function<void (void)> ready,
                             std::mutex *protector_pointer){
      if(protector_pointer == nullptr) return add_thread(run, ready);

      if(threads_number_ == 1){
        run();
        ready();
        return false;
      }else if(!protector_pointer){
        std::thread(run).detach();
      }else if(active_threads_ >= threads_number_){
        threads::process new_process{ run, ready, protector_pointer, false };
        awaiting_processes_.push_back(new_process);
        finished_ = false;
      }else{
        cpu::threads::process new_process{ run, ready, protector_pointer, false };
        std::thread(run).detach();

        active_processes_.push_back(new_process);
        finished_ = false;

        ++active_threads_;
      }
      return true;
    }

    const bool &threads::all_threads_finished(){
      return finished_;
    }

    std::size_t threads::number_of_active_threads(){
      return active_processes_.size();
    }

    std::size_t threads::number_of_awaiting_threads(){
      return awaiting_processes_.size();
    }

    unsigned int threads::number_of_threads(){
      return threads_number_;
    }

    void threads::update_threads(){
      std::vector<std::size_t> to_delete(0);
      to_delete.reserve(active_threads_);
      const std::size_t active_size{active_processes_.size()};

      for(std::size_t i = 0; i < active_size; ++i){
        if(active_processes_[i].mutex_pointer->try_lock()){
          active_processes_[i].mutex_pointer->unlock();
          active_processes_[i].ready();
          if(awaiting_processes_.size() > 0){
            active_processes_[i] = awaiting_processes_[0];
            awaiting_processes_.erase(awaiting_processes_.begin());
            std::thread(active_processes_[i].run).detach();
          }else{
            --active_threads_;
            to_delete.push_back(i);
          }
        }
      }

      const int delete_size{static_cast<int>(to_delete.size()) - 1};

      if(delete_size >= 0)
        for(int i = delete_size; i >= 0; --i){
          const std::size_t index{to_delete[static_cast<std::size_t>(i)]};

          if(active_processes_[index].lone)
            delete active_processes_[index].mutex_pointer;

          active_processes_.erase(active_processes_.begin() + index);
        }

      if((active_processes_.size() + awaiting_processes_.size()) <= 0)
        finished_ = true;
    }

    void threads::wait_microseconds(const int64_t microseconds){
      std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
    }

    void threads::wait_seconds(const int64_t seconds){
      std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }

    void threads::wait(const int64_t milliseconds){
      std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    void threads::unmutex_helper(std::function<void (void)> run, std::mutex *mutex){
      mutex->lock();
      run();
      mutex->unlock();
    }
  } // namespace: cpu
} // namespace: ramrod
