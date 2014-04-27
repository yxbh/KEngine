#pragma once
#include "IEvent.hpp"
#include "EventQueue.hpp"

namespace ke
{

/** \class IEventHandler
    \brief An abstract class for implementing an object which listens to and handles Events.

    A child class of a class which inherits directly or indirectly from this class must call it's parent's register/deregister methods when it's own method is called.
    I.E. class B which inherits from class A which is a child of EventHandler will have to call A::RegisterEventListener in it's B::RegisterEventListener method.

    An IEventHandler can handle/process Events in 3 ways: immediate, delayed-update or a mix of the two.
        -   immediate is calling ke::EventManager::addListener() with handleEvent() passed to it. When an Event is received it will be handled by the handleEvent() function which
            is supposed to handle the event immediately.
        -   delayed-update is calling ke::EventManager::addListener() with receiveEvent() passed to it. When an Event is received, the Event is stored in the IEventHandler's
            internal queue. Later processAllReceivedEvents() must be called which internally calls handleEvent() on the received Events.

    NOTE:
        The abstract class's register & deregister methods make sure:
            - Deregistration can only happen when the EventHandler is already registerd.
            - Both registration & deregistration can only happen once consecutively.
            - A Handler can register again after it's deregistered.
        Therefore a child class must call it's parent's corresponding register/deregister methods.
*/
class IEventHandler
{
private:
    ke::EventDelegateHandle     m_Handle;
    bool                        m_IsRegistered = false;
    ke::EventQueue              m_EventQueue;

public:
    IEventHandler(void);
    IEventHandler(const IEventHandler &) = default;
    virtual IEventHandler & operator = (const IEventHandler &) = default;
    // TODO : move ctor & assignment otor.
    virtual ~IEventHandler(void) = 0;

    /** Return the unique handle to this object for IDing in the EventManager. */
    const ke::EventDelegateHandle getHandle(void);

    /** Register handler to listen implementation required EventTypes. All child class in a EventHandler class hierachery must call it's parent RegisterEventListner() method. */
    virtual void registerEventListener(void);
    /** Deregister handler from listening to implementation required EventTypes. All child class in a EventHandler class hierachery must call it's parent deregisterEventListener() method. */
    virtual void deregisterEventListener(void);

    /** Receive an Event and store in it's internal thread safe EventQueue. */
    void receiveEvent(const ke::EventSPtr p_spEvent);
    /** Handle/response a single event. */
    virtual void handleEvent(const ke::EventSPtr p_spEvent) = 0;
    /** Calls handleEvent() for all received events. Call this in an update() function/method.
        NOTE: this method is NOT virtual.
        TODO : interface not final as of 07/02/2014 */
    void processAllReceivedEvents(/*const ke::Time p_Elapsed, const ke::Time p_ProcessDurationLimit = ke::Time::Zero*/);
    /** @return the 1st event from internal queue, nullptr if queue is empty. */
    ke::EventSPtr firstEvent(void);

    /** @return true if Handler is already registered to the EventManager. */
    bool isRegistered(void) const;

private:
    /** Set internal flag to true/false which indicates whether the Handler has been registered already. */
    void setRegistered(const bool p_Registered = true);

}; // IEventHandler class

} // KE ns