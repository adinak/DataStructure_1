cmake_minimum_required(VERSION 3.16)
project(Wet1)

set(CMAKE_CXX_STANDARD 11)

set(GCC_COVERAGE_COMPILE_FLAGS "-DNDEBUG -Wall -static-libstdc++ -static-libgcc")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

set(LIST ./LinkedList)
set(CHART ./StreamingChart)
set(TREE ./AVLTree)
set(MANAGER ./MusicManager)

include_directories(${LIST})
include_directories(${CHART})
include_directories(${TREE})
include_directories(${MANAGER})

add_executable(Wet1
                #main.cpp
                test_main.cpp #debug
                #main1.cpp
                ${LIST}/list.h
                ${LIST}/listNode.h
                ${CHART}/streamingChart.h
                ${CHART}/streamingChart.cpp
                ${CHART}/streamingChartNode.h
                ${CHART}/streamingChartNode.cpp
                ${CHART}/Song.h
                ${CHART}/Song.cpp
                ${TREE}/AVLTree.h
                ${MANAGER}/Artist.h
                ${MANAGER}/Artist.cpp
                #${LIST}/test_LinkedList.h #debug
                #${CHART}/Test_StreamingChart.h #debug
                ${MANAGER}/musicManager.h
                ${MANAGER}/musicManager.cpp
                library1.h
                library1.cpp)
