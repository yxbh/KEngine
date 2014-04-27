#pragma once
#include "Types.hpp"
#include "IView.hpp"
#include "../Common/Time.hpp"
#include "../Multitask/Types.hpp"
#include "../Input/Types.hpp"
#include "../Input/Interfaces.hpp"
#include "../Multitask/TaskManager.hpp"


namespace ke
{

/** \class HumanView
    A base implementation for a Human view of the engine's view layer.

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
    ke::TaskManagerUPtr    m_upTaskManager; // for audio system, button animations etc? (taken from GCC).

    //// input related
    ke::PointerHandlerUPtr     m_PointerDevice;
    ke::KeyboardHandlerUPtr    m_KeyboardDevice;

public:
    HumanView(void);

    bool load(/* TODO : define custom data structure for loading. */) {};

    /** Update the view. (Input, Event processing & etc)*/
    virtual void update(const ke::Time p_Elapsed) override;
    /** Draw the view. */
    virtual void render(const ke::Time p_Elapsed) override;

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