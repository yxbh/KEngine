#pragma once
#include "../std_common.hpp"
#include "IEventManager.hpp"
#include "EventQueue.hpp"
#include "Types.hpp"

namespace ke
{

using StdFuncDelegate       = std::function<void(EventSPtr)>;


/** \class StdFuncEventManager
    \brief A std::function implementation of the IEventManager interface.

    This event manager requires an \a EventDelegateHandle to manage all event handler operatings including adding and removing listeners. This is due to the fact that std::function has no operator== defined.
    This means that although static member functions and regular functions are supported and can be added as a listener, removal from the manager is not possible and the event manager will probably freak out when you attempt to add or remove listeners.
*/
class StdFuncEventManager
    : public IEventManager
{
public:
    using DelegateType          = ke::StdFuncDelegate;
    using ListenerMap           = std::map<ke::EventDelegateHandle, DelegateType>;
    using EventListenersMap     = std::map<ke::EventType, ListenerMap>;
    using EventQueue            = std::deque<ke::EventSPtr>;

private:
    ke::EventQueue                  m_ThreadSafeEventQueue;
    EventQueue                      m_EventQueue;
    EventListenersMap               m_Listeners;

public:
    StdFuncEventManager(void) = default;
    virtual ~StdFuncEventManager(void);

    /** Register a listener/delegate to a specific event type. */
    bool addListener(const ke::EventDelegateHandle p_Handle, const DelegateType & p_rEventDelegate, const EventType p_EventType);
    /** Deregister a listener/delegate with the given EntityID from a specific event type. */
    virtual bool removeListener(const ke::EventDelegateHandle p_Handle, const EventType p_EventType) final;
    /** Remove all listeners for the specified EventType. */
    virtual bool removeAllListeners(const EventType p_EventType) final;
    /** Deregister a listener/delegate from a specific event type. */
    //bool removeListener(const ke::CommandListenersMap & p_rEventDelegate, const EventType p_CmdType);
    /** Add an event into the Event queue. */
    virtual void queue(ke::EventSPtr p_spNewEvent) final;
    /** Dispath \a p_Event to all listeners immediately.
        Listener might not respond to event immediately (e.g. IEventHandler::receiveEvent only stores the event in a queue and does not process the event immediately).
        @return false if no listener exists for this event's type. */
    virtual bool dispatchNow(ke::EventSPtr p_Event) final;
    /** Remove first instance of an event of a particular type. If true all event belong to the type will be removed. Does not remove event from the thread safe queue.*/
    virtual bool removeEvent(const EventType p_EventType, const bool p_RemoveAllSame = false) final;

    /** Fire off all Commands (With in limit, if one is set), returns true if all Commands were fired. */
    virtual bool update(const ke::Time p_Duration, const ke::Time p_DurationLimit = ke::Time::microseconds(0)) final;

}; // StdFuncEventManager class


} // KE ns
