#ifndef TORERO_CPU_THREADS_H
#define TORERO_CPU_THREADS_H

#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <vector>

namespace torero {
  namespace cpu {
    class threads
    {
    public:
      threads();

      /*
       * ### Returning the total number of currently used threads
       * 
       * Returns the number of threads that are currently being used by this multithreading manager.
       * 
       * @Returns
       * {unsigned int} number of currently used threads in your CPU.
       * 
       */
      unsigned int multithread_active_threads();
      /*
       * ### Adds a new thread
       *
       * This function will add a new thread to execute concurrently or wait until at least one
       * is free if all CPU threads are busy. It calls *`ready`* after *`run`*'s execution is finished.
       * Do not forget to include the pointer to the mutex that you use inside `run`'s thread to
       * check if the thread is finished (if not included then *`ready`* will never be called).
       *
       * If the variable that is used in the thread cannot be saved locally inside a class, then,
       * it is preferable to create it dynamically and save its pointer in *`data_pointer`*, this
       * pointer will be delivered to you when *`ready`* is called after thread execution finishes.
       * DO NOT forget to delete the dynamically created variable.
       *
       * @Arguments
       * {boost::function<void (void)>&} run   = function to execute in concurrent thread.
       * {boost::function<void (void)>&} ready = Callback function after thread is finished.
       *         {boost::mutex*} mutex_pointer = Is the pointer to the mutex that locks the variables
       *                                         inside the thread, use `nullptr` if you don't want
       *                                         any callback.
       *
       */
      void multithread_add_process(boost::function<void (void)> run,
                                   boost::function<void (void)> ready,
                                   boost::mutex *mutex_pointer);
      /*
       * ### Getting variable that indicates if all threads have finished
       *
       * This function will return you a constant reference to a boolean variable that indicates
       * if all created threads have been executed and finished. You can save this reference into
       * a local variable and do easier checkings.
       *
       * @Returns
       * {const bool&} returns the reference of boolean variable. `true` indicates that all threads
       *               have been executed and finished.
       *
       */
      const bool &multithread_all_finished();
      /*
       * ### Returning the number of processes being executed concurrently
       * 
       * Returns the total number of active concurrent processes.
       * 
       * @Returns
       * {std::size_t} number of active concurrent processes.
       * 
       */
      std::size_t multithread_number_of_active_processes();
      /*
       * ### Returning the number of processes awaiting for execution
       * 
       * The total concurrent number of processes cannot be bigger than your number of threads,
       * the manager will wait until there are free threads to execute the awaiting processes, 
       * this will return the total number of them.
       * 
       * @Returns
       * {std::size_t} number of awaiting concurrent processes.
       * 
       */
      std::size_t multithread_number_of_awaiting_processes();
      /*
       * ### Returning the total number of threads in your computer
       * 
       * Returns the number of threads in your CPU.
       * 
       * @Returns
       * {unsigned int} number of threads in your CPU.
       * 
       */
      unsigned int multithread_number_of_threads();
      /*
       * ### Updating the state of concurrent threads
       *
       * This function will check if each created thread has been finished, and to make the
       * correspodent callbacks when they are done. Call this function constanly after threads
       * have been created until they all are finished, if not then, no callback will be made
       * when a thread ends. It is recommended to call it in a time-lapse not too frequent,
       * adequate may be 30Hz.
       *
       */
      void multithread_update_process();

    protected:
      typedef struct process {
        /* Function executed in a separated thread
         *
         * @Arguments
         * If you require special arguments, then, you should define them when creating the
         * `boost::bind` example:
         *
         *   ```c++
         *      cartografo::cpu::threads::process new_process =
         *        { boost::bind(&YourClass::your_run_function, this, &variable_1, variable_2),
         *          boost::bind(&YourClass::your_ready_function, this, &variable_1),
         *          &your_mutex };
         *   ```
         *
         */
        boost::function<void (void)> run;
        /* Callback function that is executed after thread is finished
         *
         * @Arguments
         * Same as above
         */
        boost::function<void (void)> ready;
        /* Pointer to a mutex that locks the used variables inside the thread (important for
         * checking if the thread has finished), example:
         *
         * ```c++
         *    // Function executing in concurrent thread
         *    void YourClass::your_run_function(SomeType *variable_1, SomeOtherType variable_2){
         *      your_mutex.lock();
         *
         *      ...
         *
         *      your_mutex.unlock();
         *    }
         * ```
         *
         */
        boost::mutex *mutex_pointer;
      } process;

    private:
      std::vector<torero::cpu::threads::process> active_processes_;
      std::vector<torero::cpu::threads::process> awaiting_processes_;

      unsigned int cores_number_;
      unsigned int active_cores_;
      bool finished_;
    };
  }
}

#endif // TORERO_CPU_THREADS_H
