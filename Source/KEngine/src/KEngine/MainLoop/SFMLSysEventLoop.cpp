//// Events
#include <KEngine/Events/ExitRequested_Event.hpp>
#include <KEngine/Events/SFMLEvent_Event.hpp>
#include <KEngine/Events/FrameTimeReport_Event.hpp>
////

/// engine parts
#include <KEngine/App/AppManager.hpp>
#include <KEngine/Dev/dbg.hpp>
#include <KEngine/Event/EventManager.hpp>
#include <KEngine/MainLoop/SFMLSysEventLoop.hpp>
#include <KEngine/Utility/StopWatch.hpp>

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
    auto * window = static_cast<sf::Window*>(m_spAppWindow->getInternal());

    this->setState(SFMLSysEventLoop::State::Running);

    if (!ke::AppManager::getSingleton().isRunning()) // app should be running.
        assert(false);

    sf::Event sf_event;
    ke::Time frame_time;
    ke::StopWatch stopwatch; stopwatch.Restart();

    ke::Debug::print("SFMLSysEventLoop::BeginEventLoop : entering sys event loop.");
    while (this->getState() == SFMLSysEventLoop::State::Running
            //&& ke::App::getSingleton().isRunning()
            && !ke::AppManager::getSingleton().isExiting()
            //&& m_spAppWindow
            && window->isOpen()
          )
    {
        frame_time = stopwatch.GetElapsed(); stopwatch.Restart();
        ke::EventManager::getSingleton()->queue(std::make_shared<ke::FrameTimeReport_Event>(frame_time, FrameTimeReport_Event::ID::EventLoop));

        while (window->pollEvent(sf_event))
            ke::EventManager::getSingleton()->queue(std::make_shared<SFMLEvent_Event>(sf_event));
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

void SFMLSysEventLoop::handleEvent(const ke::EventSptr p_spEvent)
{
    if (p_spEvent->getType() == ExitRequested_Event::EventType)
        m_State = State::Exiting;
    else
        ke::Debug::printWarning("SFMLSysLogic::handleEvent : unhandled/recognised Event.");
}

} // KE ns