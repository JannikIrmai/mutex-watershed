cmake_minimum_required(VERSION 3.15)
project(mutex-watershed)

include_directories(include)
file(GLOB headers
    include/*.hxx
)

# unit tests
add_executable(test-mutex-watershed src/test-mutex-watershed.cxx)
add_test(test-mutex-watershed test-mutex-watershed)


# main
add_executable(main src/main.cxx)