#pragma once
#include "StdFuncEventManager.hpp"
#include "DonFDEventManager.hpp"

namespace ke
{

template<typename Instance, typename FunctionPtr>
inline void EventManager::addListener
    (const EventType p_EventType, FunctionPtr p_FunctionPtr, Instance p_Instance)
{
    switch (s_EventManagerType)
    {
    case DelegateType::StdFunction:
    {
        StdFuncDelegate event_delegate(std::bind(p_FunctionPtr, p_Instance, std::placeholders::_1));
        static_cast<StdFuncEventManager*>(EventManager::getSingleton())
            ->addListener(p_Instance->IEventHandler::getHandle(), event_delegate, p_EventType);
        break;
    }

    case DelegateType::DonFastDelegate:
    {
        DonFastDelegate event_delegate(fastdelegate::MakeDelegate(p_Instance, p_FunctionPtr));
        static_cast<DonFDEventManager*>(EventManager::getSingleton())
            ->addListener(event_delegate, p_EventType);
        break;
    }

    default:
    {
        ke::Debug::printFatalError("EventManager::AddListener : unhandled EventManager type!");
        break;
    }
    }
}

template<typename FunctionPtr>
inline void EventManager::addListener
    (const EventType p_EventType, FunctionPtr p_FunctionPtr, const EventDelegateHandle p_Handle)
{
    switch (s_EventManagerType)
    {
    case DelegateType::StdFunction:
    {
        StdFuncDelegate event_delegate(std::bind(p_FunctionPtr, std::placeholders::_1));
        static_cast<StdFuncEventManager*>(EventManager::getSingleton())
            ->addListener(p_Handle, event_delegate, p_EventType);
        break;
    }

    case DelegateType::DonFastDelegate:
    {
        //DonFastDelegate event_delegate(p_FunctionPtr));
        DonFastDelegate event_delegate = p_FunctionPtr;
        static_cast<DonFDEventManager*>(EventManager::getSingleton())
            ->addListener(event_delegate, p_EventType);
        break;
    }

    default:
    {
        ke::Debug::printFatalError("EventManager::AddListener : unhandled EventManager type!");
        break;
    }
    }
}

template<>
inline StdFuncEventManager * EventManager::getSingleton<StdFuncEventManager>(void)
{
    assert(s_EventManagerType == EventManager::DelegateType::StdFunction);
    assert(ke::EventManager::getSingleton());
    return static_cast<StdFuncEventManager*>(ke::EventManager::getSingleton());
}

template<>
inline DonFDEventManager * EventManager::getSingleton<DonFDEventManager>(void)
{
    assert(s_EventManagerType == EventManager::DelegateType::DonFastDelegate);
    assert(ke::EventManager::getSingleton());
    return static_cast<DonFDEventManager*>(ke::EventManager::getSingleton());
}

template<class DelegateT>
inline DelegateT * EventManager::getSingleton(void)
{
    static_assert(false, "EventManager::getSingleton : invalid template arguement. Wrong EventManager delegate type!");
    return static_cast<DelegateT*>(ke::EventManager::getSingleton());
}

} // KE ns