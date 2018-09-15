#include "glrenderer.h"
#include "3rdparty/soil/src/SOIL.h"
#include <cstdio>

GLuint loadTexture(const char *path)
{
    GLuint m_tex_2d = SOIL_load_OGL_texture(
        path,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

    /* check for an error during the load process */
    if (0 == m_tex_2d)
    {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
    }

    return m_tex_2d;
}

void drawTexturedRectangle(const Rect &rect, GLuint tex, BlendingMode bmode)
{
    switch (bmode)
    {
    case BlendingMode::Normal:
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        break;

    case BlendingMode::Additive:
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        break;

    case BlendingMode::None:
    default:
        break;
    }

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(rect.x, rect.y, 0.0f); // Низ лево

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(rect.x + rect.width, rect.y, 0.0f); // Низ право

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(rect.x + rect.width, rect.y + rect.height, 0.0f); // Верх право

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(rect.x, rect.y, 0.0f); // Низ лево

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(rect.x + rect.width, rect.y + rect.height, 0.0f); // Верх право

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(rect.x, rect.y + rect.height, 0.0f); // Верх лево

    glEnd();

    glDisable(GL_TEXTURE_2D);

    glDisable(GL_BLEND);
}
