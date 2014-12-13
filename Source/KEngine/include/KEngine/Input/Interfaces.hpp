/**

    This header file contains all/marjority of the interfaces/abstract-class/es used for implementing KEngine's input facilities.

    NOTE:
        - All direct child class of IInputHandler uses  virtual inheritance to get around the diamond of death problem.

*/

#pragma once
#include "Types.hpp"
#include "Keys.hpp"
#include <cstdint>
#include "../Common/Time.hpp"

namespace ke
{

/** \class IInputHandler

    Interface for implementing input handler that interprets hardware input into Events and queue them with the EventManager.

    The handler type interfaces are used to implement specific controllers for reacting to different input devices.
    All handler classes have handle* methods that takes one or more arguement of type/s that are specific to the corresponding input devices.
        These methods will return true if the method has successfully handled/processed the input. Otherwise false is returned.
*/
class IInputHandler
{
public:
    virtual ~IInputHandler(void) = default;

    virtual void update(const ke::Time & p_rTime) = 0;
}; // class


/** \class IPointerHandler

    An interface for implementing pointer type input device controllers (e.g. touch & mouse input).

*/
class IPointerHandler
    : public virtual IInputHandler
{
public:
    using RadiusType = unsigned;
    using ButtonType = std::uint8_t;

public:
    virtual ~IPointerHandler(void) = default;

    //// Pointer devices button 'pressed' & 'released' handling.
    virtual bool handleButtonPressed(const ButtonType p_Button) = 0;
    virtual bool handleButtonReleased(const ButtonType p_Button) = 0;
    ////

    ////
    /// Should these methods be handled under a Pointer class (similar to the Keyboard class)?
    virtual RadiusType getPointerRadius(void) const = 0;
    virtual void setPointerRadius(const RadiusType p_Radius) = 0;
    ////
}; // class


/** \class IKeyboardHandler

    An interface for implementing keyboard type input device controllers (i.e. keyboard).

*/
class IKeyboardHandler
    : public virtual IInputHandler
{
public:
    virtual ~IKeyboardHandler(void) = default;

    //// Keyboard devices button 'pressed' & 'released' handling.
    virtual bool handleKeyPressed(const ke::Key p_Key) = 0;
    virtual bool handleKeyReleased(const ke::Key p_Key) = 0;
    ////
}; // class IKeyboardHandler


/** \class IGamepadHandler

    An interface for implementing gamepad type input device controllers (e.g. 360 controllers)

*/
class IGamepadHandler
    : public virtual IInputHandler
{
public:
    using TriggerType   = char * const;
    using ButtonType    = TriggerType;

public:
    virtual ~IGamepadHandler(void) = default;

    //// Gamepad devices trigger 'pressed' & 'released' handling.
    virtual bool handleTriggerPressed(const TriggerType p_TriggerName) = 0;
    virtual bool handleTriggerReleased(const TriggerType p_TriggerName) = 0;
    ////

    //// Gamepad devices button 'pressed' & 'released' handling.
    virtual bool handleButtonPressed(const ButtonType p_ButtonName) = 0;
    virtual bool handleButtonReleased(const ButtonType p_ButtonName) = 0;
    ////

    //// Gamepad devices thumbstick handling.
    virtual bool handleThumbStickX(void /* TODO : figure out design of interface. */) = 0;
    ////

}; // class IGamepadHandler


/** \class IJoystickHandler

    An interface for implementing joystick type input device controllers.

*/
class IJoystickHandler
    : public virtual IInputHandler
{
public:
    using ButtonType = std::uint8_t;

public:
    virtual ~IJoystickHandler(void) = default;

    //// Joystick devices button 'pressed' & 'released' handling.
    virtual bool handleButtonPressed(const ButtonType p_ButtonName) = 0;
    virtual bool handleButtonReleased(const ButtonType p_ButtonName) = 0;

    /// TODO : other joystick related handling methods.
    ////

    ////
    /// TODO : other joystick related methods.
    ////
}; // class IJoystickHandler


/** \class IKeyboard

    An interface class for concrete implementations of classes that allow the user to access current keyboard key states.
    The Keyboard singleton object has an internal pointer that points to a specific implementation of a IKeyboard object.
    User/s access the current keyboard states via the Keyboard class where internally the Keyboard singleton instance will query a concrete implementation of the IKeyboard interface.

*/
class IKeyboard
{
public:
    ~IKeyboard(void) = default;

    virtual bool keyPressed(const ke::Key p_Key) = 0;
    virtual bool keyReleased(const ke::Key p_Key) = 0;

}; // IKeyboard class

} // KE ns