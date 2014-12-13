#pragma once
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4201 4245 4310) // nameless struct/union warning. Caused by C++11 flag in GLM?
#endif
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#ifdef _MSC_VER
#pragma warning(pop)
#endif

namespace ke
{

/* double floating point vector types. */
using Vec2 = glm::dvec2;
using Vec3 = glm::dvec3;
using Vec4 = glm::dvec4;

/* floating point vector types. */
using Vec2f = glm::fvec2;
using Vec3f = glm::fvec3;
using Vec4f = glm::fvec4;

/* integer vector types. */
using Vec2i = glm::ivec2;
using Vec3i = glm::ivec3;
using Vec4i = glm::ivec4;

/* unsigned vector types. */
using Vec2u = glm::uvec2;
using Vec3u = glm::uvec3;
using Vec4u = glm::uvec4;


namespace maths
{

static const double Pi = 3.14159265358979323846264; /** Value of Pi. */

} // math ns

} // KE ns