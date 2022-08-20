cmake_minimum_required(VERSION 3.24.0)

project(
  JobyEVtolSim
  VERSION 1.0.0
  DESCRIPTION "eVTOL Simulator"
  LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
  
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  enable_testing()

  add_subdirectory(src)
  add_subdirectory(main_app)
  add_subdirectory(test)

  include(FetchContent)
  FetchContent_Declare(
    googletest
    # Specify the commit you depend on and update it regularly.
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
  )

  FetchContent_GetProperties(googletest)
  if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
  endif()
endif()
