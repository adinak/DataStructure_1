cmake_minimum_required(VERSION 3.16)
project(LinkedList)

set(CMAKE_CXX_STANDARD 11)

add_executable(LinkedList main.cpp list.h listNode.h test_LinkedList.h)