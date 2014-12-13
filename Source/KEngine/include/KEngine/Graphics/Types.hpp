#include "../std_common.hpp"

namespace ke
{

class ISceneNode;
using SceneNodeSptr = Sptr<ISceneNode>;
using SceneNodeWptr = Wptr<ISceneNode>;
using SceneNodeUptr = Uptr<ISceneNode>;

class IScene;
using SceneSptr = Sptr<IScene>;
using SceneWptr = Wptr<IScene>;
using SceneUptr = Uptr<IScene>;

class IRenderSurface;
using RenderSurfaceSptr = Sptr<IRenderSurface>;
using RenderSurfaceWptr = Wptr<IRenderSurface>;
using RenderSurfaceUptr = Uptr<IRenderSurface>;

class IWindow;
using WindowSptr = Sptr<IWindow>;
using WindowWptr = Wptr<IWindow>;
using WIndowUptr = Uptr<IWindow>;

} // ke ns