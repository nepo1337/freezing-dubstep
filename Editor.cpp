#include "Editor.h"

Editor::Editor()
{
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 1;
	settings.majorVersion = 4;
	settings.minorVersion = 2;

    
	window.create(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
	
	window.setVerticalSyncEnabled(true);
	window.setActive(true);
	
	GLenum err = glewInit();	
	glClearColor(0.2,0.4,0.6,1.0);

	this->meshHandler.init();
	this->meshHandler.setWidthHeight(1,1);
	this->meshHandler.setCamera(&this->cam);
	cam.updateProjectionMatrix(800,600);
	this->meshHandler.windowResizedUpdate();
    
	this->mousedx=this->mousedy=0;
	
	gWin.create(20,40,50,50);
	guiS.init(800,600);
	guiS.addWindow(gWin);
}

void Editor::run()
{	
	this->running=true;
	
	while (this->running)
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					this->running=false;
				break;

				case sf::Event::Resized:
					// adjust the viewport when the window is resized
					glViewport(0, 0, event.size.width, event.size.height);
					cam.updateProjectionMatrix(event.size.width, event.size.height);
					this->meshHandler.windowResizedUpdate();
				break;

				case sf::Event::MouseWheelMoved:
					if(event.mouseWheel.delta>0)
						cam.zoomIn(event.mouseWheel.delta*5);
					else
						cam.zoomOut(-event.mouseWheel.delta*5);
				break;
				case sf::Event::KeyPressed:
					switch(event.key.code)
					{
						case sf::Keyboard::T:
							this->meshHandler.setWidthHeight(10,10);
						break;
						case sf::Keyboard::Y:
							this->meshHandler.setWidthHeight(1,1);
						break;
					}
				break;
			}
			guiS.handleEvent(event);
		}
		//poll move camera
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			cam.moveForeward(0.2);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			cam.moveBackward(0.2);
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			cam.strafeLeft(0.2);
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			cam.strafeRight(0.2);

		if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
		{
			cam.rotateLeft(mousedx-sf::Mouse::getPosition(this->window).x);
			cam.rotateUp(mousedy-sf::Mouse::getPosition(this->window).y);
		}
		this->mousedx = sf::Mouse::getPosition(this->window).x;
		this->mousedy = sf::Mouse::getPosition(this->window).y;

		
		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		this->meshHandler.draw();

		guiS.draw();
		window.display();
		clock.restart();
	}
}

