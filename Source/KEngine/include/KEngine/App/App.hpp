#pragma once

#include "KEngine/App/Types.hpp"
#include "KEngine/Common/Geometry.hpp"
#include "KEngine/Common/Time.hpp"
#include "KEngine/Utility/NonCopyable.hpp"
#include "KEngine/Graphics/Types.hpp"
#include "KEngine/Graphics/Renderer/Types.hpp"
#include "KEngine/Event/IEventHandler.hpp"

#include "KEngine/engine_common.hpp"

namespace ke
{

class LuaStateManager; // TODO : waitting for concrete implementation.

/**
    \class App
    \brief A base class for implementing the application layer of KEngine.

    Inherit this class and provide overloads for \a initialise() and \a createLogicAndViews() for custom initialisation, resource loading and log.
*/
class App
    : public ke::NonCopyable
    , public ke::IEventHandler
{
protected:
    /* application states */
    std::atomic_bool    m_IsRunning;
    std::atomic_bool    m_ExitRequested;
    std::atomic_bool    m_IsExiting;

    /* engine/game logic */
    ke::LogicUptr      m_upLogic       = nullptr;

    /* render related. */
    Vec2u                       m_WindowSize        = { 860, 640 };
    Vec2u                       m_ViewportSize      = { 860, 640 };
    bool                        m_InWindowedMode    = true;
    ke::WindowSptr              m_spAppWindow       = nullptr; // TODO : let render system control life time?
    ke::RenderSptr              m_spRender          = nullptr; // TODO : let render system control life time?
    ke::RenderSystemSptr        m_spRenderSystem    = nullptr; // TODO : let render system control life time?

public:
    App(void);
    virtual ~App(void) = 0;

    //// Initialisation methods.
    /** Initialisation. NOTE: Call this method from child class if this method is going to be overloaded!*/
    virtual bool initialise(void);
    virtual bool shutDown(void);
    /** Activate the rendering context on the current thread. */
    virtual bool activateGlContext(void);
    /** Deactivate the rendering context on the current thread. */
    virtual bool deactivateGlContext(void);
    /** */
    virtual ke::LogicUptr createLogicAndViews(void) = 0;
    /** Carry out any necessary loading. */
    virtual bool load(void);
    ////

    //// Running methods (mainloop processing).
    /** Call update on the global EventManager and internal Logic object. */
    void updateApp(const ke::Time p_Elapsed);
    /** Render the logic's current View?. */
    void renderApp(const ke::Time p_Elapsed);
    /** Returns true if the app instance is operating normally. */
    bool isRunning(void) const;
    /** Returns true if the app instance is exiting. */
    bool isExiting(void) const;
    /** Sets the internal quit flag to true. Begins the exiting procudures. */
    void setQuitting(const bool p_Quitting = true);
    /** */
    void abort(void);
    ////

    //// Getters (non-virtual).
    ke::Logic * const getLogic(void);
    ke::IView * const getHumanView(void);
    ke::IRender * const getRenderer(void);
    ////

    ////
    virtual void registerEventListener(void) override;
    virtual void deregisterEventListener(void) override;
    virtual void handleEvent(const ke::EventSptr p_spEvent) override;
    ////

}; // KEApp class


} // KE ns