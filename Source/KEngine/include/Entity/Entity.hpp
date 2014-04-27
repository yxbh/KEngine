#pragma once
#include "../Utility/NonCopyable.hpp"
#include "Types.hpp"
#include "EntityID.hpp"
#include "../Common/Time.hpp"

namespace ke
{

/** \class Entity
    \brief A container and manager class for EntityComponents. Also an abstract representation of an entity.

    This class is not meant to be inhertied.
    This class is not copyable.

    Entity holds strong reference to it's Components and the components also hold strong references to
    the entity. Therefore Destory() must be called otherwise the Entity cannnot be destoryed due to circular reference, and the components
    won't be able to destory themselves either.

    This class is modeled after GCC(4th ed)'s Actor class, and so the principles are similar.
*/
class Entity
    : public ke::NonCopyable
{
    friend class EntityFactory;

public:
    using EntityType    = std::string;
    using TagList       = std::vector<std::string>;

private:
    ke::EntityComponentSPMap        m_ComponentSPMap; // <EntityComponentType, EntityComponent>
    ke::EntityID                    m_EntityID;
    EntityType                      m_EntityType;

    TagList                         m_Tags; /** */
    std::string                     m_Name; /** An usually unique name. */

public:
    /** */
    Entity(const ke::EntityID = ke::EntityID::newID());
    Entity(const Entity & p_rEntity) = delete;
    Entity & operator = (const Entity & p_rEntity) = delete;
    Entity(ke::Entity && p_rrEntity); // need '= default'
    Entity & operator = (ke::Entity && p_rrEntity); // need '= default'
    ~Entity(void);

    /** Adds a componenet. This function must be called when the Entity is passed to say EntityComponent. */
    void addComponent(ke::EntityComponentSPtr p_spEntityComponent);
    /** Destory the Entity. Breaks the circular/strong references to the Entity's components. */
    inline void destory(void) { m_ComponentSPMap.clear(); }

    /** Update all components with elapsed time. */
    virtual void updateAll(const ke::Time p_ElapsedTime);

    /** @return a weak pointer to the requested Component type with the specified EntityComponentID. */
    template <class ComponentClassType>
    std::weak_ptr<ComponentClassType> getComponent(const ke::EntityComponentType p_ComponentType);

    /** @return the unique EntityID. */
    ke::EntityID getID(void) const;
    /** @return the type of the Entity. */
    Entity::EntityType getType(void) const;
    /** @return a reference to the list of tags this Entity has. */
    const TagList & getTags(void) const;
    /** @return reference to name of the entity. */
    const std::string & getName(void) const;

}; // Entity class


inline ke::EntityID Entity::getID(void) const { return m_EntityID; }
inline Entity::EntityType Entity::getType(void) const { return m_EntityType; }
inline const Entity::TagList & Entity::getTags(void) const { return m_Tags; }
inline const std::string & Entity::getName(void) const { return m_Name; }
template <class ComponentClassType>
inline std::weak_ptr<ComponentClassType> getComponent(const ke::EntityComponentType p_ComponentType)
{
    EntityComponentSPMap::iterator it(m_Components.find(p_ComponentType));
    if (it == m_Components.end()) // does not contain component
        return nullptr;
    return std::weak_ptr<ComponentClassType>(std::static_pointer_cast<ComponentClassType>(it->second)); // return weak pointer version.
}

} // KE ns
