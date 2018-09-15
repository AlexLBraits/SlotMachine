#include "wheel.h"
#include "texmanager.h"
#include "slotmachine.h"
#include <algorithm>
#include <random>

float getRandomSpeed()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(0.15, 0.75);
    return dis(gen) * 3.0;
}

GLuint Wheel::images[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void Wheel::loadImages()
{
    images[0] = TextureManager::getInstance().get("res/symbols/1.png");
    images[1] = TextureManager::getInstance().get("res/symbols/2.png");
    images[2] = TextureManager::getInstance().get("res/symbols/3.png");
    images[3] = TextureManager::getInstance().get("res/symbols/4.png");
    images[4] = TextureManager::getInstance().get("res/symbols/5.png");
    images[5] = TextureManager::getInstance().get("res/symbols/6.png");
    images[6] = TextureManager::getInstance().get("res/symbols/7.png");
    images[7] = TextureManager::getInstance().get("res/symbols/8.png");
    images[8] = TextureManager::getInstance().get("res/symbols/9.png");
    images[9] = TextureManager::getInstance().get("res/symbols/10.png");
}

Wheel::Wheel(const Rect &rect) 
: m_rect(rect), m_offset(0), m_speed(0), m_pos(0)
{
    m_cells.resize(10);
    for (int i = 0; i < 10; ++i)
    {
        m_cells[i].m_id = i;
    }
    std::random_shuffle(m_cells.begin(), m_cells.end());
}
void Wheel::update(double time)
{
    m_offset += m_speed * time;
    if (m_offset > CELL_SIZE)
    {
        m_offset = 0;
        m_pos = _next(m_pos);
        if (m_stop) m_speed = 0;
    }
}
void Wheel::draw()
{
    glEnable(GL_SCISSOR_TEST);
    Vec2 scale = SlotMachine::getInstance().scale();
    Rect sr = m_rect * scale;
    glScissor(sr.x, sr.y, sr.width, sr.height);

    Rect r = Rect(m_rect.x, m_rect.y - m_offset, CELL_SIZE, CELL_SIZE) * scale;
    for (int i = 0, p = m_pos; i < 4; ++i, p = _next(p))
    {
        drawTexturedRectangle(r, Wheel::images[m_cells[p].m_id]);
        r.y += r.height;
    }
    glDisable(GL_SCISSOR_TEST);
}
void Wheel::reset()
{
    m_pos = 0;
    m_speed = getRandomSpeed();
    m_stop = false;
}
