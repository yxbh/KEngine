#include <KEngine/Entity/EntityID.hpp>

#include <climits> // for max & min values.

namespace ke
{

const EntityID      EntityID::InvalidID = EntityID(0);
EntityID::IDSet     EntityID::s_CurrentlyActiveIDs;
EntityID            EntityID::s_CurrentID = EntityID::InvalidID;

EntityID EntityID::newID(void)
{
    while (EntityID::used(s_CurrentID))
        ++s_CurrentID;
    s_CurrentlyActiveIDs.insert(s_CurrentID);
    return s_CurrentID;
}

bool EntityID::used(const EntityID & p_rID)
{
    if (p_rID == ke::EntityID::InvalidID)
        return true;
    return s_CurrentlyActiveIDs.find(p_rID) != s_CurrentlyActiveIDs.end();
}

bool EntityID::free(const EntityID & p_rID)
{
    if (p_rID == ke::EntityID::InvalidID)
        return false;
    if (s_CurrentlyActiveIDs.erase(p_rID) != 1)
        return false;
    return true;
}

EntityID::IDType EntityID::maxIDValue(void)
{
    return ULLONG_MAX;
}

EntityID::IDType EntityID::minIDValue(void)
{
    return 0;
}

const ke::EntityID InvalidEntityID = ke::EntityID::InvalidID;

} // KE ns
