#include "KEngine/Graphics/Renderer/SfmlRender.hpp"

#include "KEngine/Graphics/SceneNode.hpp"
#include "KEngine/Graphics/SfmlWindow.hpp"

namespace ke
{

bool SfmlRender::initialise(void)
{
    // Nothing to do here?

    return true;
}

void SfmlRender::clear(void)
{
    //
    // Note: maybe we could implement so that all surfaces know how to clear themselves?
    //

    assert(m_spRenderSurface);
    switch (m_spRenderSurface->type())
    {
    case IRenderSurface::Type::Window:
        static_cast<sf::RenderWindow*>(m_spRenderSurface->getInternal())
            ->clear(sf::Color((char)m_BgColour.r, (char)m_BgColour.g, (char)m_BgColour.b, (char)m_BgColour.a));
        break;

    case IRenderSurface::Type::Texture:
        static_cast<sf::RenderTexture*>(m_spRenderSurface->getInternal())
            ->clear(sf::Color((char)m_BgColour.r, (char)m_BgColour.g, (char)m_BgColour.b, (char)m_BgColour.a));
        break;

    default:
        assert(false);
        throw std::runtime_error("invalid surface type.");
        break;
    }
}

void SfmlRender::draw(ke::SceneNodeSptr p_spNode)
{
    //switch (p_spNode->)
}

void SfmlRender::clear(const Vec4u & p_rColour4)
{
    assert(m_spRenderSurface);
    switch (m_spRenderSurface->type())
    {
    case IRenderSurface::Type::Window:
        static_cast<sf::RenderWindow*>(m_spRenderSurface->getInternal())
            ->clear(sf::Color((char)p_rColour4.r, (char)p_rColour4.g, (char)p_rColour4.b, (char)p_rColour4.a));
        break;

    case IRenderSurface::Type::Texture:
        static_cast<sf::RenderTexture*>(m_spRenderSurface->getInternal())
            ->clear(sf::Color((char)p_rColour4.r, (char)p_rColour4.g, (char)p_rColour4.b, (char)p_rColour4.a));
        break;

    default:
        assert(false);
        throw std::runtime_error("invalid surface type."); 
        break;
    }
}

void SfmlRender::display(void)
{
    assert(m_spRenderSurface);
}

void SfmlRender::shutDown(void)
{
    assert(m_spRenderSurface);
}

void SfmlRender::setBackgroundColour(const ke::Vec4u & p_rColour4)
{
    m_BgColour = p_rColour4;
}

void SfmlRender::setRenderSurface(ke::RenderSurfaceSptr p_spRenderSurface)
{
    assert(p_spRenderSurface);
    assert(m_spRenderSurface == nullptr);
    m_spRenderSurface = p_spRenderSurface;
}

void SfmlRender::setAppWindow(ke::WindowSptr p_spAppWindow)
{
    assert(p_spAppWindow);
    assert(m_spRenderSurface == nullptr);
    m_spRenderSurface = p_spAppWindow;
}

} // KE ns