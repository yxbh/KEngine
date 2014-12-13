#pragma once

#include "KEngine/engine_common.hpp"
#include "KEngine/Graphics/Renderer/IRender.hpp"

namespace ke
{

/**
    \class SfmlRender
    \brief A render implementation that renders to a SFML render target based object.
*/
class SfmlRender final
    : public IRender
{
private:
    ke::Vec4u               m_BgColour          = Vec4u(255, 0, 255, 255);       // colour the framebuffer is cleared to.
    ke::RenderSurfaceSptr   m_spRenderSurface   = nullptr;

public:
    SfmlRender(void) = default;
    virtual ~SfmlRender(void) = default;

    /** Render initialisation. */
    virtual bool initialise(void) final;
    /** Draw the specified node to the internal target. */
    virtual void draw(ke::SceneNodeSptr p_spNode) final;
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

    virtual void setRenderSurface(ke::RenderSurfaceSptr p_spRenderSurface) final;
    virtual void setAppWindow(ke::WindowSptr p_spAppWindow);

}; // SFMLRendererImpl class

} // KE ns
