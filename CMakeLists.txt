cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0 LANGUAGES C CXX)

# Compile options
add_compile_options(-std=c++11)


set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -O0 -g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -O2 -Wall")

include(CTest)
enable_testing()

include_directories(
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/thirdpart/include
)

link_directories(
    ${CMAKE_SOURCE_DIR}/thirdpart/lib
)

add_executable(main main.cpp ${CMAKE_SOURCE_DIR}/src/FFmpegDecoder.cpp ${CMAKE_SOURCE_DIR}/src/FFmpegEncoder.cpp)

target_link_libraries(main PUBLIC avcodec
    avutil
    swscale
    avformat)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
