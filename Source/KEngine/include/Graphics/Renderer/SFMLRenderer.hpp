#pragma once
#include "../../engine_common.hpp"
#include "IRenderer.hpp"

namespace ke
{


/** \class SFMLRenderer
*/
template <class RendererType = sf::RenderWindow>
class SFMLRendererImpl
    : public IIRenderer<RendererType>
{
private:
    ke::Vec4u                               m_BGColour          = Vec4u(255, 0, 255, 255);       // colour the framebuffer is cleared to.
    std::shared_ptr<sf::RenderWindow>       m_spAppWindow = nullptr;

public:
    SFMLRendererImpl(void) = default;
    virtual ~SFMLRendererImpl(void) = default;

    /** Render initialisation. */
    virtual bool initialise(void) final;
    /** Call before rendering a single frame. */
    virtual bool prerender(void) final;
    /** Call after rendering a single frame. */
    virtual bool postrender(void) final;
    /** Clear the screen/framebuffer. */
    virtual void clear(void) final;
    /** Clear the screen/framebuffer with specified color. Disregarding internal background colour setting. (This does not change the setting). */
    virtual void clear(const Vec4u & p_rColour4) final;
    /** Swap framebuffer. */
    virtual void display(void) final;
    /** Shut down render system. */
    virtual void shutDown(void) final;
    /** Set the colour of clear buffer to a vec3 of unsigned. (range 0~255) */
    virtual void setBackgroundColour(const ke::Vec4u & p_rColour4 = ke::Vec4u(0,0,0,255)) final;

    void setAppWindow(std::shared_ptr<sf::RenderWindow> p_spAppWindow);
    /** */
    RendererType & get(void) final
    {
        assert(m_spAppWindow);
        return *m_spAppWindow;
    };

}; // SFMLRendererImpl class


/** \class SFMLRenderer
*/
using SFMLRenderer = SFMLRendererImpl<sf::RenderWindow>;


} // KE ns

//#include "../../../src/Graphics/Renderer/SFMLRenderer.cpp"