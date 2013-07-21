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


#include "VerticalSlider.h"

VerticalSlider::VerticalSlider()
{
	this->bVal=0;
}

VerticalSlider::~VerticalSlider()
{
	glDeleteBuffers(1,&this->VBOh);
	glDeleteVertexArrays(1,&this->VAOh);
}
void VerticalSlider::handleLeftClick(int x, int y)
{
	BaseControl::handleLeftClick(x,y);
	if(this->mouseButtonDown)
	{
		//0.051, 0.05 caused errors O_O?
		//the slider button is always 10% of the slider,
		//hence 0.1 and 0.5(used for middle of the slider)
		float xVal=this->x-this->width*0.051+(x-this->collisionRect.x);
		this->bVal = x-this->collisionRect.x;
		this->bVal/=this->width;
		
		//under 10% the slider should stop at the bottom
		if((x-this->collisionRect.x)<=this->width*0.05)
		{
			xVal=this->x;
			this->bVal=0;
		}
		//and the top of the slider at 90%
		if((x-this->collisionRect.x)>=this->width-this->width*0.05)
		{
			xVal=this->x+this->width-this->width*0.1;
			this->bVal=1;
		}
		
		this->scrollButton.create(xVal,this->y,this->width*0.1,this->height,-1);
	}
}
void VerticalSlider::mouseHover(int x, int y)
{
	BaseControl::mouseHover(x,y);
	if(this->mouseOver&&this->mouseButtonDown)
	{
		//0.051, 0.05 caused errors O_O?
		//the slider button is always 10% of the slider,
		//hence 0.1 and 0.5(used for middle of the slider)
		float xVal=this->x-this->width*0.051+(x-this->collisionRect.x);
		this->bVal = x-this->collisionRect.x;
		this->bVal/=this->width;
		
		//under 10% the slider should stop at the bottom
		if((x-this->collisionRect.x)<=this->width*0.05)
		{
			xVal=this->x;
			this->bVal=0;
		}
		//and the top of the slider at 90%
		if((x-this->collisionRect.x)>=this->width-this->width*0.05)
		{
			xVal=this->x+this->width-this->width*0.1;
			this->bVal=1;
		}
		
		this->scrollButton.create(xVal,this->y,this->width*0.1,this->height,-1);
	}
}

void VerticalSlider::create(float x, float y, float w, float h, int id)
{
	BaseControl::create(x,y,w,h,id);
	//w*0.1, the slider button is always 10% of the width
	this->scrollButton.create(x,y,w*0.1,h,-1);
}
void VerticalSlider::draw(GLSLProgram& shader)
{
	BaseControl::draw(shader);
	this->scrollButton.draw(shader);
}
void VerticalSlider::setBackgroundColor(vec4 c)
{
	this->bgColor=c;
	this->scrollButton.setBackgroundColor(vec4(vec3(1-this->bgColor.x,1-this->bgColor.y,1-this->bgColor.z),c.w));
}
void VerticalSlider::setScrollButtonBackgroundColor(vec4 c)
{
	this->scrollButton.setBackgroundColor(c);
}
void VerticalSlider::setScrollButtonFrameColor(vec4 c)
{
	this->scrollButton.setFrameColor(c);
}

void VerticalSlider::setFrameColor(vec4 c)
{
	this->frameColor=c;
	this->scrollButton.setFrameColor(c);
}

void VerticalSlider::updateCollisionRect(float x, float y)
{
	this->scrollButton.updateCollisionRect(x,y);
	BaseControl::updateCollisionRect(x, y);
}
float VerticalSlider::getNormalizedSliderValue()
{
	return this->bVal;
}

//places the slider button somewhere in the slider space
void VerticalSlider::setNormalizedSliderValue(float f)
{
	this->bVal=f;
	if(this->bVal<0)
		this->bVal=0;
	if(this->bVal>1)
		this->bVal=1;
	
	float xVal=this->x-this->width*0.05+this->width*this->bVal;
	//under 10% the slider should stop at the bottom
	if(this->bVal<0.1)
	{
		xVal=this->x;
	}
	//and the top of the slider at 90%
	if(this->bVal>0.9)
	{
		xVal=this->x+this->width-this->width*0.1;
	}
	this->scrollButton.create(xVal,this->y,this->width*0.1,this->height,-1);

}
void VerticalSlider::setScrollButtonTexture(GLuint tex)
{
	//this->scrollBtnTexH=tex;
	this->scrollButton.setTexture(tex);
}
void VerticalSlider::hideScrollButtonFrame()
{
	this->scrollButton.hideFrame();
}
