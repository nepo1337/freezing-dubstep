#ifndef EDITOR_H
#define EDITOR_H

#include <iostream>
#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFGUI/SFGUI.hpp>
#include "MeshHandler.h"
#include "Camera.h"

class Editor
{
private:
  sf::ContextSettings settings;
  sf::Window window;
  sf::Clock clock;
  MeshHandler meshHandler;
  Camera cam;
  int mousedx,mousedy;
public:
  Editor();
  void init();
  void run();
};
#endif