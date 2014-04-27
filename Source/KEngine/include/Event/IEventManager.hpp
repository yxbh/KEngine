#pragma once
#include "../Utility/NonCopyable.hpp"
#include "../Common/Time.hpp"
#include "Types.hpp"

namespace ke
{

/** \class IEventManager
    \brief An interface for implementing an EventManager class.
*/
class IEventManager
    : public ke::NonCopyable
{
public:
    using DelegateType = void;

public:
    virtual ~IEventManager(void) = default;

    /** Remove all listeners for the specified EventType. */
    virtual bool removeAllListeners(const EventType p_EventType) = 0;
    /** Deregister a listener/delegate with the given EntityID from a specific event type. */
    virtual bool removeListener(const ke::EventDelegateHandle p_Handle, const EventType p_CmdType) = 0;
    /** Add an event into the Event queue. */
    virtual void queue(ke::EventSPtr p_spNewEvent) = 0;
    /** Call all delegates listening to that event now. Return false if Event is not handled for whatever reason. */
    virtual bool dispatchNow(ke::EventSPtr p_Event) = 0;
    /** Remove first instance of an event of a particular type. If true all event belong to the type will be removed. Does not remove event from the thread safe queue.*/
    virtual bool removeEvent(const EventType p_EventType, const bool p_RemoveAllSame = false) = 0;

    /** Fire off all Commands (With in limit, if one is set), returns true if all Commands were fired. */
    virtual bool update(const ke::Time p_Duration, const ke::Time p_DurationLimit = Time::Zero) = 0;

}; // IEventManager class

} // KE ns