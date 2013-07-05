#include "Editor.h"

Editor::Editor()
{

}
void Editor::init()
{
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 1;
    settings.majorVersion = 4;
    settings.minorVersion = 0;
    
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
    
    
}
void Editor::run()
{
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close(); 
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
			}
		}
		//poll
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			cam.moveForeward(0.1);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			cam.moveBackward(0.1);
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			cam.strafeLeft(0.1);
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			cam.strafeRight(0.1);

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
        // draw...

        // end the current frame (internally swaps the front and back buffers)

	window.display();
	}
}

