#include <KEngine/Entity/Entity.hpp>

#include <KEngine/Entity/EntityComponentID.hpp>
#include <KEngine/Entity/IEntityComponent.hpp>

#include <cassert>

namespace ke
{

Entity::Entity(const ke::EntityID p_ID)
    : m_EntityID(p_ID)
{}

Entity::Entity(ke::Entity && p_rrEntity)
    : m_ComponentSPMap(std::move(p_rrEntity.m_ComponentSPMap))
    , m_EntityID(std::move(p_rrEntity.getId()))
    , m_EntityType(std::move(p_rrEntity.getType()))
{}

Entity & Entity::operator=(ke::Entity && p_rrEntity)
{
    m_ComponentSPMap    = std::move(p_rrEntity.m_ComponentSPMap);
    m_EntityID          = std::move(p_rrEntity.getId());
    m_EntityType        = std::move(p_rrEntity.getType());
    return *this;
}

Entity::~Entity(void)
{
    assert(m_ComponentSPMap.empty());
}

void Entity::addComponent(ke::EntityComponentSptr p_spEntityComponent)
{
    assert(p_spEntityComponent != nullptr); // should not be null.
    assert(p_spEntityComponent->getId() != ke::Invalid_EntityComponentID);  //
    const auto result = m_ComponentSPMap.insert(std::make_pair(p_spEntityComponent->getId(), p_spEntityComponent));
    assert(result.second); // fails if insertion failed.
}

void Entity::updateAll(const ke::Time p_ElapsedTime)
{
    for (auto & it : m_ComponentSPMap)  it.second->update(p_ElapsedTime);
}

} // KE ns
