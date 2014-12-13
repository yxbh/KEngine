
/// events
#include <KEngine/Events/SFMLWindowRequest_Event.hpp>
#include <KEngine/Events/SFMLWindow_Event.hpp>
#include <KEngine/Events/FrameTimeReport_Event.hpp>
///

/// engine parts
#include <KEngine/MainLoop/MainLoop.hpp>
#include <KEngine/Event/EventManager.hpp>
#include <KEngine/Dev/dbg.hpp>
#include <KEngine/App/AppManager.hpp>
#include <KEngine/Utility/StopWatch.hpp>

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
    ke::EventManager::getSingleton()->queue(std::make_shared<SFMLWindowRequest_Event>());
    const unsigned wait_limit(1000);
    unsigned current_count(0);
    while (m_SFMLSysEventLoop.getState() == SFMLSysEventLoop::State::Uninitialised)
    {
        ke::EventManager::getSingleton()->update();
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        ++current_count;
        if (current_count > wait_limit)
            break;
    }
    if (m_SFMLSysEventLoop.getState() == SFMLSysEventLoop::State::Uninitialised)
    {
        ke::Debug::printError("MainLoop::SetupAndBeginUpdate : failed to initialise SFMLSysEventLoop.");
        throw std::runtime_error("MainLoop::SetupAndBeginUpdate : failed to initialise SFMLSysEventLoop.");
    }
    ///

    // deactivate GL context on current thread so it can be enabled on render thread.
    bool ret = ke::AppManager::getSingleton().deactivateGlContext();
    assert(ret);
    if (!ret) throw std::runtime_error("failure deactivating GL context.");

    /*
     * create & launch thread for app logic.
    */ 
    auto app_mainloop = [this]()
    {
        bool ret = ke::AppManager::getSingleton().activateGlContext(); // activate the GL context on the logic/render thread.
        assert(ret);
        if (!ret) throw std::runtime_error("failure activating GL context.");

        ke::Time cumulated_elapsed_time, elapsed_time;
        const auto min_frame_duration = ke::Time::milliseconds(5); // TEMP
        ke::StopWatch stop_watch;
        stop_watch.Restart();

        /*
         * Enter the game loop.
        */
        ke::Debug::print("MainLoop::SetupAndBeginUpdate : entering app main loop.");
        while (ke::AppManager::getSingleton().isRunning() && !ke::AppManager::getSingleton().isExiting())
        {
            elapsed_time = stop_watch.GetElapsed();
            stop_watch.Restart();

            // report last frame duration.
            ke::EventManager::getSingleton()->queue(std::make_shared<ke::FrameTimeReport_Event>(elapsed_time, FrameTimeReport_Event::ID::MainLoop));

            // update app logic if elapsed > min frame duration.
            cumulated_elapsed_time += elapsed_time;
            if (cumulated_elapsed_time > min_frame_duration)
            {
                cumulated_elapsed_time -= min_frame_duration;
                try
                {
                    ke::AppManager::update(min_frame_duration);
                }
                catch (std::exception & e)
                {
                    ke::Debug::printError(e.what());
                }
                //ke::Debug::print("logic thread updated!");
            }

            ke::AppManager::render(elapsed_time);

            if (!this->isUpdateAtFullSpeed()) sf::sleep(sf::milliseconds(2));
        }
        ke::Debug::print("MainLoop::SetupAndBeginUpdate : exited app main loop.");
    }; // application main loop lambda.
    ke::Debug::print("MainLoop::SetupAndBeginUpdate : launching main loop thread.");
    std::thread mainloop_thread(app_mainloop);

    /*
     * begin SFMLSysEventLoop
    */
    m_SFMLSysEventLoop.BeginEventLoop();

    mainloop_thread.join();
    ke::AppManager::getSingleton().shutDown();

    return 0;
}

void MainLoop::registerEventListener(void)
{
    this->IEventHandler::registerEventListener();
    ke::EventManager::getSingleton()->addListener(SFMLWindow_Event::EventType, ke::EventDelegate::from<MainLoop, &MainLoop::handleEvent>(this));
}

void MainLoop::deregisterEventListener(void)
{
    this->IEventHandler::deregisterEventListener();
    ke::EventManager::getSingleton()->removeListener(SFMLWindow_Event::EventType, ke::EventDelegate::from<MainLoop, &MainLoop::handleEvent>(this));
}

void MainLoop::handleEvent(ke::EventSptr p_spEvent)
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