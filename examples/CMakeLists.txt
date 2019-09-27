
cmake_minimum_required(VERSION 3.1...3.15)

project(torero_thread_example
  VERSION 1.0.0
  DESCRIPTION "Example using torero multithreading"
  LANGUAGES CXX
)

find_package(Boost REQUIRED COMPONENTS chrono system thread)

# +++++++++++++++++++++++++++++++++++++ TORERO THREAD MANAGER +++++++++++++++++++++++++++++++++++++
# Adding the root directory of torero source tree to your project
add_subdirectory(${PROJECT_SOURCE_DIR}/.. build)

# -------------------------------------- END ADDING LIBRARIES -------------------------------------

# Add every file to the executable
add_executable(${PROJECT_NAME}
  main.cpp
)

# Indicates which libraries to use in the executable
target_link_libraries(${PROJECT_NAME}
  ${TORERO_THREADS_LIB}
  ${Boost_LIBRARIES}
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${TORERO_THREADS_DIRS}
  ${Boost_INCLUDE_DIRS}
)

target_compile_features(${PROJECT_NAME}
  PUBLIC
  cxx_std_11
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED yes
  CXX_EXTENSIONS no
)