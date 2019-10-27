cmake_minimum_required(VERSION 3.13)
project(b64 CXX)

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

set(COMPILATION_COMMANDS -Wdouble-promotion -Weffc++ -Wunused -Wall -Weffc++ -pedantic -pedantic-errors -Wextra -Wcast-align -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion -Wdisabled-optimization -Wfloat-equal  -Wformat  -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport  -Winit-self  -Winline -Winvalid-pch -Wunsafe-loop-optimizations -Wmissing-braces -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked  -Wpadded -Wparentheses  -Wpointer-arith -Wredundant-decls -Wreturn-type -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default -Wswitch-enum -Wtrigraphs  -Wuninitialized -Wunknown-pragmas  -Wunreachable-code -Wunused -Wunused-function  -Wunused-label  -Wunused-parameter -Wunused-value  -Wunused-variable  -Wvariadic-macros -Wvolatile-register-var  -Wwrite-strings -Wsign-compare -Wsign-conversion -Wfloat-conversion -Wpedantic -g -fconcepts -O0)

add_executable(b64_tests tests/test_main.cpp)
target_include_directories(b64_tests PRIVATE inc)
target_compile_options(b64_tests PRIVATE ${COMPILATION_COMMANDS})
set_target_properties(b64_tests PROPERTIES ${TARGET_PROPERTIES})
target_link_libraries(b64_tests ${CONAN_LIBS})

enable_testing()

catch_discover_tests(b64_tests TEST_PREFIX "constexpr." EXTRA_ARGS -s --reporter=xml --out=constexpr.xml)


# Microbenchmark

# https://mirkokiefer.com/cmake-by-example-f95eb47d45b1
# ExternalProject_Add(project_luajit
#   URL http://luajit.org/download/LuaJIT-2.0.1.tar.gz
#   PREFIX ${CMAKE_CURRENT_BINARY_DIR}/luajit-2.0.1
#   CONFIGURE_COMMAND ""
#   BUILD_COMMAND make
#   INSTALL_COMMAND make install
#   PREFIX=${CMAKE_CURRENT_BINARY_DIR}/luajit-2.0.1
#   )

# ExternalProject_Get_Property(project_luajit install_dir)
add_library(libbenchmark STATIC IMPORTED)
set_property(TARGET libbenchmark PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/third-party-libs/benchmark/build/src/libbenchmark.a)
# add_dependencies(libbenchmark project_luajit)
# add_executable(myapp main.c)
# include_directories(${install_dir}/include/luajit-2.0)

# target_link_libraries(myapp luajit)

add_executable(b64_performance tests/test_benchmark.cpp)
target_include_directories(b64_performance PRIVATE inc third-party-libs/benchmark/include)
target_compile_options(b64_performance PRIVATE -Wall -Wextra -fconcepts -O3 -g)
set_target_properties(b64_performance PROPERTIES ${TARGET_PROPERTIES})
# target_link_libraries(b64_performance Threads::Threads ${CONAN_LIBS} libbenchmark libbenchmark_main)
target_link_libraries(b64_performance Threads::Threads ${CONAN_LIBS} libbenchmark)
