#pragma once
#include <KEngine/Input/Keyboard.hpp>
#include <KEngine/Dev/dbg.hpp>
#include <KEngine/Input/Keyboard/SFMLKeyboard.hpp>

namespace ke
{

KeyboardUptr Keyboard::s_upKeyboard(new ke::SFMLKeyboard);

void Keyboard::set(KeyboardUptr && p_upKeyboard)
{
    if (Keyboard::isReady())
        ke::Debug::printWarning("Keyboard::Set : Instance already instantiated. Freeing and replacing the previous instance...");
    s_upKeyboard = std::move(p_upKeyboard);
}

bool Keyboard::isReady(void)
{
    return s_upKeyboard != nullptr;
}

bool Keyboard::keyPressed(const ke::Key p_Key)
{
    if (!Keyboard::isReady())
    {
        ke::Debug::printError("Keyboard::IsKeyPressed : Keyboard singleton has not been instantiated yet!");
        return false;
    }
    return s_upKeyboard->keyPressed(p_Key);
}

bool Keyboard::keyReleased(const ke::Key p_Key)
{
    if (!Keyboard::isReady())
    {
        ke::Debug::printError("Keyboard::IsKeyReleased : Keyboard singleton has not been instantiated yet!");
        return false;
    }
    return s_upKeyboard->keyReleased(p_Key);
}

} // KE ns