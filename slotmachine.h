#ifndef SLOT_MACHINE_H
#define SLOT_MACHINE_H

#include "singleton.h"
#include "glrenderer.h"

class SlotMachine : public Singleton<SlotMachine>
{
    friend class Singleton<SlotMachine>;

  public:
    void reset();
    int update(double time);
    void draw();

    void mouse(int button, int state, int x, int y);
    void reshape(int width, int height);

  private:
    SlotMachine();

  private:
    Rectangle m_rect;
    GLuint m_tex;
};

#endif /* SLOT_MACHINE_H */