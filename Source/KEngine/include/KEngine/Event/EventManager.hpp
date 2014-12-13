#pragma once

#include "../Common/Time.hpp"
#include "IEventHandler.hpp"
#include "../std_common.hpp"
#include "Types.hpp"
#include "../Utility/Singleton.hpp"

#include <SRDelegate/SRDelegate.hpp>

#include <unordered_map>

namespace ke
{

template<typename R, typename... A>
using Delegate = typename generic::delegate<R(A...)>;

/**
    \class EventDelegate
    \brief The event delegate type.
*/
using EventDelegate = generic::delegate<void(EventSptr)>;

/**
    \class EventManager
    \brief Event control and delivery manager.
*/
class EventManager final
    : public ke::Singleton<EventManager>
{
public:
    using DelegateType      = ke::EventDelegate;
    using ListenerList      = std::vector<DelegateType>;
    using EventListenersMap = std::unordered_map<ke::EventType, ListenerList>;
    using EventQueue        = std::deque<ke::EventSptr>;

private:
    ke::EventQueue              m_ThreadSafeEventQueue;
    EventQueue                  m_EventQueue;
    EventListenersMap           m_Listeners;

public:
    virtual ~EventManager(void);

    /**
        Add an event delegate for the specified event type.
        @return false if the delegate is already listening to the specified event type.
    */
    bool EventManager::addListener(const EventType p_EventType, const DelegateType p_Delegate);
    /**
        Remove the given event delegate from the specified event type.
        @return false if the delegate does not listen to the specified event type.
    */
    bool EventManager::removeListener(const EventType p_EventType, const DelegateType p_Delegate);
    /**
        Remove all listeners of a specific EventType from the EventManager.
        @return true if success, false otherwise.
    */
    bool removeAllListeners(const EventType p_EventType);
    /**
        Dispath \a p_Event to all listeners immediately.
        Event is delivered to all listeners of the event type immediately, but it is not guaranteed that the listener will process immediately.
        (e.g. IEventHandler::receiveEvent only stores the event in a queue and does not process the event immediately).
        @return false if no listener exists for this event's type.
    */
    bool dispatchNow(ke::EventSptr p_spEvent);
    /**
        Queue an Event. This method should be thread safe.
    */
    void queue(ke::EventSptr p_spNewEvent);
    /** 
        Remove first instance of an event of a particular type. If true all event belong to the type will be removed.
        Does not remove event from the thread safe queue.
    */
    virtual bool removeEvent(const EventType p_EventType, const bool p_RemoveAllSame = false) final;
    /**
        Process Events in the internal queue(with in the duration limit if there is one. Zero means no duration limit).
        @return true if all events were processed.
    */
    bool update(const ke::Time p_Elapsed = ke::Time::Zero, const ke::Time p_ExcutionDurationLimit = ke::Time::Zero);

}; // EventManager class

} // KE ns