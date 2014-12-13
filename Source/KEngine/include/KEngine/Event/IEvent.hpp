#pragma once
#include "../engine_common.hpp"
#include "../Common/Time.hpp"
#include "Types.hpp"


namespace ke
{

/** \class IEvent

    Base class for a Command object.
    Each derived class needs to define their own unique static EventType.

    Assignment operators and copy constructors are disabled as user should only use smart pointers to an Event class type.
    Use the makeCopy() method to make copies of the same event.

*/
class IEvent
{
private:
    ke::Time m_TimeStamp;

public:
    explicit IEvent(const Time p_TimeStamp = ke::Time::Zero);
    IEvent(const ke::IEvent & p_rIEvent) = delete;
    IEvent(const ke::IEvent && p_rrIEvent) = delete;
    IEvent & operator=(const IEvent & p_rIEvent) = delete;
    IEvent & operator=(const IEvent && p_rrIEvent) = delete;
    virtual ~IEvent(void) = default;

    ke::Time getTimeStamp(void) const;
    virtual ke::EventType getType(void) const = 0;
    virtual std::string getName(void) const = 0;
    virtual ke::EventSptr makeCopy(void) const = 0;

}; // IEvent class



/** \class TestEvent

    Just a simple test event for confirming the minimal functinoal level of the EventManager.

*/
class TestEvent
    : public ke::IEvent
{
public:
    static const EventType EventType = 0x4a6ee2cf;

public:
    TestEvent(void) = default;
    virtual ~TestEvent(void) = default;

    virtual ke::EventType getType(void) const final;
    virtual std::string getName(void) const final;
    virtual ke::EventSptr makeCopy(void) const final;

}; // TestEvent class

/** \class Test2Event

Just a simple test event for confirming the minimal functinoal level of the EventManager.

*/
class Test2Event
    : public ke::IEvent
{
public:
    static const EventType EventType = 0xB058ACFE;

public:
    Test2Event(void) = default;
    virtual ~Test2Event(void) = default;

    virtual ke::EventType getType(void) const final;
    virtual std::string getName(void) const final;
    virtual ke::EventSptr makeCopy(void) const final;

}; // TestEvent class

} // KE ns
