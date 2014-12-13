#pragma once

#include "EntityComponentID.hpp"
#include "Types.hpp"
#include "../Common/Time.hpp"

#include <string>

namespace ke
{

/**
    \class IEntityComponent
    \brief A base class for implementing custom EntityComponent's. A EntityComponent is a container of 'data' belonging to an Entity.

    An EntityComponent must be created with a valid Entity object. A valid Entity object must always
    be provided into the constructors. Bad things would happen if you don't!!!

    Each different EntityComponent has a type, which is created from an UUID.

    Copy and move operations are disabled since this class utilises polymorphism.
*/
class IEntityComponent
{
    friend class EntityFactory;

public:
    using IDType        = ke::EntityComponentID; // type of the component instance id. each instance has an unique id at run time.

    static const EntityComponentType type = 0x0;

private:
    ke::EntitySptr      m_spOwnerEntity;  // owner
    std::string         m_Name;

public:
    /** Ctor. */
    IEntityComponent(EntitySptr p_spEntity);
    /** Copy ctor. */
    IEntityComponent(const IEntityComponent &) = delete;
    /** Move ctor. */
    //IEntityComponent(IEntityComponent &&) = delete; //NOTE: default move ctor not supported in VS12
    /** Assignment operator. */
    IEntityComponent & operator=(const IEntityComponent &) = delete;
    /** Move assignment operator. */
    //IEntityComponent & operator=(const IEntityComponent &&) = delete; // NOTE: default move assigment operaot not supported in VS12
    /** Dtor. */
    virtual ~IEntityComponent(void) = 0;

    /** Initalise the component with a JSON config resource file.
        @return true on success. */
    virtual bool initialise(void /* path to ini file? */) = 0;
    /** Carry out any post initialisation operations(e.g. operations that can't be done during initialisation). */
    virtual void postInitialise(void) = 0;
    /** Update this EntityComponent instance. */
    virtual void update(const ke::Time p_ElapsedTime) = 0;

    /** @return the instance ID of this EntityComponent. */
    inline const ke::EntityComponentID getId(void) const
    {
        return ke::Invalid_EntityComponentID; // TODO: There's no facility at the moment for ComponentID. Don't have a need for it yet anyway.
    }
    /** @return the type of this particular EntityComponent. */
    virtual const EntityComponentType getType(void) const = 0 { IEntityComponent::type; };
    /** @return the name of this particular EntityComponent. */
    inline const std::string & getName(void) const
    {
        return m_Name;
    }

    /** @return a shared pointer to this Component's owner Entity. */
    EntitySptr getOwnerEntity(void);
    /** Set the owner Entity of this Component instance.
        TODO: remove the component from it's original owner as well. */
    void setOwnerEntity(ke::EntitySptr p_spEntity);

}; // IEntityComponent class

} // KE ns
