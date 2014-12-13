#pragma once
#include "../engine_common.hpp"
#include "../Event/IEvent.hpp"

namespace ke
{


/** \class SFMLWindowRequest_Event

    Request Event for the main application window.

*/
class SFMLWindowRequest_Event
    : public ke::IEvent
{
public:
    static const EventType EventType = 0xC53002CF;

public:
    /** Ctor. */
    SFMLWindowRequest_Event(void) = default;
    /** Dtor. */
    virtual ~SFMLWindowRequest_Event(void) = default;

    ke::EventType getType(void) const
    {
        return SFMLWindowRequest_Event::EventType;
    }

    virtual std::string getName(void) const final
    {
        return "SFMLEvent_Event";
    }

    virtual ke::EventSptr makeCopy(void) const final
    {
        return std::make_shared<SFMLWindowRequest_Event>();
    }

}; // SFMLEvent_Event class


} // KE ns