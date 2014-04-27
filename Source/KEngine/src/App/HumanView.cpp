#include "../../include/App/HumanView.hpp"
#include "../../include/App/App.hpp"
#include "../../include/Graphics/Renderer/IRenderer.hpp"
#include "../../include/Graphics/Renderer/SFMLRenderer.hpp"

namespace ke
{


HumanView::HumanView(void)
    : m_upTaskManager(std::move(std::make_unique<ke::TaskManager>()))
{
    m_ViewType = ViewType::Human;
    m_ViewState = State::Initializing;

    if (!this->initialiseAudio())
    {
        ke::Debug::printError("HumanView::HumanView : Audio failed to initialise!");
        ke::Debug::printWarning("Continue anyway...");
    }

    if (!this->registerEventDelegates())
    {
        ke::Debug::printError("HumanView::HumanView : Failed to register event delegates.");
        assert(false);
    }
}

void HumanView::update(const ke::Time p_Elapsed)
{
    m_upTaskManager->updateAllTasks(p_Elapsed);

    // TODO : update console.
    // TODO : update GUI elements.
}

void HumanView::render(const ke::Time p_Elapsed)
{
    m_CurrentTime += p_Elapsed;
    if ((m_MinTimeBetweenDraw == ke::Time::Zero) // run at full speed?
            || ((m_CurrentTime - m_LastRenderTime) < m_MinTimeBetweenDraw)) // minimum frame time reached?
        return;

    ke::RendererSPtr renderer_sp(ke::App::getSingleton().getRenderer());
    if (!renderer_sp)
    {
        ke::Debug::printError("HumanView::Render : Renderer pointer points to null!");
        return;
    }

    if (!renderer_sp->prerender())
    {
        ke::Debug::printError("HumanView::Render : Renderer failed to prerender!");
        return;
    }

    ////
    this->renderText();
    // TODO : render console.
    // TODO : render GUI elements.
    m_LastRenderTime = m_CurrentTime;
    ////

    if (!renderer_sp->postrender())
        ke::Debug::printError("HumanView::Render : Renderer failed to clean up!");
}

ke::TaskManager & HumanView::getTaskManager(void)
{
    if (!m_upTaskManager) // invalid TaskManager
    {
        ke::Debug::printError("HumanView::GetTaskManager : Invalid TaskManager!");
        assert(false);
    }
    return *m_upTaskManager;
}

bool HumanView::initialiseAudio(void)
{
    // TODO : implementation.

    return true;
}

bool HumanView::registerEventDelegates(void)
{
    // TODO : Implementation.
    return true;
}


} // KE ns