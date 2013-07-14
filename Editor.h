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
#include "Button.h"
#include "EventTraveller.h"
#include "VerticalSlider.h"
#include "CheckBox.h"

using namespace std;
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
	Button gB;
	VerticalSlider vS;
	CheckBox cB;
	void handleGUIEvents(EventTraveller t);
	float bOffX,bOffY;
	bool followWindow;
public:
	Editor();
	void run();
};
#endif
