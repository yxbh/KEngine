#include <KEngine/App/HumanView.hpp>
#include <KEngine/App/App.hpp>
#include <KEngine/Graphics/Renderer/IRender.hpp>

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

    if (!this->registerEventDelegates()) assert(false);
}

void HumanView::update(const ke::Time p_Elapsed)
{
    m_upTaskManager->updateAllTasks(p_Elapsed);

    // TODO : update console.
    // TODO : update GUI elements.
}

std::vector<SceneSptr> HumanView::getScenes(void)
{
    return m_Scenes;
}

ke::TaskManager & HumanView::getTaskManager(void)
{
    assert(m_upTaskManager);
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