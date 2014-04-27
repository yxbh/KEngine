#pragma once
#include <cstdint>

namespace ke
{

using EntityComponentID = std::uint64_t;

/** \class EntityComponentID
    An ID that is statically unique.
    Each EntityComponent type should have an unique ID, declared at compile time.
*/
static const EntityComponentID Invalid_EntityComponentID = 0;

}
