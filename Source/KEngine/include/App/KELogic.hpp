#pragma once
#include "../engine_common.hpp"
#include "Types.hpp"
#include "ILogic.hpp"
#include "../Common/Time.hpp"
#include "../Multitask/TaskManager.hpp"
#include "../Entity/Types.hpp"
#include "../System/ISystem.hpp"

namespace ke
{

/** \class KELogic

    An abstract class for implementing the application's logic layer.
    Any child/further new virtual function implementation must call it's parent method.

*/
class KELogic
    : public ke::ILogic
{
public:
    using SystemVector = std::vector<ke::SystemSPtr>;

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
    ke::TaskManagerUPtr         m_upTaskManager = nullptr;
    ke::ViewSPList              m_ViewSPs;
    ke::EntitySPMap             m_EntitySPMap;
    SystemVector                m_NonUpdatableSystems;  // work-in-progress
    SystemVector                m_UpdatableSystems;     // work-in-progress

public:
    KELogic(void);

    /** Carry out any necessary initialisation. Child class must call it's parent's initialise() at the start of it's method.
        @return true if initialisation was successful. */
    virtual bool initialise(void) override;
    /** Carry out the shut down procedures. Child class must call it's parent's initialise() at the end of it's method. */
    virtual void shutDown(void) override;

    /** Update the Logic layer. */
    virtual void update(const ke::Time p_ElapsedTime);

    //// Views related operations.
    virtual ke::ViewSPList & getViews(void) override;
    virtual void addView(ViewSPtr p_spNewView, const EntityID p_EntityID = ke::InvalidEntityID) override;
    virtual void removeView(ViewSPtr p_spView) override;
    ////

    //// Entity related operations.
    virtual ke::EntityWPtr getEntity(const ke::EntityID p_EntityID) override;
    virtual void destoryEntity(const EntityID p_EntityID) override;
    ////

    //// Multitask related operations.
    void attachTask(ke::TaskSPtr p_spTask);
    ////

    //// Application/Game System related operations.
    bool registerSystem(SystemSPtr p_spSystem);
    ////

    virtual void renderDiagnostics(void) {};

};

} // KE ns