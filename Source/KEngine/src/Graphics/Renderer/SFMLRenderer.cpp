#include "../../../include/Graphics/Renderer/SFMLRenderer.hpp"

namespace ke
{

template<> bool SFMLRendererImpl<sf::RenderWindow>::initialise(void)
{
    // Nothing to do here?

    return true;
}

template<> bool SFMLRenderer::prerender(void)
{
    assert(m_spAppWindow);
    this->clear();
    return true;
}

template<> bool SFMLRenderer::postrender(void)
{
    assert(m_spAppWindow);
    m_spAppWindow->display();
    return true;
}

template<> void SFMLRenderer::clear(void)
{
    m_spAppWindow->clear(sf::Color((char)m_BGColour.x, (char)m_BGColour.y, (char)m_BGColour.z, (char)m_BGColour.w));
}

template<> void SFMLRenderer::clear(const Vec4u & p_rColour4)
{
    m_spAppWindow->clear(sf::Color((char)p_rColour4.x, (char)p_rColour4.y, (char)p_rColour4.z, (char)p_rColour4.w));
}

template<> void SFMLRenderer::display(void)
{
    m_spAppWindow->display();
}

template<> void SFMLRenderer::shutDown(void)
{
    m_spAppWindow->close();
}

template<> void SFMLRenderer::setBackgroundColour(const ke::Vec4u & p_rColour4)
{
    m_BGColour = p_rColour4;
}

template<> void SFMLRenderer::setAppWindow(std::shared_ptr<sf::RenderWindow> p_spAppWindow)
{
    assert(p_spAppWindow);
    assert(m_spAppWindow == nullptr);
    m_spAppWindow = p_spAppWindow;
}

} // KE ns