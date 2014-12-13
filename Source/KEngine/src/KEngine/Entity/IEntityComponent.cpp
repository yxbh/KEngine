#include <KEngine/Entity/IEntityComponent.hpp>

#include <cassert>

namespace ke
{

IEntityComponent::IEntityComponent(EntitySptr p_spEntity)
{
    if (p_spEntity == nullptr) assert(false); // unacceptable.
    this->setOwnerEntity(p_spEntity);
}

IEntityComponent::~IEntityComponent(void)
{
    m_spOwnerEntity.reset(); // break circular pointer dependency.
};

EntitySptr IEntityComponent::getOwnerEntity(void)
{
    return m_spOwnerEntity;
}

void IEntityComponent::setOwnerEntity(ke::EntitySptr p_spEntity)
{
    m_spOwnerEntity = p_spEntity;
}


} // KE ns
