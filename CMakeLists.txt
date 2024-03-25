cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

Set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)


project(CppTask)

Set(CppTask_SRC
        group_handler.cpp
)

Set(CppTask_Test_SRC
        group_handler_test.cpp
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
enable_testing()

add_executable(cpp_task_test
	${CppTask_Test_SRC}
	${CppTask_SRC}
)
target_link_libraries(cpp_task_test
        GTest::gtest_main
        gmock_main
)
