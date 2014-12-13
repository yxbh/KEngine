#pragma once

#include "../IScene.hpp"

namespace ke
{

///
/// \class Default2DScene
/// \brief 
///
class Default2DScene final
    : public IScene
{
private:
    SceneNodeSptr m_RootNode;

public:

    /**
        Add a SceneNode to the Scene.
        \return true on success, false if scenenode already exists for the specified EntityID.
    */
    virtual bool addChild(EntityID, SceneNodeSptr) final;
    /**
        Remove a SceneNode from the Scene.
        \return true on success.
    */
    virtual bool removeChild(EntityID p_EntityId) final;

    /** */
    virtual void delegateNewRenderComponent(EventSptr p_spEvt) final;
    /** */
    virtual void delegateDestoryRenderComponent(EventSptr p_spEvt) final;

}; // Default2DScene class

} // ke ns