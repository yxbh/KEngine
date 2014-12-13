#include "../Event/IEvent.hpp"

namespace ke
{

/** \class FrameTimeReport_Event

    Broadcasts the last frame-time/tick-duration for a particular system or loop.

*/
class FrameTimeReport_Event
    : public ke::IEvent
{
public:
    static const ke::EventType EventType = 0xEAA5CD8E;

    enum class ID
    {
        Invalid,
        EventLoop,
        MainLoop,
    };

private:
    ke::Time    m_TickDuration;
    ID          m_ID;

public:
    FrameTimeReport_Event(const Time p_FrameTime, const ID p_ID = ID::Invalid)
        : m_TickDuration(p_FrameTime), m_ID(p_ID)
    {}
    virtual ~FrameTimeReport_Event(void) = default;

    ke::EventType getType(void) const
    {
        return FrameTimeReport_Event::EventType;
    }

    virtual std::string getName(void) const final
    {
        return "FrameTimeReport_Event";
    }

    virtual ke::EventSptr makeCopy(void) const final
    {
        return std::make_shared<FrameTimeReport_Event>(m_TickDuration, m_ID);
    }

    ke::Time GetFrameDuration(void) const
    {
        return m_TickDuration;
    }

}; // IEvent class

} // KE ns