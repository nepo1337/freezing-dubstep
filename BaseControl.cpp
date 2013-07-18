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


#include "BaseControl.h"

BaseControl::BaseControl()
{
	visible=true;
	frameVisible=true;
	width=0;
	height=0;
	x=0;
	y=0;
	VAOh=0;
	VBOh=0;
	VBOuh=0;
	bgColor=vec4(1.0f);
	frameColor=vec4(1.0f);
	controlID=0;
	collisionRect=vec4(0.0f);
	this->hasTex=false;
}

BaseControl::~BaseControl()
{
	glDeleteBuffers(1,&this->VBOh);
	glDeleteBuffers(1,&this->VBOh);
	glDeleteVertexArrays(1,&this->VAOh);
}

void BaseControl::hide()
{
	this->visible=false;
}
void BaseControl::show()
{
	this->visible=true;
}
void BaseControl::hideFrame()
{
	this->frameVisible=false;
}
void BaseControl::showFrame()
{
	this->frameVisible=true;
}

void BaseControl::create(float x, float y, float w, float h,int id)
{
	glDeleteBuffers(1,&this->VBOh);
	glDeleteBuffers(1,&this->VBOuh);
	glDeleteVertexArrays(1,&this->VAOh);
	
	this->controlID=id;
	this->x=x;
	this->y=y;
	this->width=w;
	this->height=h;
	this->collisionRect=vec4(x,y,this->width,this->height);
	
	float verts[]=
	{
		this->x,this->y,0,
		this->x,this->y+this->height,0,
		this->x+this->width,this->y,0,
		this->x+this->width,this->y+this->height,0,
		this->x,this->y,0,
		this->x,this->y+this->height,0,
		this->x+this->width,this->y+this->height,0,
		this->x+this->width,this->y,0,
		this->x,this->y,0
		
	};
	float uvs[]=
	{
		0.0,0.0,
		0.0,1.0,
		1.0,0.0,
		1.0,1.0
	};
	glGenVertexArrays(1,&this->VAOh);
	glBindVertexArray(this->VAOh);
	glGenBuffers(1,&this->VBOh);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBOh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts),&verts,GL_STATIC_DRAW);
	
	glGenBuffers(1,&this->VBOuh);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBOuh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs),&uvs,GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBOh);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBOuh);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,NULL);
	glBindVertexArray(0);
}
void BaseControl::draw(GLSLProgram &shader)
{
	if(this->visible)
	{
		glBindVertexArray(this->VAOh);
		if(this->hasTex)
		{
			glBindTexture(GL_TEXTURE_2D,this->texHandle);
			shader.setSubroutine(GLSLShader::FRAGMENT, "texOut");
		}
		else
		{
			shader.setUniform("color",this->bgColor);
			shader.setSubroutine(GLSLShader::FRAGMENT, "defOut");
		}
		glDrawArrays(GL_TRIANGLE_STRIP,0,4);
		
		if(this->frameVisible)
		{
			shader.setUniform("color",this->frameColor);
			shader.setSubroutine(GLSLShader::FRAGMENT, "defOut");
			glDrawArrays(GL_LINE_STRIP,4,5);
		}
	}
}
vec4 BaseControl::getBackgroundColor()
{
	return this->bgColor;
}
vec4 BaseControl::getFrameColor()
{
	return this->frameColor;
}
void BaseControl::setBackgroundColor(vec4 c)
{
	this->bgColor=c;
}
void BaseControl::setFrameColor(vec4 c)
{
	this->frameColor=c;
}
EventTraveller BaseControl::intersect(int x, int y)
{
	EventTraveller t;
	if(x>this->collisionRect.x&&x<this->collisionRect.x+this->collisionRect.z)
	{
		if(y>this->collisionRect.y&&y<this->collisionRect.y+this->collisionRect.w)
		{
			t.setID(this->controlID);
			t.setOffset(vec2(x-this->collisionRect.x,y-this->collisionRect.y));
		}
	}
	return t;
}
void BaseControl::updateCollisionRect(float x, float y)
{
	this->collisionRect.x=this->x+x;
	this->collisionRect.y=this->y+y;
}
void BaseControl::leftMBTNReleased()
{

}


void BaseControl::setTexture(GLuint texH)
{
	this->texHandle=texH;
	this->hasTex=true;
}
