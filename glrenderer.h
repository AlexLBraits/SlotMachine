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

    Vec2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
};

struct Rect
{
    int x;
    int y;
    int width;
    int height;

    Rect(float x = 0, float y = 0, float width = 0, float height = 0)
        : x(x), y(y), width(width), height(height)
    {
    }
    Rect operator*(const Vec2 &v)
    {
        Rect r;
        r.x = x * v.x;
        r.y = y * v.y;
        r.width = width * v.x;
        r.height = height * v.y;
        return r;
    }
    bool contains(float x, float y) 
    {
        return (x >= this->x && x < this->x + this->width) &&
                (y >= this->y && y < this->y + this->height);
    }
};

GLuint loadTexture(const char *path);

enum class BlendingMode
{
    None,
    Normal,
    Additive
};

struct Color
{
    float r;
    float g;
    float b;
    float a;
    Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
};

void drawTexturedRectangle(const Rect &rect, GLuint tex, const Color &color, BlendingMode bmode);

struct Quad
{
    Rect m_rect;
    GLuint m_tex;

    void draw(const Vec2 &scale,
              BlendingMode bmode = BlendingMode::None,
              const Color &color = Color())
    {
        drawTexturedRectangle(m_rect * scale, m_tex, color, bmode);
    }
};

#endif /* GL_RENDERER_H */
