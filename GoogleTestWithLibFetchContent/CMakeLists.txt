cmake_minimum_required(VERSION 3.13)

project(googletest_sample)

include(CMakePrintHelpers)

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

message("============googletest properties============")
cmake_print_variables(${googletest_POPULATED})
cmake_print_variables(${googletest_SOURCE_DIR})
cmake_print_variables(${googletest_BUILD_DIR})

add_library(sumLibrary STATIC LibraryCode.cpp)

add_executable(mainApp main.cpp)
target_link_libraries(mainApp sumLibrary)

add_executable(testRunner test.cpp)
target_link_libraries(testRunner sumLibrary gtest_main gmock_main)

