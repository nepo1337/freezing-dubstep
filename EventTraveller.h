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


#ifndef EVENTTRAVELLER_H
#define EVENTTRAVELLER_H
#include <glm/glm.hpp>

namespace EventType
{
	enum code
	{
		NONE,LEFT_MOUSE_CLICK,LEFT_MOUSE_RELEASE,RIGHT_MOUSE_CLICK,RIGHT_MOUSE_RELEASED,
		KEY_PRESSED,KEY_RELEASED
	};
};

using namespace glm;

class EventTraveller
{
private:
	int id;
	EventType::code type;
	vec2 offset;
public:
	EventTraveller();
	EventTraveller(EventType::code e, int id);
	virtual ~EventTraveller();
	EventType::code getEventType();
	int getID();
	void setID(int id);
	void setEventType(EventType::code e);
	void setOffset(vec2 o);
	vec2 getOffset();
	bool hasValidID();
};

#endif // EVENTTRAVELLER_H
