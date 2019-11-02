cmake_minimum_required(VERSION 3.13)
project(b64 CXX)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_C_COMPILER "/usr/bin/clang")

find_package(Threads)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET_PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)

include(build/conanbuildinfo.cmake)
conan_basic_setup()

if(CONAN_CATCH2_ROOT_DEBUG)
  include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
  include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()

set(COMPILATION_COMMANDS -Weffc++ -Wunused -Wall -Wextra -Wfloat-conversion -Wpedantic -march=native)

add_executable(b64_tests tests/test_main.cpp)
target_include_directories(b64_tests PRIVATE inc)
target_compile_options(b64_tests PRIVATE ${COMPILATION_COMMANDS})
set_target_properties(b64_tests PROPERTIES ${TARGET_PROPERTIES})
target_link_libraries(b64_tests ${CONAN_LIBS})

enable_testing()

catch_discover_tests(b64_tests TEST_PREFIX "constexpr." EXTRA_ARGS -s --reporter=xml --out=constexpr.xml)


# Microbenchmark

add_library(libbenchmark STATIC IMPORTED)
set_property(TARGET libbenchmark PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/third-party-libs/benchmark/build/src/libbenchmark.a)

add_executable(b64_performance tests/test_benchmark.cpp)
target_include_directories(b64_performance PRIVATE inc third-party-libs/benchmark/include)
target_compile_options(b64_performance PRIVATE ${COMPILATION_COMMANDS} -O3)
set_target_properties(b64_performance PROPERTIES ${TARGET_PROPERTIES})
target_link_libraries(b64_performance Threads::Threads ${CONAN_LIBS} libbenchmark)
