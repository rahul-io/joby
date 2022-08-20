set(HEADERS
    chargingStation.h
    enums.h
    processor.h
    simulator.h
    vehicle.h
    vehicleParams.h
)

set(SOURCES
    processor.cpp
    simulator.cpp
    vehicle.cpp
)

add_library(simulator ${SOURCES} ${HEADERS})

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)                                                                                                                                                                                                           
set(THREADS_PREFER_PTHREAD_FLAG TRUE)                                                                                                                                                                                                      
find_package(Threads REQUIRED)

target_link_libraries(simulator PRIVATE Threads::Threads)

target_compile_features(simulator PUBLIC cxx_std_20)

set_target_properties(simulator PROPERTIES LINKER_LANGUAGE CXX)