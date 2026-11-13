cmake_minimum_required(VERSION 3.16)

project(TextEditor)

set(CURSES_NEED_WIDE TRUE)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(textEditor
  src/main.cpp
  src/file.cpp
  src/editor/editor.cpp
  src/editor/cursor.cpp
)

set_target_properties(textEditor
  PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)

target_link_libraries(textEditor ${CURSES_LIBRARIES})