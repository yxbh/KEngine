#pragma once

#include "KEngine/engine_common.hpp"
#include "Types.hpp"
#include "ILogic.hpp"
#include "KEngine/Common/Time.hpp"
#include "KEngine/Multitask/TaskManager.hpp"
#include "KEngine/Entity/Types.hpp"
#include "KEngine/System/ISystem.hpp"

namespace ke
{

/** \class Logic
    \brief  An abstract class for implementing the application's logic layer.
            Any child/further new virtual function implementation must call it's parent method.

*/
class Logic
    : public ke::ILogic
{
public:
    using SystemVector = std::vector<ke::SystemSptr>;

    enum class State
    {
        Menu,
        Loading,
        Spawning,
        Running,
        NumStates,
    };

protected:
    bool                        m_RenderDiagnostic = true;
    ke::Time                    m_LifeTime; // duration of the game session so far.
    ke::TaskManagerUptr         m_upTaskManager = nullptr;
    ke::ViewSPList              m_ViewSPs;
    ke::EntitySPMap             m_EntitySPMap;
    SystemVector                m_NonUpdatableSystems;  // work-in-progress
    SystemVector                m_UpdatableSystems;     // work-in-progress

public:
    Logic(void);

    /** Carry out any necessary initialisation. Child class must call it's parent's initialise() at the start of it's method.
        @return true if initialisation was successful. */
    virtual bool initialise(void) override;
    /** Carry out the shut down procedures. Child class must call it's parent's initialise() at the end of it's method. */
    virtual void shutDown(void) override;

    /** Update the Logic layer. */
    virtual void update(const ke::Time p_ElapsedTime);

    //// Views related operations.
    virtual ke::ViewSPList & getViews(void) override;
    virtual void addView(ViewSptr p_spNewView, const EntityID p_EntityID = ke::InvalidEntityID) override;
    virtual void removeView(ViewSptr p_spView) override;
    ////

    //// Entity related operations.
    virtual ke::EntityWptr getEntity(const ke::EntityID p_EntityID) override;
    virtual void destoryEntity(const EntityID p_EntityID) override;
    ////

    //// Multitask related operations.
    void attachTask(ke::TaskSptr p_spTask);
    ////

    //// Application/Game System related operations.
    bool registerSystem(SystemSptr p_spSystem);
    ////

    virtual void renderDiagnostics(void) {};

};

} // KE ns