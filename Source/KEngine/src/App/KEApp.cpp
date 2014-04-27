#include "../../include/App/KEApp.hpp"
#include "../../include/Event/EventManager.hpp"
#include "../../include/Graphics/Renderer/SFMLRenderer.hpp"
#include "../../include/App/HumanView.hpp"

//// events
#include "../../include/Event/EngineEvents/SFMLWindowRequest_Event.hpp"
#include "../../include/Event/EngineEvents/SFMLWindow_Event.hpp"
#include "../../include/Event/EngineEvents/ExitRequested_Event.hpp"
////

namespace ke
{

KEApp::KEApp(void)
{
    m_IsRunning.store(true);
    m_ExitRequested.store(false);
    m_IsExiting = false; // same thing as .store()
}

KEApp::~KEApp(void)
{
    if (this->isRegistered()) this->deregisterEventListener();
}

bool KEApp::initialise(void)
{
    // ???
    /* TODO : Check for singleton instance of Application.  */

    /* TODO : Check hardware requirement met. */

    /* TODO : Initialise resource caches. */

    /* TODO : Load localisation strings. */

    /* TODO : Initialise LuaStateManager. */

    /* Initialise EventManager. */
    if (!ke::EventManager::initialise(/*ke::EventManager::DelegateType::DonFastDelegate*/))
    {
        ke::Debug::printError("KEApp::Init : failure to initialise EventManager.");
        return false;
    }
    this->registerEventListener();

    /* Create application window. */
    m_spAppWindow = std::make_shared<sf::RenderWindow>();
    sf::VideoMode desktop_vmode(sf::VideoMode::getDesktopMode());
    if (m_InWindowedMode)
    {
        ke::Debug::print("KEApp::Init : Creating window...");
        m_spAppWindow->create(sf::VideoMode(m_WindowSize.x, m_WindowSize.y, desktop_vmode.bitsPerPixel), "KEApp", sf::Style::Default);
        m_spRenderer = std::make_shared<ke::SFMLRenderer>();
        if (!m_spRenderer->initialise())
        {
            ke::Debug::printError("KEApp::Init : Failure to initialise Renderer.");
            return false;
        }
        std::static_pointer_cast<ke::SFMLRenderer>(m_spRenderer)->setAppWindow(m_spAppWindow);
    }
    else
    {
        // TODO : Handle creating fullscreen window.
        return false;
    }

    /* Create logic & application views. */
    m_upLogic = std::move(this->createLogicAndViews());
    assert(m_upLogic);
    if (!m_upLogic->initialise())
    {
        ke::Debug::printError("ProjKApp::CreateLogicAndViews : logic failed to initialise.");
        exit(EXIT_FAILURE);
    }

    /* TODO : Preload resources. */

    /* TODO : Initialise input devices (e.g. check for joystick). */

    return true;
}

bool KEApp::shutDown(void)
{
    ke::Debug::print("KEApp::ShutDown : begin shutdown.");

    m_IsRunning = false;
    m_upLogic->shutDown();

    ke::Debug::print("KEApp::ShutDown : /shutdown.");
    return true;
}

bool KEApp::load(void)
{
    ke::Debug::printWarning("KEApp::Load : no overloaded method?");
    return true;
}

void KEApp::updateApp(const ke::Time p_Elapsed)
{
    if (this->isExiting())
    {
        ke::EventManager::queue(ke::EventSPtr(new ke::ExitRequested_Event));
        return;
    }

    if (m_upLogic)
    {
        // process events.
        ke::EventManager::update(p_Elapsed, ke::Time::milliseconds(10));
        // update logic.
        m_upLogic->update(p_Elapsed);
    }
    else
    {
        ke::Debug::printError("KEApp::UpdateApp : Logic layer invalid.");
        ke::Debug::pause();
    }

}

void KEApp::renderApp(const ke::Time p_Elapsed)
{
    for (auto view_sptr : this->getLogic()->getViews())
        view_sptr->render(p_Elapsed);

    // we can render diagnostic information here.
    this->getLogic()->renderDiagnostics();
}

bool KEApp::isRunning(void) const
{
    return m_IsRunning;
}

bool KEApp::isExiting(void) const
{
    return m_IsExiting;
}

void KEApp::setQuitting(const bool p_Quitting)
{
    m_IsExiting = p_Quitting;
}

void KEApp::abort(void)
{
    this->setQuitting(true);
}

ke::KELogic * const KEApp::getLogic(void)
{
    return m_upLogic.get();
}

ke::RendererSPtr KEApp::getRenderer(void)
{
    return m_spRenderer;
}

void KEApp::registerEventListener(void)
{
    this->IEventHandler::registerEventListener();
    ke::EventManager::addListener(ke::SFMLWindowRequest_Event::EventType, &KEApp::handleEvent, this);
    //ke::EventManager::addListener(ke::ExitRequested_Event::EventType, &KEApp::handleEvent, this, this->GetEventDelegateHandle());
}

void KEApp::deregisterEventListener(void)
{
    this->IEventHandler::deregisterEventListener();
    ke::EventManager::removeListener(ke::SFMLWindowRequest_Event::EventType, this);
    //ke::EventManager::removeListener(ke::ExitRequested_Event::EventType, this->GetEventDelegateHandle());
}

void KEApp::handleEvent(const ke::EventSPtr p_spEvent)
{
    switch (p_spEvent->getType())
    {
    case ke::SFMLWindowRequest_Event::EventType:
        ke::EventManager::dispatchNow(std::make_shared<SFMLWindow_Event>(m_spAppWindow));
        break;

    //case ke::ExitRequested_Event::EventType:
    //  this->setQuitting(true);
    //  break;

    default:
        ke::Debug::printWarning("KEApp::handleEvent : unhandled event = " + std::to_string(p_spEvent->getType()));
    }
}

} // KE ns