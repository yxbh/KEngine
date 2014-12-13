#pragma once

#include "Types.hpp"

#include "KEngine/Entity/Types.hpp"
#include "KEngine/Entity/EntityRenderComponent.hpp"

#include <memory>
#include <vector>

namespace ke
{

/**
    \class ISceneNode
    \brief A pure virtual base class for implementing custom SceneNodes.
*/
class ISceneNode
{
public:
    virtual ~ISceneNode(void) = 0 {};

    /** @return the owner Entity's EntityID. */
    virtual EntityID entityId(void) const = 0;

    /** Add a SceneNode into this SceneNode as a child. */
    virtual bool addChild(SceneNodeSptr) = 0;
    /** Remove a child SceneNode with the specified EntityID. */
    virtual bool removeChild(EntityID) = 0;

    /** @return the parent entity. */
    virtual EntityWptr getEntity(void) = 0;
    /** @return the render component. */
    virtual EntityRenderComponentWptr getRenderComponent(void) = 0;

}; // ISceneNode class

/**
    \class SceneNode
    \brief A base class for implementing custom SceneNodes.
*/
class SceneNode
    : public ISceneNode
{
public:
    using SceneNodeVec = std::vector<SceneNodeSptr>;

protected:
    SceneNodeSptr               m_spParent                  = nullptr;
    SceneNodeVec                m_Children;
    EntityRenderComponentWptr   m_wpOwnerRenderComponent;
    EntityID                    m_OwnerEntityId             = ke::InvalidEntityID;

public:
    SceneNode(EntityRenderComponentSptr p_spRenderComponent);
    SceneNode(EntityID p_EId, EntityRenderComponentWptr p_wpRenderComponent);
    virtual ~SceneNode(void) = default;

    /** @return the owner Entity's EntityID. */
    virtual EntityID entityId(void) const override { return m_OwnerEntityId; }

    /** Add a SceneNode into this SceneNode as a child. */
    virtual bool addChild(SceneNodeSptr p_spChild) override
    {
        m_Children.push_back(p_spChild);
        return true;
    }
    /** Remove a child SceneNode with the specified EntityID. */
    virtual bool removeChild(EntityID p_EntityId) final;

    /** @return the parent entity. */
    virtual EntityWptr getEntity(void) final;
    /** @return the render component. */
    virtual EntityRenderComponentWptr getRenderComponent(void) final;


}; // SceneNode class

} // ke ns