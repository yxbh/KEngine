#pragma once

#include "Types.hpp"
#include "../Entity/Types.hpp"
#include "../Event/Types.hpp"

namespace ke
{

/**
    \class IScene
    \brief Base class for implementing a graphics scene held by a view (usually a HumanView).
*/
class IScene
{
public:
    virtual ~IScene(void) = 0;

    /**
        Add a SceneNode to the Scene.
        @return true on success, false if scenenode already exists for the specified EntityID.
    */
    virtual bool addChild(EntityID, SceneNodeSptr) = 0;
    /**
        Remove a SceneNode from the Scene.
        @return true on success.
    */
    virtual bool removeChild(EntityID p_EntityId) = 0;

    /**
        Delegate for responding to a new render component being created.
        Register this in the implementation class.
    */
    virtual void delegateNewRenderComponent(EventSptr p_spEvt) = 0;
    /**
        Delegate for responding to a current render component being destoryed.
        Register this in the implementation class.
    */
    virtual void delegateDestoryRenderComponent(EventSptr p_spEvt) = 0;

}; // IScene class

inline IScene::~IScene(void) {}

} // ke ns