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


#include "FontInfo.h"

FontInfo::FontInfo()
{
	this->pixWidth=0;
}

FontInfo::~FontInfo()
{

}

vec2 FontInfo::getCharOffset(char c)
{
	return offsets[(int)c];
}
structs::uvPosTranslated FontInfo::getUV(char c)
{
	return this->uvs[(int)c];
}

void FontInfo::init(sf::Image img, string fontFile, int charWidth, int charHeight)
{
	this->charHeight=charHeight;
	this->charWidth=charWidth;
	bool leftFound=false;
	bool rightFound=false;
	int counter=0;
	ifstream file;
	string chars="";
	file.open(fontFile.c_str());
	file >> chars;
	file.close();
	int lazyW=0;
	this->pixWidth=img.getSize().x/charWidth;
	this->pixHeight=img.getSize().y/charHeight;
	

	float leftScale=(float)1/this->getNrCharLeft();
	float upScale=(float)1/this->getNrCharUp();
	for(int k=0;k<this->charHeight;k++)
	{
		for(int i=0;i<this->charWidth;i++)
		{
			//check from left to right
			for(int l=i*(img.getSize().x/this->charWidth);l<(i+1)*(img.getSize().x/this->charWidth)&&!leftFound;l++)
			{
				for(int j=k*(img.getSize().y/this->charHeight);j<(k+1)*(img.getSize().y/this->charHeight)&&!leftFound;j++)
				{
					if(img.getPixel(l,j).a>0)
					{
						leftFound=true;
						if((int)chars[counter]>0&&(int)chars[counter]<128)
						{
							this->offsets[(int)chars[counter]].x=lazyW;
							
							//uv calculation for each letter
							structs::uvPosTranslated uv;
							uv.ll=vec2(i*leftScale,upScale*k);
							uv.ul=vec2(i*leftScale,upScale*(k+1));
							uv.lr=vec2((i+1)*leftScale,upScale*k);
							uv.ur=vec2((i+1)*leftScale,upScale*(k+1));
							this->uvs[(int)chars[counter]] = uv;
						}
					}
				}
				lazyW++;
			}
			lazyW=0;
			//check from right to left
			for(int l=(i+1)*(img.getSize().x/this->charWidth);l>i*(img.getSize().x/this->charWidth)&&!rightFound;l--)
			{
				for(int j=k*(img.getSize().y/this->charHeight);j<(k+1)*(img.getSize().y/this->charHeight)&&!rightFound;j++)
				{
					if(img.getPixel(l,j).a>0)
					{
						rightFound=true;

						if((int)chars[counter]>0&&(int)chars[counter]<128)
						{
							this->offsets[(int)chars[counter]].y=lazyW;
						}
					}
				}
				lazyW++;
			}
			lazyW=0;
			leftFound=false;
			rightFound=false;
			counter++;
		}
	}
	
	//setting up space
	this->offsets[(int)' '].x=this->pixWidth*0.4;
	this->offsets[(int)' '].y=this->pixWidth*0.4;
}
int FontInfo::getNrCharLeft()
{
	return this->charWidth;
}
int FontInfo::getNrCharUp()
{
	return this->charHeight;
}

int FontInfo::getPixWidth()
{
	return this->pixWidth;
}
int FontInfo::getPixHeight()
{
	return this->pixHeight;
}
