#pragma once
#include "../engine_common.hpp"
#include <SFML\System\Clock.hpp>
#include "IStopWatch.hpp"

namespace ke
{

/** \class SFML_Time

    A time utility class implementing the ITime interface using the SFML library's time related class.
*/
class SFML2StopWatch
    : public ke::IStopWatch
{
private:
    sf::Clock   m_SFMLClock;
    bool        m_IsTicking         = false;
    ke::Time    m_CummulatedTime    = ke::Time::Zero;

public:
    /** Ctor */
    SFML2StopWatch(void) = default;
    /** Dtor */
    virtual ~SFML2StopWatch(void) = default;

    /** Begin ticking. */
    virtual void Start(void) final;
    /** Stop/pause the ticking. */
    virtual void pause(void) final;
    /** Reset the internal time and start the ticking again. */
    virtual void Restart(void) final;
    /** Reset and stop the timer. */
    virtual void Reset(void) final;
    /** Get elapsed time. */
    virtual ke::Time GetElapsed(void) final;
    /** @return true if the StopWatch is ticking. */
    virtual bool IsTicking(void) const final;

}; // SFML_Time class


inline void SFML2StopWatch::Start(void)
{
    if (!m_IsTicking)
    {
        m_SFMLClock.restart();
        m_IsTicking = true;
    }
    else
        ke::Debug::printWarning("SFML2StopWatch::Start : Timer already started!");
}

inline void SFML2StopWatch::pause(void)
{
    if (m_IsTicking)
    {
        m_IsTicking = false;
        m_CummulatedTime += ke::Time::microseconds(m_SFMLClock.getElapsedTime().asMicroseconds());
    }
    else
        ke::Debug::printWarning("SFML2StopWatch::Pause : Timer already stopped!");
}

inline void SFML2StopWatch::Restart(void)
{
    m_SFMLClock.restart();
    m_CummulatedTime = ke::Time::Zero;
    m_IsTicking = true;
}

inline void SFML2StopWatch::Reset(void)
{
    m_CummulatedTime = ke::Time::Zero;
    m_IsTicking = false;
}

inline ke::Time SFML2StopWatch::GetElapsed(void)
{
    if (m_IsTicking)
    {
        m_CummulatedTime += ke::Time::microseconds(m_SFMLClock.getElapsedTime().asMicroseconds());
        m_SFMLClock.restart();
        return m_CummulatedTime;
    }
    return m_CummulatedTime;
}

inline bool SFML2StopWatch::IsTicking(void) const
{
    return m_IsTicking;
}

} // KE ns
