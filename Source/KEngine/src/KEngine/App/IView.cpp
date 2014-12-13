#include <KEngine/App/IView.hpp>

namespace ke
{

void IView::attach(const ViewID p_ViewID, const EntityID p_EntityID)
{
    m_ViewId = p_ViewID;
    m_EntityId = p_EntityID;
}

AIView::AIView(void)
    : IView()
{
    m_ViewType = ViewType::AI;
}

} // KE ns