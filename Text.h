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


#ifndef TEXT_H
#define TEXT_H
#include <iostream>
#include "GLSLProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <vector>
#include "TextureHandler.h"
#include "FontInfo.h"

#include <GL/glew.h>

using namespace std;
using namespace glm;

class Text
{
private:
	string text;
	FontInfo fontInfo;
	GLuint VAOh,VBOvh,VBOuvh,texH;
	int x,y;
	float scale;
	vec4 color;
	struct uvPosTranslated
	{
		public:
			vec2 ll,ul,lr,ur;
	};
	uvPosTranslated translateChar(char c);
public:
    Text();
    virtual ~Text();
    void create(int x, int y, float scale,FontInfo f, GLuint tex,string text);
    void setText(string text);
    string getText();
    int getTextLength();
    void draw(GLSLProgram &shader);
    void setColor(vec4 c);
};

#endif // TEXT_H
