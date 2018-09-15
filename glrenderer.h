#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

struct Rect
{
    float x;
    float y;
    float width;
    float height;

    Rect() : x(0), y(0), width(0), height(0) {}
};

GLuint loadTexture(const char* path);
void drawTexturedRectangle(const Rect &rect, GLuint tex);

#endif /* GL_RENDERER_H */
