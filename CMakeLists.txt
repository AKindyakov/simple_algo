CMAKE_MINIMUM_REQUIRED(VERSION 1.0)

# ------------------------------------------------
# ------------------- algolib --------------------

SET( ALGO_LIB_DIR ${CMAKE_SOURCE_DIR}/algo )

ADD_SUBDIRECTORY( ${ALGO_LIB_DIR} )
INCLUDE_DIRECTORIES ( ${ALGO_LIB_DIR} )
# ------------------------------------------------


# ------------------------------------------------
# ------------------- tests ----------------------

SET( TEST_ALGO_DIR ${CMAKE_SOURCE_DIR}/tests )

ADD_SUBDIRECTORY( ${TEST_ALGO_DIR}/LinkedListTest )
#ADD_SUBDIRECTORY( ${TEST_ALGO_DIR}/ )
# ------------------------------------------------

