#pragma once

#include "KEngine/App/Types.hpp"
#include "KEngine/App/App.hpp"
#include "KEngine/Utility/NonCopyable.hpp"


namespace ke
{

/**
    \class AppManager
    \brief Static global object. Representing the application's application(platform dependent) layer.
    This is where the application layer resides.
*/
class AppManager
    : ke::NonCopyable
{
private:
    static AppUptr s_upApp; /** KEngine application object. */

public:
    AppManager(void) = delete;

    /** Check if the global instance is instantiated and ready to be used (the actual App object itself could still be uninitialised). */
    static bool isReady(void);
    /** Return a reference to the current app version. Make sure the singleton object is already instanstiated! */
    static App & getSingleton(void);
    /** Setting the global App instance to the given one if it is a valid instance. Any previous instance will also be freed first. */
    static void setSingleton(App * const p_pKEApp);
    /** Initialise the internal global App instance. */
    static bool initialise(void);
    /** Call update on the internal App object. */
    static void update(const ke::Time & p_rTime);
    /** Call render on the internal App object. */
    static void render(const ke::Time & p_rTime);
    /** Free & cleanup the internal App object. */
    static void free(void);

}; // App class


} // KE ns