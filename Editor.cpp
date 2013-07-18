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
	glClearColor(0.2,0.4,0.6,0.0);

	this->meshHandler.init();
	this->meshHandler.setWidthHeight(1,1);
	this->meshHandler.setCamera(&this->cam);
	cam.updateProjectionMatrix(800,600);
	this->meshHandler.windowResizedUpdate();
    
	this->mousedx=this->mousedy=0;
	
	sf::Image image;
	image.loadFromFile("sfml.png");
	GLuint th=TextureHandler::uploadSimpleTexLinear(image);
	sf::Image scimg;
	scimg.loadFromFile("add.png");
	GLuint ball = TextureHandler::uploadSimpleTexLinear(scimg);
	gB.create(0,0,100,20,1);
	vS.create(10,75,90,10,2);
	cB.create(10,40,20,20,3);
	sP.create(10,90,90,90,4);
	sP.setTexture(th);
	sP.hideFrame();
	hS.create(105,90,10,90,5);
	gWin.create(20,40,150,200,0);
	gWin.setBackgroundColor(vec4(0.4,0.8,0.4,0.7));
	gWin.setFrameColor(vec4(0.2,0.3,0.2,1.0));
	guiS.init(800,600);
	guiS.addWindow(gWin);
	gWin.addControl(gB);
	gWin.addControl(vS);
	gWin.addControl(cB);
	gWin.addControl(sP);
	gWin.addControl(hS);

	this->followWindow=false;
	this->bOffX=0;
	this->bOffY=0;
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
			this->handleGUIEvents(guiS.handleEvent(event));
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

		if(this->followWindow)
		{
			this->gWin.setPosition(vec2((float)sf::Mouse::getPosition(this->window).x-bOffX,(float)sf::Mouse::getPosition(this->window).y-bOffY));
		}
		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		this->meshHandler.draw();

		guiS.draw();
		window.display();
		clock.restart();
	}
}
void Editor::handleGUIEvents(EventTraveller t)
{
	if(t.getID()==1&&t.getEventType()==EventType::LEFT_MOUSE_CLICK)
	{
		this->followWindow=true;
		bOffX=t.getOffset().x;
		bOffY=t.getOffset().y;
	}
	if(t.getEventType()==EventType::LEFT_MOUSE_RELEASE)
	{
		this->followWindow=false;
	}
	if(t.getEventType()==EventType::LEFT_MOUSE_CLICK&&t.getID()==2)
	{
		cout << vS.getNormalizedSliderValue()<<endl;
	}
	if(t.getEventType()==EventType::LEFT_MOUSE_CLICK&&t.getID()==3)
	{
		this->meshHandler.toggleWireframe();
	}
	if(t.getEventType()==EventType::LEFT_MOUSE_CLICK&&t.getID()==4)
	{
		cout<<"SLUTA TA PÅ MIG!"<<endl;
	}
}