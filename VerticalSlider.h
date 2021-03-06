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


#ifndef VERTICALSLIDER_H
#define VERTICALSLIDER_H
#include "BaseControl.h"
#include "Button.h"
#include <iostream>
class VerticalSlider : public BaseControl
{
private:
	Button scrollButton;
	float bVal;
	bool hasScrollButtonTriTex;
	GLuint scrollButtonTex;
public:
	VerticalSlider();
	virtual ~VerticalSlider();
	void create(float x, float y, float w, float h);
	void draw(GLSLProgram &shader);
	void setBackgroundColor(vec4 c);
	void setFrameColor(vec4 c);
	void updateCollisionRect(float x, float y);
	float getNormalizedSliderValue();
	void setNormalizedSliderValue(float f);
	void setScrollButtonTexture(GLuint tex);
	void setScrollButtonTriTexture(GLuint tex);
	void hideScrollButtonFrame();
	void setScrollButtonBackgroundColor(vec4 c);
	void setScrollButtonFrameColor(vec4 c);
	void handleLeftClick(int x, int y);
	bool mouseHover(int x, int y);
	void leftMBTNReleased();
	void hide();
	void show();
};

#endif // VERTICALSLIDER_H
