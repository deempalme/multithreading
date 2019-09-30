# Torero multithreading manager

Simple C++ multithreading library to run functions in different CPU threads, check and perform callbacks when they are finished.

Several problems arise when you use multithreading; one of the most important is that you cannot call a function in the **main** thread from another function being executed in a different thread, if you do so, the secondary thread will create a copy of the function and execute it in that same secondary thread (even if you wanted to run it in the main thread). An alternative solution is to use `join()` and call the other function after is joined but, this has a big disadvantage; it will wait (froze the main thread execution) until the concurrent function is finished.

**This library will allow you** to run your functions concurrently and make callbacks in the main thread after they are finished. Therefore, you will not have to wait until they finish.

___

#### Table of Contents
   [1 Required components](#section1)  
   &nbsp; &nbsp; [1.1 Installing Boost](#section1.1)  
   [2 Adding the library to your project](#section2)  
   [3 How of use](#section3)  
   &nbsp; &nbsp; [3.1 Defining necessary variables](#section3.1)  
   &nbsp; &nbsp; [3.2 Defining a run function](#section3.2)  
   &nbsp; &nbsp; [3.3 Defining a callback function](#section3.3)  
   &nbsp; &nbsp; [3.4 Creating the multithreading object](#section3.4)  
   &nbsp; &nbsp; [3.5 Adding an execution in a new thread](#section3.5)  
___
<a section="section1"/>

## 1 Required components
<a section="section1.1"/>

### 1.1 Installing Boost
Boost libraries must be installed. To do it in Ubuntu use the following commands in a terminal (your account need to have sudo permissions):

```sh
sudo apt-get install libboost-all-dev
sudo apt-get install aptitude
aptitude search boost
```
The installation in windows is a little more complicated, here is the [official installation guide](https://www.boost.org/doc/libs/1_71_0/more/getting_started/windows.html).
<a section="section2"/>

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
<a section="section3"/>

## 3 How of use
<a section="section3.1"/>

### 3.1 Defining necessary variables

It is not really necessary to have a **mutex** that would _lock_ all the variables inside the function that will be running in a different thread but, it is highly recommended to do so, and avoid reading a variable while is written in a different thread (or viceversa). Additionally, the mutex will allow this library to perform a callback when the execution of the concurrent function is finished. This step is really easy, just create a new `boost::mutex` object in your class or as a lone variable:

```cpp
boost::mutex our_mutex;
```
<a section="section3.2"/>

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
<a section="section3.3"/>

### 3.3 Defining a callback function

This is the function that will be executed after the "run function" is finished, its returning type should be **`void`**. It could be a class member or a lone function, and it could have as many parameter as you wish. **Note:** this is executed in the main thread.

```c++
void test_ready(const double parameter, const int &referenced_par, float *pointed_par){

  ... // Callback code

}
```
<a section="section3.4"/>

### 3.4 Creating the multithreading object

The creation of objects from this class is very easy, it does not require any additional parameter:

```cpp
torero::cpu::threads thread_manager;
```
<a section="section3.5"/>

### 3.5 Adding an execution in a new thread

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
```
For more info about `boost::bind` please visit [here](https://theboostcpplibraries.com/boost.bind).
