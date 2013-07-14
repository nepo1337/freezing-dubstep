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

void VerticalSlider::create(float x, float y, float w, float h, int id)
{
	BaseControl::create(x,y,w,h,id);
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
	this->scrollButton.setBackgroundColor(vec4(vec3(c),1.0));
}
void VerticalSlider::setFrameColor(vec4 c)
{
	this->frameColor=c;
	this->scrollButton.setFrameColor(c);
}
EventTraveller VerticalSlider::intersect(int x, int y)
{
	EventTraveller t = BaseControl::intersect(x, y);
	if(t.hasValidID())
	{
		this->bVal = x-this->collisionRect.x;
		this->scrollButton.create(this->x-this->width*0.05+t.getOffset().x,this->y,this->width*0.1,this->height,-1);
		this->scrollButton.setBackgroundColor(vec4(vec3(this->bgColor),1.0));
		this->scrollButton.setFrameColor(this->frameColor);
	}
	return t;
}
void VerticalSlider::updateCollisionRect(float x, float y)
{
	this->scrollButton.updateCollisionRect(x,y);
	BaseControl::updateCollisionRect(x, y);
}
float VerticalSlider::getNormalizedSliderValue()
{
	this->bVal/=this->width;
	if(this->bVal<0.02)
		this->bVal=0;
	if(this->bVal>0.98)
		this->bVal=1;
	return this->bVal;
}
