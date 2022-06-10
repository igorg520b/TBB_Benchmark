cmake_minimum_required(VERSION 3.5)

project(tbbtest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tbbtest main.cpp)

if(WIN32)
target_compile_options(tbbtest PRIVATE /openmp)

target_include_directories(tbbtest PRIVATE "C:\\Program Files (x86)\\Intel\\oneAPI\\tbb\\2021.5.2\\include")
target_link_directories(tbbtest PRIVATE "C:\\Program Files (x86)\\Intel\\oneAPI\\tbb\\2021.5.2\\lib\\intel64\\vc_mt")
target_link_libraries(tbbtest PRIVATE tbb)


#[[
target_include_directories(tbbtest PRIVATE "C:\\Program Files (x86)\\Intel\\oneAPI\\mkl\\2022.0.3\\include")
target_link_directories(tbbtest PRIVATE "C:\\Program Files (x86)\\Intel\\oneAPI\\mkl\\2022.0.3\\lib\\intel64")
target_link_directories(tbbtest PRIVATE "C:\\Program Files (x86)\\Intel\\oneAPI\\compiler\\2022.0.3\\windows\\compiler\\lib\\intel64_win")
target_link_libraries(tbbtest PRIVATE mkl_intel_lp64_dll mkl_tbb_thread_dll mkl_core_dll libiomp5md)
#]]
else()

    target_link_directories(tbbtest PUBLIC /home/s2/Projects-libraries/oneTBB/build/linux_intel64_gcc_cc9.3.0_libc2.31_kernel5.4.0_release)
target_include_directories(tbbtest PUBLIC /home/s2/Projects-libraries/oneTBB/include/)
target_include_directories(tbbtest PUBLIC /home/s2/Projects-libraries/oneTBB/include/tbb/)
target_link_libraries(tbbtest PUBLIC tbb gomp)

endif()
