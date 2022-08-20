cmake_minimum_required(VERSION 3.24.0)

add_executable(run_sim main.cpp)

target_link_libraries(run_sim simulator)