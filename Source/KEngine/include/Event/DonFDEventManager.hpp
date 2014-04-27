#pragma once
#include "../engine_common.hpp"
#include "IEventManager.hpp"
#include "EventQueue.hpp"
#include "Types.hpp"

namespace ke
{

using DonFastDelegate = fastdelegate::FastDelegate<void(ke::EventSPtr)>; // for unofficial version
//using DonFastDelegate = fastdelegate::FastDelegate1<ke::EventSPtr>; // for official version

/** \class DonFDEventManager
    \brief An IEventManager implementation that uses Don C's FastDelegate system.
*/
class DonFDEventManager
    : public ke::IEventManager
{
public:
    using DelegateType          = ke::DonFastDelegate;
    using ListenerMap           = std::map<DelegateType, ke::EventDelegateHandle>;
    using ListenerList          = std::list<DelegateType>;
    using EventListenersMap     = std::map<ke::EventType, ListenerList>;
    using EventQueue            = std::deque<ke::EventSPtr>;

private:
    ke::EventQueue                  m_ThreadSafeEventQueue;
    EventQueue                      m_EventQueue;
    EventListenersMap               m_Listeners;

public:
    DonFDEventManager(void) = default;
    virtual ~DonFDEventManager(void);

    /** */
    bool addListener(const DelegateType & p_rDelegate, const EventType p_EventType);
    /** Deregister a/all listener/delegate with the given EntityID from a specific event type.
        WARNING: This method currently removes all listeners that listens to the same EventType. */
    virtual bool removeListener(const ke::EventDelegateHandle p_Handle, const EventType p_EventType) final;
    /** Remove all listeners for the specified EventType. */
    virtual bool removeAllListeners(const EventType p_EventType) final;
    /** Remove a listener of DonFastDelegate type for a specified EventType. */
    bool removeListener(const DelegateType & p_rDelegate, const EventType p_EventType);
    /** Add an event into the Event queue. */
    virtual void queue(ke::EventSPtr p_spNewEvent) final;
    /** Dispath \a p_Event to all listeners immediately.
        Listener might not respond to event immediately (e.g. IEventHandler::receiveEvent only stores the event in a queue and does not process the event immediately).
        @return false if no listener exists for this event's type. */
    virtual bool dispatchNow(ke::EventSPtr p_Event) final;
    /** Remove first instance of an event of a particular type. If true all event belong to the type will be removed. Does not remove event from the thread safe queue.*/
    virtual bool removeEvent(const EventType p_EventType, const bool p_RemoveAllSame = false) final;

    /** Fire off all Commands (With in limit, if one is set), returns true if all Commands were fired. */
    virtual bool update(const ke::Time p_Duration, const ke::Time p_DurationLimit = Time::Zero) final;

}; // DonFDEventManager class

} // KE ns