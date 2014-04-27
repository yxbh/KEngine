#pragma once
#include "../std_common.hpp"

namespace ke
{

/** \class EventType
*/
using EventType = std::uint32_t;
using EventID   = EventType;
const EventType InvalidEvent = 0x00000000;

using ListenerID = std::uint64_t;
const ListenerID InvalidListenerID
{
    0
};

class IEvent;
using EventSPtr = std::shared_ptr<ke::IEvent>;
using EventUPtr = std::unique_ptr<ke::IEvent>;
using EventWPtr = std::weak_ptr<ke::IEvent>;

class IEventManager;
using EventManagerSPtr = std::shared_ptr<ke::IEventManager>;
using EventManagerUPtr = std::unique_ptr<ke::IEventManager>;
using EventManagerWPtr = std::weak_ptr<ke::IEventManager>;

/** \class EventDelegateHandle

    A handle is used to represent a single connection/delegate to a specific event type.

*/
using EventDelegateHandle = std::uint32_t;
const EventDelegateHandle InvalidEventDelegateHandle = 0;

} // KE ns