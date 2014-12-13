#pragma once

#include "KEngine/Graphics/Types.hpp"
#include "KEngine/Common/Geometry.hpp"
#include "KEngine/Utility/NonCopyable.hpp"

namespace ke
{


/**
    \class IRender
    \brief Interface for implementing a Renderer. The sole purpose of a render is to 
           draw contents of a scene node to the render target (a surface or window).
*/
class IRender
    : public ke::NonCopyable
{
public:
    virtual ~IRender(void) = default;

    /** Render initialisation. */
    virtual bool initialise(void) = 0;
    /** Draw the specified node to the internal target. */
    virtual void draw(ke::SceneNodeSptr p_spNode) = 0;
    /** Clear the screen/framebuffer. */
    virtual void clear(void) = 0;
    /** Clear the screen/framebuffer with specified color. Disregarding internal background colour setting. (This does not change the setting). */
    virtual void clear(const Vec4u & p_rColour4) = 0;
    /** Swap framebuffer. */
    virtual void display(void) = 0;
    /** Shut down render system. */
    virtual void shutDown(void) = 0;
    /** Set the colour of clear buffer to a vec3 of unsigned. (range 0~255) */
    virtual void setBackgroundColour(const ke::Vec4u & p_rColour4 = ke::Vec4u(0, 0, 0, 255)) = 0;

    /** Set the render surface for the render. */
    virtual void setRenderSurface(ke::RenderSurfaceSptr p_spRenderSurface) = 0;

}; // IRenderer class

} // KE ns