#include "slotmachine.h"
#include "texmanager.h"

#include <cstdlib>
#include <cstdio>

SlotMachine::SlotMachine()
    : m_state(State::idle)
{
    m_back.m_rect = Rect(0, 0, 960, 640);
    m_back.m_tex = TextureManager::getInstance().get("res/parts/back.png");

    m_shadow.m_rect = Rect(121, 159, 720, 432);
    m_shadow.m_tex = TextureManager::getInstance().get("res/parts/reel_shadow.png");

    Rect r(121, 159, 142, 431);
    for (int i = 0; i < 5; ++i)
    {
        m_wheels.push_back(r);
        r.x += 144;
    }
}
void SlotMachine::reset()
{
    for (auto &wheel : m_wheels)
    {
        wheel.reset();
    }
    m_state = State::working;
}
void SlotMachine::stop()
{
    m_state = State::idle;
    for (auto &wheel : m_wheels)
    {
        if (wheel.speed() > 0)
        {
            wheel.stop();
            m_state = State::stops;
            break;
        }
    }
}
void SlotMachine::update(double time)
{
    for (auto &wheel : m_wheels)
    {
        wheel.update(time);
    }
}
void SlotMachine::draw()
{
    // drawTexturedRectangle(m_rect * m_scale, m_tex);
    m_back.draw(m_scale);
    for (auto &wheel : m_wheels)
    {
        wheel.draw(m_scale);
    }
    // drawTexturedRectangle(m_rect_shadow * m_scale, m_tex_shadow, BlendingMode::Normal);
    m_shadow.draw(m_scale, BlendingMode::Normal);
}
void SlotMachine::mouse(int button, int state, int x, int y)
{
}
void SlotMachine::reshape(int width, int height)
{
    m_scale.x = (float)width / m_back.m_rect.width;
    m_scale.y = (float)height / m_back.m_rect.height;
}
