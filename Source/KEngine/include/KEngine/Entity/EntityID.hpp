#pragma once
#include "../std_common.hpp"

namespace ke
{

/** \class EntityID
    \brief An unique identifier for IDing game/application Entities.
*/
class EntityID
{
public:
    //// typedefs
    using IDType = std::uint64_t;
    using IDSet = std::set<EntityID>;
    ////

    //// constants
    static const EntityID InvalidID;
    ////

private:
    IDType  m_ID;

private:
    static IDSet            s_CurrentlyActiveIDs;
    static EntityID         s_CurrentID;

public:
    /** Default construct an unique EntityID. */
    EntityID(void) : m_ID(ke::EntityID::newID()) {};
    /** Construct an EntityID with the specified value \a p_ID. */
    explicit EntityID(const IDType p_ID) : m_ID(p_ID) {};

    inline operator IDType(void) const
    {
        return m_ID;
    };

    /** Return the internal ID value. */
    inline IDType getValue(void) const
    {
        return m_ID;
    }

    inline EntityID & operator ++(void)
    {
        ++m_ID;    // prefix
        return *this;
    }
    inline EntityID & operator --(void)
    {
        --m_ID;    // prefix
        return *this;
    }
    inline EntityID operator ++(const int)
    {
        decltype(m_ID) previous_val { m_ID };    // postfix
        ++(*this);
        return EntityID(previous_val);
    }
    inline EntityID operator --(const int)
    {
        decltype(m_ID) previous_val { m_ID };    // postfix
        --(*this);
        return EntityID(previous_val);
    }
    inline bool operator <(const EntityID & p_ID) const
    {
        return this->getValue() < p_ID.getValue();
    }
    inline bool operator >(const EntityID & p_ID) const
    {
        return this->getValue() > p_ID.getValue();
    }

    //// static methods
    /** return a new unsued EntityID. */
    static EntityID newID(void);
    /** check if an EntityID is currently being used. */
    static bool used(const EntityID & p_rID);
    /** remove an EntityID from the used pool. */
    static bool free(const EntityID & p_rID);
    /** @return the largest possible value for EntityID. */
    constexpr static IDType maxIDValue(void);
    /** @return the smallest possible value for EntityID. */
    constexpr static IDType minIDValue(void);
    ////

}; // EntityID class


extern const ke::EntityID InvalidEntityID;

}
