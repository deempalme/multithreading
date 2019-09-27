cmake_minimum_required(VERSION 3.1...3.15)

if(NOT TARGET ${TORERO_THREADS_LIB})
  project(torero_threads
    VERSION 1.0.0
    DESCRIPTION "Torero sub-library to manage multithreading"
    LANGUAGES CXX
  )

  find_package(Boost REQUIRED COMPONENTS system thread)

  set(CPP_SOURCES
    src/torero/cpu/threads.cpp
  )

  set(HPP_HEADERS
    include/torero/cpu/threads.h
  )

  add_library(${PROJECT_NAME}
    ${CPP_SOURCES}
    ${HPP_HEADERS}
  )

  target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
  )

  target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES}
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

  set(TORERO_THREADS_DIRS
    ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL ""
  )
  set(TORERO_THREADS_LIB ${PROJECT_NAME} CACHE INTERNAL "")

endif(NOT TARGET ${TORERO_THREADS_LIB})
