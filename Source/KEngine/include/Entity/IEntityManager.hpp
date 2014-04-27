#pragma once
#include "../engine_common.hpp"
#include "Types.hpp"
#include "../Common/Time.hpp"
#include "../System/ISystem.hpp"

namespace ke
{

/** class IEntityManager
    Interface defining the standard operations of an EntityManager implementation.
*/
class IEntityManager
    : public ke::ISystem
{
public:
    /** Dtor. */
    virtual ~IEntityManager(void) = 0 {};

    /** Add an Entity to the manager. */
    virtual bool addEntity(const ke::EntitySPtr p_Entity) = 0;
    /** @return a weak pointer to an Entity. nullptr if the Entity does not exist. */
    virtual ke::EntityWPtr getEntity(const ke::EntityID p_EID) = 0;
    /** Update all Entities with elapsed time. */
    virtual void updateAllEntities(const ke::Time p_Elapsed) = 0;
    /** Destory an Entity. @return true if success, false otherwise. */
    virtual bool destoryEntity(const ke::EntityID p_EID) = 0;
    /** Destory all Entities managed by this EntityManager. */
    virtual void destoryAllEntity(void) = 0;
    /** Return a vector to all Entities that are currently managed by this IEntityManager instance.
        NOTE: Use this only for switching IEntityManager implementation instances! */
    virtual std::vector<ke::EntitySPtr> dumpAllEntites(void) = 0;

}; // IEntityManager class

} // KE ns