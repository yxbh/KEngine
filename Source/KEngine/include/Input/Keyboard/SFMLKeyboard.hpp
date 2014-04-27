#pragma once
#include "../Interfaces.hpp"
#include "SFML/Window/Keyboard.hpp"

namespace ke
{

/** class SFMLKeyboard
*/
class SFMLKeyboard
    : public ke::IKeyboard
{
public:
    ~SFMLKeyboard(void) = default;

    virtual bool keyPressed(const ke::Key p_Key);
    virtual bool keyReleased(const ke::Key p_Key);

}; // SFMLKeyboard class

extern sf::Keyboard::Key SFMLKey_Cast(const ke::Key p_Key);
extern ke::Key KEKey_Cast(const sf::Keyboard::Key p_Key);

} // KE ns
