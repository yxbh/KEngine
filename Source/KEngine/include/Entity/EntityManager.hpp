#pragma once
#include "../engine_common.hpp"
#include "Types.hpp"
#include "../Common/Time.hpp"
#include "../Utility/NonCopyable.hpp"
#include "IEntityManager.hpp"

namespace ke
{

/** class EntityManager
    Singleton class.
*/
class EntityManager
    : public ke::NonCopyable
{
private:
    static ke::EntityManagerUPtr  s_upEntityManager;

public:
    /** Initialise singleton with a raw pointer point to an instance of IEntityManager derived type.
        The internal IEntityManager instance is replaced if this method is called again after the first time.
        All Entities are moved over to the new manager during the swap.
        @return false if argv is null or initialisation fails. */
    static bool initialise(IEntityManager * const p_pEntityManager);
    /** Shut down the system. Destory & remove all Entities. */
    static void shutDown(void);

    /** @return reference to singleton. */
    static ke::IEntityManager & getSingleton(void);

    /** */
    static bool createEntity(/** */);
    /** Add an Entity to the manager. */
    static bool addEntity(const ke::EntitySPtr p_Entity);
    /** @return a weak pointer to an Entity. nullptr if the Entity does not exist. */
    static ke::EntityWPtr getEntity(const ke::EntityID p_EID);
    /** Destory an Entity. @return true if success, false otherwise. */
    static bool destoryEntity(const ke::EntityID p_EID);
    /** Destory all Entities managed by this EntityManager. */
    static void destoryAllEntity(void);


private:
    static bool isReady(void);

}; // EntityManager class

} // KE ns