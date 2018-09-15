#ifndef SLOT_MACHINE_H
#define SLOT_MACHINE_H

#include "singleton.h"
#include "glrenderer.h"
#include "wheel.h"
#include <vector>

class SlotMachine : public Singleton<SlotMachine>
{
    friend class Singleton<SlotMachine>;

  public:
    void reset();
    void stop();
    void update(double time);
    void draw();

    void mouse(int button, int state, int x, int y);
    void reshape(int width, int height);

    Vec2 getScale() const {return m_scale;};

  private:
    SlotMachine();

  private:
    Vec2 m_scale;

    Rect m_rect;    
    GLuint m_tex;

    Rect m_rect_shadow;
    GLuint m_tex_shadow;

    std::vector<Wheel> m_wheels;
    bool m_stop;
};

#endif /* SLOT_MACHINE_H */