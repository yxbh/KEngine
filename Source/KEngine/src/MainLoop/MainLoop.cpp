#include "../../include/MainLoop/MainLoop.hpp"
#include "../../include/Event/EventManager.hpp"
#include "../../include/Dev/dbg.hpp"
#include "../../include/App/App.hpp"
#include "../../include/Utility/StopWatch.hpp"
/// events
#include "../../include/Event/EngineEvents/SFMLWindowRequest_Event.hpp"
#include "../../include/Event/EngineEvents/SFMLWindow_Event.hpp"
#include "../../include/Event/EngineEvents/FrameTimeReport_Event.hpp"
///

namespace ke
{
MainLoop::MainLoop(void)
    : ke::IEventHandler()
{
    this->registerEventListener();
}

MainLoop::~MainLoop(void)
{
    this->deregisterEventListener();
}

int MainLoop::setupAndBeginupdate(void)
{
    /// request sf::RenderWindow for event polling.
    ke::EventManager::queue(std::make_shared<SFMLWindowRequest_Event>());
    const unsigned wait_limit(1000);
    unsigned current_count(0);
    while (m_SFMLSysEventLoop.getState() == SFMLSysEventLoop::State::Uninitialised)
    {
        ke::EventManager::update();
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        ++current_count;
        if (current_count > wait_limit)
            break;
    }
    if (m_SFMLSysEventLoop.getState() == SFMLSysEventLoop::State::Uninitialised)
    {
        ke::Debug::printError("MainLoop::SetupAndBeginUpdate : failed to initialise SFMLSysEventLoop.");
        assert(false);
    }
    ///

    /// create & launch thread for app logic.
    auto app_mainloop = [this]()
    {
        ke::Time cumulated_elapsed_time, elapsed_time;
        const ke::Time min_frame_duration(ke::Time::milliseconds(5));
        ke::StopWatch stop_watch;
        stop_watch.Restart();

        ke::Debug::print("MainLoop::SetupAndBeginUpdate : entering app main loop.");
        while (ke::App::getSingleton().isRunning() && !ke::App::getSingleton().isExiting())
        {
            elapsed_time = stop_watch.GetElapsed();
            stop_watch.Restart();

            // report last frame duration.
            ke::EventManager::queue(std::make_shared<ke::FrameTimeReport_Event>(elapsed_time, FrameTimeReport_Event::ID::MainLoop));

            // update app if elapsed > min frame duration.
            cumulated_elapsed_time += elapsed_time;
            if (cumulated_elapsed_time > min_frame_duration)
            {
                cumulated_elapsed_time -= min_frame_duration;
                ke::App::update(min_frame_duration);
                //ke::Debug::print("logic thread updated!");
            }

            if (!this->isUpdateAtFullSpeed())
                sf::sleep(sf::milliseconds(2));
        }
        ke::Debug::print("MainLoop::SetupAndBeginUpdate : exited app main loop.");
    };
    ke::Debug::print("MainLoop::SetupAndBeginUpdate : launching main loop thread.");
    std::thread mainloop_thread(app_mainloop);
    ///

    /// begin SFMLSysEventLoop
    m_SFMLSysEventLoop.BeginEventLoop();
    ///

    mainloop_thread.join();
    ke::App::getSingleton().shutDown();

    return 0;
}

void MainLoop::registerEventListener(void)
{
    this->IEventHandler::registerEventListener();
    ke::EventManager::addListener(SFMLWindow_Event::EventType, &MainLoop::handleEvent, this);
}

void MainLoop::deregisterEventListener(void)
{
    this->IEventHandler::deregisterEventListener();
    ke::EventManager::removeListener(SFMLWindow_Event::EventType, this);
}

void MainLoop::handleEvent(ke::EventSPtr p_spEvent)
{
    switch (p_spEvent->getType())
    {
    case SFMLWindow_Event::EventType:
    {
        auto sfml_window_event(std::static_pointer_cast<SFMLWindow_Event>(p_spEvent));
        auto window_sp(sfml_window_event->GetAppWindow());
        if (window_sp)
            m_SFMLSysEventLoop.initialise(window_sp);
        else
            assert(false);
        break;
    }

    default:
        ke::Debug::printWarning("MainLoop::EventHandler : unhandled event type = " + std::to_string(p_spEvent->getType()));
    }

}

bool MainLoop::isUpdateAtFullSpeed(void) const
{
    return m_UpdateAtFullSpeed;
}

} // KE ns