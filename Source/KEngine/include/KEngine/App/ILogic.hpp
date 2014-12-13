#pragma once

#include "Types.hpp"
#include "KEngine/Common/Time.hpp"
#include "KEngine/Entity/Types.hpp"

namespace ke
{

/** 
    \class ILogic
    \brief Defines the interface for KEngine's logic layer.
*/
class ILogic
{
public:
    virtual ~ILogic(void) = 0 {};

    /** Carry out any necessary initialisation. Child class must call it's parent's initialise() at the start of it's method.
    @return true if initialisation was successful. */
    virtual bool initialise(void) = 0;
    /** Carry out the shut down procedures. Child class must call it's parent's initialise() at the end of it's method.*/
    virtual void shutDown(void) = 0;

    /** Update method. */
    virtual void update(const ke::Time p_ElapsedTime) = 0;

    //// Views related operations.
    virtual ke::ViewSPList & getViews(void) = 0;
    virtual void addView(ViewSptr p_spNewView, const EntityID p_EntityID = ke::InvalidEntityID) = 0;
    virtual void removeView(ViewSptr p_spView) = 0;
    ////

    //// Entity related operations.
    virtual ke::EntityWptr getEntity(const ke::EntityID p_EntityID) = 0;
    virtual void destoryEntity(const EntityID p_EntityID) = 0;
    ////

}; // ILogic class

} // KE ns