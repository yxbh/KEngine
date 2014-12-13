#include <KEngine/Entity/DefaultEntityManager.hpp>
#include <KEngine/Entity/Entity.hpp>

namespace ke
{

bool DefaultEntityManager::addEntity(const ke::EntitySptr p_Entity)
{
    const auto result(m_EntityMap.insert(std::make_pair(p_Entity->getId(), p_Entity)));
    return result.second;
}

ke::EntityWptr DefaultEntityManager::getEntity(const ke::EntityID p_EID)
{
    std::map<EntityID, EntitySptr>::iterator entity_it { m_EntityMap.find(p_EID) };
    if (entity_it == m_EntityMap.end()) // not in manager.
        return EntityWptr();
    return entity_it->second; // implicit cast to Wptr
}

void DefaultEntityManager::updateAllEntities(const ke::Time p_Elapsed)
{
    for (auto & entity_pair : m_EntityMap)
        entity_pair.second->updateAll(p_Elapsed);
}

bool DefaultEntityManager::destoryEntity(const ke::EntityID p_EID)
{
    auto entity_it = m_EntityMap.find(p_EID);
    if (entity_it == m_EntityMap.end())
        return false;
    entity_it->second->destory(); // destory Entity first.
    m_EntityMap.erase(entity_it); // remove from Manager.
    return true;
}

void DefaultEntityManager::destoryAllEntity(void)
{
    for (auto key_val_pair : m_EntityMap) // destory all Entity first.
        key_val_pair.second->destory();
    m_EntityMap.clear(); // remove from map.
}

std::vector<ke::EntitySptr> DefaultEntityManager::dumpAllEntites(void)
{
    std::vector<ke::EntitySptr> dump_list;
    dump_list.reserve(m_EntityMap.size());
    for (auto entity_pair : m_EntityMap)
        dump_list.push_back(entity_pair.second);
    return dump_list;
}

bool DefaultEntityManager::initialise(void)
{
    return true;
}

bool DefaultEntityManager::shutDown(void)
{
    ke::Debug::print("DefaultEntityManager::ShutDown : shutting down.");
    this->destoryAllEntity();
    ke::Debug::print("DefaultEntityManager::ShutDown : /shutdown.");
    return true;
}

void DefaultEntityManager::update(const ke::Time p_Elapsed)
{
    this->updateAllEntities(p_Elapsed);
}

std::string DefaultEntityManager::getName(void) const
{
    return "DefaultEntityManager";
}

void DefaultEntityManager::handleEvent(const ke::EventSptr p_spEvent)
{
    switch (p_spEvent->getType())
    {
    // TODO : implementation.
    //  - add in handle for Entity related Events.

    default: assert(false); break;
    }
}

}