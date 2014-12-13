#include "KEngine/Graphics/RenderSystem.hpp"

#include "KEngine/App/Types.hpp"
#include "KEngine/App/IView.hpp"
#include "KEngine/Graphics/IWindow.hpp"
#include "KEngine/Graphics/Renderer/IRender.hpp"

namespace ke
{

void IRenderSystem::setMainWindow(ke::WindowSptr p_spWindow)
{
    m_spMainWindow = p_spWindow;
}

void IRenderSystem::setRender(ke::RenderSptr p_spRender)
{
    m_spRender = p_spRender;
}

ke::IWindow * IRenderSystem::getMainWindow(void)
{
    assert(m_spMainWindow);
    return m_spMainWindow.get();
}

ke::IRender * IRenderSystem::getRender(void)
{
    assert(m_spRender);
    return m_spRender.get();
}

bool SfmlRenderSystem::initialise(void)
{
    // implementation.

    return true;
}

bool SfmlRenderSystem::shutDown(void)
{
    // add shut down routine.

    return true;
}

bool SfmlRenderSystem::prepareRender(void)
{
    assert(m_spRender);
    assert(m_spMainWindow);
    
    /*
    * dummy test code.
    */
    static bool f = true;
    f = !f;
    if (f)
        m_spRender->clear({ 255, 255, 0, 255 });
    else
        m_spRender->clear({ 0, 255, 0, 255 });
    
    return true;
}

void SfmlRenderSystem::render(ke::ViewSptr p_spView, ke::Time p_Elapsed)
{
    assert(m_spRender);
    assert(m_spMainWindow);

    // TODO implement rendering of given view.
    // render each scene inside the view.
    
    if (p_spView->getType() != ke::ViewType::Human)
        return; 
}

bool SfmlRenderSystem::finaliseRender(void)
{
    assert(m_spRender);
    assert(m_spMainWindow);
    m_spMainWindow->display();
    return true;
}

void SfmlRenderSystem::handleEvent(const ke::EventSptr p_spEvent)
{
    switch (p_spEvent->getType())
    {
    default: /* ignore */
        break;
    }
}

}