#include <KEngine/Event/IEvent.hpp>

namespace ke
{

IEvent::IEvent(const Time p_TimeStamp)
    : m_TimeStamp(p_TimeStamp)
{}

ke::Time IEvent::getTimeStamp(void) const
{
    return m_TimeStamp;
}


ke::EventType TestEvent::getType(void) const
{
    return TestEvent::EventType;
}

std::string TestEvent::getName(void) const
{
    return "TestEvent";
}

ke::EventSptr TestEvent::makeCopy(void) const
{
    return std::make_shared<TestEvent>();
}


ke::EventType Test2Event::getType(void) const
{
    return Test2Event::EventType;
}

std::string Test2Event::getName(void) const
{
    return "Test2Event";
}

ke::EventSptr Test2Event::makeCopy(void) const
{
    return std::make_shared<Test2Event>();
}

} // KE ns