#pragma once

#include "KEngine/Common/Time.hpp"
#include "KEngine/Event/IEventHandler.hpp"
#include "KEngine/Utility/NonCopyable.hpp"

#include "KEngine/macro_common.hpp"

namespace ke
{

/**
    \class ISystem
    \brief An interface/abstract class for implementing a specific application or gameplay system.
          (i.e. A grenade system. Or a loot system which controls item drops. )

    A System it self is an EventHandler.
*/
class ISystem
    : public ke::IEventHandler
    , public ke::NonCopyable
{
private:
    bool m_IsUpdatable = false;

public:
    /** Ctor. */
    ISystem(const bool p_Updatable = false)
        : m_IsUpdatable(p_Updatable) {}
    /** Dtor. */
    virtual ~ISystem(void) = default;

    /** Method for implementing initialisations. */
    virtual bool initialise(void) = 0;
    /** \return true if the System has shut down correctly. */
    virtual bool shutDown(void) = 0;
    /** The update method. Override if the child class is an updatable system. */
    virtual void update(const ke::Time p_Elapsed)
    {
        KE_UNUSED(p_Elapsed);
    }
    /** \return the name of the system. */
    virtual std::string getName(void) const = 0;

    /** Return true is the system is updatable. */
    bool isUpdatable(void) const
    {
        return m_IsUpdatable;
    }

}; // ISystem class


//// System pointers.
using SystemSptr = std::shared_ptr<ISystem>;
using SystemWptr = std::weak_ptr<ISystem>;
using SystemUptr = std::unique_ptr<ISystem>;
////

} // KE ns