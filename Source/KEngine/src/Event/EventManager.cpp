#include "../../include/Event/EventManager.hpp"


namespace ke
{
namespace core
{
static ke::EventManagerUPtr g_upEventManager{nullptr};
} // core ns

EventManager::DelegateType  EventManager::s_EventManagerType { EventManager::DelegateType::StdFunction };

bool EventManager::initialise(const EventManager::DelegateType p_EventManagerType)
{
    if (core::g_upEventManager) // check if EventManager is already initialised.
    {
        ke::Debug::printError("EventManager::Init : there is already an EventManager running!");
        return false;
    }

    switch (p_EventManagerType)
    {
    case EventManager::DelegateType::StdFunction:
    {
        ke::Debug::print("EventManager::Init : type StdFunction.");
        s_EventManagerType = DelegateType::StdFunction;
        core::g_upEventManager = std::make_unique<ke::StdFuncEventManager>();
        assert(core::g_upEventManager);
        return true;
    }

    case EventManager::DelegateType::DonFastDelegate:
    {
        ke::Debug::print("EventManager::Init : type DonFastDelegate.");
        s_EventManagerType = DelegateType::DonFastDelegate;
        core::g_upEventManager = std::make_unique<ke::DonFDEventManager>();
        assert(core::g_upEventManager);
        return true;
    }

    default:
    {
        ke::Debug::printFatalError("EventManager::AddListener : unhandled EventManager type!");
        break;
    }
    }

    return false;
}

ke::IEventManager * EventManager::getSingleton(void)
{
    assert(core::g_upEventManager);
    return core::g_upEventManager.get();
}

bool EventManager::removeListener(EventType p_EventType, IEventHandler * const  p_pInstance)
{
    return EventManager::removeListener(p_EventType, p_pInstance->getHandle());
}

bool EventManager::removeListener(EventType p_EventType, EventDelegateHandle p_Handle)
{
    // warn if invalid handle is provided and the event manager is StdFunction type. The handler cannot be removed!
    if (p_Handle == ke::InvalidEventDelegateHandle && s_EventManagerType == DelegateType::StdFunction)
        ke::Debug::printWarning("EventManager::RemoveListener : Invalid delegate handle given to a StdFunction type EventManager.");

    return core::g_upEventManager->removeListener(p_Handle, p_EventType);
}

bool EventManager::removeAllListeners(const EventType p_EventType)
{
    assert(core::g_upEventManager);
    return core::g_upEventManager->removeAllListeners(p_EventType);
}

void EventManager::dispatchNow(ke::EventSPtr p_spEvent)
{
    assert(core::g_upEventManager);
    core::g_upEventManager->dispatchNow(p_spEvent);
}

void EventManager::queue(ke::EventSPtr p_spNewEvent)
{
    assert(core::g_upEventManager);
    core::g_upEventManager->queue(p_spNewEvent);
}

void EventManager::update(const ke::Time p_Elapsed, const ke::Time p_ExcutionDurationLimit)
{
    assert(core::g_upEventManager);
    core::g_upEventManager->update(p_Elapsed, p_ExcutionDurationLimit);
}

EventDelegateHandle EventManager::genNewHandle(void)
{
    EventDelegateHandle current_unused_handle = 0;
    return ++current_unused_handle;
}

} // KE ns