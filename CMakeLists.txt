cmake_minimum_required(VERSION 3.5)

project(tbbtest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tbbtest main.cpp)

target_link_directories(tbbtest PUBLIC /home/s2/Projects-libraries/oneTBB/build/linux_intel64_gcc_cc9.3.0_libc2.31_kernel5.4.0_release)
target_include_directories(tbbtest PUBLIC /home/s2/Projects-libraries/oneTBB/include/)
target_include_directories(tbbtest PUBLIC /home/s2/Projects-libraries/oneTBB/include/tbb/)
target_link_libraries(tbbtest PUBLIC tbb gomp)
