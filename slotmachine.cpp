#include "slotmachine.h"
#include "texmanager.h"

#include <cstdlib>
#include <cstdio>

SlotMachine::SlotMachine()
    : m_tex(0)
{
    m_tex = TextureManager::getInstance().get("res/parts/back.png");
    m_rect = Rect(0, 0, 960, 640);

    m_tex_shadow = TextureManager::getInstance().get("res/parts/reel_shadow.png");
    m_rect_shadow = Rect(121, 159, 720, 432);

    Wheel::loadImages();
    Rect r(121, 159, 142, 431);
    for (int i = 0; i < 5; ++i)
    {
        m_wheels.push_back(r);
        r.x += 144;
    }

    this->reset();
}
void SlotMachine::reset()
{
    for (auto &wheel : m_wheels)
    {
        wheel.reset();
    }

    m_stop = false;
}
void SlotMachine::stop()
{
    m_stop = true;
}
void SlotMachine::update(double time)
{
    for (auto &wheel : m_wheels)
    {
        wheel.update(time);
    }

    if (m_stop)
    {
        for (auto &wheel : m_wheels)
        {
            if (wheel.speed() > 0)
            {
                wheel.stop();
                break;
            }
        }
    }
}
void SlotMachine::draw()
{
    drawTexturedRectangle(m_rect * m_scale, m_tex);
    for (auto &wheel : m_wheels)
    {
        wheel.draw();
    }
    drawTexturedRectangle(m_rect_shadow * m_scale, m_tex_shadow, BlendingMode::Normal);
}
void SlotMachine::mouse(int button, int state, int x, int y)
{
}
void SlotMachine::reshape(int width, int height)
{
    m_scale.x = (float)width / m_rect.width;
    m_scale.y = (float)height / m_rect.height;
}
