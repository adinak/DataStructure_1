cmake_minimum_required(VERSION 3.16)
project(Wet1)

set(CMAKE_CXX_STANDARD 11)

set(LIST ./LinkedList)
set(CHART ./StreamingChart)
set(TREE ./AVLTree)

include_directories(${LIST})
include_directories(${CHART})
include_directories(${TREE})

add_executable(Wet1
                main.cpp
                ${LIST}/list.h
                ${LIST}/listNode.h
                ${LIST}/test_LinkedList.h
                ${CHART}/streamingChart.h
                ${CHART}/streamingChart.cpp
                ${CHART}/streamingChartNode.h
                ${CHART}/streamingChartNode.cpp
                ${CHART}/artistID.h
                ${CHART}/artistID.cpp
                ${CHART}/Song.h
                ${CHART}/Song.cpp
                ${TREE}/AVLTree.h
                Artist.h
                Artist.cpp )