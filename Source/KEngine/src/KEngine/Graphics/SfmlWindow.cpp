#include "KEngine/Graphics/SfmlWindow.hpp"

namespace ke
{

void SfmlWindow::display(void)
{
    m_Window.display();
}

void SfmlWindow::clear(const ke::Vec4u & p_rColour4)
{
    m_Window.clear(sf::Color((char)p_rColour4.r, (char)p_rColour4.g, (char)p_rColour4.b, (char)p_rColour4.a));
}

void SfmlWindow::close(void)
{
    m_Window.close();
}

void SfmlWindow::setWindowTitle(std::string p_Title)
{
    m_Window.setTitle(p_Title);
}

bool SfmlWindow::isOpen(void)
{
    return m_Window.isOpen();
}

void * SfmlWindow::getInternal(void)
{
    return &m_Window;
}

bool SfmlWindow::setActive(bool p_Active)
{
    return m_Window.setActive(p_Active);
}

}