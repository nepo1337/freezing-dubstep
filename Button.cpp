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
	this->buttonDown=false;
}

Button::~Button()
{
	glDeleteBuffers(1,&this->VBOh);
	glDeleteVertexArrays(1,&this->VAOh);
}

void Button::leftMBTNReleased()
{
	if(this->mouseButtonDown)
	{
		this->bgColor=vec4(1-this->bgColor.x,1-this->bgColor.y,1-this->bgColor.z,this->bgColor.w);
		this->released=true;
		this->mouseButtonDown=false;
	}
}
void Button::handleLeftClick(int x, int y)
{
	BaseControl::handleLeftClick(x,y);
	if(BaseControl::intersect(x, y))
	{
		this->bgColor=vec4(1-this->bgColor.x,1-this->bgColor.y,1-this->bgColor.z,this->bgColor.w);
	}
}