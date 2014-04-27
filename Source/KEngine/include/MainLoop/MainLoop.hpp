#pragma once
#include "../engine_common.hpp"
#include "SFMLSysEventLoop.hpp"
#include "../Event/IEvent.hpp"
#include "../Event/IEventHandler.hpp"

namespace ke
{


/** class MainLoop
*/
class MainLoop
    : public ke::IEventHandler
{
private:
    SFMLSysEventLoop    m_SFMLSysEventLoop;

    volatile bool m_UpdateAtFullSpeed = false;

public:
    MainLoop(void);
    ~MainLoop(void);

    /** Launches the logic thread and immediately begin the application event polling on main thread.
        When this method returns it means the application has exited.
        @return 0 is returned if application exits successfully. Otherwise it is an error code. */
    int setupAndBeginupdate(void);

    /** Register handler to listen implementation required EventTypes. All child class in a EventHandler class hierachery must call it's parent RegisterEventListner() method. */
    virtual void registerEventListener(void) final;
    /** Deregister handler from listening to implementation required EventTypes. All child class in a EventHandler class hierachery must call it's parent deregisterEventListener() method. */
    virtual void deregisterEventListener(void) final;
    /** Interface defining the method for handling an EventSPtr. */
    virtual void handleEvent(const ke::EventSPtr p_spEvent) final;

    bool isUpdateAtFullSpeed(void) const;

}; // MainLoop class


} // KE ns