#pragma once
#include <cstdint> // std::int64_t
#include "../Common/Time.hpp"


namespace ke
{

/** \class IStopWatch

    An interface for implementing a Timer class.

*/
class IStopWatch
{
public:
    virtual ~IStopWatch() = default;

    /** Begin ticking. */
    virtual void Start(void) = 0;
    /** Stop/pause the ticking. */
    virtual void pause(void) = 0;
    /** Reset the internal time and start the ticking again. */
    virtual void Restart(void) = 0;
    /** Reset and stop the timer. */
    virtual void Reset(void) = 0;
    /** @return the elapsed time so far. The stopwatch continues ticking. */
    virtual ke::Time GetElapsed(void) = 0;
    /** @return true if the StopWatch is ticking. */
    virtual bool IsTicking(void) const = 0;

}; // ITimer class

} // KE ns