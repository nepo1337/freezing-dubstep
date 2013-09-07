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


#include "TextField.h"

TextField::TextField()
{
	this->isActive=false;
	this->maxChars=999;
	this->isActive=false;
}

TextField::~TextField()
{
	
}

void TextField::create(float x, float y, float w, float h, FontInfo f, GLuint texh)
{
	BaseControl::create(x, y, w, h);
	this->fontInfo=f;
	this->text.create(this->x+2,this->y,this->height/this->fontInfo.getPixHeight(),this->fontInfo,texh,"");
}
void TextField::draw(GLSLProgram& shader)
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
			if(this->isActive)
				shader.setUniform("color",vec4(1-this->frameColor.r,1-this->frameColor.g,1-this->frameColor.b,this->frameColor.a));
			else
				shader.setUniform("color",this->frameColor);
			shader.setSubroutine(GLSLShader::FRAGMENT, "defOut");
			glDrawArrays(GL_LINE_STRIP,4,5);
		}
		this->text.draw(shader);
	}
}
void TextField::setText(string text)
{
	this->text.setText(text);
}

void TextField::handleLeftClick(int x, int y)
{
	this->frameColor=vec4(this->frameColor.r,this->frameColor.g,this->frameColor.b,this->frameColor.a);
	if(BaseControl::intersect(x,y))
	{
		if(!this->isActive)
			this->isActive=true;
	}
	else
	{
		this->isActive=false;
			
	}
}

void TextField::handleKeyDown(char c)
{
	if(this->isActive)
	{
		//backspace
		if((int)c==8)
		{
			string t = this->text.getText();
			if(t.size()>0)
			{
				t.pop_back();
				this->text.setText(t);
			}
		}//enter
		else if((int)c==13)
		{
			this->isActive=false;
		}//add char
		else
		{
			if(this->text.getTextLength()<this->maxChars)
				this->text.setText(this->text.getText()+c);
		}
	}
}
void TextField::setMaxCharLength(int l)
{
	this->maxChars=l;
}
string TextField::getText()
{
	return this->text.getText();
}
bool TextField::isActivated()
{
    return this->isActive;
}
