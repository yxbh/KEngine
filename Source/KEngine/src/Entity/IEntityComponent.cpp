#include "../../include/Entity/IEntityComponent.hpp"
#include <cassert>

namespace ke
{

IEntityComponent::IEntityComponent(EntitySPtr p_spEntity)
{
    if (p_spEntity == nullptr) assert(false); // unacceptable.
    this->setOwnerEntity(p_spEntity);
}

IEntityComponent::~IEntityComponent(void)
{
    m_spOwnerEntity.reset(); // break circular pointer dependency.
};

EntitySPtr IEntityComponent::getOwnerEntity(void)
{
    return m_spOwnerEntity;
}

void IEntityComponent::setOwnerEntity(ke::EntitySPtr p_spEntity)
{
    m_spOwnerEntity = p_spEntity;
}


} // KE ns
