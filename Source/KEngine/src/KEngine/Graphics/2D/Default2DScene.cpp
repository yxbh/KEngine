#include <KEngine/Graphics/2D/Default2DScene.hpp>

#include <KEngine/Graphics/SceneNode.hpp>

namespace ke
{

bool Default2DScene::addChild(EntityID, SceneNodeSptr)
{
    // TODO : implementation.

    return false;
}

bool Default2DScene::removeChild(EntityID p_EntityId)
{
    // TODO : implementation.

    return false;
}

void Default2DScene::delegateNewRenderComponent(EventSptr p_spEvt)
{
    // TODO : implementation.
}

void Default2DScene::delegateDestoryRenderComponent(EventSptr p_spEvt)
{
    // TODO : implementation.
}

} // ke ns