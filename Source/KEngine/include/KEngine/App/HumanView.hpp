#pragma once

#include "Types.hpp"
#include "IView.hpp"
#include "KEngine/Common/Time.hpp"
#include "KEngine/Multitask/Types.hpp"
#include "KEngine/Input/Types.hpp"
#include "KEngine/Input/Interfaces.hpp"
#include "KEngine/Multitask/TaskManager.hpp"

namespace ke
{

/** 
    \class HumanView
    \brief A base implementation for a Human view of the engine's view layer.

    Note : Any child class inheriting from this class MUST call the original parent methods.
*/
class HumanView
    : public IView
{
public:
    enum class State
    {
        Invalid,
        Initializing,
        MainMenu,
        Loading,
        Running,
    };

private:
    ////
    State           m_ViewState = State::Invalid;

    //// view life time related.
    ke::Time        m_CurrentTime;          // View's latest lifetime.
    ke::Time        m_LastRenderTime;       // the last time the view was rendered.
    ke::Time        m_MinTimeBetweenDraw;   // minimum time between each draw calls. Used to render FPS. Zero for full speed.

    ////
    ke::TaskManagerUptr    m_upTaskManager; // for audio system, button animations etc? (taken from GCC).

    //// input related
    ke::PointerHandlerUptr     m_PointerDevice;
    ke::KeyboardHandlerUptr    m_KeyboardDevice;

protected:
    // scenes
    std::vector<ke::SceneSptr> m_Scenes;

public:
    HumanView(void);
    virtual ~HumanView(void) = default;

    bool load(/* TODO : define custom data structure for loading. */) {};

    /** Update the view. (Input, Event processing & etc)*/
    virtual void update(const ke::Time p_Elapsed) override;

    virtual std::vector<SceneSptr> getScenes(void) final;

    /** Render all text elements. */
    virtual void renderText(void) {};

    ke::TaskManager & getTaskManager(void);

    //// Event delegates
    ////

protected:
    /** Initialise the audio system for the human view. */
    bool initialiseAudio(void);
    /** Register all event delegates to the global event manager. */
    bool registerEventDelegates(void);

}; // HumanView class


} // KE ns