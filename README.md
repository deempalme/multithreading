# Torero multithreading manager

Simple C++ multithreading library to run functions in different CPU threads, check and perform callbacks when they are finished.

Several problems arise when you use multithreading; one of the most important is that you cannot call a function in the **main** thread from another function being executed in a different thread, if you do so, the secondary thread will create a copy of the function and execute it in that same secondary thread (even if you wanted to run it in the main thread). An alternative solution is to use `join()` and call the other function after is joined but, this has a big disadvantage; it will wait (froze the main thread execution) until the concurrent function is finished.

**This library will allow you** to run your functions concurrently and make callbacks in the main thread after they are finished. Therefore, you will not have to wait until they finish.

___

#### Table of Contents
   [1 Required components](#1-required-components)  
   &nbsp; &nbsp; [1.1 Installing Boost](#11-installing-boost)  
   [2 Adding the library to your project](#2-adding-the-library-to-your-project)  
   [3 How of use](#3-how-to-use)  
   &nbsp; &nbsp; [3.1 Defining necessary variables](#31-defining-necessary-variables)  
   &nbsp; &nbsp; [3.2 Defining a run function](#32-defining-a-run-function)  
   &nbsp; &nbsp; [3.3 Defining a callback function](#33-defining-a-callback-function)  
   &nbsp; &nbsp; [3.4 Creating the multithreading object](#34-creating-the-multithreading-object)  
   &nbsp; &nbsp; [3.5 Adding an execution in a new thread](#35-adding-an-execution-in-a-new-thread)  
   &nbsp; &nbsp; [3.6 Checking if all concurrent functions have finished](#36-checking-if-all-concurrent-functions-have-finished)  
   &nbsp; &nbsp; [3.7 Updating ready callbacks](#37-updating-ready-callbacks)  
   [4 Example](#4-example)  
   &nbsp; &nbsp; [4.1 Building the example](#41-building-the-example)  
   [5 Reference guide](#5-reference-guide)  
   &nbsp; &nbsp; [5.1 List of public member functions](#51-list-of-public-member-functions)  
   &nbsp; &nbsp; [5.2 Public member functions](#52-public-member-functions)  
   &nbsp; &nbsp; &nbsp; &nbsp; [5.2.1 Returning the total number of currently used threads](#521-returning-the-total-number-of-currently-used-threads)  
   &nbsp; &nbsp; &nbsp; &nbsp; [5.2.2 Adding a new thread](#522-adding-a-new-thread)  
   &nbsp; &nbsp; &nbsp; &nbsp; [5.2.3 Getting variable that indicates if all threads have finished](#523-getting-variable-that-indicates-if-all-threads-have-finished)  
   &nbsp; &nbsp; &nbsp; &nbsp; [5.2.4 Returning the number of processes being executed concurrently](#524-returning-the-number-of-processes-being-executed-concurrently)  
   &nbsp; &nbsp; &nbsp; &nbsp; [5.2.5 Returning the number of processes awaiting for execution](#525-returning-the-number-of-processes-awaiting-for-execution)  
   &nbsp; &nbsp; &nbsp; &nbsp; [5.2.6 Returning the total number of threads in your computer](#526-returning-the-total-number-of-threads-in-your-computer)  
   &nbsp; &nbsp; &nbsp; &nbsp; [5.2.7 Updating the state of concurrent threads](#527-updating-the-state-of-concurrent-threads)
___

## 1 Required components

### 1.1 Installing Boost
Boost libraries must be installed. To do it in Ubuntu use the following commands in a terminal (your account need to have sudo permissions):

```sh
sudo apt-get install libboost-all-dev
sudo apt-get install aptitude
aptitude search boost
```
The installation in windows is a little more complicated, here is the [official installation guide](https://www.boost.org/doc/libs/1_71_0/more/getting_started/windows.html).

## 2 Adding the library to your project
You must copy this repository folder (or make a link [ubuntu] or shortcut [windows]) into your project's folder and add/modify the next lines in your CMakeLists.txt:

```cmake
# Tripe points (...) represent possible content that may 
# already exist in your CMakeLists.txt
...
# Replace <multithreading_folder_path> with the actual folder path
add_subdirectory(<multithreading_folder_path>)
...
# Replace <project_name> with the actual project name
target_include_directories(<project_name>
  PRIVATE #or PUBLIC (depending in your preferences)
  ...
  ${TORERO_THREADS_DIRS}
  ...
)
...
target_link_libraries(<project_name>
  ...
  ${TORERO_THREADS_LIB}
  ...
)
...
```

## 3 How of use

### 3.1 Defining necessary variables

It is not really necessary to have a **mutex** that would _lock_ all the variables inside the function that will be running in a different thread but, it is highly recommended to do so, and avoid reading a variable while is written in a different thread (or viceversa). Additionally, the mutex will allow this library to perform a callback when the execution of the concurrent function is finished. This step is really easy, just create a new `boost::mutex` object in your class or as a lone variable:

```cpp
boost::mutex our_mutex;
```

### 3.2 Defining a run function

This is the function that will run in a separated thread, the returning type should be **`void`**, it could be a class member or a lone function, and it could have as many parameter as you wish. Remember that you **must use** the recently created `boost::mutex` object inside this function if you want to use the callback after this function finishes.

```c++
void test_run(const double parameter, const int &referenced_par, float *pointed_par){
  // Our boost::mutex object:
  our_mutex.lock();   // Locking all the variables inside this function

  ... // All the code that should be executed in a different thread

  our_mutex.unlock(); // Unlocking the variables
}
```

### 3.3 Defining a callback function

This is the function that will be executed after the "run function" is finished, its returning type should be **`void`**. It could be a class member or a lone function, and it could have as many parameter as you wish. **Note:** this is executed in the main thread.

```c++
void test_ready(const double parameter, const int &referenced_par, float *pointed_par){

  ... // Callback code

}
```

### 3.4 Creating the multithreading object

The creation of objects from this class is very easy, it does not require any additional parameter:

```cpp
torero::cpu::threads thread_manager;
```

### 3.5 Adding an execution in a new thread

This function will add a new thread to execute concurrently or wait until at least one is free if all CPU threads are busy. It calls ready after run's execution is finished.

```cpp
  // When using lone functions:
  thread_manager.multithread_add_process(
    boost::bind(test_run, parameter_variable_1, referenced_variable, &pointed_variable),
    boost::bind(test_ready, parameter_variable_1, referenced_variable_2, &pointed_variable_2),
    &our_mutex
  );

  // When using class member functions:
  your_class my_class;

  thread_manager.multithread_add_process(
    boost::bind(&your_class::test_run, &my_class, variable_1, referenced_var_1, &pointed_var_1),
    boost::bind(&your_class::test_ready, &my_class, variable_1, referenced_var_2, &pointed_var_2),
    &your_class.our_mutex
  );

  // If you don't want to use a boost::mutex nor the callback function use the following:
  thread_manager.multithread_add_process(
    boost::bind(test_run, parameter_variable_1, referenced_variable, &pointed_variable),
    0,
    nullptr
  );
```
For more info about `boost::bind` please visit [here](https://theboostcpplibraries.com/boost.bind).

### 3.6 Checking if all concurrent functions have finished

To check if all concurrent executions that you created using `multithread_add_process` have finished, just use the following line:

```cpp
// This will return `true` when all concurrent functions have finished
thread_manager.multithread_all_finished();
```

### 3.7 Updating ready callbacks

The following code line will check if functions running in another thread have finished, and execute their callbacks every time one or more conclude.

```cpp
// Checking if threads have finished, if yes then, calls their ready function
thread_manager.multithread_update_process();
```

It is necessary to use that line to execute the callbacks. You could place it in your main loop so it will check it in every iteration. Example:

```cpp
int main(int argc, char *argv[]){
  ...
  // This could be your main loop
  while(your_conditional){
    ...
    // Checking if the threads have finished, if yes then, calls their ready functions
    thread_manager.multithread_update_process();
    ...
  }
  ...
  return 0;
}
```

## 4 Example

There is a full running example in the folder [examples](examples/).

### 4.1 Building the example

Open a terminal and go into the [examples](examples/) folder in this repository then, execute the following commands:

```sh
mkdir build
cd build
cmake ../
# -j8 is an argument to increase compilation speed, it selects how
# many processor's cores should be used; -j8 will utilize 8 cores, 
# MAKE SURE you DO NOT select more cores than what you actually have.
make -j8
```
To run the program execute this command:
```sh
./torero_thread_example
```

## 5 Reference guide

Main header:

| Type | Code |
| --- | --- |
| Header | `#include "torero/cpu/threads.h"` |

### 5.1 List of public member functions

<table>
  <tbody>
    <tr>
      <th>Returns</th>
      <th>Member</th>
    </tr>
    <tr>
      <td><code>unsigned int</code></td>
      <td><a href="#521-returning-the-total-number-of-currently-used-threads">multithread_active_threads</a>()</td>
    </tr>
    <tr>
      <td><code>void</code></td>
      <td><a href="#522-adding-a-new-thread">multithread_add_process</a>(<code>boost::function<void (void)> run, boost::function<void (void)> ready, boost::mutex *mutex_pointer</code>)</td>
    </tr>
    <tr>
      <td><code>const bool&</code></td>
      <td><a href="#523-getting-variable-that-indicates-if-all-threads-have-finished">multithread_all_finished</a>()</td>
    </tr>
    <tr>
      <td><code>std::size_t</code></td>
      <td><a href="#524-returning-the-number-of-processes-being-executed-concurrently">multithread_number_of_active_processes</a>()</td>
    </tr>
    <tr>
      <td><code>std::size_t</code></td>
      <td><a href="#525-returning-the-number-of-processes-awaiting-for-execution">multithread_number_of_awaiting_processes</a>()</td>
    </tr>
    <tr>
      <td><code>unsigned int</code></td>
      <td><a href="#526-returning-the-total-number-of-threads-in-your-computer">multithread_number_of_threads</a>()</td>
    </tr>
    <tr>
      <td><code>void</code></td>
      <td><a href="#527-updating-the-state-of-concurrent-threads">multithread_update_process</a>()</td>
    </tr>
  </tbody>
</table>

### 5.2 Public member functions

#### 5.2.1 Returning the total number of currently used threads

Returns the number of threads that are currently being used by this multithreading manager.

```cpp
unsigned int multithread_active_threads();
```

 &nbsp; **Returns**

| Type | Description |
| --- | --- |
| [`unsigned int`] | Number of currently used threads in your CPU. |

___
#### 5.2.2 Adding a new thread

This function will add a new thread to execute concurrently or wait until at least one is free if all CPU threads are busy. It calls *`ready`* after *`run`*'s execution is finished. Do not forget to include the pointer to the mutex that you use inside `run`'s thread to check if the thread is finished (if not included then *`ready`* will never be called).

```cpp
void multithread_add_process(boost::function<void (void)> run,
                             boost::function<void (void)> ready,
                             boost::mutex *mutex_pointer);
```

 &nbsp; **Arguments**

| Type | Name | Description |
| --- | --- | --- |
| [`boost::function<void (void)>&`] | **run** | Function to execute in concurrent thread. |
| [`boost::function<void (void)>&`] | **ready** | Callback function after thread is finished. |
| [`boost::mutex*`] | **mutex_pointer** | Is the pointer to the mutex that locks the variables inside the thread, use `nullptr` if you don't want any callback |

___
#### 5.2.3 Getting variable that indicates if all threads have finished

This function will return you a constant reference to a boolean variable that indicates if all created threads have been executed and finished. You can save this reference into a local variable and do easier checkings.

```cpp
const bool &multithread_all_finished();
```

 &nbsp; **Returns**

| Type | Description |
| --- | --- |
| [`const bool&`] | Returns the reference of boolean variable. `true` indicates that all threads have been executed and finished. |

___
#### 5.2.4 Returning the number of processes being executed concurrently

Returns the total number of active concurrent processes.

```cpp
std::size_t multithread_number_of_active_processes();
```

 &nbsp; **Returns**

| Type | Description |
| --- | --- |
| [`std::size_t`] | Number of active concurrent processes. |

___
#### 5.2.5 Returning the number of processes awaiting for execution

The total concurrent number of processes cannot be bigger than your number of threads, the manager will wait until there are free threads to execute the awaiting processes, this will return the total number of them.

```cpp
std::size_t multithread_number_of_awaiting_processes();
```

 &nbsp; **Returns**

| Type | Description |
| --- | --- |
| [`std::size_t`] | Number of awaiting concurrent processes. |

___
#### 5.2.6 Returning the total number of threads in your computer

Returns the number of threads in your CPU.

```cpp
unsigned int multithread_number_of_threads();
```

 &nbsp; **Returns**

| Type | Description |
| --- | --- |
| [`unsigned int`] | Number of threads in your CPU. |

___
#### 5.2.7 Updating the state of concurrent threads

This function will check if each created thread has been finished, and to make the correspodent callbacks when they are done. Call this function constanly after threads have been created until they all are finished, if not then, no callback will be made when a thread ends. It is recommended to call it in a time-lapse not too frequent, adequate may be around 30Hz.

```cpp
void multithread_update_process();
```


