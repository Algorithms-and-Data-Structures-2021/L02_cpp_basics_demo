cmake_minimum_required(VERSION 3.2)

project(L02_cpp_basics_demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# добавление пути до заголовочных файлов для всех целей (target-ов)
# include_directories(include)

# цели (target-ы)
add_executable(constants src/constants.cpp)
add_executable(enums src/enums.cpp)
add_executable(structs src/structs.cpp)
add_executable(strings src/strings.cpp)
add_executable(iostreams src/iostreams.cpp)
add_executable(utilities src/utilities.cpp)


# добавление пути до заголовочных файлов для определенной цели (target-а)
target_include_directories(structs PRIVATE include)

target_compile_definitions(iostreams PRIVATE PROJECT_DIR="${PROJECT_SOURCE_DIR}")