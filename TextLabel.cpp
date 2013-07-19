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


#include "TextLabel.h"

TextLabel::TextLabel()
{
	this->visible=false;
}

TextLabel::~TextLabel()
{

}

void TextLabel::setText(string text)
{
	this->text.setText(text);
}
void TextLabel::draw(GLSLProgram& shader)
{
    BaseControl::draw(shader);
    this->text.draw(shader);
}
void TextLabel::create(float x, float y, float w, float h, int id,FontInfo f, GLuint texh)
{
    BaseControl::create(x, y, w, h, id);
    this->fontInfo=f;
    this->text.create(this->x+2,this->y,this->height/this->fontInfo.getPixHeight(),this->fontInfo,texh,"");
}