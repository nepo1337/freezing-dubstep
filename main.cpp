#include <iostream>
#include "MeshData.h"
#include "TextureHandler.h"
#include "Editor.h"

int main(int argc, char **argv)
{
    Editor editor;
    
    editor.run();
    TextureHandler::freeOnceInEndOfMain();
    MeshData::free();
    return 0;
}
