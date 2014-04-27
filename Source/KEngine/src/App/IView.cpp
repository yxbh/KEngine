#include "../../include/App/IView.hpp"

namespace ke
{

void IView::Attach(const ViewID p_ViewID, const EntityID p_EntityID)
{
    m_ViewID = p_ViewID;
    m_EntityID = p_EntityID;
}

ViewID IView::GetViewID(void)
{
    return m_ViewID;
}

ViewType IView::getType(void)
{
    return m_ViewType;
}

EntityID IView::GetEntityID(void)
{
    return m_EntityID;
}



AIView::AIView(void)
{
    m_ViewType = ViewType::AI;
}

void AIView::render(const ke::Time p_Elapsed)
{
    // TODO
    assert(false);
}

} // KE ns