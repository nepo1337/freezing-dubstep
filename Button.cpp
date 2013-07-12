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


#include "Button.h"

Button::Button()
{
	
}

Button::~Button()
{
	glDeleteBuffers(1,&this->VBOh);
	glDeleteVertexArrays(1,&this->VAOh);
}
void Button::draw()
{

}
void Button::create(float x, float y, float w, float h)
{
	this->x=x;
	this->y=y;
	this->width=w;
	this->height=h;
	this->colissionRect = sf::FloatRect(x,y,this->width,this->height);
	
	float verts[]=
	{
		this->x,this->y,0,
		this->x,this->y+this->height,0,
		this->x+this->width,this->y,0,
		this->x+this->width,this->y+this->width,0,
		this->x+this->width,this->y,0,
		this->x,this->y+this->height,0
	};
	glGenVertexArrays(1,&this->VAOh);
	glBindVertexArray(this->VAOh);
	glGenBuffers(1,&this->VBOh);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBOh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts),&verts,GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
	glBindVertexArray(0);
}
void Button::draw(glm::mat4& ortho, glm::vec2 )
{
	
}
void Button::hide()
{
	this->visible=false;
}
void Button::show()
{
	this->visible=true;
}


