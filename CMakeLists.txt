
cmake_minimum_required(VERSION 3.20)
project(Monte_Carlo)

set(BINARY ${CMAKE_PROJECT_NAME})
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


find_package(Threads REQUIRED)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${INCLUDE_DIR})
add_library(${BINARY}_lib STATIC ${SOURCE_DIR}/monte_carlo.c)

add_executable(main main.c)

target_link_libraries(main 
    ${BINARY}_lib 
    Threads::Threads
)