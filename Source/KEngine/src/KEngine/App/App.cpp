#include "KEngine/App/App.hpp"
#include "KEngine/App/Logic.hpp"
#include "KEngine/Event/EventManager.hpp"
#include "KEngine/Graphics/Renderer/SfmlRender.hpp"
#include "KEngine/Graphics/RenderSystem.hpp"
#include "KEngine/Graphics/SfmlWindow.hpp"
#include "KEngine/App/HumanView.hpp"

//// events
#include "KEngine/Events/SFMLWindowRequest_Event.hpp"
#include "KEngine/Events/SFMLWindow_Event.hpp"
#include "KEngine/Events/ExitRequested_Event.hpp"
////

namespace ke
{

App::App(void)
{
    m_IsRunning.store(true);
    m_ExitRequested.store(false);
    m_IsExiting = false; // same thing as .store()
}

App::~App(void)
{
    if (this->isRegistered()) this->deregisterEventListener();
}

bool App::initialise(void)
{
    // ???
    /* TODO : Check for singleton instance of Application.  */

    /* TODO : Check hardware requirement met. */

    /* TODO : Initialise resource caches. */

    /* TODO : Load localisation strings. */

    /* TODO : Initialise LuaStateManager. */

    /* Initialise EventManager. */
    ke::EventManager::setSingleton(new EventManager);
    this->registerEventListener();

    /* Create application window. */
    m_spAppWindow     = std::make_shared<SfmlWindow>();
    m_spRender        = std::make_shared<ke::SfmlRender>();
    m_spRenderSystem  = std::make_shared<ke::SfmlRenderSystem>();
    m_spRenderSystem->setRender(m_spRender);
    m_spRenderSystem->setMainWindow(m_spAppWindow);
    sf::VideoMode desktop_vmode(sf::VideoMode::getDesktopMode());
    if (m_InWindowedMode)
    {
        ke::Debug::print("KEApp::Init : Creating window...");
        auto * window_ptr = static_cast<sf::RenderWindow*>(m_spAppWindow->getInternal());
        window_ptr->create(sf::VideoMode(m_WindowSize.x, m_WindowSize.y, desktop_vmode.bitsPerPixel), "KEApp", sf::Style::Default);
        
        if (!m_spRender->initialise())
        {
            ke::Debug::printError("KEApp::Init : Failure to initialise Renderer.");
            return false;
        }
        m_spRender->setRenderSurface(m_spAppWindow);
    }
    else
    {
        // TODO : Handle creating fullscreen window.
        // fail for now.
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

bool App::shutDown(void)
{
    ke::Debug::print("KEApp::ShutDown : begin shutdown.");

    m_upLogic->shutDown();
    m_IsRunning = false;

    ke::Debug::print("KEApp::ShutDown : /shutdown.");
    return true;
}

bool App::activateGlContext(void)
{
    return std::dynamic_pointer_cast<ke::SfmlWindow>(m_spAppWindow)->setActive(true);
}

bool App::deactivateGlContext(void)
{
    return std::dynamic_pointer_cast<ke::SfmlWindow>(m_spAppWindow)->setActive(false);
}

bool App::load(void)
{
    ke::Debug::printWarning("KEApp::Load : no overloaded method?");
    return true;
}

void App::updateApp(const ke::Time p_Elapsed)
{
    if (this->isExiting())
    {
        ke::EventManager::getSingleton()->queue(ke::EventSptr(new ke::ExitRequested_Event));
        return;
    }

    //// update logic
    assert(m_upLogic);
    if (!m_upLogic)
    {
        ke::Debug::printFatalError("KEApp::UpdateApp : Logic layer invalid.");
        throw std::runtime_error("KEApp::UpdateApp : Logic layer invalid.");
    }
    // process events.
    ke::EventManager::getSingleton()->update(p_Elapsed, ke::Time::milliseconds(10));
    // update logic.
    m_upLogic->update(p_Elapsed);
}

void App::renderApp(const ke::Time p_Elapsed)
{
    bool ret;
    ret = m_spRenderSystem->prepareRender();
    assert(ret);
    for (auto view_sptr : this->getLogic()->getViews())
    {
        m_spRenderSystem->render(view_sptr, p_Elapsed);
    }
    ret = m_spRenderSystem->finaliseRender();
    assert(ret);

    // we can render diagnostic information here.
    this->getLogic()->renderDiagnostics();
}

bool App::isRunning(void) const
{
    return m_IsRunning;
}

bool App::isExiting(void) const
{
    return m_IsExiting;
}

void App::setQuitting(const bool p_Quitting)
{
    m_IsExiting = p_Quitting;
}

void App::abort(void)
{
    this->setQuitting(true);
}

ke::Logic * const App::getLogic(void)
{
    return m_upLogic.get();
}

ke::IRender * const App::getRenderer(void)
{
    return m_spRenderSystem->getRender();
}

void App::registerEventListener(void)
{
    this->IEventHandler::registerEventListener();
    ke::EventManager::getSingleton()->addListener(ke::SFMLWindowRequest_Event::EventType, ke::EventDelegate::from<App, &App::handleEvent>(this));
    //ke::EventManager::addListener(ke::ExitRequested_Event::EventType, &KEApp::handleEvent, this, this->GetEventDelegateHandle());
}

void App::deregisterEventListener(void)
{
    this->IEventHandler::deregisterEventListener();
    ke::EventManager::getSingleton()->removeListener(ke::SFMLWindowRequest_Event::EventType, ke::EventDelegate::from<App, &App::handleEvent>(this));
    //ke::EventManager::removeListener(ke::ExitRequested_Event::EventType, this->GetEventDelegateHandle());
}

void App::handleEvent(const ke::EventSptr p_spEvent)
{
    switch (p_spEvent->getType())
    {
    case ke::SFMLWindowRequest_Event::EventType:
        ke::EventManager::getSingleton()->dispatchNow(std::make_shared<SFMLWindow_Event>(m_spAppWindow));
        break;

    //case ke::ExitRequested_Event::EventType:
    //  this->setQuitting(true);
    //  break;

    default:
        ke::Debug::printWarning("KEApp::handleEvent : unhandled event = " + std::to_string(p_spEvent->getType()));
    }
}

} // KE ns