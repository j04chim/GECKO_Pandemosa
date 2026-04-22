cmake_minimum_required(VERSION 3.23)

project(Kausjan CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)


add_executable( Kausjan )

target_sources( Kausjan
    PRIVATE
        src/main.cpp
)

target_include_directories( Kausjan
    PRIVATE
        include/Crow
)


add_executable( Kausjan_test )

target_sources( Kausjan_test
    PRIVATE
        include/cppTest/cppTest.cpp
        test/main.cpp
)

target_include_directories( Kausjan_test
    PRIVATE
        include/cppTest
)
