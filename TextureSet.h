#ifndef TEXTURESET_H
#define TEXTURESET_H
#include <GL/glew.h>
#include <vector>
#include <string>


using namespace std;
class TextureSet
{
private:
	string path,textureSetname;
	vector<GLuint> texHandels;
	vector<string> textureNames;
public:
	TextureSet();
	~TextureSet();
	void create(string path, string tsn);
	GLuint getTexHandle(int i);
	GLuint getTexHandle(string s);
	void addTexture(GLuint t,string name);
	vector<GLuint> getTexHandles();
	string getPath();
	string getTextureSetName();
	void freeTextures();
};
#endif
