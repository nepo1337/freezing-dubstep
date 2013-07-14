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


#include "CheckBox.h"

CheckBox::CheckBox()
{
	this->checked=false;
}

CheckBox::~CheckBox()
{

}
EventTraveller CheckBox::intersect(int x, int y)
{
	EventTraveller t = BaseControl::intersect(x, y);
	if(t.hasValidID())
	{
	    this->checked=!this->checked;
	    this->bgColor=vec4(1-this->bgColor.x,1-this->bgColor.y,1-this->bgColor.z,this->bgColor.w);
	}
	return t;
}

void CheckBox::draw(GLSLProgram& shader)
{
	glBindVertexArray(this->VAOh);
	shader.setUniform("color",this->bgColor);
	glDrawArrays(GL_TRIANGLE_STRIP,0,4);
	shader.setUniform("color",this->frameColor);
	glDrawArrays(GL_LINE_STRIP,4,5);
}

bool CheckBox::isChecked()
{
	return this->checked;
}