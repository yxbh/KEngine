#include "../../include/Event/StdFuncEventManager.hpp"
#include "../../include/Utility/StopWatch.hpp"
#include "../../include/Event/IEvent.hpp"

namespace ke
{


StdFuncEventManager::~StdFuncEventManager(void)
{
    m_Listeners.clear();
    m_EventQueue.clear();
}

bool StdFuncEventManager::addListener(const ke::EventDelegateHandle p_Handle, const DelegateType & p_rEventDelegate, const EventType p_EventType)
{
    if (p_EventType == ke::InvalidEvent)
    {
        ke::Debug::printError("CommandManager : Invalid command type.");
        return false;
    }
    if (p_Handle == ke::InvalidEventDelegateHandle)
    {
        ke::Debug::printError("CommandManager : InvalidEventDelegateHandle.");
        return false;
    }

    ListenerMap & listeners = m_Listeners[p_EventType]; // find or create entry.
    if (listeners.find(p_Handle) != listeners.end())
    {
        ke::Debug::printWarning("EventManager : double registration.");
        return false;
    }

    listeners.insert(std::make_pair(p_Handle, p_rEventDelegate));
    return true;
}

bool StdFuncEventManager::removeListener(const ke::EventDelegateHandle p_Handle, const EventType p_EventType)
{
    if (p_Handle == ke::InvalidEventDelegateHandle)
        ke::Debug::printError("CommandManager : InvalidEventDelegateHandle.");
    auto it = m_Listeners.find(p_EventType);
    if (it == m_Listeners.end()) // no such event type registered.
        return false;

    ListenerMap & listeners = it->second;
    if (listeners.erase(p_Handle) == 0)
        return false;
    return true;
}

bool StdFuncEventManager::removeAllListeners(const EventType p_EventType)
{
    if (m_Listeners.find(p_EventType) == m_Listeners.end())
    {
        ke::Debug::printWarning("StdFuncEventManager::RemoveAllListener : no listener is registrated to listen to EventType " + std::to_string(p_EventType));
        return false;
    }
    m_Listeners[p_EventType].clear();
    return true;
}

void StdFuncEventManager::queue(ke::EventSPtr p_spNewEvent)
{
    m_ThreadSafeEventQueue.push(p_spNewEvent);
}

bool StdFuncEventManager::dispatchNow(ke::EventSPtr p_Event)
{
    assert(p_Event->getType() != ke::InvalidEvent);
    EventListenersMap::iterator it = m_Listeners.find(p_Event->getType());

    if (it == m_Listeners.end())
        return false;

    const ListenerMap & listeners(it->second);
    bool handled_event{ false };
    for (auto & listener : listeners)
    {
        listener.second(p_Event);
        handled_event = true;
    }
    return handled_event;
}

bool StdFuncEventManager::removeEvent(const EventType p_EventType, const bool p_RemoveAllSame)
{
    bool remove_success{ false };
    EventListenersMap::iterator listeners_it = m_Listeners.find(p_EventType);
    if (listeners_it == m_Listeners.end())
        return false;

    EventQueue::iterator it = m_EventQueue.begin();
    while (it != m_EventQueue.end())
    {
        auto it_for_delete = it; ++it; // erase() invalidates iterator. Make a copy and iterate original first.

        if (p_EventType != (*it_for_delete)->getType()) // different type, move on to next.
            continue;

        m_EventQueue.erase(it_for_delete); // type match, so remove.
        remove_success = true;

        if (!p_RemoveAllSame)
            break;
    }
    return remove_success;
}

bool StdFuncEventManager::update(const ke::Time p_Duration, const ke::Time p_DurationLimit)
{
    bool has_duraton_limit{ true };
    if (p_DurationLimit == ke::Time::Zero)
        has_duraton_limit = false;
    ke::Time elapsed;
    ke::StopWatch stopwatch;
    stopwatch.Restart();

    ke::EventSPtr moving_event_ptr;
    while (m_ThreadSafeEventQueue.poll(moving_event_ptr))
        m_EventQueue.push_back(moving_event_ptr);

    ke::EventSPtr event_ptr;
    while (!m_EventQueue.empty())
    {
        elapsed += stopwatch.GetElapsed(); stopwatch.Restart();
        if (elapsed >= p_Duration && has_duraton_limit) // if elapsed time if duration limit setted.
            break;

        event_ptr = m_EventQueue.front(); m_EventQueue.pop_front();

        auto listeners_it = m_Listeners.find(event_ptr->getType());
        if (listeners_it == m_Listeners.end()) // no listeners registered for this type.
            continue;

        ListenerMap & list(listeners_it->second);
        for (auto & listener : list)
            listener.second(event_ptr); // call delegate
    }

    if (m_ThreadSafeEventQueue.isEmpty())
        return true;
    return false;
}


} // KE ns
