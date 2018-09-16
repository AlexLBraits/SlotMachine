#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

struct Vec2
{
    float x;
    float y;

    Vec2() : x(0), y(0) {}
};

struct Rect
{
    int x;
    int y;
    int width;
    int height;

    Rect(float x = 0, float y = 0, float width = 0, float height = 0) 
        : x(x), y(y), width(width), height(height) {

        }
    Rect operator*(const Vec2& v) {
        Rect r;
        r.x = x * v.x;
        r.y = y * v.y;
        r.width = width * v.x;
        r.height = height * v.y;        
        return r;
    }
};

GLuint loadTexture(const char* path);

enum class BlendingMode {
    None,
    Normal,
    Additive
};

void drawTexturedRectangle(const Rect &rect, GLuint tex, BlendingMode bmode);

struct Quad
{
    Rect m_rect;
    GLuint m_tex;

    void draw(const Vec2& scale, BlendingMode bmode = BlendingMode::None)
    {
        drawTexturedRectangle(m_rect * scale, m_tex, bmode);
    }
};

#endif /* GL_RENDERER_H */
