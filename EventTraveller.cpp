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


#include "EventTraveller.h"
EventTraveller::EventTraveller()
{
	this->id=-1;
	this->type=EventType::NONE;
	this->offset=vec2(-1.0f);
}

EventTraveller::EventTraveller(EventType::code e, int id)
{
	this->type = e;
	this->id=id;
	this->offset=vec2(-1.0f);
}

EventTraveller::~EventTraveller()
{

}

EventType::code EventTraveller::getEventType()
{
	return this->type;
}
int EventTraveller::getID()
{
	return this->id;
}
void EventTraveller::setEventType(EventType::code e)
{
	this->type=e;
}
void EventTraveller::setID(int id)
{
	this->id=id;
}
vec2 EventTraveller::getOffset()
{
	return this->offset;
}
void EventTraveller::setOffset(vec2 o)
{
	this->offset=o;
}
bool EventTraveller::hasValidID()
{
	return this->id>=0;
}