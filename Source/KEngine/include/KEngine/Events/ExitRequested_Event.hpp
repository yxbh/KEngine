#pragma once
#include "../Event/IEvent.hpp"

namespace ke
{

/** \class ExitRequested_Event

    Internal Engine event for requesting application exit. Used to shut down different systems and engine components.

*/
class ExitRequested_Event
    : public ke::IEvent
{
public:
    static const EventType EventType = 0x9A2C952E;

public:

    virtual ke::EventType getType(void) const final
    {
        return ExitRequested_Event::EventType;
    }

    virtual std::string getName(void) const final
    {
        return "ExitRequested_Event";
    }

    virtual ke::EventSptr makeCopy(void) const final
    {
        return std::make_shared<ExitRequested_Event>();
    }

}; // ExitRequested_Event class


} // KE ns