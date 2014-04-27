#pragma once
#include "../IEvent.hpp"
#include "../../Entity/Types.hpp"

namespace ke
{

/** class EntityComponentRequested_Event
    An event specifying a request for building a specific EntityComponent.
*/
class EntityComponentRequested_Event
    : public ke::IEvent
{
public:
    static const EventType EventType = 0xC6319717;

private:
    ke::EntityComponentSPtr         m_spEComponent;
    ke::EntityComponentType         m_RequestedComponentType;       // unique id for the type of EntityComponent requested.
    std::string                     m_RequestedConfigRsrcPath;      // resource path to another JSON file used for initialising the new EntityComponent.

public:
    EntityComponentRequested_Event(const ke::EntityComponentType p_RequestedComponentType, const std::string p_RequestedConfigRsrcPath)
        : m_RequestedComponentType(p_RequestedComponentType), m_RequestedConfigRsrcPath(p_RequestedConfigRsrcPath) {}

    virtual ke::EventType getType(void) const final
    {
        return EntityComponentRequested_Event::EventType;
    }

    virtual std::string getName(void) const final
    {
        return "EntityComponentRequested_Event";
    }

    virtual ke::EventSPtr makeCopy(void) const final
    {
        auto copy = std::make_shared<EntityComponentRequested_Event>(m_RequestedComponentType, m_RequestedConfigRsrcPath);
        copy->SetComponent(m_spEComponent);
        return copy;
    }

    /** @return true if the EntityComponent is built (not nullptr). */
    bool IsComponentBuilt(void) const
    {
        return nullptr == m_spEComponent;
    }

    /** Set the EntityComponent held in this event/spec. */
    void SetComponent(ke::EntityComponentSPtr p_NewComponent = nullptr)
    {
        m_spEComponent = p_NewComponent;
    }

    /** @return the ID of the requested EntityComponent. */
    const ke::EntityComponentType GetComponentType(void) const
    {
        return m_RequestedComponentType;
    }

    /** @return path to the Component configuration resource file. */
    const std::string & GetConfigResourcePath(void) const
    {
        return m_RequestedConfigRsrcPath;
    }

    /** @return the EntityComponent. Could be nullptr if it's not built. */
    ke::EntityComponentSPtr getComponent(void)
    {
        return m_spEComponent;
    }

}; // ExitRequested_Event class


} // KE ns