CMAKE_MINIMUM_REQUIRED(VERSION 1.0)

PROJECT( listContainerTest )

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

SET( LIST_TEST_SRC_DIR ${CMAKE_SOURCE_DIR}/tests/LinkedListTest/src )

INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/algo )
LINK_DIRECTORIES( ${CMAKE_SOURCE_DIR}/algo )

SET ( listContainerTest_SRCS
        ${LIST_TEST_SRC_DIR}/ListContainerTest.cpp
        ${LIST_TEST_SRC_DIR}/main.cpp
    )

SET ( listContainerTest_HRDS
        ${LIST_TEST_SRC_DIR}/ListContainerTest.h
    )

ADD_EXECUTABLE( listContainerTest ${listContainerTest_SRCS} ${listContainerTest_HRDS})

TARGET_LINK_LIBRARIES ( listContainerTest libalgo )

