cmake_minimum_required(VERSION 3.15)
project(AVLTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(AVLTree TreeNode.h main.cpp AVLTree.h TestAVLTree.h)