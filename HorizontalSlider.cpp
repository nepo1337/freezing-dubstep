#include "HorizontalSlider.h"


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

HorizontalSlider::HorizontalSlider()
{
	this->bVal=0;
}

HorizontalSlider::~HorizontalSlider()
{
	glDeleteBuffers(1,&this->VBOh);
	glDeleteVertexArrays(1,&this->VAOh);
}

void HorizontalSlider::create(float x, float y, float w, float h, int id)
{
	BaseControl::create(x,y,w,h,id);
	this->scrollButton.create(x,y,w,h*0.1,-1);
}
void HorizontalSlider::draw(GLSLProgram& shader)
{
	BaseControl::draw(shader);
	this->scrollButton.draw(shader);
}
void HorizontalSlider::setBackgroundColor(vec4 c)
{
	this->bgColor=c;
	this->scrollButton.setBackgroundColor(vec4(vec3(1-this->bgColor.x,1-this->bgColor.y,1-this->bgColor.z),c.w));
}
void HorizontalSlider::setFrameColor(vec4 c)
{
	this->frameColor=c;
	this->scrollButton.setFrameColor(c);
}
void HorizontalSlider::setScrollButtonBackgroundColor(vec4 c)
{
	this->scrollButton.setBackgroundColor(c);
}
void HorizontalSlider::setScrollButtonFrameColor(vec4 c)
{
	this->scrollButton.setFrameColor(c);
}

EventTraveller HorizontalSlider::intersect(int x, int y)
{
	EventTraveller t = BaseControl::intersect(x, y);
	if(t.hasValidID())
	{
		float yVal=this->y-this->height*0.05+t.getOffset().y;
		this->bVal = y-this->collisionRect.y;
		this->bVal/=this->height;
		if(t.getOffset().y<=this->height*0.05)
		{
			yVal=this->y;
			this->bVal=0;
		}
		if(t.getOffset().y>=this->height-this->height*0.05)
		{
			yVal=this->y+this->height-this->height*0.1;
			this->bVal=1;
		}

		this->scrollButton.create(this->x,yVal,this->width,this->height*0.1,-1);
	}
	return t;
}
void HorizontalSlider::updateCollisionRect(float x, float y)
{
	this->scrollButton.updateCollisionRect(x,y);
	BaseControl::updateCollisionRect(x, y);
}
float HorizontalSlider::getNormalizedSliderValue()
{
	return 1-this->bVal;
}
void HorizontalSlider::setNormalizedSliderValue(float f)
{
	this->bVal=f;
	float yVal=this->y-this->height*0.05+this->height*this->bVal;
	if(this->bVal<0.1)
	{
		yVal=this->y;
	}
	if(this->bVal>0.9)
	{
		yVal=this->y+this->height-this->height*0.1;
	}
	this->scrollButton.create(this->x,yVal,this->width,this->height*0.1,-1);
}
void HorizontalSlider::setScrollButtonTexture(GLuint tex)
{
	this->scrollButton.setTexture(tex);
}
void HorizontalSlider::hideScrollButtonFrame()
{
	this->scrollButton.hideFrame();
}
