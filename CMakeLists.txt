cmake_minimum_required(VERSION 3.16.3)

project(joby_evtol_sim)

set(CMAKE_CXX_STANDARD 11)

add_executable(hello_world hello_world.cc)

# Declare dependency on the absl::strings library
target_link_libraries(hello_world absl::strings)