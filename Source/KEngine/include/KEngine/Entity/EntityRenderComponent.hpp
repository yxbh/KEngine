#pragma once

#include "KEngine/Entity/IEntityComponent.hpp"
#include "KEngine/Graphics/Types.hpp"

namespace ke
{

/**
    \class EntityRenderComponent
    \brief An EntityComponent that contains renderable element/s.
*/
class EntityRenderComponent final
    : public IEntityComponent
{
public:
    static const EntityComponentType type = 0x123456;

private:
    SceneNodeSptr m_SceneNodes;

public:
    EntityRenderComponent(EntitySptr p_spEntity) : IEntityComponent(p_spEntity) {};
    virtual ~EntityRenderComponent(void) = default;

    virtual bool initialise(void /* path to ini file? */) final { return true; }
    /** Carry out any post initialisation operations(e.g. operations that can't be done during initialisation. */
    virtual void postInitialise(void) final {}
    /** Update this EntityComponent instance. */
    virtual void update(const ke::Time p_ElapsedTime) final { KE_UNUSED(p_ElapsedTime); }
    /** @return the type of this particular EntityComponent. */
    virtual const EntityComponentType getType(void) const final { return EntityRenderComponent::type; };

}; // EntityRenderComponent class

using EntityRenderComponentSptr = std::shared_ptr<EntityRenderComponent>;
using EntityRenderComponentWptr = std::weak_ptr<EntityRenderComponent>;
using EntityRenderComponentUptr = std::unique_ptr<EntityRenderComponent>;

} // ke ns