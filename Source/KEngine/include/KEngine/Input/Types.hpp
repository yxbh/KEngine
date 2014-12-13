#pragma once
#include <memory>

namespace ke
{


////
class IInputHandler;
using InputHandlerSptr         = std::shared_ptr<IInputHandler>;
using InputHandlerWptr         = std::weak_ptr<IInputHandler>;
using InputHandlerUptr         = std::unique_ptr<IInputHandler>;
////

////
class IPointerHandler;
using PointerHandlerSptr       = std::shared_ptr<IPointerHandler>;
using PointerHandlerWptr       = std::weak_ptr<IPointerHandler>;
using PointerHandlerUptr       = std::unique_ptr<IPointerHandler>;
////

////
class IKeyboardHandler;
using KeyboardHandlerSptr      = std::shared_ptr<IKeyboardHandler>;
using KeyboardHandlerWptr      = std::weak_ptr<IKeyboardHandler>;
using KeyboardHandlerUptr      = std::unique_ptr<IKeyboardHandler>;
////

////
class IGamepadHandler;
using GamepadHandlerSptr       = std::shared_ptr<IGamepadHandler>;
using GamepadHandlerWptr       = std::weak_ptr<IGamepadHandler>;
using GamepadHandlerUptr       = std::unique_ptr<IGamepadHandler>;
////

////
class IJoystickHandler;
using JoystickHandlerSptr      = std::shared_ptr<IJoystickHandler>;
using JoystickHandlerWptr      = std::weak_ptr<IJoystickHandler>;
using JoystickHandlerUptr      = std::unique_ptr<IJoystickHandler>;
////

////
class IKeyboard;
using KeyboardSptr             = std::shared_ptr<IKeyboard>;
using KeyboardWptr             = std::weak_ptr<IKeyboard>;
using KeyboardUptr             = std::unique_ptr<IKeyboard>;
////

} // KE ns