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


#ifndef BASECONTROL_H
#define BASECONTROL_H
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <GL/glew.h>
#include "GLSLProgram.h"
#include <iostream>

using namespace std;
using namespace glm;

class BaseControl
{
protected:
	vec4 collisionRect;
	bool visible,frameVisible;
	float x,y,width,height;
	GLuint VAOh,VBOh,VBOuh,VBO2uh,VBO3uh,texHandle;
	vec4 bgColor,frameColor;
	bool hasTex,hasTriTex,mouseOver,mouseButtonDown,released, isActive;
public:
	BaseControl();
	virtual ~BaseControl()=0;
    
	virtual void setBackgroundColor(vec4 c);
	virtual void setFrameColor(vec4 c);
	vec4 getCollisionRect();
	vec4 getBackgroundColor();
	vec4 getFrameColor();
	void setCollisionRect(vec4 rect);
	virtual void updateCollisionRect(float x,float y);
	virtual void draw(GLSLProgram &shader);
	virtual void hide();
	virtual void hideFrame();
	virtual void showFrame();
	virtual void show();
	virtual void create(float x, float y, float w, float h);
	virtual bool intersect(int x, int y);
	virtual void leftMBTNReleased();
	virtual void setTexture(GLuint texH);
	virtual void setTriTexture(GLuint texH);
	virtual void handleKeyDown(char c);
	virtual bool mouseHover(int x, int y);
	virtual void handleLeftClick(int x, int y);
	virtual bool isDown();
	virtual bool wasReleased();
	virtual bool isActivated();
	
};

#endif // BASECONTROL_H
