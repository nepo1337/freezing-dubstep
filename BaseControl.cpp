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
	VBO2uh=0;
	VBO3uh=0;
	bgColor=vec4(1.0f);
	frameColor=vec4(1.0f);
	collisionRect=vec4(0.0f);
	this->hasTex=false;
	mouseButtonDown=false;
	this->mouseOver=false;
	this->released=false;
	this->hasTriTex=false;
}

BaseControl::~BaseControl()
{
	glDeleteBuffers(1,&this->VBOh);
	glDeleteBuffers(1,&this->VBOuh);
	glDeleteBuffers(1,&this->VBO2uh);
	glDeleteBuffers(1,&this->VBO3uh);
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

void BaseControl::create(float x, float y, float w, float h)
{
	glDeleteBuffers(1,&this->VBOh);
	glDeleteBuffers(1,&this->VBOuh);
	glDeleteVertexArrays(1,&this->VAOh);
	
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
			if(this->hasTriTex)
			{
				shader.setUniform("uvIndex",0);
				if(this->mouseOver)
					shader.setUniform("uvIndex",1);
				if(this->mouseButtonDown)
					shader.setUniform("uvIndex",2);
			}
			glBindTexture(GL_TEXTURE_2D,this->texHandle);
			shader.setSubroutine(GLSLShader::FRAGMENT, "texOut");
		}
		else
		{
			shader.setUniform("color",this->bgColor);
			shader.setSubroutine(GLSLShader::FRAGMENT, "defOut");
		}
		glDrawArrays(GL_TRIANGLE_STRIP,0,4);
		shader.setUniform("uvIndex",0);
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
bool BaseControl::intersect(int x, int y)
{
	bool intersected = false;
	if(this->visible)
		if(x>this->collisionRect.x&&x<this->collisionRect.x+this->collisionRect.z)
		{
			if(y>this->collisionRect.y&&y<this->collisionRect.y+this->collisionRect.w)
			{
				intersected=true;
			}
		}
	return intersected;
}
void BaseControl::updateCollisionRect(float x, float y)
{
	this->collisionRect.x=this->x+x;
	this->collisionRect.y=this->y+y;
}
void BaseControl::leftMBTNReleased()
{
	if(this->mouseButtonDown)
	{
		this->released=true;
		this->mouseButtonDown=false;
	}
}


void BaseControl::setTexture(GLuint texH)
{
	this->texHandle=texH;
	this->hasTex=true;
}
void BaseControl::setTriTexture(GLuint texH)
{
	this->hasTriTex=true;
	this->texHandle=texH;
	this->hasTex=true;
	glDeleteBuffers(1,&this->VBOuh);
	glDeleteBuffers(1,&this->VBO2uh);
	glDeleteBuffers(1,&this->VBO3uh);
	
	float uvs1[]=
	{
		0.0,0.0,
		0.0,1.0,
		1.0/3.0,0.0,
		1.0/3.0,1.0
	};
	float uvs2[]=
	{
		1.0/3.0,0.0,
		1.0/3.0,1.0,
		2.0/3.0,0.0,
		2.0/3.0,1.0
	};
	float uvs3[]=
	{
		2.0/3.0,0.0,
		2.0/3.0,1.0,
		1.0,0.0,
		1.0,1.0
	};
	
	glBindVertexArray(this->VAOh);
	glGenBuffers(1,&this->VBOuh);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBOuh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs1),&uvs1,GL_STATIC_DRAW);
	
	glGenBuffers(1,&this->VBO2uh);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBO2uh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs2),&uvs2,GL_STATIC_DRAW);
	
	glGenBuffers(1,&this->VBO3uh);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBO3uh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs3),&uvs3,GL_STATIC_DRAW);
	
	
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBOuh);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,NULL);
	
	glBindBuffer(GL_ARRAY_BUFFER,this->VBO2uh);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,NULL);
	
	glBindBuffer(GL_ARRAY_BUFFER,this->VBO3uh);
	glVertexAttribPointer(3,2,GL_FLOAT,GL_FALSE,0,NULL);
	glBindVertexArray(0);
}

void BaseControl::handleKeyDown(char c)
{

}
vec4 BaseControl::getCollisionRect()
{
	return this->collisionRect;
}
bool BaseControl::mouseHover(int x, int y)
{
	this->mouseOver=this->intersect(x,y);
	return this->mouseOver;
}
void BaseControl::handleLeftClick(int x, int y)
{
	mouseButtonDown=this->intersect(x,y);
	this->released=false;
}
bool BaseControl::isDown()
{
	return this->mouseButtonDown;
}
bool BaseControl::wasReleased()
{
	if(this->released)
	{
		this->released=false;
		return true;
	}
	return false;
}
bool BaseControl::isActivated()
{
	return false;
}
void BaseControl::setCollisionRect(vec4 rect)
{
	this->collisionRect=rect;
}
bool BaseControl::isHovered()
{
	return this->mouseOver;
}