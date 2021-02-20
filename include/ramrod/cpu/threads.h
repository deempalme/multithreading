#ifndef RAMROD_CPU_THREADS_H
#define RAMROD_CPU_THREADS_H

#include <functional>
#include <mutex>
#include <vector>

namespace ramrod {
  namespace cpu {
    class threads
    {
    public:
      threads();

      /**
        * @brief Returning the total number of currently used threads
        *
        * Returns the number of threads that are currently being used by this multithreading manager.
        *
        * @returns number of currently used threads in your CPU.
        *
        */
      unsigned int active_threads();
      bool add_thread(std::function<void()> run, std::function<void()> ready);
      /**
        * @brief Adds a new thread
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
        * @param run           Function to execute in concurrent thread.
        *        ready         Callback function after thread is finished.
        *        mutex_pointer Is the pointer to the mutex that locks the variables
        *                      inside the thread, use `nullptr` if you don't want
        *                      any callback.
        *
        */
      bool add_thread(std::function<void (void)> run,
                      std::function<void (void)> ready,
                      std::mutex *mutex_pointer);
      /**
        * @brief Getting variable that indicates if all threads have finished
        *
        * This function will return you a constant reference to a boolean variable that indicates
        * if all created threads have been executed and finished. You can save this reference into
        * a local variable and do easier checkings.
        *
        * @returns returns the reference to the variable that indicates if all threads have
        *          finished. `true` indicates that all threads have been executed and finished.
        *
        */
      const bool &all_threads_finished();
      /**
        * @brief Returning the number of threads being executed concurrently
        *
        * Returns the total number of active concurrent threads.
        *
        * @returns number of active concurrent threads.
        *
        */
      std::size_t number_of_active_threads();
      /**
        * @brief Returning the number of threads awaiting for execution
        *
        * The total concurrent number of threads cannot be bigger than your number of threads,
        * the manager will wait until there are free threads to execute the awaiting threads,
        * this will return the total number of them.
        *
        * @returns number of awaiting concurrent threads.
        *
        */
      std::size_t number_of_awaiting_threads();
      /**
        * @brief Returning the total number of threads in your computer
        *
        * Returns the number of threads in your CPU.
        *
        * @returns number of threads in your CPU.
        *
        */
      unsigned int number_of_threads();
      /**
        * @brief Updating the state of concurrent threads
        *
        * This function will check if each created thread has been finished, and to make the
        * correspodent callbacks when they are done. Call this function constanly after threads
        * have been created until they all are finished, if not then, no callback will be made
        * when a thread ends. It is recommended to call it in a time-lapse not too frequent,
        * adequate may be 30Hz.
        *
        */
      void update_threads();

      void wait_microseconds(const std::int64_t microseconds);
      void wait_seconds(const std::int64_t seconds);
      void wait(const std::int64_t milliseconds);

    protected:
      typedef struct process {
        /* Function executed in a separated thread
         *
         * @Arguments
         * If you require special arguments, then, you should define them when creating the
         * `std::bind` example:
         *
         *   ```c++
         *      cartografo::cpu::threads::process new_process =
         *        { std::bind(&YourClass::your_run_function, this, &variable_1, variable_2),
         *          std::bind(&YourClass::your_ready_function, this, &variable_1),
         *          &your_mutex };
         *   ```
         */
        std::function<void (void)> run;
        /* Callback function that is executed after thread is finished
         *
         * @Arguments
         * Same as above
         */
        std::function<void (void)> ready;
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
         */
        std::mutex *mutex_pointer;
        bool lone;
      } process;

    private:
      void unmutex_helper(std::function<void(void)> run, std::mutex *mutex);

      std::vector<ramrod::cpu::threads::process> active_processes_;
      std::vector<ramrod::cpu::threads::process> awaiting_processes_;

      unsigned int threads_number_;
      unsigned int active_threads_;
      bool finished_;
    };
  } // namespace: cpu
} // namespace: ramrod

#endif // RAMROD_CPU_THREADS_H
