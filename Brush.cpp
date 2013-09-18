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


#include "Brush.h"



Brush::Brush()
{
	this->radius=1.0f;
	this->brushType=BrushType::CIRCLE;
	this->paintTex=0;
	this->paintSpeed=1;
}
Brush::~Brush()
{

}
BrushType::type Brush::getBrushType()
{
	return this->brushType;
}
float Brush::getRadius()
{
	return this->radius;
}
void Brush::setBrushType(BrushType::type t)
{
	this->brushType=t;
}
void Brush::setRadius(float f)
{
	this->radius=f;
}
GLuint Brush::getBrushTexture()
{
	return this->paintTex;
}
void Brush::setBrushTexture(GLuint t)
{
	this->paintTex=t;
}

int Brush::getPaintSpeed()
{
	return this->paintSpeed;
}

void Brush::setPaintSpeed(float f)
{
	this->paintSpeed=f;
}

