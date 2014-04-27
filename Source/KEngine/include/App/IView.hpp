#pragma once
#include "../engine_common.hpp"
#include "Types.hpp"
#include "../Entity/Types.hpp"
#include "../Utility/NonCopyable.hpp"
#include "../Common/Time.hpp"


namespace ke
{

/** \class IView
    An abstract interface class for implementing application View.
*/
class IView
{
protected:
    ViewID      m_ViewID        = InvalidViewID;
    ViewType    m_ViewType      = ViewType::Other;

    EntityID    m_EntityID      = InvalidEntityID;

public:
    virtual ~IView(void) = default;

    /** 'Attach' an Entity to this view. */
    void Attach(const ViewID p_ViewID, const EntityID p_EntityID);

    virtual void update(const ke::Time p_Elapsed) = 0;
    virtual void render(const ke::Time p_Elapsed) = 0;

    ViewID GetViewID(void);
    ViewType getType(void);
    EntityID GetEntityID(void);

}; // IView class


/** \class AIView
    An abstract interface class for implementing AI application View.
*/
class AIView
    : public IView
{
public:
    AIView(void);
    virtual ~AIView(void) = default;

    virtual void update(const ke::Time p_Elapsed) = 0;
    virtual void render(const ke::Time p_Elapsed) = 0;

}; // AIView class


} // KE ms