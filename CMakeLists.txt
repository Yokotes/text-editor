cmake_minimum_required(VERSION 3.16)

project(TextEditor)

set(CMAKE_CXX_STANDARD 20)

add_executable(textEditor
src/main.cpp
src/file.cpp
)

# Прочитать позже в доке, что это делает
target_compile_definitions(textEditor PRIVATE PROJECT_ROOT="${CMAKE_SOURCE_DIR}")