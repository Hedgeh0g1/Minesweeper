cmake_minimum_required(VERSION 3.6.2)
project(cvicenie12)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)

set(SOURCE_FILES
        Board.cpp
        testyGame.cpp

        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc
        Cell.h
        NumberException.h
)

include_directories(GoogleTest)
add_executable(cvicenie12 ${SOURCE_FILES})
target_link_libraries(cvicenie12 ${CMAKE_THREAD_LIBS_INIT})
add_custom_command(TARGET cvicenie12 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/gameBoard.txt
        ${CMAKE_SOURCE_DIR}/gameBoard2.txt
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        $<TARGET_FILE_DIR:cvicenie12>
        VERBATIM)
set(filename "gameBoard2.txt.txt")
