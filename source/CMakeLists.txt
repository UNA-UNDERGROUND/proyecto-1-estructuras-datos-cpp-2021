cmake_minimum_required(VERSION 3.0.0)
project(proyecto1-estructuras-datos-cpp-2021 VERSION 0.1.0)


set(header_sources
)

set(sources
    ${header_sources}
)

add_executable(proyecto1 ${sources} src/source.cpp)
target_include_directories(proyecto1 PRIVATE include)