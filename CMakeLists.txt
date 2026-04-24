cmake_minimum_required(VERSION 3.23)

project(Kausjan CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

add_definitions(-DLOG_LEVEL=0)

add_executable( Kausjan )

target_sources( Kausjan
    PRIVATE
        src/main.cpp
        src/App.cpp
        src/datatypes/Session.cpp
        src/datatypes/Note.cpp
        src/datatypes/Event.cpp
        src/datatypes/Config.cpp
        src/drivers/Sqlite.cpp
        include/logger/logger.cpp
)

target_include_directories( Kausjan
    PRIVATE
        include/Crow
        include/logger
)


add_executable( Kausjan_test )

target_sources( Kausjan_test
    PRIVATE
        test/main.cpp
        include/cppTest/cppTest.cpp
        include/logger/logger.cpp
)

target_include_directories( Kausjan_test
    PRIVATE
        include/Crow
        include/cppTest
        include/logger
)
