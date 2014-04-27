#pragma once

namespace ke
{


/** \class Key

    Keys on a standard US keyboard.

*/
enum class Key
{
    Invalid,
    Unknown,
    // Alphabet
    A,  B,  C,  D,  E,  F,  G,
    H,  I,  J,  K,  L,  M,  N,
    O,  P,  Q,  R,  S,  T,
    U,  V,  W,  X,  Y,  Z,
    // number row  keys
    Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0,
    // numpad numbers
    Numpad1, Numpad2, Numpad3, Numpad4, Numpad5, Numpad6, Numpad7, Numpad8, Numpad9, Numpad0,
    // F keys
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,
    F11, F12, F13, F14, F15, F16, F17, F18, F19, F20,
    F21, F22, F23, F24, F25, F26, F27, F28, F29, F30,
    //
    Escape,
    //
    LControl, LShift, LAlt, LSystem,
    //
    RControl, RShift, RAlt, RSystem,
    //
    Menu,
    LBracket,   RBracket,
    // Punctuations.
    SemiColon, Comma, Period,
    Quote,
    Slash, BackSlash,
    Tilde,
    Equal,
    Dash,
    Space,
    Return,
    BackSpace,
    Tab,
    //
    PageUp, PageDown, End, Home, Insert, Delete,
    // Arithemic operator
    Add, Subtract, Multiply, Divide,
    // Arrow keys
    Left, Right, Up, Down,
    // Number of keys
    NumKey,

}; // Key enum class


} // KE ns