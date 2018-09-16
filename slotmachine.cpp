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

    m_button.m_rect = Rect(647, 20, 197, 82);
    m_button.m_tex = TextureManager::getInstance().get("res/parts/spin.png");
    m_alpha_speed = -0.002;

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

    /// анимация цвета кнопки (альфа-канала)
    m_button_color.a += m_alpha_speed * time;
    if (m_button_color.a > 1.0f || m_button_color.a < 0.3f)
    {
        m_alpha_speed = -m_alpha_speed;
    }
    m_button_color.a = std::max(0.3f, std::min(1.0f, m_button_color.a));
}
void SlotMachine::draw()
{
    m_back.draw(m_scale);
    for (auto &wheel : m_wheels)
    {
        wheel.draw(m_scale);
    }
    m_shadow.draw(m_scale, BlendingMode::Normal);

    if (m_state == SlotMachine::State::idle)
    {
        /// если машина простаивает, рисуем кнопку SPIN
        m_button.draw(m_scale, BlendingMode::Normal, m_button_color);
    }
}
void SlotMachine::mouse(int button, int state, int x, int y)
{
}
void SlotMachine::reshape(int width, int height)
{
    m_scale.x = (float)width / m_back.m_rect.width;
    m_scale.y = (float)height / m_back.m_rect.height;
}
