#ifndef EDITOR_H
#define EDITOR_H

#include <iostream>
#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "MeshHandler.h"
#include "Camera.h"
#include "GuiSystem.h"
#include "Window.h"

class Editor
{
private:
	sf::ContextSettings settings;
	sf::RenderWindow window;
	sf::Clock clock;
	MeshHandler meshHandler;
	GuiSystem guiS;
	Camera cam;
	int mousedx,mousedy;
	bool running;
	Window gWin;
public:
	Editor();
	void run();
};
#endif
