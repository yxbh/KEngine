#pragma once
#include <string>
#include <sstream>

/** macro */
#define KE_UNREFERENCED_PARAMETER(P) P

namespace ke
{
template <typename IntType>
std::string IntToHexString(const IntType p_Value)
{
    std::stringstream sstream;
    sstream << std::hex << std::showbase << p_Value;
    return sstream.str();
}

}
