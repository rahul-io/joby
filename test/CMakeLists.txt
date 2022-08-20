cmake_minimum_required(VERSION 3.24.0)

set(SOURCES
VehicleTest.cpp
SimulatorTest.cpp
)

add_executable(eVTOLSimTests ${SOURCES})
target_link_libraries(eVTOLSimTests PUBLIC 
  GTest::gtest_main
  simulator
)

include(GoogleTest)
gtest_discover_tests(eVTOLSimTests)