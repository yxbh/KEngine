#pragma once
#include "Types.hpp"
#include "../Utility/NonCopyable.hpp"
#include "KEApp.hpp"

namespace ke
{

/** \class App
    Static global object. Representing the application's application(platform dependent) layer.
    This is where the application layer resides.
*/
class App
    : ke::NonCopyable
{
private:
    static AppUPtr s_upApp; /** KEngine application object. */

public:
    App(void) = delete;

    /** Check if the global instance is instantiated and ready to be used (the actual App object itself could stil be uninitialised). */
    static bool isReady(void);
    /** Return a reference to the current app version. Make sure the singleton object is already instanstiated! */
    static KEApp & getSingleton(void);
    /** Setting the global App instance to the given one if it is a valid instance. Any previous instance will also be freed first. */
    static void setSingleton(KEApp * const p_pKEApp);
    /** Initialise the internal global App instance. */
    static bool initialise(void);
    /** Call update on the internal KEApp object. */
    static void update(const ke::Time & p_rTime);
    /** Free & cleanup the internal App object. */
    static void free(void);

}; // App class


} // KE ns