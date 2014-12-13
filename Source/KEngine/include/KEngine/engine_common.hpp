#pragma once

//// SFML & OpenGL
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
////

//// GLM library
#ifdef _MSC_VER
#pragma warning(push)
// 4201 : nameless struct/union warning. Caused by C++11 flag in GLM?
// 4245 : conversion from int to glm::uint (glm/gtc/packing.inl)
// 4310 : csat truncates constant value (glm/gtx/bit.inl)
#pragma warning(disable : 4201 4245 4310)
#endif
//#define GLM_MESSAGES // it will generate messages for each translation unit.
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#ifdef _MSC_VER
#pragma warning(pop)
#endif
////

//// FastDelegate lib
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100) // nameless struct/union warning. Caused by C++11 flag in GLM?
#endif
//#include "FastDelegate.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif
////

//// libJSON lib
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100) // unreferenced formal parameter.
#pragma warning(disable : 4127) // conditional expression is constant.
#endif
#include "libjson_7.6.1/libjson.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif
////

//// C++ std & STL stuff
#include "std_common.hpp"
////

//// engine utility/debug/tool
#include "Utility/Utility.hpp"
#include "Dev/dbg.hpp"
////