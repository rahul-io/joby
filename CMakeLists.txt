cmake_minimum_required(VERSION 3.24.0)

project(joby_evtol_sim VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)

add_library(
  vehicle
  vehicle.h
  vehicle.cpp
)

add_library(
  simulator
  simulator.h
  simulator.cpp
)

add_library(
  processor
  processor.h
  processor.cpp
)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)                                                                                                                                                                                                           
set(THREADS_PREFER_PTHREAD_FLAG TRUE)                                                                                                                                                                                                           
find_package(Threads REQUIRED)   

add_executable(joby_evtol_sim main.cpp)

target_link_libraries(joby_evtol_sim PRIVATE simulator vehicle processor Threads::Threads)