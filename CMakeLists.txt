cmake_minimum_required(VERSION 2.8)

project(editor)

add_executable(editor main.cpp)
target_link_libraries(editor sfml-system)

install(TARGETS editor RUNTIME DESTINATION bin)
