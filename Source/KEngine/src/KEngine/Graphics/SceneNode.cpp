#include <KEngine/Graphics/SceneNode.hpp>

#include <KEngine/Entity/Entity.hpp>

namespace ke
{

SceneNode::SceneNode(EntityRenderComponentSptr p_spRenderComponent)
{
    assert(p_spRenderComponent);
    m_OwnerEntityId = p_spRenderComponent->getOwnerEntity()->getId();
    m_wpOwnerRenderComponent = p_spRenderComponent;
}

SceneNode::SceneNode(EntityID p_EId, EntityRenderComponentWptr p_wpRenderComponent)
    : m_OwnerEntityId(p_EId), m_wpOwnerRenderComponent(p_wpRenderComponent)
{
    assert(!p_wpRenderComponent.expired());
}

bool SceneNode::removeChild(EntityID p_EntityId)
{
    for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
    {
        if ((*it)->entityId() == p_EntityId)
        {
            m_Children.erase(it);
            return true;
        }
    }
    return false;
}

EntityWptr SceneNode::getEntity(void)
{
    if (auto component = m_wpOwnerRenderComponent.lock())
        return component->getOwnerEntity();
    else
        return EntityWptr();
}

EntityRenderComponentWptr SceneNode::getRenderComponent(void)
{
    return m_wpOwnerRenderComponent;
}

} // ke ns