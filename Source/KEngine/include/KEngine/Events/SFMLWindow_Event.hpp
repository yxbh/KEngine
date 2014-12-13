#pragma once

#include "KEngine/engine_common.hpp"
#include "KEngine/Event/IEvent.hpp"
#include "KEngine/Graphics/Types.hpp"

namespace ke
{

/** 
    \class SFMLWindow_Event
    \brief Request event for the main application window.

*/
class SFMLWindow_Event
    : public ke::IEvent
{
public:
    static const EventType EventType = 0xBE054DE7;

    using WindowType = ke::WindowSptr;

private:
    WindowType  m_AppWindow;

public:
    /** Ctor. */
    SFMLWindow_Event(WindowType p_spWindow) : m_AppWindow(p_spWindow) {}
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

    virtual ke::EventSptr makeCopy(void) const final
    {
        return std::make_shared<SFMLWindow_Event>(m_AppWindow);
    }

    WindowType GetAppWindow(void)
    {
        return m_AppWindow;
    }

}; // SFMLEvent_Event class


} // KE ns