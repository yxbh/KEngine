#pragma once
#include "Types.hpp"
#include "../../Utility/NonCopyable.hpp"
#include "../../Common/Geometry.hpp"

namespace ke
{


/** \class IRenderer

    Interface for implementing a Renderer...

*/
class IRenderer
    : public ke::NonCopyable
{
public:
    virtual ~IRenderer(void) = default;

    /** Render initialisation. */
    virtual bool initialise(void) = 0;
    /** Call before rendering a single frame. */
    virtual bool prerender(void) = 0;
    /** Call after rendering a single frame. */
    virtual bool postrender(void) = 0;
    /** Clear the screen/framebuffer. */
    virtual void clear(void) = 0;
    /** Clear the screen/framebuffer with specified color. Disregarding internal background colour setting. (This does not change the setting). */
    virtual void clear(const Vec4u & p_rColour4) = 0;
    /** Swap framebuffer. */
    virtual void display(void) = 0;
    /** Shut down render system. */
    virtual void shutDown(void) = 0;
    /** Set the colour of clear buffer to a vec3 of unsigned. (range 0~255) */
    virtual void setBackgroundColour(const ke::Vec4u & p_rColour4) = 0;


}; // IRenderer class


/** \class

    Interface for implementing a Renderer...

    Develop note:
        A second level of the interface is necessary to have pointers pointing to different
        implementations of Renderer while allowing the following member functions to be called
        with out the need for an explicit cast.

*/
template<class RendererType>
class IIRenderer // interface of an interface.
    : public IRenderer
{
public:
    virtual ~IIRenderer(void) = default;

    /** Return a reference to the internal renderer/application-window. */
    virtual RendererType & get(void) = 0;
}; // IIRenderer class

} // KE ns