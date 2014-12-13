#pragma once
#include "../engine_common.hpp"
#include "../Event/IEvent.hpp"

namespace ke
{


/** \class SFMLEvent_Event

    A wrapper for a SFML event.

*/
class SFMLEvent_Event
    : public ke::IEvent
{
public:
    static const EventType EventType = 0xD1341C34;

private:
    sf::Event   m_SfEvent;

public:
    /** Ctor. */
    SFMLEvent_Event(const sf::Event & p_rEvent)
        : m_SfEvent(p_rEvent)
    {}
    /** Dtor. */
    virtual ~SFMLEvent_Event(void) = default;

    const sf::Event GetSFMLEvent(void) const
    {
        return m_SfEvent;
    }

    ke::EventType getType(void) const
    {
        return SFMLEvent_Event::EventType;
    }

    virtual std::string getName(void) const final
    {
        return "SFMLEvent_Event";
    }

    virtual ke::EventSptr makeCopy(void) const final
    {
        return std::make_shared<SFMLEvent_Event>(m_SfEvent);
    }

}; // SFMLEvent_Event class


} // KE ns