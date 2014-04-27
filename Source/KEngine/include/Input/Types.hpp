#pragma once
#include <memory>

namespace ke
{


////
class IInputHandler;
using InputHandlerSPtr         = std::shared_ptr<IInputHandler>;
using InputHandlerWPtr         = std::weak_ptr<IInputHandler>;
using InputHandlerUPtr         = std::unique_ptr<IInputHandler>;
////

////
class IPointerHandler;
using PointerHandlerSPtr       = std::shared_ptr<IPointerHandler>;
using PointerHandlerWPtr       = std::weak_ptr<IPointerHandler>;
using PointerHandlerUPtr       = std::unique_ptr<IPointerHandler>;
////

////
class IKeyboardHandler;
using KeyboardHandlerSPtr      = std::shared_ptr<IKeyboardHandler>;
using KeyboardHandlerWPtr      = std::weak_ptr<IKeyboardHandler>;
using KeyboardHandlerUPtr      = std::unique_ptr<IKeyboardHandler>;
////

////
class IGamepadHandler;
using GamepadHandlerSPtr       = std::shared_ptr<IGamepadHandler>;
using GamepadHandlerWPtr       = std::weak_ptr<IGamepadHandler>;
using GamepadHandlerUPtr       = std::unique_ptr<IGamepadHandler>;
////

////
class IJoystickHandler;
using JoystickHandlerSPtr      = std::shared_ptr<IJoystickHandler>;
using JoystickHandlerWPtr      = std::weak_ptr<IJoystickHandler>;
using JoystickHandlerUPtr      = std::unique_ptr<IJoystickHandler>;
////

////
class IKeyboard;
using KeyboardSPtr             = std::shared_ptr<IKeyboard>;
using KeyboardWPtr             = std::weak_ptr<IKeyboard>;
using KeyboardUPtr             = std::unique_ptr<IKeyboard>;
////

} // KE ns