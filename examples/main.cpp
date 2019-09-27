
#include "torero/cpu/threads.h"

#include <boost/bind.hpp>           // for bind
#include <boost/thread/mutex.hpp>   // for mutex
#include <boost/thread/thread.hpp>  // for this_thread, sleep, posix_time
#include <iomanip>                  // for setprecision
#include <iostream>                 // for cout, endl, fixed

// Function to call in a different thread
void test_run(double *value_to_add, const std::size_t number_of_iterations,
              boost::posix_time::ptime *final_time, boost::mutex *mutex){
  mutex->lock();
  const double addition{*value_to_add};

  for(std::size_t i = 0; i < number_of_iterations; ++i){
    (*value_to_add) += addition;
  }

  *final_time = boost::posix_time::microsec_clock::local_time();

  mutex->unlock();
}

// Function that will be called after the thread finishes
void test_ready(const double *result, boost::posix_time::ptime *initial_time,
                boost::posix_time::ptime *final_time){
  const boost::posix_time::time_duration duration = *final_time - *initial_time;

  std::cout << std::setprecision(2) << std::fixed
            << "\n   Multithreading: the final value is: " << *result 
            << " -> time invested: " << duration.total_microseconds() << "us\n"
            << std::endl;
}


int main(int argc, char *argv[]){
  // The value we want to add
  double a_value { 1.0 };
  // Total iterations
  const std::size_t iterations { 1000000 };
  // Mutex to lock the our used variable
  boost::mutex variable_protector;

  // Waiting time for each loop ~30Hz
  boost::posix_time::milliseconds waiting_time(33);

  // Variables to calculate the invested time
  boost::posix_time::ptime initial_time = boost::posix_time::microsec_clock::local_time();
  boost::posix_time::ptime final_time;
  
  // Creating the thread manager
  torero::cpu::threads thread_manager;

  // Adding a new thread process
  thread_manager.multithread_add_process(
    boost::bind(test_run, &a_value, iterations, &final_time, &variable_protector),
    boost::bind(test_ready, &a_value, &initial_time, &final_time),
    &variable_protector
  );

  // Loops while there are pending process
  while(!thread_manager.multithread_all_finished()){
    boost::this_thread::sleep(waiting_time);
    // Checking if the thread has finished, if yes then, calls the ready function
    thread_manager.multithread_update_process();
  }

  return 0;
}
