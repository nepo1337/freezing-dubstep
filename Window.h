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


#ifndef WINDOW_H
#define WINDOW_H
#include "BaseControl.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <vector>
#include <iostream>
#include "FontInfo.h"

using namespace glm;
using namespace std;
class Window : public BaseControl
{
private:
	vector<BaseControl*> controls;
	mat4 modelMatrix;
	vec3 pos;
	vec2 lastClickOffset;
	
public:
	Window();
	virtual ~Window();
	void addControl(BaseControl &c);
	void draw(GLSLProgram &shader);
	void handleLeftClick(int x, int y);
	void handleLeftRelease();
	void setPosition(vec2 p);
	vec2 getPosition();
	void create(float x, float y, float w, float h);
	void handleKeyDown(char c);
	bool mouseHover(int x, int y);
	vec2 getClickOffset();
	bool checkTextfieldsActive();
};

#endif // WINDOW_H
