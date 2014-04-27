#pragma once
#include "../IEvent.hpp"
#include <string>

namespace ke
{

/** class Text_Event

    A string event.

*/
class Text_Event
    : public ke::IEvent
{
public:
    static const EventType EventType = 0x7D56E8F4;

private:
    std::string  m_Text;

public:
    /** Ctor. */
    Text_Event(const std::string & p_rString)
        : m_Text(p_rString)
    {}
    /** Dtor. */
    virtual ~Text_Event(void) = default;

    virtual ke::EventType getType(void) const final
    {
        return Text_Event::EventType;
    }

    virtual std::string getName(void) const final
    {
        return "Text_Event";
    }

    virtual ke::EventSPtr makeCopy(void) const
    {
        return std::make_shared<Text_Event>(m_Text);
    }

}; // Text_Event class


} // KE ns