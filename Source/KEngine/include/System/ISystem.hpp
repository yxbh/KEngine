#pragma once
#include "../Common/Time.hpp"
#include "../Event/IEventHandler.hpp"
#include "../Utility/NonCopyable.hpp"

namespace ke
{

/** class ISystem

    An interface/abstract class for implementing a specific application or gameplay system. (I.E. A grenade system. Or a loot system which controls item drops. )

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
    /** @return true if the System has shut down correctly. */
    virtual bool shutDown(void) = 0;
    /** The update method. Override if the child class is an updatable system. */
    virtual void update(const ke::Time p_Elapsed)
    {
        KE_UNREFERENCED_PARAMETER(p_Elapsed);
    }
    /** Return the name of the system. */
    virtual std::string getName(void) const = 0;

    /** Return true is the system is updatable. */
    bool isUpdatable(void) const
    {
        return m_IsUpdatable;
    }

}; // ISystem class


//// System pointers.
using SystemSPtr = std::shared_ptr<ISystem>;
using SystemWPtr = std::weak_ptr<ISystem>;
using SystemUPtr = std::unique_ptr<ISystem>;
////

} // KE ns