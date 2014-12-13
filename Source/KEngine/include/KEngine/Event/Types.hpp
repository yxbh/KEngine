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
using EventSptr = std::shared_ptr<ke::IEvent>;
using EventUptr = std::unique_ptr<ke::IEvent>;
using EventWptr = std::weak_ptr<ke::IEvent>;

class IEventManager;
using EventManagerSptr = std::shared_ptr<ke::IEventManager>;
using EventManagerUptr = std::unique_ptr<ke::IEventManager>;
using EventManagerWptr = std::weak_ptr<ke::IEventManager>;

} // KE ns