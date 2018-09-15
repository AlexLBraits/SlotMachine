#include "wheel.h"
#include "texmanager.h"
#include "slotmachine.h"
#include <algorithm>

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

Wheel::Wheel(const Rect &rect) : m_rect(rect)
{
    m_cells.resize(10);
    for (int i = 0; i < 10; ++i)
    {
        m_cells[i].m_id = i;
    }
    std::random_shuffle(m_cells.begin(), m_cells.end());
}
int Wheel::update(double time)
{
    return 1;
}
void Wheel::draw()
{
    glEnable(GL_SCISSOR_TEST);
    Rect sr = m_rect * SlotMachine::getInstance().getScale(); 
    glScissor(sr.x, sr.y, sr.width, sr.height);

    Rect r = Rect(m_rect.x, m_rect.y - 72, 144, 144) * SlotMachine::getInstance().getScale();
    for (int i = 0; i < 4; ++i)
    {
        drawTexturedRectangle(r, Wheel::images[m_cells[i].m_id]);
        r.y += r.height;
    }
    glDisable(GL_SCISSOR_TEST);
}
void Wheel::reset()
{
}
