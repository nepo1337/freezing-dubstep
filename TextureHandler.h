#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H
#include "TextureSet.h"
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

namespace TextureHandler
{
	bool addTextureSet(TextureSet set);
	TextureSet getTextureSet(int index);
	TextureSet getTextureSet(string name);
	GLuint uploadTextureGFX(sf::Image img);
	GLuint uploadSimpleTexNearest(sf::Image img);
	GLuint uploadSimpleTexLinear(sf::Image img);
}
#endif
