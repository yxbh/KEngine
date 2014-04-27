#include "../../include/Event/DonFDEventManager.hpp"
#include "../../include/Event/IEvent.hpp"
#include "../../include/Utility/StopWatch.hpp"

namespace ke
{

DonFDEventManager::~DonFDEventManager(void)
{
    m_Listeners.clear();
    m_EventQueue.clear();
}


bool DonFDEventManager::addListener(const DelegateType & p_rDelegate, const EventType p_EventType)
{
    ListenerList & listeners(m_Listeners[p_EventType]);
    for (const DelegateType & listener : listeners)
        if (listener == p_rDelegate) // check if already in the list for specified EventType.
        {
            ke::Debug::printWarning("DonFDEventManager::AddListener : this listener already listens to event type " + std::to_string(p_EventType));
            return false;
        }

    listeners.push_back(p_rDelegate);
    return true;
}

bool DonFDEventManager::removeListener(const ke::EventDelegateHandle p_Handle, const EventType p_EventType)
{
    KE_UNREFERENCED_PARAMETER(p_Handle);
    m_Listeners[p_EventType].clear();
    return true;
}

bool DonFDEventManager::removeAllListeners(const EventType p_EventType)
{
    if (m_Listeners.find(p_EventType) == m_Listeners.end())
    {
        ke::Debug::printWarning("DonFDEventManager::RemoveAllListener : no listener is registerted to listen to EventType " + std::to_string(p_EventType));
        return false;
    }
    m_Listeners[p_EventType].clear();
    return true;
}

bool DonFDEventManager::removeListener(const DelegateType & p_rDelegate, const EventType p_EventType)
{
    if (m_Listeners.find(p_EventType) == m_Listeners.end())
    {
        ke::Debug::printWarning("DonFDEventManager::RemoveListener : no listener is registerted to listen to EventType " + std::to_string(p_EventType));
        return false;
    }
    ListenerList & listeners(m_Listeners[p_EventType]);
    for (ListenerList::const_iterator cit(listeners.begin()); cit != listeners.end(); ++cit)
    {
        if (*cit == p_rDelegate)
        {
            listeners.erase(cit);
            return true;
        }
    }
    return false;
}

void DonFDEventManager::queue(ke::EventSPtr p_spNewEvent)
{
    m_ThreadSafeEventQueue.push(p_spNewEvent);
}

bool DonFDEventManager::dispatchNow(ke::EventSPtr p_Event)
{
    assert(p_Event->getType() != ke::InvalidEvent);
    EventListenersMap::iterator it = m_Listeners.find(p_Event->getType());

    if (it == m_Listeners.end())
        return false;

    const ListenerList & listeners = it->second;
    bool handled_event(false);
    for (auto & listener : listeners)
    {
        listener(p_Event);
        handled_event = true;
    }
    return handled_event;
}

bool DonFDEventManager::removeEvent(const EventType p_EventType, const bool p_RemoveAllSame)
{
    bool remove_success(false);
    EventListenersMap::iterator listeners_it(m_Listeners.find(p_EventType));
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

bool DonFDEventManager::update(const ke::Time p_Duration, const ke::Time p_DurationLimit)
{
    bool has_duraton_limit = true;
    if (p_DurationLimit == ke::Time::Zero)
        has_duraton_limit = false;
    ke::Time elapsed;
    ke::StopWatch stopwatch; stopwatch.Restart();

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

        ListenerList & list(listeners_it->second);
        for (auto & listener : list)
            listener(event_ptr);    // call delegate
    }

    if (m_ThreadSafeEventQueue.isEmpty())
        return true;
    return false;
}

} // KE ns