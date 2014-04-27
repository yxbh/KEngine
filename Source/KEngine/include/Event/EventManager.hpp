#pragma once
#include "../std_common.hpp"
#include "../Utility/StaticClass.hpp"
#include "../Common/Time.hpp"
#include "Types.hpp"
#include "IEventHandler.hpp"

namespace ke
{

/** \class EventManager
    \brief Singleton EventManger. A global event manager.
    EventManager is a singleton object whose lifetime is the same as the applications. Therefore it can be used at anytime as soon as it's initialised.

    The EventManager supports two types of delegates (callback types), handled internally by two different implementations. Only one can be used at any single time.
    The available delegate types are \a DonFastDelegate and \a StdFunction. The type is set during initialisation and cannot be changed after.
    The DelegateType::DonFastDelegate implmentation is the fastest but does not support lambda.
    The DelegateType::StdFunction implementation supports all function types.

    In the StdFunction implementation, all listeners are registerd & ID'ed via handles. Each handle is unique. It's used to identify the listener during registration & deregistration.
    Read the implementation documentation for more details (DonFDEventManager, StdFuncEventManager).
*/
class EventManager
    : ke::StaticClass
{
public:
    enum class DelegateType
    {
        StdFunction,
        DonFastDelegate,
    };

private:
    static DelegateType             s_EventManagerType;

public:
    /** Initialise the EventManager to the default/specified EventManager type.
        This method must be called before calling anyother EventManager related methods/functions. */
    static bool initialise(const EventManager::DelegateType p_EventManagerType = DelegateType::StdFunction);
    /** @return raw pointer to the EventManager singleton instance. */
    static ke::IEventManager * getSingleton(void);
    /** @return a raw pointer to the singleton instance of the specific EventManager implementation type. */
    template<class DelegateT>
    static DelegateT * getSingleton(void);
    /** Add a listener (class functions) to the EventManager. */
    template<typename Instance, typename FunctionPtr>
    static void addListener(const EventType p_EventType, FunctionPtr p_FunctionPtr, Instance p_Instance);
    /** Add a listener (regular functions & static functions) to the EventManager. */
    template<typename FunctionPtr>
    static void addListener(const EventType p_EventType, FunctionPtr p_FunctionPtr, const EventDelegateHandle p_Handle = ke::InvalidEventDelegateHandle);
    /** Remove a listener of a specific EventType from the EventManager. @return true if success, false otherwise. */
    static bool removeListener(EventType p_EventType, IEventHandler * const p_pInstance);
    /** Remove a listener of a specific EventType from the EventManager. @return true if success, false otherwise. */
    static bool removeListener(EventType p_EventType, EventDelegateHandle p_Handle = ke::InvalidEventDelegateHandle);
    /** Remove all listeners of a specific EventType from the EventManager. @return true if success, false otherwise.*/
    static bool removeAllListeners(const EventType p_EventType);
    /** Dispath \a p_Event to all listeners immediately.
        Listener might not respond to event immediately (e.g. IEventHandler::receiveEvent only stores the event in a queue and does not process the event immediately).
        @return false if no listener exists for this event's type. */
    static void dispatchNow(ke::EventSPtr p_spEvent);
    /** Queue an Event. This method should be thread safe. */
    static void queue(ke::EventSPtr p_spNewEvent);
    /** Process Events in the internal queue. (with in the duration limit if there is one. Zero means no duration limit)*/
    static void update(const ke::Time p_Elapsed = ke::Time::Zero, const ke::Time p_ExcutionDurationLimit = ke::Time::Zero);
    /** Generate a new unused handle. */
    static EventDelegateHandle genNewHandle(void);

}; // EventManager class

} // KE ns

#include "EventManager.inl"