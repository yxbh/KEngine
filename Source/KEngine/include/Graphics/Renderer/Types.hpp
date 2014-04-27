#pragma once
#include <memory>

namespace ke
{

class IRenderer;
using RendererSPtr = std::shared_ptr<IRenderer>;

/** \class RendererType
*/
enum class RendererType
{
    SFML,
    OpenGL,
    DirectX9,
    DirectX11,
};

} // KE ns