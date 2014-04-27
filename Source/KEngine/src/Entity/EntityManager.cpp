#include "../../include/Entity/EntityManager.hpp"
#include "../../include/Entity/IEntityManager.hpp"

namespace ke
{

ke::EntityManagerUPtr  EntityManager::s_upEntityManager = nullptr;

bool EntityManager::initialise(IEntityManager * const p_pEntityManager)
{
    ke::Debug::print("EntityManager::Init : initialising singleton.");

    // setup lambda to check valid argv.
    auto valid_ptr_argv = [&p_pEntityManager]()
    {
        if (!p_pEntityManager) // check parameter ptr.
        {
            ke::Debug::printError("EntityManager::Init : Invalid instance of p_pEntityManager given.");
            return false;
        }
        return true;
    };

    if (EntityManager::isReady()) // check internal ptr.
    {
        ke::Debug::printWarning("EntityManager::Init : Singleton already initialised, go ahead with re-initialisation.");

        if (!valid_ptr_argv())
            return false;

        // move all the Entity's over to the new Manager.
        auto entities = EntityManager::getSingleton().dumpAllEntites();
        for (ke::EntitySPtr entity : entities)
            p_pEntityManager->addEntity(entity);
    }
    else if (!valid_ptr_argv())
        return false;

    s_upEntityManager.reset(p_pEntityManager);
    return s_upEntityManager->initialise();
}

void EntityManager::shutDown(void)
{
    ke::Debug::print("EntityManager::ShutDown : shutting down.");
    if (!s_upEntityManager->shutDown())
        ke::Debug::printError("EntityManager::ShutDown : error shutting down instance of IEntityManager.");
    ke::Debug::print("EntityManager::ShutDown : /shutdown.");
}

ke::IEntityManager & EntityManager::getSingleton(void)
{
    assert(EntityManager::isReady());
    return *s_upEntityManager;
}

bool EntityManager::createEntity(/** */)
{
    assert(EntityManager::isReady());

    // TODO : call EntityFactory build method and then add to concrete IEntityManager instance.

    return false;
}

bool EntityManager::addEntity(const ke::EntitySPtr p_Entity)
{
    assert(EntityManager::isReady());
    return s_upEntityManager->addEntity(p_Entity);
}

ke::EntityWPtr EntityManager::getEntity(const ke::EntityID p_EID)
{
    assert(EntityManager::isReady());
    return s_upEntityManager->getEntity(p_EID);
}

bool EntityManager::destoryEntity(const ke::EntityID p_EID)
{
    assert(EntityManager::isReady());
    return s_upEntityManager->destoryEntity(p_EID);
}

void EntityManager::destoryAllEntity(void)
{
    s_upEntityManager->destoryAllEntity();
}

bool EntityManager::isReady(void)
{
    return s_upEntityManager != nullptr;
}

} // KE ns