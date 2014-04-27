#pragma once
#include "../../engine_common.hpp"
#include "../IEvent.hpp"

namespace ke
{

/** class SFMLWindow_Event

Request Event for the main application window.

*/
class SFMLWindow_Event
    : public ke::IEvent
{
public:
    static const EventType EventType = 0xBE054DE7;

    using WindowType = std::shared_ptr<sf::RenderWindow>;

private:
    WindowType  m_AppWindow;

public:
    /** Ctor. */
    SFMLWindow_Event(WindowType p_spWindow)
        : m_AppWindow(p_spWindow)
    {}
    /** Dtor. */
    virtual ~SFMLWindow_Event(void) = default;

    ke::EventType getType(void) const
    {
        return SFMLWindow_Event::EventType;
    }

    virtual std::string getName(void) const final
    {
        return "SFMLEvent_Event";
    }

    virtual ke::EventSPtr makeCopy(void) const final
    {
        return std::make_shared<SFMLWindow_Event>(m_AppWindow);
    }

    WindowType GetAppWindow(void)
    {
        return m_AppWindow;
    }

}; // SFMLEvent_Event class


} // KE ns