#include "../../include/MainLoop/SFMLSysEventLoop.hpp"
#include "../../include/Dev/dbg.hpp"
#include "../../include/Event/EventManager.hpp"
#include "../../include/App/App.hpp"
#include "../../include/Utility/StopWatch.hpp"
//// Events
#include "../../include/Event/EngineEvents/ExitRequested_Event.hpp"
#include "../../include/Event/EngineEvents/SFMLEvent_Event.hpp"
#include "../../include/Event/EngineEvents/FrameTimeReport_Event.hpp"
////

namespace ke
{

SFMLSysEventLoop::SFMLSysEventLoop(void)
    : m_PollAtFullSpeed(false)
{}

bool SFMLSysEventLoop::initialise(AppWindow_SP p_spAppWindow)
{
    if (!p_spAppWindow) // nullptr for app window.
    {
        m_State = SFMLSysEventLoop::State::InitialisationFailed;
        ke::Debug::printError("SFMLSysLogic::Init : trying initialise with invalid AppWindow pointer.");
        assert(false);
        return false;
    }

    m_spAppWindow = p_spAppWindow;
    m_State = SFMLSysEventLoop::State::Initialised;
    return true;
}

void SFMLSysEventLoop::BeginEventLoop(void)
{
    if (!m_spAppWindow)
    {
        ke::Debug::printError("SFMLSysEventLoop::BeginEventLoop : invalid pointer to app window, cannot begin systom event polling.");
        assert(false);
    }

    this->setState(SFMLSysEventLoop::State::Running);

    if (!ke::App::getSingleton().isRunning()) // app should be running.
        assert(false);
    if (!m_spAppWindow)
        assert(false); // app window should be valid.

    sf::Event sf_event;
    ke::Time frame_time;
    ke::StopWatch stopwatch; stopwatch.Restart();

    ke::Debug::print("SFMLSysEventLoop::BeginEventLoop : entering sys event loop.");
    while (this->getState() == SFMLSysEventLoop::State::Running
            //&& ke::App::getSingleton().isRunning()
            && !ke::App::getSingleton().isExiting()
            //&& m_spAppWindow
            && m_spAppWindow->isOpen()
          )
    {
        frame_time = stopwatch.GetElapsed(); stopwatch.Restart();
        ke::EventManager::queue(std::make_shared<ke::FrameTimeReport_Event>(frame_time, FrameTimeReport_Event::ID::EventLoop));

        while (m_spAppWindow->pollEvent(sf_event))
            ke::EventManager::queue(std::make_shared<SFMLEvent_Event>(sf_event));
        //ke::Debug::print("polling thread updated!");

        if (!m_PollAtFullSpeed) sf::sleep(sf::milliseconds(1));
    }
    ke::Debug::print("SFMLSysEventLoop::BeginEventLoop : exited sys event loop.");

    ke::Debug::print("SFMLSysEventLoop::BeginEventLoop : closing app window.");
    m_spAppWindow->close();

    return;
}

SFMLSysEventLoop::State SFMLSysEventLoop::getState(void) const
{
    return m_State;
}

void SFMLSysEventLoop::setState(const SFMLSysEventLoop::State p_NewState)
{
    m_State = p_NewState;
}

void SFMLSysEventLoop::handleEvent(const ke::EventSPtr p_spEvent)
{
    if (p_spEvent->getType() == ExitRequested_Event::EventType)
        m_State = State::Exiting;
    else
        ke::Debug::printWarning("SFMLSysLogic::handleEvent : unhandled/recognised Event.");
}

} // KE ns