#include <KEngine/Event/IEventHandler.hpp>
#include <KEngine/Event/EventManager.hpp>

namespace ke
{

IEventHandler::~IEventHandler(void)
{
    if (this->isRegistered()) this->deregisterEventListener();
}

void IEventHandler::registerEventListener(void)
{
    if (this->isRegistered())
    {
        ke::Debug::printError("IEventHandler::RegisterEventListener : handler already registered.");
        assert(false);
    }
    this->setRegistered();
}

void IEventHandler::deregisterEventListener(void)
{
    if (!this->isRegistered())
    {
        ke::Debug::printError("IEventHandler::RegisterEventListener : handler already deregistered.");
        assert(false);
    }
    this->setRegistered(false);
}

void IEventHandler::receiveEvent(const ke::EventSptr p_spEvent)
{
    m_EventQueue.push(p_spEvent);
}

void IEventHandler::processAllReceivedEvents(void)
{
    ke::EventSptr event_sp;
    while ((event_sp = this->firstEvent()))
    {
        if (!event_sp) break; // queue empty, so nullptr returned.
        this->handleEvent(event_sp);
    }
}

ke::EventSptr IEventHandler::firstEvent(void)
{
    return m_EventQueue.pop();
}

bool IEventHandler::isRegistered(void) const
{
    return m_IsRegistered;
}

void IEventHandler::setRegistered(const bool p_Registered)
{
    m_IsRegistered = p_Registered;
}

} // KE ns