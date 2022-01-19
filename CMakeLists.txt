CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
SET(project_name metable)
set(CMAKE_CXX_STANDARD 17)

PROJECT(${project_name})

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

ADD_DEFINITIONS(-D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)

SET(ENABLE_ASIO_STANDALONE ON)
if(ENABLE_ASIO_STANDALONE)
	ADD_DEFINITIONS(-DASIO_STANDALONE)
else()
	FIND_PACKAGE(Boost 1.60 REQUIRED COMPONENTS system)
endif()
INCLUDE(CompilerOptions)
INCLUDE(ExternalProject)
INCLUDE(GtestExternalProject)
INCLUDE(AsioExternalProject)
INCLUDE(GflagsExternalProject)
INCLUDE(CustomeFunctions)
INCLUDE(SpdlogExternalProject)
INCLUDE_DIRECTORIES(SYSTEM thirdparty/logging)
INCLUDE_DIRECTORIES(src/)
INCLUDE_DIRECTORIES(includes)
INCLUDE_DIRECTORIES(
		SYSTEM ${GTEST_INCLUDE_DIR}
		SYSTEM ${ASIO_INCLUDE_DIR}
		SYSTEM ${MSGPACK_INCLUDE_DIR}
		SYSTEM ${GFLAGS_INCLUDE_DIR}
		SYSTEM ${SPDLOG_INCLUDE_DIR}
)

# common library
ADD_LIBRARY(common_lib
#		src/common/config.cc
#		src/common/timer.cc
#		src/common/file.cc
		src/common/logging.cc)
ADD_DEPENDENCIES(common_lib asio_ep spdlog_ep)

# Test targets
if(UNIX)
	set(link_libs pthread)
else()
	set(link_libs )
endif()

if(WIN32)
	ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN)
endif()

#METABLE_DEFINE_TEST(metable_server SRC_FILES src/server/server_main.cc LINKS gflags)
METABLE_DEFINE_TEST(metable_server SRC_FILES src/server/server_main.cc LINKS common_lib)

# Test targets
if(UNIX)
	set(link_libs pthread)
else()
	set(link_libs )
endif()

if(WIN32)
	ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN)
endif()

METABLE_DEFINE_TEST(test_logging SRC_FILES tests/logging_test.cc LINKS common_lib)
