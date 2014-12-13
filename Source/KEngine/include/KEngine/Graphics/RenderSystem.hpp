#pragma once

#include "KEngine/System/ISystem.hpp"

#include "KEngine/App/Types.hpp"
#include "KEngine/Graphics/Types.hpp"
#include "KEngine/Graphics/Renderer/Types.hpp"

namespace ke
{

/** 
    \class IRenderSystem
    \brief A system controlling the rendering of the engine's views.
*/
class IRenderSystem
    : public ke::ISystem
{
protected:
    ke::RenderSptr m_spRender;
    ke::WindowSptr m_spMainWindow;

public:
    /** Set the main application window for rendering. */
    virtual void setMainWindow(ke::WindowSptr p_spWindow);
    /** Set the render used for rendering. */
    virtual void setRender(ke::RenderSptr p_spRender);

    virtual ke::IWindow * getMainWindow(void);
    virtual ke::IRender * getRender(void);

    /** Prepare the system for rendering. Call before rendering views. */
    virtual bool prepareRender(void) = 0;
    /** Render the given view. */
    virtual void render(ke::ViewSptr p_spView, ke::Time p_Elapsed) = 0;
    /** Finalise the render process and display to screen. Call after rendering all views. */
    virtual bool finaliseRender(void) = 0;

};

class SfmlRenderSystem
    : public ke::IRenderSystem
{
public:
    virtual bool initialise(void) final;
    /** \return true if the System has shut down correctly. */
    virtual bool shutDown(void) final;
    /** Return the name of the system. */
    virtual std::string getName(void) const final { return "render system"; }

    /** Prepare the system for rendering. Call before rendering views. */
    virtual bool prepareRender(void) final;
    /** Render the given view. */
    virtual void render(ke::ViewSptr p_spView, ke::Time p_Elapsed) final;
    /** Finalise the render process and display to screen. Call after rendering all views. */
    virtual bool finaliseRender(void) final;
    
    virtual void handleEvent(const ke::EventSptr p_spEvent) final;
};

}
