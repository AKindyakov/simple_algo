CMAKE_MINIMUM_REQUIRED(VERSION 1.8)

# ------------------------------------------------
# ------------------- algolib --------------------

SET( ALGO_DIR ${CMAKE_SOURCE_DIR}/algo )

ADD_SUBDIRECTORY( ${ALGO_DIR}/ )
ADD_SUBDIRECTORY( ${ALGO_DIR}/ )
# ------------------------------------------------


# ------------------------------------------------
# ------------------- tests ----------------------

SET( TEST_ALGO_DIR ${CMAKE_SOURCE_DIR}/tests )

ADD_SUBDIRECTORY( ${TEST_ALGO_DIR}/ )
ADD_SUBDIRECTORY( ${TEST_ALGO_DIR}/ )
# ------------------------------------------------

