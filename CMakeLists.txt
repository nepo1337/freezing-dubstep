cmake_minimum_required(VERSION 2.8)

project(editor)

add_executable(editor MeshHandler.cpp MeshHandler.h main.cpp GLSLProgram.cpp GLSLProgram.h Camera.cpp Camera.h Editor.cpp Editor.h Quad.cpp Quad.h Face.cpp Face.h Mesh.cpp Mesh.h)
target_link_libraries(editor sfml-system sfml-window sfml-graphics GL GLEW sfgui)

install(TARGETS editor RUNTIME DESTINATION bin)
