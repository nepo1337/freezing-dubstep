#ifndef EDITOR_H
#define EDITOR_H

#include <iostream>
#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "MeshHandler.h"
#include "Camera.h"
#include "GuiSystem.h"
#include "Window.h"
#include "Button.h"
#include "VerticalSlider.h"
#include "CheckBox.h"
#include "Sprite.h"
#include "HorizontalSlider.h"
#include "TextLabel.h"
#include "TextField.h"
#include "Brush.h"

using namespace std;
class Editor
{
private:
	const int numTex=5;
	sf::ContextSettings settings;
	sf::Window window;
	sf::Clock clock;
	MeshHandler meshHandler;
	GuiSystem guiS;
	Camera cam;
	int mousedx,mousedy;
	bool running;
	Window gWin,propsWin,fileWindow,toolsWindow;
	Button gB,fileButton,propsButton,toolsButton,updateButton;
	VerticalSlider vS,toolRadiusSlider;
	CheckBox cB;
	Sprite textureSprites[5], displaySprite,smallDisplaySprite;
	HorizontalSlider hS;
	TextLabel textL,propsLabel,toolLabel,wireframeLabel,nameLabel,widthHeightLabel,updateLabel,toolTextureLabel,toolRadiusLabel;
	TextField textF,mapWidth,mapHeight;
	Brush brush;
	//void handleGUIEvents(EventTraveller t);
	bool followWindow;
	void createGui();
public:
	Editor();
	void run();
};
#endif
