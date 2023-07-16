cmake_minimum_required(VERSION 3.7.2)

project(echo-servers)

add_executable(echo-server-coroutine echo-server-coroutine.cpp)
target_link_libraries(echo-server-coroutine pthread)
target_compile_features(echo-server-coroutine PUBLIC cxx_std_20)
target_compile_options(echo-server-coroutine PUBLIC -fcoroutines)