cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(cpp-basics-demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# добавление пути до заголовочных файлов для всех целей (target-ов)
# include_directories(include)

# цели (target-ы) - в данном случае это "исполняемые файлы"
add_executable(constants src/constants.cpp)
add_executable(enums src/enums.cpp)
add_executable(strings src/strings.cpp)
add_executable(structs src/structs.cpp)
add_executable(iostreams src/iostreams.cpp)
add_executable(utilities src/utilities.cpp)

# добавление пути до заголовочных файлов для определенной цели
target_include_directories(structs PRIVATE include)

target_compile_definitions(iostreams PRIVATE PROJECT_DIR="${PROJECT_SOURCE_DIR}")
