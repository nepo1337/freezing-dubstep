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


#include "Text.h"

Text::Text()
{
	this->VAOh=this->VBOuvh=this->VBOvh=0;
	this->color=vec4(1.0f);
	this->scale=0;
	this->spacing=3;
}

Text::~Text()
{
	glDeleteBuffers(1,&this->VBOvh);
	glDeleteBuffers(1,&this->VBOuvh);
	glDeleteVertexArrays(1,&this->VAOh);
}

void Text::create(int x, int y, float scale,FontInfo f, GLuint tex,string text)
{
	this->scale=scale;
	this->fontInfo=f;
	this->texH=tex;
	this->text=text;
	glDeleteBuffers(1,&this->VBOvh);
	glDeleteBuffers(1,&this->VBOuvh);
	glDeleteVertexArrays(1,&this->VAOh);
	
	this->x=x;
	this->y=y;
	int pixWidth=fontInfo.getPixWidth()*this->scale;
	int pixHeight= fontInfo.getPixHeight()*this->scale;
	vector<float> verts;
	int spaceBuffer=0;

	for(int i=0;i<this->text.size();i++)
	{
		spaceBuffer+=-this->fontInfo.getCharOffset(this->text[i]).x*this->scale;
		verts.push_back(this->x+spaceBuffer);
		verts.push_back(this->y);
		verts.push_back(0);
		
		verts.push_back(this->x+spaceBuffer);
		verts.push_back(this->y+pixHeight);
		verts.push_back(0);
		
		verts.push_back(this->x+pixWidth+spaceBuffer);
		verts.push_back(this->y);
		verts.push_back(0);
		
		verts.push_back(this->x+pixWidth+spaceBuffer);
		verts.push_back(this->y+pixHeight);
		verts.push_back(0);
		
		verts.push_back(this->x+pixWidth+spaceBuffer);
		verts.push_back(this->y);
		verts.push_back(0);
		
		verts.push_back(this->x+spaceBuffer);
		verts.push_back(this->y+pixHeight);
		verts.push_back(0);
		
		spaceBuffer+=pixWidth-this->fontInfo.getCharOffset(this->text[i]).y*this->scale+spacing;
	}
	
	vector<float> uvs;
	for(int i=0;i<this->text.size();i++)
	{
		structs::uvPosTranslated uv;
		uv = this->fontInfo.getUV(this->text[i]);
		uvs.push_back(uv.ll.x);
		uvs.push_back(uv.ll.y);
		uvs.push_back(uv.ul.x);
		uvs.push_back(uv.ul.y);
		uvs.push_back(uv.lr.x);
		uvs.push_back(uv.lr.y);
		uvs.push_back(uv.ur.x);
		uvs.push_back(uv.ur.y);
		uvs.push_back(uv.lr.x);
		uvs.push_back(uv.lr.y);
		uvs.push_back(uv.ul.x);
		uvs.push_back(uv.ul.y);
	}
	glGenVertexArrays(1,&this->VAOh);
	glBindVertexArray(this->VAOh);
	glGenBuffers(1,&this->VBOvh);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBOvh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*verts.size(),&verts.front(),GL_STATIC_DRAW);
	
	glGenBuffers(1,&this->VBOuvh);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBOuvh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*uvs.size(),&uvs.front(),GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER,this->VBOvh);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
	
	glBindBuffer(GL_ARRAY_BUFFER,this->VBOuvh);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,NULL);
	glBindVertexArray(0);
	
}
void Text::draw(GLSLProgram& shader)
{
	glBindVertexArray(this->VAOh);
	glBindTexture(GL_TEXTURE_2D,this->texH);
	shader.setUniform("color",this->color);
	shader.setSubroutine(GLSLShader::FRAGMENT, "texOut");
	glDrawArrays(GL_TRIANGLES,0,6*this->text.size());
}
string Text::getText()
{
	return this->text;
}
int Text::getTextLength()
{
	return this->text.size();
}
void Text::setText(string text)
{
	this->create(this->x,this->y,this->scale,this->fontInfo,this->texH,text);
}

void Text::setFontTexture(GLuint textH)
{
	this->texH=textH;
}
void Text::setSpacing(float f)
{
	this->spacing=f;
}