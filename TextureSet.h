#ifndef TEXTURESET_H
#define TEXTURESET_H
#include <GL/glew.h>
#include <vector>
#include <string>


using namespace std;
class TextureSet
{
private:
	GLuint tex1,tex2,tex3,tex4;
	string name1,name2,name3,name4,path,textureSetname;
	vector<GLuint> texHandels;
public:
	TextureSet();
	~TextureSet();
	void create(string path, string tsn, string n1, string n2, string n3, string n4);
	void setTextureIDs(GLuint t1, GLuint t2, GLuint t3, GLuint t4);
	GLuint getTex1H();
	GLuint getTex2H();
	GLuint getTex3H();
	GLuint getTex4H();
	string getTex1Name();
	string getTex2Name();
	string getTex3Name();
	string getTex4Name();
	vector<GLuint> getTexHandles();
	string getPath();
	string getTextureSetName();

};
#endif
