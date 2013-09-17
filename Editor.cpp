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
	
	this->createGui();
}
void Editor::createGui()
{
	sf::Image image;
	image.loadFromFile("textures/green/grass02small.png");
	GLuint th=TextureHandler::uploadTextureGFX(image);
	sf::Image scimg;
	scimg.loadFromFile("add.png");
	GLuint ball = TextureHandler::uploadSimpleTexLinear(scimg);
	
	//font stuff
	GLuint fontH;
	sf::Image fI;
	fI.loadFromFile("fnt.png");
	fontH = TextureHandler::uploadSimpleTexLinear(fI);

	FontInfo f;
	f.init(fI,"fntletters.txt",26,4);
	textL.create(0,20,40,20,f,fontH);
	textL.setText("File");
	propsLabel.create(40,20,40,20,f,fontH);
	propsLabel.setText("Props");
	toolLabel.create(90,20,40,20,f,fontH);
	toolLabel.setText("Tools");
	wireframeLabel.create(25,10,0,15,f,fontH);
	wireframeLabel.setText("Wireframe");
	nameLabel.create(5,10,0,15,f,fontH);
	nameLabel.setText("Mapname:");
	widthHeightLabel.create(5,45,0,15,f,fontH);
	widthHeightLabel.setText("Width:     Height:");
	
	updateLabel.create(5,90,0,15,f,fontH);
	updateLabel.setText("Update");
	
	toolTextureLabel.create(5,10,0,15,f,fontH);
	toolTextureLabel.setText("Textures:");
	toolRadiusLabel.create(5,220,0,15,f,fontH);
	toolRadiusLabel.setText("Radius");
	
	textF.create(5,25,140,15,f,fontH);
	mapWidth.create(10,60,40,15,f,fontH);
	mapWidth.setText("1");
	mapHeight.create(70,60,40,15,f,fontH);
	mapHeight.setText("1");
	
	gB.create(0,0,150,20);
	fileButton.create(0,20,40,20);
	propsButton.create(40,20,50,20);
	toolsButton.create(90,20,60,20);
	updateButton.create(5,90,60,15);

	vS.create(10,75,90,10);
	toolRadiusSlider.create(5,240,80,10);
	toolRadiusSlider.setNormalizedSliderValue(0.5);
	this->brush.setRadius(toolRadiusSlider.getNormalizedSliderValue()*9+1);
	cB.create(5,10,15,15);
	displaySprite.create(150,40,150,150);
	displaySprite.hide();
	smallDisplaySprite.create(80,5,25,25);
	smallDisplaySprite.setTexture(TextureHandler::getTextureSet(0).getTexHandle(0));
	textureSprites[0].create(5,35,40,40);
	textureSprites[0].setTriTexture(th);
	image.loadFromFile("textures/green/grass07small.png");
	th=TextureHandler::uploadTextureGFX(image);
	textureSprites[1].create(50,35,40,40);
	textureSprites[1].setTriTexture(th);
	image.loadFromFile("textures/green/dirt01small.png");
	th=TextureHandler::uploadTextureGFX(image);
	textureSprites[2].create(95,35,40,40);
	textureSprites[2].setTriTexture(th);
	image.loadFromFile("textures/green/dirt05small.png");
	th=TextureHandler::uploadTextureGFX(image);
	textureSprites[3].create(5,80,40,40);
	textureSprites[3].setTriTexture(th);
	image.loadFromFile("textures/green/gravel01small.png");
	th=TextureHandler::uploadTextureGFX(image);
	textureSprites[4].create(50,80,40,40);
	textureSprites[4].setTriTexture(th);
	
	hS.create(105,90,10,90);
	gWin.create(20,40,150,40);
	propsWin.create(20,80,150,160);
	propsWin.setBackgroundColor(vec4(0.4,0.8,0.4,0.7));
	propsWin.setFrameColor(vec4(0.2,0.3,0.2,1.0));
	propsWin.hide();
	fileWindow.create(20,80,150,160);
	fileWindow.setBackgroundColor(vec4(0.4,0.8,0.4,0.7));
	fileWindow.setFrameColor(vec4(0.2,0.3,0.2,1.0));
	toolsWindow.create(20,80,150,300);
	toolsWindow.setBackgroundColor(vec4(0.4,0.8,0.4,0.7));
	toolsWindow.setFrameColor(vec4(0.2,0.3,0.2,1.0));
	toolsWindow.addControl(toolTextureLabel);
	toolsWindow.addControl(smallDisplaySprite);
	toolsWindow.addControl(toolRadiusLabel);
	toolsWindow.addControl(toolRadiusSlider);
	toolsWindow.hide(); 
	//fileWindow.hide();
	gWin.setBackgroundColor(vec4(0.4,0.8,0.4,0.7));
	gWin.setFrameColor(vec4(0.2,0.3,0.2,1.0));
	guiS.init(800,600);
	guiS.addWindow(gWin);
	guiS.addWindow(propsWin);
	guiS.addWindow(toolsWindow);
	guiS.addWindow(fileWindow);
	gWin.addControl(gB);
	gWin.addControl(displaySprite);
	propsWin.addControl(cB);
	propsWin.addControl(wireframeLabel);
	fileWindow.addControl(textF);
	fileWindow.addControl(nameLabel);
	fileWindow.addControl(mapWidth);
	fileWindow.addControl(mapHeight);
	fileWindow.addControl(widthHeightLabel);
	fileWindow.addControl(updateButton);
	fileWindow.addControl(updateLabel);
	for(int i=0;i<numTex;i++)
	{
		toolsWindow.addControl(textureSprites[i]);
	}
	gWin.addControl(fileButton);
	gWin.addControl(textL);
	gWin.addControl(propsButton);
	gWin.addControl(propsLabel);
	gWin.addControl(toolsButton);
	gWin.addControl(toolLabel);
	gB.setBackgroundColor(vec4(0.4,0.4,0.9,1.0));

	this->followWindow=false;
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
			if(!guiS.handleEvent(event))
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
			
		}
		if(!this->guiS.isTextfieldsActivated())
		{
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
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if(!this->toolsWindow.isHovered())
					this->meshHandler.paintMesh(this->brush,cam.getPos(),cam.getClickRay(sf::Mouse::getPosition(this->window).x,sf::Mouse::getPosition(this->window).y));
			}
		}
		
		this->mousedx = sf::Mouse::getPosition(this->window).x;
		this->mousedy = sf::Mouse::getPosition(this->window).y;
		
		followWindow=false;
		if(gB.isDown())
		{
			followWindow=true;
		}
		if(fileButton.wasReleased())
		{
			fileWindow.show();
			propsWin.hide();
			toolsWindow.hide();
		}
		if(propsButton.wasReleased())
		{
			propsWin.show();
			fileWindow.hide();
			toolsWindow.hide();
		}
		if(this->toolsButton.wasReleased())
		{
			propsWin.hide();
			fileWindow.hide();
			toolsWindow.show();
		}
		if(this->updateButton.wasReleased())
		{
			int w =1;
			int h = 1;
			w=atoi(mapWidth.getText().c_str());
			h=atoi(mapHeight.getText().c_str());
			this->meshHandler.setWidthHeight(w,h);
		}
		if(cB.wasReleased())
			this->meshHandler.toggleWireframe();
		
		if(toolRadiusSlider.wasReleased())
			brush.setRadius(1+toolRadiusSlider.getNormalizedSliderValue()*9);
		this->displaySprite.hide();
		for(int i=0;i<numTex;i++)
		{
			if(this->textureSprites[i].isHovered())
			{
				this->displaySprite.show();
				this->displaySprite.setTexture(TextureHandler::getTextureSet(0).getTexHandle(i));
				if(this->textureSprites[i].wasReleased())
				{
					this->brush.setBrushTexture(i);
					this->smallDisplaySprite.setTexture(TextureHandler::getTextureSet(0).getTexHandle(i));
				}
			}
		}
		if(this->followWindow)
		{
			this->gWin.setPosition(vec2((float)sf::Mouse::getPosition(this->window).x+gWin.getClickOffset().x,(float)sf::Mouse::getPosition(this->window).y+gWin.getClickOffset().y));
			this->fileWindow.setPosition(vec2(gWin.getPosition().x,gWin.getPosition().y+40));
			this->propsWin.setPosition(vec2(gWin.getPosition().x,gWin.getPosition().y+40));
			this->toolsWindow.setPosition(vec2(gWin.getPosition().x,gWin.getPosition().y+40));
		}
		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		this->meshHandler.draw();

		guiS.draw();
		window.display();
		clock.restart();
	}
}
/*
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
}*/