CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT( libalgo CXX )

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

SET ( LIB_ALGO_SRC_DIR ${CMAKE_SOURCE_DIR}/src )

INCLUDE_DIRECTORIES(${LIB_ALGO_SRC_DIR}/ListContainer)

SET ( libalgo_SRCS
        ${LIB_ALGO_SRC_DIR}/ListContainer/dublyLinkedList.cpp
    )

SET ( libalgo_HDRS
        ${LIB_ALGO_SRC_DIR}/ListContainer/LinkedList.h
        ${LIB_ALGO_SRC_DIR}/ListContainer/dublyLinkedList.h
    )


ADD_LIBRARY( libalgo STATIC ${libalgo_SRCS}  ${libalgo_HDRS} )

