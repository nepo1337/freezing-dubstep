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
	void freeOnceInEndOfMain();
	GLuint uploadTextureGFX(sf::Image img);
}
#endif
