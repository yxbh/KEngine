#pragma once
#include "Types.hpp"
#include "Interfaces.hpp"
#include "../Utility/NonCopyable.hpp"
#include "Keys.hpp"

namespace ke
{

/** class Keyboard

    A singleton class for accessing connected keyboard key states.

    The class internally holds a pointer to an instance of a specific implementation of the IKeyboard interface.
    This allows different keyboard class type implementations to be used in the future.

*/
class Keyboard
    : public ke::NonCopyable
{
private:
    static KeyboardUPtr s_upKeyboard;

public:
    static void set(KeyboardUPtr && p_upKeyboard);
    static bool isReady(void);
    static bool keyPressed(const ke::Key p_Key);
    static bool keyReleased(const ke::Key p_Key);

}; // Keyboard

} // KE ns