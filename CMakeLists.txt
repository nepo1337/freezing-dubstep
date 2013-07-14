cmake_minimum_required(VERSION 2.8)

project(editor)
list( APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
add_executable(editor CheckBox.cpp VerticalSlider.cpp EventTraveller.cpp Window.cpp Button.cpp BaseControl.cpp GuiSystem.cpp MeshData.cpp TextureHandler.cpp TextureSet.cpp MeshHandler.cpp main.cpp GLSLProgram.cpp Camera.cpp Editor.cpp Quad.cpp Face.cpp Mesh.cpp)
target_link_libraries(editor sfml-system sfml-window sfml-graphics GL GLEW)

install(TARGETS editor RUNTIME DESTINATION bin)
