#ifndef WHEEL_H
#define WHEEL_H

#include "glrenderer.h"
#include <vector>

#define CELL_SIZE 144

struct Cell : public Quad
{
    static const char* image_names[10];

    Cell()
    {
        m_tex = 0;
        m_rect.x = 0;
        m_rect.y = 0;
        m_rect.width = CELL_SIZE;
        m_rect.height = CELL_SIZE;
    }
};

class Wheel
{
  public:
    Wheel(const Rect &rect);
    void update(double time);
    void draw(const Vec2& scale);
    void reset();

    float speed() const {return m_speed;}
    void stop() {m_stop = true;}

  private:
    Rect m_rect;
    std::vector<Cell> m_cells;
    int m_pos;
    int m_offset;
    float m_speed;
    bool m_stop;

    int _next(int pos) const {
        return pos + 1 < m_cells.size() ? pos + 1 : 0;
    }
};

#endif /* WHEEL_H */
