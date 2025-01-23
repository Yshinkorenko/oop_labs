cmake_minimum_required(VERSION 3.29)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)

# Создаём список исходных файлов
set(SOURCES
    src/main.cpp
    src/BaseUniverse.cpp
    src/ToroidalUniverse.cpp
    src/LifeLikeRule.cpp
    src/Game.cpp
)

# Подключаем библиотеку (можно статическую)
add_library(life_lib ${SOURCES})

# Создаём исполняемый файл
add_executable(game_of_life src/main.cpp)

# Связываем исполняемый файл с библиотекой life_lib
target_link_libraries(game_of_life PRIVATE life_lib)

# Пути к заголовочным файлам
target_include_directories(life_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(game_of_life PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
