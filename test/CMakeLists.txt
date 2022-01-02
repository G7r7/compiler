cmake_minimum_required(VERSION 3.1.0)
project(tester)

set(SOURCE_FILES exec.cpp node.cpp omp.cpp test.cpp tester.cpp thread.cpp tokens.cpp usage.cpp)

add_executable(tester ${SOURCE_FILES})

set_property(TARGET tester PROPERTY CXX_STANDARD 17)

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(tester PUBLIC OpenMP::OpenMP_CXX)
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
if(Threads_FOUND)
    target_link_libraries(tester PUBLIC Threads::Threads)
endif()