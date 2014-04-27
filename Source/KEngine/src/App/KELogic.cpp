#include "../../include/App/KELogic.hpp"
#include "../../include/App/HumanView.hpp"
#include "../../include/Input/Interfaces.hpp"
#include "../../include/Entity/EntityManager.hpp"
#include "../../include/Entity/DefaultEntityManager.hpp"

namespace ke
{

KELogic::KELogic(void)
{
    m_upTaskManager = std::move(std::make_unique<ke::TaskManager>());
}

bool KELogic::initialise(void)
{
    ke::Debug::print("KELogic::Init : begin initialisation.");

    ke::EntityManager::initialise(new ke::DefaultEntityManager());
    return true;
}

void KELogic::shutDown(void)
{
    ke::Debug::print("KELogic::ShutDown : begin shutdown.");

    // shut down EntityManager (all Entity's are expected to be destoryed before/during this).
    ke::EntityManager::shutDown();

    // shut down all updatable & non-updatable Systems.
    for (auto system : m_UpdatableSystems)
        system->shutDown();
    for (auto system : m_NonUpdatableSystems)
        system->shutDown();

    ke::Debug::print("KELogic::ShutDown : /shutdown.");
}

void KELogic::update(const ke::Time p_ElapsedTime)
{
    /*
        NOTE:
            In the GCC engine, the logic Update call checks what state the application is currently in and then carry out different operations accordingly.
            So we probably should define some logic states(i.e. running, paused, mainmenu etc) and have a switch statement.
    */

    // update logic lifetime.
    m_LifeTime += p_ElapsedTime;
    if (m_LifeTime.asMicroseconds() < 0)
        ke::Debug::printWarning("KELogic::Update : Logic life time over flow!");

    // call update on Logic's TaskManager
    assert(m_upTaskManager);
    m_upTaskManager->updateAllTasks(p_ElapsedTime);

    // update all updatable systems.
    for (ke::SystemSPtr system_sp : m_UpdatableSystems)
        system_sp->update(p_ElapsedTime);

    // update all views regardless of Logic state.
    for (ke::ViewSPtr view_sp : m_ViewSPs)
        view_sp->update(p_ElapsedTime);

    // update all in app/game Entity's.
    ke::EntityManager::getSingleton().updateAllEntities(p_ElapsedTime);
}

ke::ViewSPList & KELogic::getViews(void)
{
    return m_ViewSPs;
}

void KELogic::addView(ViewSPtr p_spNewView, const EntityID p_EntityID)
{
    static ViewID view_id { 0 };
    assert(p_EntityID != InvalidEntityID); // make sure EntityID is valid.
    ++view_id;  assert(view_id > 0);
    m_ViewSPs.push_back(p_spNewView);
    p_spNewView->ke::IView::Attach(view_id, p_EntityID);
}

void KELogic::removeView(ViewSPtr p_spView)
{
    m_ViewSPs.remove(p_spView);
}

ke::EntityWPtr KELogic::getEntity(const ke::EntityID p_EntityID)
{
    ke::EntitySPMap::iterator it(m_EntitySPMap.find(p_EntityID));
    if (it == m_EntitySPMap.end())
        return ke::EntityWPtr();
    return it->second;
}

void KELogic::destoryEntity(const EntityID p_EntityID)
{
    if (p_EntityID == ke::InvalidEntityID)
        ke::Debug::printError("KELogic::DestoryEntity : Invalid EntityID.");

    EntitySPMap::size_type num_erased(m_EntitySPMap.erase(p_EntityID));
    if (num_erased != 1)
        ke::Debug::printError("KELogic::DestoryEntity : number of Entity removed does not equal 1.");
}

void KELogic::attachTask(ke::TaskSPtr p_spTask)
{
    m_upTaskManager->add(p_spTask);
}

bool KELogic::registerSystem(SystemSPtr p_spSystem)
{
    bool already_registered { false };
    if (p_spSystem->isUpdatable()) // register updatable system
    {
        for (auto system_sp : m_UpdatableSystems)
            if (system_sp == p_spSystem)
            {
                already_registered = true;
                break;
            }
        if (!already_registered)
            m_UpdatableSystems.push_back(p_spSystem);
    }
    else // register none updatable system
    {
        for (auto system_sp : m_NonUpdatableSystems)
            if (system_sp == p_spSystem)
            {
                already_registered = true;
                break;
            }
        if (!already_registered)
            m_NonUpdatableSystems.push_back(p_spSystem);
    }

    if (already_registered)
    {
        ke::Debug::printWarning("KELogic::RegisterSystem : System already registered, system name = " + std::string(p_spSystem->getName()));
        return already_registered;
    }
    return true;
}

} // KE ns