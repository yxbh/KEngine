#pragma once
#include "IEntityManager.hpp"
#include "EntityID.hpp"

namespace ke
{

/** \class DefaultEntityManager
    Default implementation of the IEntityManager interface.
*/
class DefaultEntityManager
    : public ke::IEntityManager
{
private:
    std::map<EntityID, EntitySptr>     m_EntityMap;

public:

    //// IEntityManager interface.
    /** Add an Entity to the manager. */
    virtual bool addEntity(const ke::EntitySptr p_Entity) final;
    /** @return a weak pointer to an Entity. nullptr if the Entity does not exist. */
    virtual ke::EntityWptr getEntity(const ke::EntityID p_EID) final;
    /** Update all Entities with elapsed time. */
    virtual void updateAllEntities(const ke::Time p_Elapsed) final;
    /** Destory an Entity. @return true if success, false otherwise. */
    virtual bool destoryEntity(const ke::EntityID p_EID) final;
    /** Destory all Entities managed by this EntityManager. */
    virtual void destoryAllEntity(void) final;
    /** Return a vector to all Entities that are currently managed by this IEntityManager instance.
        NOTE: Use this only for switching IEntityManager implementation instances! */
    virtual std::vector<ke::EntitySptr> dumpAllEntites(void) final;
    ////

    //// ISystem interfaces.
    /** Initialise DefaultEntityManager. */
    virtual bool initialise(void) final;
    /** @return true if the System has shut down correctly. */
    virtual bool shutDown(void) final;
    /** Update all Entity's. */
    virtual void update(const ke::Time p_Elapsed) final;
    /** Return the name of the system. */
    virtual std::string getName(void) const final;
    ////

    //// IEventHandler interface
    virtual void handleEvent(const ke::EventSptr p_spEvent) final;
    ////

}; // DefaultEntityManager class

} // KE ns