/*
    Copyright (c) 2013 rolle <email>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/


#include "GuiSystem.h"

void GuiSystem::init(int w, int h)
{
	this->orthoCam = glm::ortho(0.0f, (float)w,(float)h,0.0f, -1.f, 1.f);
	guiShader.compileShaderFromFile("gui.vsh",GLSLShader::VERTEX);
	cout << guiShader.log()<<endl;
	guiShader.compileShaderFromFile("gui.fsh",GLSLShader::FRAGMENT);
	cout << guiShader.log()<<endl;

	this->guiShader.bindAttribLocation(0,"vertexPosition");
	this->guiShader.link();
	cout << this->guiShader.log()<<endl;
	this->guiShader.use();
	this->guiShader.setUniform("orthoMatrix",this->orthoCam);
}

GuiSystem::GuiSystem()
{
	this->orthoCam = glm::ortho(0.0f, (float)10,(float)10,0.0f, -1.f, 1.f);
}

GuiSystem::~GuiSystem()
{

}

void GuiSystem::handleEvent(const sf::Event &e)
{
	switch(e.type)
	{
		case sf::Event::Resized:
					// adjust the viewport when the window is resized
				this->orthoCam = glm::ortho(0.0f, (float)e.size.width,(float)e.size.height,0.0f, -1.f, 1.f);
				this->guiShader.use();
				this->guiShader.setUniform("orthoMatrix",this->orthoCam);
			break;
		case sf::Event::KeyPressed:
			switch(e.key.code)
			{
				case sf::Keyboard::C:
					std::cout<<"hej"<<std::endl;
					break;
			}
	}
}
void GuiSystem::addWindow(Window& w)
{
	this->windows.push_back(&w);
	
}
void GuiSystem::draw()
{
	this->guiShader.use();
	for(int i=0;i<this->windows.size();i++)
	{
		if(this->windows[i])
		{
			this->windows[i]->draw();
		}
		else
		{
			this->windows[i]=this->windows[this->windows.size()-1];
			this->windows.pop_back();
		}
	}
	
	glUseProgram(0);
	glBindVertexArray(0);
}