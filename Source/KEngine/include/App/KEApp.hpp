#pragma once
#include "../engine_common.hpp"
#include "Types.hpp"
#include "../Common/Geometry.hpp"
#include "../Common/Time.hpp"
#include "../Utility/NonCopyable.hpp"
#include "KELogic.hpp" // required by default dtor?
#include "../Graphics/Renderer/Types.hpp"
#include "../Event/IEventHandler.hpp"

namespace ke
{

class LuaStateManager; // TODO : waitting for concrete implementation.

/** \class KEApp
    \brief A base class for implementing the application layer of KEngine.

    Inherit this class and provide overloads for \a initialise() and \a createLogicAndViews() for custom initialisation, resource loading and log.
*/
class KEApp
    : public ke::NonCopyable
    , public ke::IEventHandler
{
protected:
    /* application states */
    std::atomic_bool    m_IsRunning;
    std::atomic_bool    m_ExitRequested;
    std::atomic_bool    m_IsExiting;

    /* engine/game logic */
    ke::LogicUPtr      m_upLogic       = nullptr;

    /* render related. */
    ke::RendererSPtr             m_spRenderer        = nullptr;
    Vec2u                        m_WindowSize        = Vec2u(800, 600);
    Vec2u                        m_ViewportSize      = Vec2u(800, 600);
    bool                         m_InWindowedMode    = true;
    SPtr<sf::RenderWindow>       m_spAppWindow       = nullptr;

public:
    KEApp(void);
    virtual ~KEApp(void) = 0;

    //// Initialisation methods.
    /** Initialisation. NOTE: Call this method from child class if this method is going to be overloaded!*/
    virtual bool initialise(void);
    virtual bool shutDown(void);
    /** */
    virtual ke::LogicUPtr createLogicAndViews(void) = 0;
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
    ke::KELogic * const getLogic(void);
    ke::IView * const getHumanView(void);
    ke::RendererSPtr getRenderer(void);
    ////

    ////
    virtual void registerEventListener(void) override;
    virtual void deregisterEventListener(void) override;
    virtual void handleEvent(const ke::EventSPtr p_spEvent) override;
    ////

}; // KEApp class


} // KE ns