cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

#get googletest
include(FetchContent)
FetchContent_Declare(googletest
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG release-1.11.0)

# Make googletest available in my project
FetchContent_MakeAvailable(googletest)
# Get properties of the fetched content
FetchContent_GetProperties(googletest)
#googletest_POPULATED
#googletest_SOURCE_DIR
#googletest_BUILD_DIR
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest) #in normal FetchContent_Populate will auto call after FetchContent_MakeAvailable
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

find_package(GTest REQUIRED)
message("GTest_INCLUDE_DIRS = ${GTest_INCLUDE_DIRS}")

add_library(commonLibrary LibraryCode.cpp)

add_executable(mainApp main.cpp)
target_link_libraries(mainApp commonLibrary)

add_executable(unitTestRunner testRunner.cpp)
target_link_libraries(unitTestRunner commonLibrary ${GTEST_LIBRARIES} pthread)

