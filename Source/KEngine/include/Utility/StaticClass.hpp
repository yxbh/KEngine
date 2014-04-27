#pragma once
#include "NonCopyable.hpp"

namespace ke
{


/** \class StaticClass
*/
class StaticClass
    : NonCopyable
{
public:
    StaticClass(void) = delete;
}; // StaticClass class


} // KE ns