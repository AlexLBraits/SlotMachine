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
    enum class State
    {
      idle,
      working,
      stops
    };

    void reset();
    void stop();
    void update(double time);
    void draw();

    void mouse(int button, int state, int x, int y);
    void reshape(int width, int height);

    Vec2 scale() const {return m_scale;}
    State state() const {return m_state;}

  private:
    SlotMachine();

  private:
    State m_state;
    Vec2 m_scale;
    Rect m_rect;    
    GLuint m_tex;
    Rect m_rect_shadow;
    GLuint m_tex_shadow;
    std::vector<Wheel> m_wheels;
};

#endif /* SLOT_MACHINE_H */