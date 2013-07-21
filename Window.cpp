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


#include "Window.h"

Window::Window()
{
	this->modelMatrix=mat4(1.0f);
}

Window::~Window()
{
	glDeleteBuffers(1,&this->VBOh);
	glDeleteVertexArrays(1,&this->VAOh);
}

void Window::addControl(BaseControl &c)
{
	c.setBackgroundColor(this->bgColor);
	c.setFrameColor(this->frameColor);
	c.updateCollisionRect(this->x,this->y);
	this->controls.push_back(&c);
}
void Window::draw(GLSLProgram &shader)
{
	glBindVertexArray(this->VAOh);
	shader.setUniform("modelMatrix",this->modelMatrix);
	shader.setUniform("color",this->bgColor);
	shader.setSubroutine(GLSLShader::FRAGMENT, "defOut");
	glDrawArrays(GL_TRIANGLE_STRIP,0,4);
	shader.setUniform("color",this->frameColor);
	glDrawArrays(GL_LINE_STRIP,4,5);
	
	for(int i=0;i<this->controls.size();i++)
	{
		this->controls[i]->draw(shader);
	}
}
void Window::handleLeftClick(int x, int y)
{
	//if the x,y coordinates intersects the window
	if(this->intersect(x,y))
	{
		//if a control is intersected, return its id
		for(int i=0;i<this->controls.size();i++)
		{
			controls[i]->handleLeftClick(x,y);
		}
	}

}
vec2 Window::getPosition()
{
	return vec2(this->pos.x,this->pos.y);
}
void Window::setPosition(vec2 p)
{
	this->pos=vec3(p.x,p.y,0);
	this->modelMatrix=mat4(1.0f);
	this->modelMatrix*=translate(this->pos);
	this->collisionRect.x=p.x;
	this->collisionRect.y=p.y;

	
	for(int i=0;i<this->controls.size();i++)
	{
		this->controls[i]->updateCollisionRect(this->pos.x,this->pos.y);
	}
}
void Window::create(float x, float y, float w, float h, int id)
{
	this->controlID=id;
	this->x=x;
	this->y=y;
	this->width=w;
	this->height=h;
	
	float verts[]=
	{
		0,0,0,
		0,this->height,0,
		this->width,0,0,
		this->width,this->height,0,
		0,0,0,
		0,this->height,0,
		this->width,this->height,0,
		this->width,0,0,
		0,0,0
		
	};
	glGenVertexArrays(1,&this->VAOh);
	glBindVertexArray(this->VAOh);
	glGenBuffers(1,&this->VBOh);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBOh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts),&verts,GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
	glBindVertexArray(0);
	this->pos.x=x;
	this->pos.y=y;
	this->modelMatrix=mat4(1.0f);
	this->modelMatrix*=translate(this->pos);
	
	this->collisionRect.x=x;
	this->collisionRect.y=y;
	this->collisionRect.z=width;
	this->collisionRect.w=height;
}
void Window::handleLeftRelease()
{
	for(int i=0;i<this->controls.size();i++)
	{
		this->controls[i]->leftMBTNReleased();
	}
}
void Window::handleKeyDown(char c)
{
	for(int i=0;i<this->controls.size();i++)
	{
		this->controls[i]->handleKeyDown(c);
	}
}
void Window::mouseHover(int x, int y)
{
	if(this->intersect(x,y))
	{
		for(int i=0;i<this->controls.size();i++)
		{
			this->controls[i]->mouseHover(x,y);
		}
	}
}