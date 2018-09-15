#ifndef TEXMANAGER_H
#define TEXMANAGER_H

#include "singleton.h"
#include "glrenderer.h"
#include <unordered_map>
#include <string>

class TextureManager : public Singleton<TextureManager>
{
    friend class Singleton<TextureManager>;

  public:
    GLuint get(const char* path);

  private:
    TextureManager();
    std::unordered_map<std::string, GLuint> m_store;
};

#endif /* TEXMANAGER_H */
