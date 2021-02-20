cmake_minimum_required(VERSION 3.1...3.15)

if(NOT TARGET ${RAMROD_THREADS_LIB})
  project(RamRodThreads
    VERSION 1.0.0
    DESCRIPTION "Ramrod library to manage multithreading"
    LANGUAGES CXX
  )

  set(CPP_SOURCES
    src/ramrod/cpu/thread.cpp
    src/ramrod/cpu/threads.cpp
  )

  set(HPP_HEADERS
    include/ramrod/cpu/thread.h
    include/ramrod/cpu/threads.h
  )

  add_library(${PROJECT_NAME}
    ${CPP_SOURCES}
    ${HPP_HEADERS}
  )

  target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
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

  set(${PROJECT_NAME}_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL ""
  )

  set(${PROJECT_NAME}_LIBRARIES
    ${PROJECT_NAME}
    CACHE INTERNAL ""
  )

endif(NOT TARGET ${RAMROD_THREADS_LIB})
