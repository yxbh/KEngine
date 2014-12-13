#pragma once
#include <memory>

namespace ke
{

class IRender;
using RenderSptr = std::shared_ptr<IRender>;
using RenderUptr = std::unique_ptr<IRender>;
using RenderWptr = std::weak_ptr<IRender>;

/** \class RendererType
*/
enum class RendererType
{
    SFML,
    OpenGL,
    DirectX9,
    DirectX11,
};

class IScene;
using SceneSptr = std::shared_ptr<IScene>;
using SceneUptr = std::unique_ptr<IScene>;
using SceneWptr = std::weak_ptr<IScene>;

class ISceneNode;
using SceneNodeSptr = std::shared_ptr<ISceneNode>;
using SceneNodeUptr = std::unique_ptr<ISceneNode>;
using SceneNodeWptr = std::weak_ptr<ISceneNode>;

class IRenderSystem;
using RenderSystemSptr = std::shared_ptr<IRenderSystem>;
using RenderSystemUptr = std::unique_ptr<IRenderSystem>;
using RenderSystemWptr = std::weak_ptr<IRenderSystem>;

} // KE ns