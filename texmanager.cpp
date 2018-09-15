#include "texmanager.h"
#include "glrenderer.h"

TextureManager::TextureManager()
{
}
GLuint TextureManager::get(const char *path)
{
    auto fr = m_store.find(path);
    if (fr != m_store.end()) return fr->second;
    auto ii = m_store.emplace(path, loadTexture(path));
    return ii.second ? ii.first->second : 0;
}
