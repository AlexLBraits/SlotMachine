#include "slotmachine.h"

#include <cstdlib>
#include <cstdio>

SlotMachine::SlotMachine()
    : m_tex(0)
{
    m_tex = loadTexture("res/parts/back.png");
}
void SlotMachine::reset()
{
}
int SlotMachine::update(double time)
{
    return 1;
}
void SlotMachine::draw()
{
    drawTexturedRectangle(m_rect, m_tex);
}
void SlotMachine::mouse(int button, int state, int x, int y)
{
}
void SlotMachine::reshape(int width, int height)
{
    m_rect.width = width;
    m_rect.height = height;
}
