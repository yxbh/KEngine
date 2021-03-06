#pragma once

#include "KEngine/engine_common.hpp"
#include "KEngine/Event/Types.hpp"
#include "KEngine/Graphics/SfmlWindow.hpp"

namespace ke
{

/**
    \class SFMLSysEventLoop

    TODO : inherit from IEventHandler?

*/
class SFMLSysEventLoop
{
public:
    enum class State
    {
        Uninitialised,
        InitialisationFailed,
        Initialised,
        Running,
        Exiting,
    };

private:
    using AppWindow_SP = ke::WindowSptr;

    AppWindow_SP    m_spAppWindow = nullptr;

    std::atomic<State> m_State = State::Uninitialised;

    bool    m_PollAtFullSpeed;

public:
    SFMLSysEventLoop(void);
    virtual ~SFMLSysEventLoop(void) = default;

    /** Set the given app window as the one for system event polling. */
    bool initialise(AppWindow_SP p_spAppWindow);
    /** Begin polling the event loop. */
    void BeginEventLoop(void);

    /** Return the current state of this Logic instance. */
    SFMLSysEventLoop::State getState(void) const;
    /** */
    void setState(const State p_NewState);

    /** Event delegate. */
    void handleEvent(const ke::EventSptr p_spEvent);

}; // SFMLSysEventLoop class

} // KE ns