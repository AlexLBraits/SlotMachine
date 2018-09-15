#ifndef WHEEL_H
#define WHEEL_H

#include "glrenderer.h"
#include <vector>

struct Cell
{
    int m_id;
    Rect m_rect;
    Cell() : m_id(0)
    {
        m_rect.x = 0;
        m_rect.y = 0;
        m_rect.width = 144;
        m_rect.height = 144;
    }
};

class Wheel
{
    static GLuint images[10];

  public:
    static void loadImages();

    Wheel(const Rect &rect);
    int update(double time);
    void draw();
    void reset();

  private:
    Rect m_rect;
    std::vector<Cell> m_cells;
};

#endif /* WHEEL_H */
