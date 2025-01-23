cmake_minimum_required(VERSION 3.29)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    src/main.cpp
    src/BaseUniverse.cpp
    src/ToroidalUniverse.cpp
    src/LifeLikeRule.cpp
    src/Game.cpp
)

add_library(life_lib ${SOURCES})

add_executable(lab2 src/main.cpp)

target_link_libraries(lab2 PRIVATE life_lib)

target_include_directories(life_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(lab2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)