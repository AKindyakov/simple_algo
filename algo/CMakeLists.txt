CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT( libalgo CXX )

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/algo )

SET ( LIB_ALGO_SRC_DIR ${CMAKE_SOURCE_DIR}/algo )

SET ( libalgo_SRCS
        ${LIB_ALGO_SRC_DIR}/ListContainer/LinkedList.cpp
    )

SET ( libalgo_HDRS
        ${LIB_ALGO_SRC_DIR}/LibAlgoCommon.h
        ${LIB_ALGO_SRC_DIR}/ListContainer/LinkedList.h
    )

ADD_LIBRARY( libalgo STATIC ${libalgo_SRCS}  ${libalgo_HDRS} )

