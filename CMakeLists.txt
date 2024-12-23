cmake_minimum_required(VERSION 3.29)
project(LR7)

set(CMAKE_CXX_STANDARD 20)

add_executable(Task_1 Task_1/main.cpp Task_1/Task_1.cpp Task_1/h.h)
add_executable(Task_2 Task_2/main.cpp Task_2/Task_2.cpp Task_2/h.h)
add_executable(Task_3 Task_3/main.cpp Task_3/Task_3.cpp Task_3/h.h)
add_executable(Task_4 Task_4/main.cpp Task_4/Task_4.cpp Task_4/h.h)
add_executable(Task_5 Task_5/main.cpp Task_5/Task_5.cpp Task_5/h.h)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")