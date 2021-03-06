project(spacy)

cmake_minimum_required(VERSION 3.1)

# The version number
set (SPACY_MAJOR_VERSION 0)
set (SPACY_MINOR_VERSION 2)
set (SPACY_PATCH_VERSION 0)
set (SPACY_VERSION ${SPACY_MAJOR_VERSION}.${SPACY_MINOR_VERSION}.${SPACY_PATCH_VERSION})

# Set path to cmake scripts
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_SOURCE_DIR}/cmake
    )

# Do not allow in-source builds
include(ConfigSafeGuards)

option(BuildTest "BuildTest" OFF)
option(Coverage "Coverage" OFF)
option(Kaskade "Kaskade" OFF)
option(Dolfin "Dolfin" OFF)
option(Logging "Logging" ON)
if(Logging)
    add_definitions(-DSPACY_ENABLE_LOGGING)
endif()

set(DOC_DIR "doc" CACHE STRING "Output directory for the doxygen documentation")

if(Coverage)
  set(CMAKE_BUILD_TYPE Debug)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage")
endif()
  
# Set compiler flags
set(CMAKE_CXX_STANDARD 14)
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Woverloaded-virtual -Wwrite-strings -Wpedantic") #-Weffc++ ")
endif()
 
# set up include-directories
include_directories("${PROJECT_SOURCE_DIR}")
include_directories(${PROJECT_SOURCE_DIR}/External/FGlue)

add_subdirectory(Spacy)
if(BuildTest)
  add_subdirectory(Test)
endif()

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)
