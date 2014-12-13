#pragma once

#include <cassert>
#include <memory>

namespace ke
{

/**
    \class Singleton
    \brief A template base class for utilising the curiously recurring template pattern to implement a class which can be used as a singleton.
*/
template<class T>
class Singleton
{
public:
    using SingletonType     = T;
    using SingletonPtrType  = typename std::unique_ptr<T>;

protected:
    static SingletonPtrType s_SingletonInstance; ///< singleton instance of the class.

public:
    /**
        Set the current singleton instance of the object to the new one. Ownership is transferred.
    */
    static void setSingleton(T * const p_pNewInstance)
    {
        s_SingletonInstance.reset(p_pNewInstance);
    }

    /**
        @return a raw pointer to the singleton instance.
    */
    static T * const getSingleton(void)
    {
        assert(s_SingletonInstance);
        if (!s_SingletonInstance)
            throw std::logic_error("Singleton::getSingleton() : singleton uninitialised.");
        return s_SingletonInstance.get();
    }

}; // Singleton class

/*
    Singleton<> template static member initialisation.
*/
template<typename T>
typename Singleton<T>::SingletonPtrType Singleton<T>::s_SingletonInstance = nullptr;

} // ke ns