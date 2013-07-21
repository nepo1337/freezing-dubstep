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


#ifndef TEXTFIELD_H
#define TEXTFIELD_H
#include "BaseControl.h"
#include "FontInfo.h"
#include "Text.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include "EventTraveller.h"
#include <iostream>

using namespace std;

class TextField : public BaseControl
{
private:
	FontInfo fontInfo;
	Text text;
	bool isActive;
	int maxChars;
public:
	TextField();
	virtual ~TextField();
	void setText(string text);
	void draw(GLSLProgram &shader);
	void create(float x, float y, float w, float h,int id,FontInfo f, GLuint texh);
	void handleKeyDown(char c);
	void setMaxCharLength(int l);
	string getText();
	void handleLeftClick(int x, int y);
};

#endif // TEXTFIELD_H
