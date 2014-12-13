#pragma once

#include "Types.hpp"
#include "KEngine/engine_common.hpp"
#include "KEngine/Common/Time.hpp"
#include "KEngine/Entity/Types.hpp"
#include "KEngine/Graphics/Types.hpp"
#include "KEngine/Utility/NonCopyable.hpp"


namespace ke
{

/** 
    \class IView
    \brief An abstract interface class for implementing application View.
*/
class IView
{
protected:
    ViewID      m_ViewId        = InvalidViewID;
    ViewType    m_ViewType      = ViewType::Other;

    EntityID    m_EntityId      = InvalidEntityID;

public:
    IView(void) = default;
    IView(const IView &) = delete;
    IView & operator=(const IView &) = delete;
    virtual ~IView(void) = default;

    /** 'Attach' an Entity to this view. */
    void attach(const ViewID p_ViewID, const EntityID p_EntityID);

    virtual void update(const ke::Time p_Elapsed) = 0;

    inline ViewID getViewId(void)
    {
        return m_ViewId;
    }

    inline ViewType getType(void)
    {
        return m_ViewType;
    }

    inline EntityID getEntityId(void)
    {
        return m_EntityId;
    }

    /** \return the available scenes in this view. */
    virtual std::vector<SceneSptr> getScenes(void) { return std::vector<SceneSptr>(); };

}; // IView class


/**
    \class AIView
    \brief An abstract interface class for implementing AI application View.
*/
class AIView
    : public IView
{
public:
    AIView(void);
    virtual ~AIView(void) = default;

    virtual void update(const ke::Time p_Elapsed) = 0;

}; // AIView class


} // KE ms