set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(cotire)

project( camman )
cmake_minimum_required(VERSION 2.8)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON)
set( CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -stdlib=libc++  -Wall -ferror-limit=4" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 " )

SET(BOOST_COMPONENTS)
LIST(APPEND BOOST_COMPONENTS system filesystem program_options)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)

FIND_PACKAGE( Boost 1.52 REQUIRED COMPONENTS ${BOOST_COMPONENTS} )
include_directories( ${Boost_INCLUDE_DIR} )
include_directories( ${MODULE_NAME} "${CMAKE_SOURCE_DIR}/src" )
set (CAM_MAN_SOURCES
	${CMAKE_SOURCE_DIR}/src/camman.cpp
	${CMAKE_SOURCE_DIR}/src/camdate.cpp
	${CMAKE_SOURCE_DIR}/src/camfile.cpp
	${CMAKE_SOURCE_DIR}/src/camopts.cpp
	${CMAKE_SOURCE_DIR}/src/main.cpp
)
set (CAM_MAN_HEADERS
	${CMAKE_SOURCE_DIR}/src/camman.hpp
	${CMAKE_SOURCE_DIR}/src/camdate.hpp
	${CMAKE_SOURCE_DIR}/src/camfile.hpp
	${CMAKE_SOURCE_DIR}/src/camopts.hpp
)
set (SOURCES
	${CAM_MAN_SOURCES}
	${CAM_MAN_HEADERS}
)

set (MODULE_NAME "camman")
set (CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(${MODULE_NAME} ${SOURCES})
target_link_libraries(${MODULE_NAME} ${Boost_LIBRARIES})
cotire(${MODULE_NAME})
set (CMAKE_EXE_LINKER_FLAGS "-static")
